/*
Muhammad Ansari
Comp 222 – Fall 2016
Meeting Time: 0800-0915
Programming Assignment 2: Cache Simulation
*/

#include <stdio.h>
#include <stdlib.h>

/* declare global var's */
int memorySize, cacheSize, blockSize;

/* define structure of dynamic cache and initialize var */
struct node {
    int tag;		//determined by location of main memory block
    int* lineBlock;	//points to a dynamically allocated line-block
}*cache = NULL;

/* define dynamic array for main memory */
int* memory = NULL;

//typedef struct node n;
//void opTwo(int);

/**********************************************************************/
void opOne()
{
/* declare local var's */
    int i;

/* Prompt for main memory size, cache size, block size */
	printf("\nEnter main memory size (words) : ");
	scanf( "%d", &memorySize );

	printf("Enter cache size (words) : ");
	scanf( "%d", &cacheSize );

	printf("Enter block size (words/block) : ");
	scanf( "%d", &blockSize );


    if (memorySize %2 != 0) {
		printf("\n*** Error - main memory size not a power of 2! ");
		return;
	}
	else if (cacheSize %2 != 0) {
		printf("\n*** Error - cache size not a power of 2! ");
		return;
	}
	else if (blockSize %2 != 0) {
		printf("\n*** Error - block size not a power of 2! ");
		return;
	}
	else if (blockSize > cacheSize) {
		printf("\n*** Error - block size large than cache size! ");
		return;
	}
    else if (cacheSize % blockSize != 0) {
        printf("\n*** Error - Cache size is not a multiple of block size\n");
        return;
    }
	else
		printf("\n*** Data accepted\n");

/* allocate and initialize main memory--value at index i = size of main memory-i*/
    memory = (int*)malloc(memorySize * sizeof(int));

    for (i = 0; i < memorySize; i++)
        memory[i] = memorySize - i;

/* allocate memory for cache based on number of lines in cache*/
	cache = (struct node*)malloc((cacheSize / blockSize) * sizeof(struct node));

	for(i = 0; i < (cacheSize / blockSize); i++) {
		cache[i].lineBlock = NULL;
		cache[i].tag = -1;
	}

  return;
}


/**********************************************************************/
void opTwo(int op)
{
/* declare local var's */
    int  address, content, tag, word, base, line;
    int i;

/* Prompt for read/write signal */

/* Prompt for main memory address to read/write */
    if (op == 2) {
		printf("\nEnter main memory address to read from: ");
		scanf( "%d", &address);
    }
    else if (op == 3) {
        printf("\nEnter main memory address to write to: ");
		scanf( "%d", &address);
		printf("Enter the value to write: ");
		scanf( "%d", &content);
    }

/* Translate main mem addr to cache addr fields*/
    tag = address / cacheSize;
	line = (address % cacheSize) / blockSize;
	word = address % blockSize;
	base = (address / blockSize) * blockSize;

/* MISS--BLOCK NOT ALLOCATED */
/* Allocate cache block based on block size */
    if(cache[line].lineBlock == NULL) {
            cache[line].lineBlock = (int*)malloc(blockSize * sizeof(int));
    }

/* MISS--NON-MATCHING TAG */
/* Print message of Read/Write miss */
/* Overwrite tag */
/* Transfer equivalent block of main memory to cache--one word at a time */
   if(cache[line].tag != tag ) {
		cache[line].tag = tag;

        for(i = 0; i < blockSize; i++)
            cache[line].lineBlock[i] = memory[base + i];

        if(op == 2)
			printf("\n*** Read miss...First Load Block from Memory!" );
		else if (op == 3)
			printf("\n*** Write miss...First Load Block from Memory!" );
	}
    else
        printf("\n*** Block in Cache" );

/* HIT--reference cache word, transfer data to/from cache and print message*/
    if (op == 2) {
       content = cache[line].lineBlock[word];
    }
    else if (op == 3) {
       cache[line].lineBlock[word] = content;
       memory[address] = content;
    }


/* Print message of word, block, tag, data value */
    printf("\n*** Word %i of cache line %i with tag %i contains value %i\n\n", word, line, tag, content);

    return;
}


/**********************************************************************/
int main()
{
/* declare local var's */
    int op = 0;
    int i;

/* until program exits, print menu, select choice via switch statement and call appropriate function*/
    while(op != 4) {
    	printf("\nMuhammad Ansari\n\nMain memory to Cache memory mapping:\n--------------------------------------\n1) Enter Configuration Parameters \n2) Read from cache \n3) Write to cache \n4) Exit \n\n");
        printf("Enter selection: ");
        scanf("%i", &op);

        if(op == 1)
            opOne();
        else if (op == 2 || op == 3)
            opTwo(op);
        else if (op == 4) {
            free(memory);

       		for(i = 0; i < (cacheSize / blockSize); i++)
				free(cache[i].lineBlock);

            printf("*** Program Terminated Normally");
            exit(EXIT_SUCCESS);
        }
    }

    return 1;
}
