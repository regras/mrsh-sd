  /*
 * File:   config.h
 * Author: Frank Breitinger
 *
 * Created on 1. Mai 2012, 12:15
 */

#ifndef CONFIG_H
#define	CONFIG_H

//#define PRINT_HASHES

#define BF_SIZE_IN_BYTES 		33554432
#define SUBHASHES           5
#define MIN_RUN					    6

typedef unsigned long long  uint64;
typedef unsigned char       uchar;
typedef unsigned int        uint32;
typedef unsigned short      ushort16;
typedef unsigned int		    uint256[5];
typedef unsigned long long  uint256r[5];

typedef short bool;
#define true 1
#define false 0

typedef struct{
    bool generateBF;
    bool readDB;
    bool helpmessage;
		bool compare;
    bool all_a_all;
    bool list;
} MODES;

extern MODES *mode; //= {.compare = false}

#endif	/* CONFIG_H */
