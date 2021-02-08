#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sha1.h"

//change this value to generate
//smaller in size rainbow tables
#define WORD_CHARACTER_LIMIT 8


int generate_table();
char * sha1Transformation(char * plainText);
char * createHashChain(char * characterList, int wordLenght);
char * reductionFuntion(char * hashValue,int wordLenght, char * characterList);
int returnDecimalValue(int x);




int generate_table(){

    FILE * fPointer;

    int counter = 0;
    int word_lenght = 0;
    int databaseEntries = 2;
    char newLine = '\n';

    char letters[26];
    char numbers[10];
    char charList[36];
    char * chainEgdeValue;

    printf("it is done\n");



    //We will be searching for a word with non-Capital letters and numbers
    //Initiallizing all the english letters.(using ASCII)
    for (counter = 0; counter < 26; counter++){
        letters[counter] = 97 + counter;
        charList[counter] = letters[counter];
    }

    //Initiallizing decimal number set (0-9).
    for (counter = 0; counter < 10; counter++){
        numbers[counter] = counter;
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

    for (word_lenght = 1; word_lenght < WORD_CHARACTER_LIMIT + 1; word_lenght++){
        for(counter = 0; counter < databaseEntries; counter ++){
            chainEgdeValue = createHashChain(charList, word_lenght);
            databaseEntries = databaseEntries * 40;
            switch (word_lenght){
            case 1:
                fPointer = fopen("tables/table1.txt", "w");
                if(fPointer == NULL){
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }
                strncat(databaseEntries, &newLine, 1);
                fputs(databaseEntries, fPointer);
                fclose(fPointer);
                break;
            case 2:
                fPointer = fopen("tables/table2.txt", "w");
                if(fPointer == NULL){
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }
                strncat(databaseEntries, &newLine, 1);
                fputs(databaseEntries, fPointer);
                fclose(fPointer);
                break;
            case 3:
                fPointer = fopen("tables/table3.txt", "w");
                if(fPointer == NULL){
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }
                strncat(databaseEntries, &newLine, 1);
                fputs(databaseEntries, fPointer);
                fclose(fPointer);
                break;
            case 4:
                fPointer = fopen("tables/table4.txt", "w");
                if(fPointer == NULL){
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }
                strncat(databaseEntries, &newLine, 1);
                fputs(databaseEntries, fPointer);
                fclose(fPointer);
                break;
            case 5:
                fPointer = fopen("tables/table5.txt", "w");
                if(fPointer == NULL){
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }
                strncat(databaseEntries, &newLine, 1);
                fputs(databaseEntries, fPointer);
                fclose(fPointer);
                break;
            case 6:
                fPointer = fopen("tables/table6.txt", "w");
                if(fPointer == NULL){
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }
                strncat(databaseEntries, &newLine, 1);
                fputs(databaseEntries, fPointer);
                fclose(fPointer);
                break;
            case 7:
                fPointer = fopen("tables/table7.txt", "w");
                if(fPointer == NULL){
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }
                strncat(databaseEntries, &newLine, 1);
                fputs(databaseEntries, fPointer);
                fclose(fPointer);
                break;
            case 8:
                fPointer = fopen("tables/table8.txt", "w");
                if(fPointer == NULL){
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }
                strncat(databaseEntries, &newLine, 1);
                fputs(databaseEntries, fPointer);
                fclose(fPointer);
                break;
            }
        }

        
    }
    
    return WORD_CHARACTER_LIMIT;
}




char * createHashChain(char * characterList,int wordLenght){

    char * tempWord;
    char * chainEndpoint;
    int counter = 0;

    typedef struct node{
        char * word;
        struct node *next;
    } hashChainNode;

    hashChainNode *chainVar1 = malloc(sizeof(hashChainNode));
    hashChainNode *chainVar2 = malloc(sizeof(hashChainNode));
    hashChainNode *chainVar3 = malloc(sizeof(hashChainNode));

    srand(time(0));
 
    //generating random words and adding them to the first point of the hash chain
    //We need a random first word for the hash chain in order to proceed.
    //we pick a random character from the array characterList, that has all characters.
    char temp = characterList[rand()%36];
    //then append that character at a string.
    strncat(tempWord, &temp, 1);

    //repeating this procedure times the word lenght.

    chainEndpoint = tempWord;


    //Making the hash Chain. We will be needing only the first and the last value of the chain,
    //so there is no need to make more than 3 hashChain Nodes.
    for(counter = 0; counter < 10; counter++){
        chainVar1->word = tempWord;
        chainVar1->next = chainVar2;
        chainVar2->word = sha1Transformation(chainVar1->word);
        chainVar2->next = chainVar3;
        chainVar3->word = reductionFuntion(chainVar2->word, wordLenght, characterList);
        tempWord = chainVar3->word;
    }

    chainEndpoint = tempWord;

    return chainEndpoint;
}




char * sha1Transformation(char * plainText){
    char const expect[] = "a9993e364706816aba3e25717850c26c9cd0d89d";
    char result[21];
    char hashValue[41];
    size_t offset;

    //calculating sha1 hash value
    SHA1( result, plainText, strlen(plainText) );

    //format the hash value
    for( offset = 0; offset < 20; offset++) {
        sprintf( ( hashValue + (2*offset)), "%02x", result[offset]&0xff);
    }

    return hashValue;
}


char * reductionFuntion(char * hashValue,int wordLenght, char * characterList){
    

    //Reduced function will be described better in the README file.
    int positionSelected = 0;
    char * reductionResult = "";
    int counter = 0;
    int startingPoint = 0;
    int temp = 0;
    int var1 = 0;
    int var2 = 0;
    int var3 = 0;

    

    for(counter = 0; counter < wordLenght; counter++){

        startingPoint = counter * 3;
        temp = hashValue[startingPoint];
        var1 = returnDecimalValue(temp);
        temp = hashValue[startingPoint + 1];
        var2 = returnDecimalValue(temp);
        temp = hashValue[startingPoint + 2];
        var3 = returnDecimalValue(temp);

        positionSelected = var1 + var2 + var3%4;
        
        strncat(reductionResult, &characterList[positionSelected], 1);

    }

    
    return reductionResult;

}


int returnDecimalValue(int asciiValue){

    if(asciiValue > 47 && asciiValue < 48){
        asciiValue = asciiValue - 48;
    }
    else if(asciiValue > 96 && asciiValue < 103){
        asciiValue = asciiValue - 87;
    }
    else return -1;

    return asciiValue;
}


