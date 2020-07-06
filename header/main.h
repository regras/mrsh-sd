/* 
 * File:   config.h
 * Author: Frank Breitinger
 *
 * Created on 1. Mai 2013, 12:15
 */

#ifndef MAIN_H
#define	MAIN_H

#include "../header/config.h"
#include "../header/hashing.h"
#include "../header/bloomfilter.h"
#include "../header/helper.h"
#include "../header/sdhash.h"
#include "../boost/filesystem.hpp"

FILE    *getFileHandle(char *filename);
void 		addPathToBloomfilter(BLOOMFILTER *bf, char *filename, unsigned char* cbf);
void 		evaluation(BLOOMFILTER *bf, int size,char *argv);
int	 		endsWithType(char *str);
//extern *results_summary;

#endif	/* MAIN_H */

