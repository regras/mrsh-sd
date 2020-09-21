/* 
 * File:   main.c
 * Author: Frank Breitinger
 * Created on 28. April 2013, 19:15
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <string>
#include<sys/stat.h>
#include<fstream>
#include <openssl/md5.h>
#include <limits.h>		
#include <vector>
#include <iostream>
#include <dirent.h>
#include<sys/types.h>
#include<errno.h>
#include "boost/filesystem.hpp"
#include "../header/main.h"
#include "../header/helper.h"
#include "../header/sdhash.h"
#include "../header/hashing.h"
#include "../header/bloomfilter.h"
using std::cout;
using namespace boost::filesystem;
// Global variable for the different modes


MODES *mode;
extern char *optarg;
extern int optind;
unsigned char *cbf;

int USE_COUNTING_BF = 0;

float MIN_ENTROPY = 0.0;
char *filetype;
static int counter=0;
char LINE[500];

FILE *log_file;
FILE *list;
FILE *results_handle;


static void show_help(void) {
	printf(
			"\nmrsh-sdhash  by Frank Breitinger and modified by João Pedro Bizzi Velho\n"
					"Copyright (C) 2013 \n"
					"\n"
					"Usage: mrsh-net [-gh] [-s size] DIR/FILE \n"
					"OPTIONS: -g: Generate the database and print it to std (save to a file like: './mrsh-net DIR > myDB, if it's a dir: ./dirname/* \n"
					"             if unsetbits is used it uset them\n"
					"         -d: Generate the database using a list of files './mrsh-net -d list.txt' \n"
					"         -f: generates the false positive for a list of files; call: ./mrsh-net -f mydir/* \n"
					"         -i: Reads DB-FILE and compares DIR/FILE against it, adapted to use a list with file names instead of a single file name, './mrsh-net -i digestname list.txt . \n"
					"         -e: sets the minimum entropy\n"
					"         -t  excludes a filetype, e.g., './mrsh-net -t .jpg -g DIR' filetype has to start with a '.' \n"
					"         -r: Reads directory recursive, default no \n"
					"         -h: Print this help message \n\n");
}


static void initalizeDefaultModes() {
	mode = (MODES *) malloc(sizeof(MODES));
	mode->helpmessage = false;
	mode->generateBF = false;
	mode->recursive = true;
	mode->fp_mode = false;
	mode->readDB = false;
	mode->all_a_all = false;
	mode->list = false;
}


int main(int argc, char **argv) {
	
	int i;	
	initalizeDefaultModes();
	filetype = malloc(5);
	filetype = ".foo";
	log_file = fopen(mylog,"w");

	char *listName = NULL;

	while ((i = getopt(argc, argv, "i:ghrfed:t:a:")) != -1) {
		switch (i) {
		case 'a':
			listName = optarg;
			mode->all_a_all = true;
			break;
		case 'd':
			mode->list = true;
			break;
		case 'i':
			mode->readDB = true;
			listName = optarg;
			break;
		case 'g':
			mode->generateBF = true;
			break;
		case 'f':
			mode->fp_mode = true;
			break;
		case 'e':
			MIN_ENTROPY = atof(optarg);
			break;
		case 't':
			filetype = optarg;
			break;
		case 'r':
			mode->recursive = true;
			break;
		case 'h':
			mode->helpmessage = true;
			break;
		default:
			mode->helpmessage = true;
			fprintf(stderr, "[*] Unknown option(s) \n");
			break;
		}
	}

	if (mode->helpmessage) {
		show_help();
		exit(0);
	}


	unsigned long cbf_size = (unsigned int) BF_SIZE_IN_BYTES * 8; //for all bits we need 1 byte ... *8
	initialize_settings();		//Bloom filter settings

	BLOOMFILTER *bf = init_empty_BF();
	cbf = (unsigned char*) malloc(cbf_size); // creates a cbf with 8 times the size of a normal bf 
	memset(cbf, 0, cbf_size); 




	//read db from file and compare stuff against it
	if (mode->readDB) {
		
		results_handle = fopen(results_file,"w");
		USE_COUNTING_BF = 0;
		BLOOMFILTER *bf = init_empty_BF();

		// Reads the BF to the memory
		readFileToBF(listName, bf); 
		unsigned char *buffer;
		int size;

		list = fopen(argv[3],"r");
		int total_de_linhas = 0;

		// Find the # of lines
		while(fgets(LINE,500,list))total_de_linhas++;
		fseek(list, 0 , SEEK_SET);

		// Find the filename in each line and search the file in bf
		// Printing each result in a log_file file
		for (int j = 1	; j <= total_de_linhas; j++) {	
			fgets (LINE, 500 ,list);
			char *filename;
			filename = strtok(LINE,"\n");
			//printf("%s\n",filename);
			if (endsWithType(filename)) continue;
			
			FILE *file = getFileHandle(filename);
			size = find_file_size(file);
			evaluation(bf,size,filename);

			
			fclose(file);

		}

		log_file = fopen(mylog,"a");
	 	fprintf(log_file,"All files checked\n");
		destroy_bf(bf);
		fprintf(log_file,"Exiting now\n");
		fclose(log_file);
		fclose(results_handle);
		exit(1);
	}

	//read all arguments, create the bloomfilter, and print it to stdout
	if (mode->generateBF || optind == 1) {

		//Create new BF including setting counting Bloom filter	
		
		BLOOMFILTER *bf = init_empty_BF();
		if (USE_COUNTING_BF == 1) {
			cbf = (unsigned char*) malloc(cbf_size); // creates a cbf with 8 times the size of a normal bf 
			memset(cbf, 0, cbf_size); // sets all cbf's positions to zero
		}
		int size;
		
		//fill bloom filter with all files
		for (int j = optind; j < argc; j++) {
			if(endsWithType(argv[j])){
				continue;
			}
		
			FILE *file = getFileHandle(argv[j]);
			size = find_file_size(file);
			hashFileAndDo(bf, 1, 0, size,argv[j],cbf);	 
			fclose(file);
		
		}

		free(cbf);
		print_bf(bf);
		destroy_bf(bf);
		exit(1);
	}

	// Creates new bf from a list of files
	if (mode-> list){

		// Find the # of lines = # of files to search
		list = fopen(argv[2],"r");
		int total_de_linhas = 0;
		
		while(fgets(LINE,500,list)){
			total_de_linhas++;
			char *filename;
			filename = strtok(LINE,"\n");
			FILE *temporary;
			temporary = getFileHandle(filename);
			fclose(temporary);
		}
		
		fseek(list, 0 , SEEK_SET);

		// Begin insertion
		BLOOMFILTER *bf = init_empty_BF();
		
		if (USE_COUNTING_BF == 1) {
			cbf = (unsigned char*) malloc(cbf_size); // creates a cbf with 8 times the size of a normal bf 
			memset(cbf, 0, cbf_size); // sets all cbf's positions to zero
		}
	
		int size;

		// Inserting every file listed
		for (int j = 1	; j <= total_de_linhas; j++) {
			fgets (LINE, 500 ,list);
			char *filename;
			filename = strtok(LINE,"\n");
	
			if (endsWithType(filename))continue;
			FILE *file = getFileHandle(filename);
			size = find_file_size(file);
			hashFileAndDo(bf, 1, 0, size,LINE,cbf);	 
			fprintf(log_file,"|Current File:%s|Size = %i|Inserted: = %i/%i|\n",filename,size,j,total_de_linhas);
			fclose(file);
		}

		/*for (int i = 0; i < cbf_size; i++) {
			if (cbf[i] >= UNSET_BITS_THRES) // if the cbf position is bigger than 15, the bf's position is unset!
				unset_bit(bf, i);
						}*/
	 	
	 	fprintf(log_file,"All files inserted, now printing bf\n");
		
		free(cbf);
		print_bf(bf);
		destroy_bf(bf);

		fprintf(log_file,"Bf printed and closed, exiting now\n");
	//	printf("total size  = %llu\n",total_size2);
		fclose(log_file);
		exit(1);

	}

	//read all arguments, create the bloomfilter, and print it to stdout
	if (mode->fp_mode || optind == 1) {

		BLOOMFILTER *bf = init_empty_BF();
		if (USE_COUNTING_BF == 1)
			cbf = (unsigned char*) calloc(1, cbf_size);


		int size;
		unsigned char *buffer;
		//fill bloom filter with all files
		for (int j = optind; j < argc; j++) {
			if (endsWithType(argv[j]))
				continue;
			FILE *file = getFileHandle(argv[j]);
			size = find_file_size(*argv[j]);
			hashFileAndDo(bf, 1, 0, size,argv[j],cbf);
			fclose(file);
		}
		//unsetting all bits that set to often (over threshold)
		for (int i = 0; i < cbf_size; i++) {
			if (cbf[i] >= UNSET_BITS_THRES)
				unset_bit(bf, i);
		}
		//do false positive test by using counting bloom filter to delete a file and compare it afterwards
		//printf("fp-mode - MIN_ENTROPY: %.2f, UNSET_BITS_THRES: %i, MIN_RUN: %i, BLOCK_SIZE: %i (filetyp: %s) \n", MIN_ENTROPY, UNSET_BITS_THRES, MIN_RUN, BLOCK_SIZE, filetype);
		for (int j = optind; j < argc; j++) {
			if (!endsWithType(argv[j]) && !endsWithType(".foo"))
				continue;

			FILE *file = getFileHandle(argv[j]);
			size = find_file_size(file);
		
			hashFileAndDo(bf,  3, 0, size,argv[j],cbf);
			evaluation(bf, size,argv[j]);
			hashFileAndDo(bf,1, 0, size,argv[j],cbf);

			 
			fclose(file);
		}

		destroy_bf(bf);
		exit(1);
}


	//read all arguments, create the bloomfilter, and print it to stdout
	if (mode->all_a_all) {
		BLOOMFILTER *bf = init_empty_BF();
		readFileToBF(listName, bf);

		if (USE_COUNTING_BF == 1)
					cbf = (unsigned char*) calloc(1, cbf_size);


		unsigned char *buffer;
		int size;

		BLOOMFILTER *tmp_BF = init_empty_BF();

		//fill bloom filter with all files
		for (int j = optind; j < argc; j++) {
			FILE *file = getFileHandle(argv[j]);
			size = find_file_size(file);
			hashFileAndDo(tmp_BF, 1, 0, size,argv[j],cbf);

			 
			fclose(file);
		}
		destroy_bf(tmp_BF);


		//unsetting all bits that set to often (over threshold)
		for (int i = 0; i < cbf_size; i++) {
			if (cbf[i] >= UNSET_BITS_THRES)
				unset_bit(bf, i);
		}

		//compare files to DB
		for (int j = optind; j < argc; j++) {
			FILE *file = getFileHandle(argv[j]);
			size = find_file_size(file);
			evaluation(bf, size,argv[j]);
			 
			fclose(file);
		}

		destroy_bf(bf);
		exit(1);
}
	

}

char* FindFileName(char *digest){
	unsigned char *token;
	token =	strstr(digest,"cb_target_set/");
	token =	strtok(token,"/"); 
	return strtok(NULL,"\"");
}

/* Função que faz a comparação entre os objetos inseridos */
void evaluation(BLOOMFILTER *bf,int size,char *filename) {
	
	unsigned int found = 0,total = 0,longest_run = 0;
	int *results;

	results = hashFileAndDo(bf, 2, 0, size,filename,0);
	found = *(results+1);
	total = *(results)+ found;
	longest_run = *(results+2);
	char* name;
	name = FindFileName(filename);

	if (longest_run >= 0){
		printf("%s:%d of %d(Longest run %d)\n", name, found, total,longest_run);
		fprintf(results_handle,"%s\t%d\t%d\t%d\n", name, found, total,longest_run);
	}
	else{
		printf("%s not found, min long run not long enough \n",name);
		fprintf(results_handle,"%s\t%d\t%d\t%d\n", name, found, total,longest_run);
	}
}



int endsWithType(char *str) {

	char *dot = strrchr(str, '.');
	return strcmp(dot, filetype) == 0;
}

