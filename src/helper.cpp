
#include <stdio.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <openssl/md5.h>
#include <limits.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include "../header/config.h"
#include "../header/helper.h";




bool is_file(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

bool is_dir(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

void fatal_error(char *message){
	printf("%s \n", message);
	exit(-1);
}   
FILE *getFileHandle(char *filename){
    FILE *handle = NULL;
    
    if((handle = fopen(filename, "r"))==NULL) {
        printf("Sorry,%s\n",strerror(errno));
        exit(-1);
    }    
    return handle;
}
unsigned int find_file_size(FILE *fh){
  unsigned int size;
  if(fh != NULL)
   {
    if( fseek(fh, SEEK_SET, SEEK_END) )
    {
      return -1;
    }
    size = ftell(fh);
    //printf("FILE SIZE: %d \n", size);
    return size;
   }
   return -1;
}


