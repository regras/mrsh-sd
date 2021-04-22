#include "../header/hashing.h"
#include "../header/config.h"
#include "../header/main.h"
#include "../header/sdhash.h"
#include <stdio.h>


//Depending on the third parameter it fills the Bloom filter (1) or it compares File against Bloom filter
//doWhat: 1 = hashAndAdd  ; 2 = hashAndCompare ; 3 = remove
int  *hashFileAndDo(BLOOMFILTER *bf,	int doWhat,	unsigned int start,	unsigned int stop,char *argv) {
		return SDHASH_EXT(bf,doWhat,argv,stop,start);
}

int createResultsSummary(BLOOMFILTER *bf, uint256 hash_val, int *results_summary) {
	if (is_in_bloom(bf, hash_val) == 1){
		results_summary[1]++;					//counter for found chunks
		results_summary[3]++;
		if (results_summary[3] > results_summary[2]) //check if there is a long run
			results_summary[2] = results_summary[3];
		return 1;
	}
	else
		results_summary[3] = 0;
		// counter for not found chunks
		results_summary[0]++;
		// o total de pedaços do arquivo será results_summary[0] + results_summary[1] - total de encontrados  + total de não encontrados
		// o longest run será o results_summary[2]
	return 0;
}

void hexDump(char *desc, void *addr, int len) {
	int i;
	unsigned char buff[17];
	unsigned char *pc = addr;

	// Output description if given.
	if (desc != NULL)
		printf("%s:\n", desc);

	// Process every byte in the data.
	for (i = 0; i < len; i++) {
		// Multiple of 16 means new line (with line offset).

		if ((i % 16) == 0) {
			// Just don't print ASCII for the zeroth line.
			if (i != 0)
				printf("  %s\n", buff);

			// Output the offset.
			printf("  %04x ", i);
		}

		// Now the hex code for the specific character.
		printf(" %02x", pc[i]);

		// And store a printable ASCII character for later.
		if ((pc[i] < 0x20) || (pc[i] > 0x7e))
			buff[i % 16] = '.';
		else
			buff[i % 16] = pc[i];
		buff[(i % 16) + 1] = '\0';
	}

	// Pad out last line if not exactly 16 characters.
	while ((i % 16) != 0) {
		printf("   ");
		i++;
	}

	// And print the final ASCII bit.
	printf("  %s\n", buff);
}
