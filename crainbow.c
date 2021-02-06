#include <stdio.h>
#include "generate_tables.h"

void drawline();


int main(){

    char option;
    char hash_value[20];

    drawline();
    printf("\tPASSWORD CRACKING WITH RAINBOW TABLES.\n");
    drawline();

    printf("Do you want to generate new rainbow tables? (Y/N):");
    scanf(" %c",&option);

    while (1)
    {
        
        sleep(1);
        if (option == 'Y' || option == 'y'){
            break;
        }
        else if(option == 'N' || option == 'n'){
            break;
        }
        else{
            printf("\nPlease enter 'y' or 'n' :");
            scanf(" %c",&option);
        }
    }

    printf("\nTest compleded\n");  

    printf("\nEnter the hash value you want to crack:");

    scanf("%s", hash_value);

    printf("You entered the SHA1 hash value:%s\n\n", hash_value);
    drawline();

    
    generate_table();

    return 0;
}

//test

void drawline(){

    printf("-------------------------------------------------------------\n");

}