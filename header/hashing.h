/* 
 * File:   hashing.h
 * Author: Frank Breitinger
 *
 * Created on 5. Juni 2012, 13:22
 */

#ifndef HASHING_H
#define	HASHING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <cmath>
#include "config.h"
#include "bloomfilter.h"
#include "sdhash.h"
#include "main.h"

//int         hashFileToBF(BLOOMFILTER *bf, FILE *handle, unsigned char* cbf);
//int 		*hashAndcompare(BLOOMFILTER *bf, FILE *handle);
int			*hashFileAndDo(BLOOMFILTER *bf, int doWhat, unsigned int start, unsigned int stop,char *argv,unsigned char *cbf);
int 		createResultsSummary(BLOOMFILTER *bf, uint256 hash_val, int *results_summary);
void 		hexDump (char *desc, void *addr, int len);
double 		entropy(int freqArray[], int size);

uint32      roll_hashx(unsigned char c, uchar window[], uint32 rhData[]);

#endif	/* HASHING_H */

