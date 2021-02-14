#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "sha1.h"

//change this value to generate
//smaller in size rainbow tables
#define WORD_CHARACTER_LIMIT 4

typedef struct chainEndpoints{
    char startingPoint[10];
    char endPoint[10];
} chainEndpoints;


int generate_table();
char * sha1Transformation(char * plainText);
chainEndpoints createHashChain(char * characterList, int wordLenght);
char * reductionFuntion(char * hashValue,int wordLenght, char * characterList);
int returnDecimalValue(int x);
void hexToDec(char * hexadecimal, long * decimal);




int generate_table(){

    FILE * fPointer;

    int counter = 0;
    int word_lenght = 0;
    int databaseEntries = 2;

    char letters[26];
    char numbers[10];
    char charList[36];
    char chainEgdeValues[2][10];
    char ** tempString;
    chainEndpoints endPoints2;
    



    //We will be searching for a word with non-Capital letters and numbers
    //Initiallizing all the english letters.(using ASCII)
    for (counter = 0; counter < 26; counter++){
        letters[counter] = 97 + counter;
        charList[counter] = letters[counter];
    }

    //Initiallizing decimal number set (0-9).
    for (counter = 0; counter < 10; counter++){
        numbers[counter] = counter + 48;
        charList[26 + counter] = numbers[counter];
    }
    

    
    // char oneCharHashChain[2];
    // char twoCharsHashChain[80];
    // char threeCharsHashChain[3200];
    // char fourCharsHashChain[128000];
    // char fiveCharsHashChain[5120000];
    // char sixCharsHashChain[204800000];
    // char sevenCharsHashChain[8192000000];
    // char eightCharsHashChain[327680000000];


    
    

    //Genarating all available passwords.
    //Starting with 1 word password. 
    //Limiting password lenght to 8 characters.


    //Initializing Files.
    
    for (counter = 1; counter <= WORD_CHARACTER_LIMIT; counter++){
        char accessFile[30] = "tables/table";
        int temp = counter + 1;
        char documentNumber = counter + 48;
        strncat(accessFile, &documentNumber, 1);
        strcat(accessFile, ".txt");

        fPointer = fopen(accessFile, "w");
        if (fPointer == NULL){
            printf("Could not the table file %d.\n",counter + 1);
            exit(EXIT_FAILURE);
        }
        fputs("", fPointer);
        fclose(fPointer);
    }
    
    

    for (word_lenght = 1; word_lenght <= WORD_CHARACTER_LIMIT; word_lenght++){
        printf("\nTable with %d characters is now being generated...",word_lenght);
        printf("\n");
        switch (word_lenght){
            case 1:
                fPointer = fopen("tables/table1.txt", "a");
                if(fPointer == NULL){
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 2:
                fPointer = fopen("tables/table2.txt", "a");
                if(fPointer == NULL){
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 3:
                fPointer = fopen("tables/table3.txt", "a");
                if(fPointer == NULL){
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 4:
                fPointer = fopen("tables/table4.txt", "a");
                if(fPointer == NULL){
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 5:
                fPointer = fopen("tables/table5.txt", "a");
                if(fPointer == NULL){
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 6:
                fPointer = fopen("tables/table6.txt", "a");
                if(fPointer == NULL){
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 7:
                fPointer = fopen("tables/table7.txt", "a");
                if(fPointer == NULL){
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 8:
                fPointer = fopen("tables/table8.txt", "a");
                if(fPointer == NULL){
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }
                break;
        }
        for(counter = 0; counter < databaseEntries; counter ++){
            endPoints2 = createHashChain(charList, word_lenght);
            //printf("Chain starting point is %s.\nEnding point is %s\n",endPoints2.startingPoint,endPoints2.endPoint);
            strcpy(chainEgdeValues[0],endPoints2.startingPoint);
            strcpy(chainEgdeValues[1],endPoints2.endPoint);
            fputs(chainEgdeValues[0], fPointer);
            fputs("\t", fPointer);
            fputs(chainEgdeValues[1], fPointer);
            fputs("\n", fPointer);
        }
        fclose(fPointer);
        printf("\n\nFinished generating table with %d characters.Created table%d file successfully.",word_lenght,word_lenght);
       
        databaseEntries = databaseEntries * 40;
    }
    printf("\n\n");
    return WORD_CHARACTER_LIMIT;
}




chainEndpoints createHashChain(char * characterList,int wordLenght){


    char tempWord[30] = "";
    int counter = 0;
    chainEndpoints endPoints;

    char * chainVar1;
    char * chainVar2;
    char * chainVar3;

 
    //generating random words and adding them to the first point of the hash chain
    //We need a random first word for the hash chain in order to proceed.
    //we pick a random character from the array characterList, that has all characters.
    
    //repeating this procedure times the word lenght.
    for(counter = 0; counter < wordLenght; counter++){
        char temp = characterList[rand()%36];
        strncat(tempWord, &temp, 1);
    }

    strcpy(endPoints.startingPoint,tempWord);


    //Making the hash Chain. We will be needing only the first and the last value of the chain,
    //so there is no need to make more than 3 hashChain Nodes.
    for(counter = 0; counter < 21; counter++){
        char * hash_value;
        hash_value = (char *) malloc(42);
        chainVar1 = tempWord;
        chainVar2 = sha1Transformation(chainVar1);
        strcpy(hash_value, chainVar2); 
        chainVar3 = reductionFuntion(hash_value, wordLenght, characterList);
        strcpy(tempWord, chainVar3);
        free(hash_value);
    }

    strcpy(endPoints.endPoint,tempWord);

    return endPoints;
}




char * sha1Transformation(char * plainText){
    char result[21];
    size_t offset;
    char hashValue[41] = {};
    char *valuePointer = hashValue;

    //calculating sha1 hash value
    SHA1( result, plainText, strlen(plainText) );

    //format the hash value
    for( offset = 0; offset < 20; offset++) {
        sprintf( ( hashValue + (2*offset)), "%02x", result[offset]&0xff);
    }

    

    return valuePointer;
}


char * reductionFuntion(char * hashValue,int wordLenght, char * characterList){
    
    //Reduced function will be described better in the README file.
    
    long positionSelected = 0;
    char sha1Hash[41];
    strcpy(sha1Hash,hashValue);
    char reductionResult[10] = "";
    char *valuePointer = reductionResult;
    int counter = 0;
    int startingPoint = 0;
    char fiveDigitHexWord[6];
    
    

    for(counter = 0; counter < wordLenght; counter++){

        startingPoint = counter * 5;

        fiveDigitHexWord[0] = sha1Hash[startingPoint];
        fiveDigitHexWord[1] = sha1Hash[startingPoint + 1];
        fiveDigitHexWord[2] = sha1Hash[startingPoint + 2];
        fiveDigitHexWord[3] = sha1Hash[startingPoint + 3];
        fiveDigitHexWord[4] = sha1Hash[startingPoint + 4];
        fiveDigitHexWord[5] = '\0';

        hexToDec(fiveDigitHexWord, &positionSelected);

        positionSelected = positionSelected % 36;
        strncat(reductionResult, &characterList[positionSelected], 1);

    }
    
    return valuePointer;
}


void hexToDec(char * hexadecimal, long * decimal){

    char hex[5];
    strcpy(hex,hexadecimal);
    int i = 0; 
    int val = 0; 
    int lenght = 0;


    *decimal = 0;
    //length of total number of hex digit
    lenght = strlen(hex);
    lenght--;
   
    //Iterate over each hex digit 
    for(i=0; hex[i]!='\0'; i++){
        //Find the decimal representation of hex[i]
        if(hex[i]>='0' && hex[i]<='9'){
            val = hex[i] - 48;
        }
        else if(hex[i]>='a' && hex[i]<='f'){
            val = hex[i] - 97 + 10;
        }
        else if(hex[i]>='A' && hex[i]<='F') {
            val = hex[i] - 65 + 10;
        }

        *decimal += val * pow(16, lenght);
        lenght--;
    }
}

