#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* declare global vars */

int max, length, parity;

/* define hamming string as a dynamic array of characters */
char *binary = NULL;

/***************************************************************/
void setParamters(FILE *file)
{
/* prompt for maximum hamming code length and for even/odd parity */

            printf("\nEnter the maximum length: ");
            fscanf(file, "%d", &max );
            printf("%d\n", max);
            printf("\nEnter the parity (0 = even, 1 = odd): ");
            fscanf(file,"%d", &parity );
            printf("%d\n", parity);

/* allocate memory for hamming string based on maximum length and size of a character element*/
            binary = (char*) malloc(max * sizeof(char));
  return;
}

/***************************************************************/
void checkHammingCode(FILE *file)
{
/* declare local vars */
 int bit = 0;
    int paritybit = 0;

    int i, j, k;

/* prompt for hamming code as a "string"*/
            printf("\nEnter the Hamming Code: ");
            fscanf(file, "%s", binary);
            printf("%s\n", binary);
             length = strlen(binary);
            if(length>max) {
                printf("\n***Invalid Entry - Exceeds Maximum Code Length of %d\n", max);
            return;
            }

/* OUTER LOOP: for each parity bit in the Hamming code*/
 /* BEGIN OF OUTER LOOP */
	for(i = 1; i < length; i = i * 2){
/* initialize appropriate local variables */
        paritybit = parity;
        /* MIDDLE LOOP: for each starting bit of a sequence */
        for(j = i; j <= length; j = j + (i * 2)){
           /* INNER LOOP: for each bit to be checked, check value and update parity information for current parity bit*/

            for(k = j; k < j + i && k <= length; k += 1){
                paritybit = paritybit ^ (binary[length - k] - '0');
            }
        }
        /* update parity checking by including result for parity bit checked in total */
        bit = bit + (paritybit * i);
    } /* END OF OUTER LOOP*/

/* report error in hamming code based on result from parity bits or report no error if none */
if (bit == 0)
        printf("***There is no bit error\n");

    else{
        printf("***There is an error in bit: %d\n", bit);
        /* correct hamming code by flipping error bit (if necessary)*/
        if (binary[length - bit] == '0')

            binary[length - bit] = '1';
        else
            binary[length - bit] = '0';
        printf("***The corrected Hamming code is: %s\n", binary);

    }



  return;
}

/***************************************************************/
int main()
{
/* print out menu, prompt for choice, and call appropriate procedure until user quits */

    FILE *file;
    file = fopen("hc_data_2016.txt", "r");
    int op;
    while(op != 3) {
        printf("\nMuhammad Ansari\n");
        printf("\nError detection/correlation:");
        printf("\n---------------------- ");
        printf("\n1) Enter parameters");
        printf("\n2) Check Hamming Code");
        printf("\n3) Quit\n");
        printf("\nEnter selection:");

        fscanf(file, "%d", &op);
        printf("%d\n", op);
        if(op == 1) {
            setParamters(file);
        }
        else if (op == 2){
            checkHammingCode(file);
        }
        else if (op == 3) {
            if (binary != NULL)
                free (binary);
            fclose(file);
            printf("***Program Terminated Normally");
            exit(EXIT_SUCCESS);
        }
        else printf("\n***Error");
    }

return 1;
}
