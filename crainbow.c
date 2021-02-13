#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "generate_tables.h"

void drawline();
char * initiateSearchInHashChain(char * fistChainWord, char * value_to_crack,int wordLenght,char * characterList);

int main(){

    srand(time(NULL));

    char option;
    char hash_value[41];
    int validation;
    int timesToReduce;
    int counter = 0;
    char inputFromFile[30];
    char reducedValue[10];
    int word_lenght = 0;
    int databaseEntries = 2;
    int passwordFound = 0;
    char password_found[10];
    char newLine = '\n';
    char * tempChar;
    char * hashPointer;
    char hash_value_to_crack[41];
    char firstHashChainWord[10] = {};
    char wordToCompare[10] = {};

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
        numbers[counter] = counter + 48;
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

    scanf("%s", hash_value_to_crack);

    printf("You entered the SHA1 hash value: %s\n\n", hash_value_to_crack);
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

        printf("Table we are searching the password is: %s.\n",accessFile);
        tempChar = reductionFuntion(hash_value_to_crack, counter + 1, charList);
        strcpy(reducedValue,tempChar);
        for(timesToReduce = 0; timesToReduce < 20; timesToReduce++){
            while ((fgets(inputFromFile, 30, fPointer)) != NULL){
                //formating the second word, the end of the chain, to an allocated string.
                for(int y = 0; y < counter + 1; y++){
                    wordToCompare[y] = inputFromFile[y + counter + 2];
                }
                
                wordToCompare[counter + 1] = '\0';
                if (strcmp(reducedValue,wordToCompare) == 0 ){
                    //formating the first word, the start of the chain, to an allocated string.
                    for(int z = 0; z <= counter; z++){
                        firstHashChainWord[z] = inputFromFile[z];
                    }
                    firstHashChainWord[counter + 1] = '\0';
                    tempChar = initiateSearchInHashChain(firstHashChainWord, hash_value_to_crack, counter + 1, charList);
                    if(tempChar != NULL){
                        strcpy(password_found,tempChar);
                        passwordFound = 1;
                        break;
                    }
                    
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
    if(passwordFound){
        drawline();
        printf("\n\nCongratulation you have found the password!\n\n");
        drawline();
        printf("\n\nThe hash:%s\nComes form the plain text:%s\n\n",hash_value_to_crack,password_found);
        drawline();
    }
    else{
        drawline();
        printf("Sadly you have not found the password...\n");
        printf("This probably means the the rainbow tables do not contain a password match.\n");
        drawline();
    }
    
    return 0;
}


void drawline(){

    printf("-------------------------------------------------------------\n");

}


char * initiateSearchInHashChain(char * fistChainWord, char * value_to_crack,int wordLenght,char * characterList){

    char * chainVar1;
    char * chainVar2;
    char * chainVar3;
    char tempWord[10];

    int counter = 0;

    strcpy(tempWord,fistChainWord);
    for(counter = 0; counter < 21; counter++){
        char * hash_value;
        hash_value = (char *) malloc(42);
        chainVar1 = tempWord;
        chainVar2 = sha1Transformation(chainVar1);
        strcpy(hash_value, chainVar2); 
        if(strcmp(value_to_crack,hash_value) == 0){
            return chainVar1;
        }
        chainVar3 = reductionFuntion(hash_value, wordLenght, characterList);
        strcpy(tempWord, chainVar3);
        free(hash_value);
    }

    return NULL;
}
