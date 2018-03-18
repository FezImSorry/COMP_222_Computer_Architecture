/*
Muhammad Ansari
Comp 222 – Fall 2016
Meeting Time: 0800-0915
Programming Assignment 4: Virtual Memory
*/

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

int memSize, pageSize, frameSize, physAddress, virAddress, alg, offset, page;

struct virtualPageTable{

    int vp;
    int pf;

}*vpTable = NULL;

void output(){

    offset = virAddress % pageSize;     //Calculates offset
    page = virAddress / pageSize;       //Calculates current page

    int index = 0;          //Current Index in Page Table

    while(index < frameSize && vpTable[index].vp != page && vpTable[index].vp != -1)
        index++;

    physAddress = (vpTable[index].pf * pageSize) - (page * pageSize) + virAddress;    //Calculates Physical Address

    if(index == frameSize){         //Case for when all page frames are used

        if(alg == 0)            //If using LRU
            physAddress = (vpTable[0].pf * pageSize) - (page * pageSize) + virAddress;      //Calculates Physical Address

        int base = vpTable[0].pf;       //Holds base value of current frame

        int i;

        for(i = 0; i <= frameSize; i++)       //Shifts Page Frames
            vpTable[i] = vpTable[i + 1];

        vpTable[frameSize - 1].vp = page;       //Updates the Virtual Page
        vpTable[frameSize - 1].pf = base;       //Updates the Page Frame

        printf("\n*** Page Fault!");
        printf("\n*** Virtual address %d maps to physical address %d\n", virAddress, physAddress);

        for(i = 0; i < frameSize; i++){
            if(vpTable[i].vp != -1)
                printf("\n***VP %d --> PF %d", vpTable[i].vp, vpTable[i].pf);
        }

    }
    else if(vpTable[index].vp == page) {        //Case for repeated values

        physAddress = virAddress + (vpTable[index].pf * pageSize) - (page * pageSize);      //Calculates Physical Address

        if(alg == 1){       //If using LRU

            vpTable[index].vp = page;       //Updates the Virtual Page
            vpTable[index].pf = index;          //Updates the Page Frame

        }
        else {              //If using FIFO

            int base = vpTable[0].pf;       //Holds base value of current frame

            int i;

            for(i = 0; i <= frameSize; i++)       //Shifts Page Frames
                vpTable[i]=vpTable[i + 1];

            vpTable[frameSize - 1].vp = page;       //Updates the Virtual Page
            vpTable[frameSize - 1].pf = base;       //Updates the Page Frame

        }

        printf("\n*** Virtual address %d maps to physical address %d\n", virAddress, physAddress);

        int i;

        for(i = 0; i < frameSize; i++){
            if(vpTable[i].vp != -1)
                printf("\n***VP %d --> PF %d", vpTable[i].vp, vpTable[i].pf);
        }

    }
    else if(vpTable[index].vp == -1){       //Case for available Page Frames

        vpTable[index].vp = page;       //Updates the Virtual Page
        vpTable[index].pf = index;      //Updates the Page Frame

        printf("\n*** Page fault!");
        printf("\n*** Virtual address %d maps to physical address %d\n", virAddress, physAddress);

        int i;

        for(i = 0; i < frameSize; i++){
            if(vpTable[i].vp != -1)
                printf("\n***VP %d --> PF %d", vpTable[i].vp, vpTable[i].pf);
        }
    }
}


int main() {

    FILE *file;
    file = fopen("vm_data_2016.txt","r");

    int input;

    while(input != 3) {

        printf("\n\nMuhammad Ansari"
                "\nVirtual Address Mapping:"
                "\n----------------------"
                "\n1) Enter parameters"
                "\n2) Map virtual address"
                "\n3) Quit");

        printf("\nEnter selection:");
        fscanf(file, "%d", &input);
        printf("%d\n", input);

        if(input == 1) {
            printf("\nEnter main memory size(words): ");
            fscanf(file, "%d", &memSize);
            printf("%d\n", memSize);

            printf("Enter page size (words/page): ");
            fscanf(file, "%d", &pageSize);
            printf("%d\n", pageSize);

            int i;

            for (i = 0; i < 1000; i++)  {           //Loops for a long time until user enters 0 or 1 for Replacement Algorithm
                printf("Enter replacement policy (0=LRU, 1=FIFO): ");
                fscanf(file, "%d", &alg);

                if (alg == 0 || alg == 1)
                    break;
            }

            printf("%d\n", alg);

            frameSize = memSize / pageSize;                     //Calculates Frame Size
            vpTable = malloc(frameSize *sizeof(vpTable));       //Allocates Memory for Page Table

            for(i = 0; i < frameSize; i++){     //Initializing the Page Table
                vpTable[i].vp = -1;
                vpTable[i].pf = i;
            }

            printf("\n*** Number of Frames: %d\n", frameSize);

            if (alg == 0)
                printf("*** Replacement Algorithm: LRU\n");
            else if (alg ==1)
                printf("*** Replacement Algorithm: FIFO\n");

        }
        else if(input == 2) {

            printf("Enter virtual memory address to access: ");
            fscanf(file, "%d", &virAddress);
            printf("%d\n", virAddress);
            output();

        }
    }

    printf("***Program Terminated Normally");
    fclose(file);
    free(vpTable);
    exit(EXIT_SUCCESS);

    return 0;
}
