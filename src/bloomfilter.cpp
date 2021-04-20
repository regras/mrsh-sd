/**
 * AUTHOR: Frank Breitinger
 * DATE: April 2013
 * Email: Frank.Breitinger@cased.de
 */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "../header/config.h"
#include "../header/hashing.h"
#include "../header/bloomfilter.h"
#include <typeinfo>


static int SHIFTOPS;       	//FILTER_AS_POW_2 + 3 -> 14
static unsigned long MASK;			//SHIFTOPS in ones    -> 0x1FFFF

void initialize_settings(){
	SHIFTOPS = (int)log2(BF_SIZE_IN_BYTES) + 3; // 27
	MASK = 0xFFFFFFFFFFFFFFFF >> (64-SHIFTOPS); // 37
	//Máscara são 27 bits
}


//Returns an empty Bloom filter
BLOOMFILTER *init_empty_BF(){
	BLOOMFILTER *bf;
	if (!(bf=(BLOOMFILTER *)malloc(sizeof(BLOOMFILTER))))
	 {
	     fprintf(stderr,"[*] Error in initializing bloom_read \n");
	     exit(-1);
	 }
	 	return bf;
}
//Destroy a Bloom filter
void destroy_bf(BLOOMFILTER *bf) {
   free(bf);
   bf=NULL;
}
/*
 * adds a hash value (eg. FNV) to the Bloom filter
 */
void add_hash_to_bloomfilter(BLOOMFILTER *bf,
							uint256 hash_val){
	uint64 masked_bits, byte_pos;
	short bit_pos;
	unsigned char *test = (unsigned char*)hash_val; // the variable test will contain the hash

	//for(int r = 0;r<8;r++) printf("Hash[%d] %X\n",r,hash_val[r]);

	uint64 *p = (uint64*)hash_val; // the pointer p will point to the hash
	//as partes 5, 6 e 7 do hash são lixo

//printf("\n");
	// Concatena hash_val[r] e hash_val[r+1]
	uint64 tmpHash = (((uint64)hash_val[1]<<32) ^ hash_val[0]);

	// the temporary hash is a power of 32 bit shift (to the left) to the first hash
	for(int j = 0; j < SUBHASHES; j++) {

        //printf("TEMP HASH = %X\n",tmpHash);
    	//printf("teste  = %s\n",test);

		masked_bits = tmpHash & MASK;
		//printf("masked bits = %X\n",masked_bits);

		byte_pos = masked_bits >> 3; // right bit shift of teh masked bit obtained - big number

		bit_pos = masked_bits & 0x7; // and of the masked bits and the number 7, that is,

		bf -> array[byte_pos] |= (1<<(bit_pos));

      //  printf("POS = %d\n",SHIFTOPS*(j+1)/8);

        p = (uint64*)&test[SHIFTOPS*(j+1) / 8];

	//	printf("p = %llX\n",*p);
	//	printf(" shift = %d\n",(SHIFTOPS*(j+1)) % 8 );
        tmpHash = *p >> ((SHIFTOPS*(j+1)) % 8);

		// the value of the tmpHash will be a right bit shift of the value obtained by the pointer!
	}
       // 		printf("######\n");




}






short is_in_bloom(BLOOMFILTER *bf, uint256 hash_val){
	unsigned int masked_bits, byte_pos;
	short bit_pos;
	unsigned char *test = (unsigned char*)hash_val;

	uint64 *p = (uint64*)hash_val;
	uint64 tmpHash = (((uint64)hash_val[1]<<32) ^ hash_val[0]);

	for(int j=0;j<SUBHASHES;j++) {
		//get least significant bytes and use one relevant by AND MASK
		masked_bits = tmpHash & MASK;
		//get byte and bit position
        byte_pos = masked_bits >> 3;
        bit_pos = masked_bits & 0x7;

        //if position in BF is zero then element isn't in BF
        if(((bf->array[byte_pos]>>bit_pos) & 0x1) != 1){
        	return 0;
        }
        //shift and continue
        p = (uint64*)&test[SHIFTOPS*(j+1) / 8];
        tmpHash = (*p) >> ((SHIFTOPS*(j+1))% 8);
	}

	return 1;
}




/*
 * Convert a hex string to a binary sequence (used for reading in hash lists)
 */
void convert_hex_binary(const unsigned char *hex_string, BLOOMFILTER *bf)
{
    unsigned int i=0;

	//WARNING: no sanitization or error-checking whatsoever
	for(i = 0; i < BF_SIZE_IN_BYTES; i++) {
	  	  sscanf(hex_string, "%2hhx", &bf->array[i]);
	  	  hex_string += 2 * sizeof(char);
	}
}

void print_bf(BLOOMFILTER *bf){
    //BLOOMFILTER *bf = fp->bf_list;

    /* FORMAT: filename:filesize:number of filters:blocks in last filter*/
    //printf("%s:%d:%d:%d", fp->file_name, fp->filesize, fp->amount_of_BF, fp->bf_list_last_element->amount_of_blocks);
    //printf(":");

   // printf("%i:", bf->amount_of_blocks);



    //while(bf != NULL) {
    	//Print each Bloom filter as a 2-digit-hex value
    	for(int j=0;j<BF_SIZE_IN_BYTES;j++)printf("%c", bf->array[j]);  //move to next Bloom filter
      // bf = bf->next;
   // }
  //  printf("\n\n");

}


void readFileToBF(const char *filename, BLOOMFILTER *bf) {
	int i;
    FILE *fp = fopen(filename, "rb");
    if (fp != 0)
    {
        for (i = 0; fread(&bf[i], sizeof(bf[i]), 1, fp) == 1; i++)
            ;
        fclose(fp);
    }
}
