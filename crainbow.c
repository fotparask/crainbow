#include <stdio.h>
#include <unistd.h>
#include "generate_tables.h"

void drawline();


int main(){

    char option;
    char hash_value[20];
    int validation;
    int counter = 0;
    char * plainText;
    char * reducedValue;
    int counter = 0;
    int word_lenght = 0;
    int databaseEntries = 2;
    char newLine = '\n';

    char letters[26];
    char numbers[10];
    char charList[36];

    //same function as generate_tables.h
    for (counter = 0; counter < 26; counter++){
        letters[counter] = 97 + counter;
        charList[counter] = letters[counter];
    }

    //Initiallizing decimal number set (0-9).
    for (counter = 0; counter < 10; counter++){
        numbers[counter] = counter;
        charList[26 + counter] = numbers[counter];
    }


    FILE * fPointer;

    drawline();
    printf("\tPASSWORD CRACKING WITH RAINBOW TABLES.\n");
    drawline();

    printf("Do you want to generate new rainbow tables? (Y/N):");
    scanf(" %c",&option);

    while (1)
    {
        
        sleep(1);
        if (option == 'Y' || option == 'y'){
            printf("\n\nPlease wait.Rainbow tables are being generated.\nThis might take several minutes...\n\n");
            validation = generate_table();
            if (validation == -1) return 0;
            else{
                drawline();
                printf("\n\nYou successfully generated %d rainbow tables.\n\n",validation);
                drawline();
            }
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

    printf("You entered the SHA1 hash value: %s\n\n", hash_value);
    sleep(1);
    drawline();
    sleep(3);
    printf("\nTrying to find a match.This might take several minutes...\n\n"); 

    for(counter = 0; counter < validation; counter++){
        char * accessFile = "tables/table1.txt";
        int temp = counter + 1;
        accessFile[12] = temp + 48;
        fPointer = fopen(accessFile, "r");
        if (fPointer == NULL){
        printf("Could not the table file %d.\n",counter + 1);
        return 1;
        }
        while (fgets(plainText, 10, fPointer) != '\n'){
            printf("%s", plainText);
            reducedValue = reductionFuntion(plainText, counter + 1, charList);
            if (reducedValue == plainText) break;
        }
        
    }

    return 0;
}

//test

void drawline(){

    printf("-------------------------------------------------------------\n");

}

