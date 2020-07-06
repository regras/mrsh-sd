/* 
 * File:   util.h
 * Author: mustafakarabat
 *
 * Created on 5. Juni 2012, 14:38
 */
#ifndef HELPER_H
#define	HELPER_H
#include <stdio.h>
#include <stdint.h>
#include <cstdlib>
#include "../header/config.h"


FILE    		*getFileHandle(char *filename);
void			*explore(char *dirname);
unsigned int	find_file_size(FILE *fh);
bool is_file(const char* path);
bool is_dir(const char* path);
#endif	/* HELPER_H */

