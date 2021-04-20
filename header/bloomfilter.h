/*
 * File:   bloom.h
 * Author: mustafakarabat
 *
 * Created on 17. April 2012, 23:34
 */


#ifndef BLOOMFILTER_H
#define	BLOOMFILTER_H
#include"config.h"
/*
 * We define a struct BLOOM, with all the properties a Bloom-Filter needs.
 */

typedef struct {
    // For a filter_size of FILTERSIZE Bytes (in the net-version probably 512MB oder 1024MB.
    unsigned char array[BF_SIZE_IN_BYTES];

}BLOOMFILTER;
extern BLOOMFILTER *bf;

void 			initialize_settings();

BLOOMFILTER     *init_empty_BF();
void            destroy_bf(BLOOMFILTER *bf);

void            bloom_set_bit(unsigned char *bit_array, unsigned short value);
void 			unset_bit(BLOOMFILTER *bf, unsigned int bit);
short 			is_in_bloom(BLOOMFILTER *bf, uint256 hash_val);

void 			add_hash_to_bloomfilter(BLOOMFILTER *bf, uint256 hash_val);
void            convert_hex_binary(const unsigned char *hex_string, BLOOMFILTER *bf);

void 			print_bf(BLOOMFILTER *bf);
void 			readFileToBF(const char *filename, BLOOMFILTER *bf);
short 			remove_hash_from_filter(BLOOMFILTER *bf, uint256 hash_val);

#endif	/* BLOOM_H */
