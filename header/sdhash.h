
#ifndef SDHASH_H
#define	SDHASH_H

#include"bloomfilter.h"
#include"main.h"
#include"hashing.h"
#include"helper.h"

int *SDHASH_EXT(BLOOMFILTER *bf,
 int doWhat,
 char *argv,
 unsigned int size,
 unsigned int start,
 unsigned char *cbf);
//int *results_summary = (unsigned int *) calloc(0, 4*sizeof(int));

#endif
