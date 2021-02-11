#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "generate_tables.h"

void drawline();


int main(){

    srand(time(NULL));

    char option;
    char hash_value[20];
    int validation;
    int timesToReduce;
    int counter = 0;
    char inputFromFile[30];
    char reducedValue[10];
    int word_lenght = 0;
    int databaseEntries = 2;
    int passwordFound = 0;
    char newLine = '\n';
    char * tempChar;
    char * hashPointer;

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

    printf("\nEnter the hash value you want to crack:");

    scanf("%s", hash_value);

    printf("You entered the SHA1 hash value: %s\n\n", hash_value);
    drawline();
    
    printf("\nTrying to find a match.This might take several minutes...\n\n");

    for(counter = 0; counter < WORD_CHARACTER_LIMIT; counter++){

        char accessFile[30] = "tables/table";
        int temp = counter + 1;
        char documentNumber = temp + 48;
        strncat(accessFile, &documentNumber, 1);
        strcat(accessFile, ".txt");
        
        fPointer = fopen(accessFile, "r");
        if (fPointer == NULL){
            printf("Could not open the table file %d.\n",counter + 1);
            exit(EXIT_FAILURE);
        }

        printf("Text to open is: %s, random char is %c.\n",accessFile, charList[0]);
        tempChar = reductionFuntion(hash_value, counter + 1, charList);
        strcpy(reducedValue,tempChar);
        for(timesToReduce = 0; timesToReduce < 10; timesToReduce++){
            while ((fgets(inputFromFile, 30, fPointer)) != NULL){
                inputFromFile[counter+1] = '\0';

                if (strcmp(reducedValue,inputFromFile) == 0 ){
                    passwordFound = 1;
                    break;
                } 
            }
            if(passwordFound) break;
            
            hashPointer = sha1Transformation(reducedValue);
            strcpy(hash_value,hashPointer);
            tempChar = reductionFuntion(hash_value, counter + 1, charList);
            strcpy(reducedValue,tempChar);
            rewind(fPointer);
        }
    }

    printf("\n\n");
    drawline();
    if(passwordFound){
        printf("Congratulation you have found the password!\n\n");
    }
    else{
        printf("Sadly you have not found the password...\n\n");
    }
    
    drawline();

    return 0;
}

//test

void drawline(){

    printf("-------------------------------------------------------------\n");

}

