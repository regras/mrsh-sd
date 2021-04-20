  /*
 * File:   config.h
 * Author: Frank Breitinger
 *
 * Created on 1. Mai 2012, 12:15
 */

#ifndef CONFIG_H
#define	CONFIG_H

#define ROLLING_WINDOW          7
#define BLOCK_SIZE              64
#define SKIPPED_BYTES           BLOCK_SIZE/3
//#define MIN_ENTROPY			0 //2.5

#define MIN_RUN					6	//greater or equal is a TP

#define UNSET_BITS_THRES		256//256 is ignore

// min run vs tamanho do filtro
/*
1	 	268435456
2		67108864
3-4		33554432
5-11	16777216
12-54	8388608
55-200	4194304
*/



#define BF_SIZE_IN_BYTES 		33554432
#define SUBHASHES               5

#define SKIP_FIRST				1	//Skip first block which often contains header info
#define SKIP_LAST				1   //Skip last block which often contains footer info
#define PACKET_SIZE				1460



typedef unsigned long long  uint64;
typedef unsigned char       uchar;
typedef unsigned int        uint32;
typedef unsigned short      ushort16;
typedef unsigned int		uint256[8];
typedef unsigned long long  uint256r[5];

typedef short bool;
#define true 1
#define false 0
#define results_file "resultado.txt"
#define mylog "LogFile.txt"

typedef struct{
    bool generateBF;
    bool readDB;
    bool helpmessage;
		bool compare;
    bool all_a_all;
    bool list;
} MODES;




extern MODES *mode; //= {.compare = false}
extern int USE_COUNTING_BF;
extern float MIN_ENTROPY;




#endif	/* CONFIG_H */
