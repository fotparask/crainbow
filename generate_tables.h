#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h> 
#include <iostream> 
#include "sha1.h"


int generate_table();
void createHashChain();
char * reductionFuntion(char * hashValue);




int generate_table(){

    

    int counter = 0;

    char letters[26];
    char numbers[10];
    char charList[36];

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
    


    //Genarating all available passwords.
    //Starting with 1 word password. 
    //Limiting password lenght to 8 characters.


    char oneCharHashChain[5];
    char twoCharsHashChain[250];
    char threeCharsHashChain[12500][2];
    char fourCharsHashChain[625000][2];
    char fiveCharsHashChain[31250000][2];
    char sixCharsHashChain[1562500000][2];
    char sevenCharsHashChain[78125000000][2];
    char eightCharsHashChain[3906250000000][2];

    //Reduced function will be described better in the README file.
    





    int numberOfCharacters = 1;
    //The value of numberOfCharacters shows how many characters our word has we want to crack.
    //Maximum value is a word (a password) with 8 characters.

    int characterPosition = 0;
    //characterPosition points to the characters we want to insert, from the initiallazation array 
    //we created earlier

    int stringPosition = 0;
    //stringPosition points in the character array(string) we want to insert our character.
    //depending on the variable numberOfCharacters, stringPosition meets its maximum value.
    //First goes till the value 1, namely the word with 1 character.
    //In the final repetition of while, goes till the value 9, namely the word with 10 character.



    // while (numberOfCharacters < 10){
    //     for (characterPosition = 0; characterPosition < 26; characterPosition++){
    //         for (stringPosition = 0; stringPosition < numberOfCharacters; stringPosition++){
    //             oneChar[stringPosition][counter][0] = letters[characterPosition];
    //             counter ++;
    //             oneChar[stringPosition][counter][0] = capitalLetters[characterPosition];
    //             counter ++;
    //             if (characterPosition < 20){
    //                 oneChar[stringPosition][counter][0] = symbols[characterPosition];
    //                 counter++;
    //             }
    //             if (characterPosition < 10){
    //                 oneChar[stringPosition][counter][0] = numbers[characterPosition];
    //                 counter++;
    //             }
    //         }
    //     }
    //     numberOfCharacters++;
    // }

    


    return 0;
}




char ** createHashChain(char * characterList){

    int wordLenght = 2;
    char word[wordLenght];
    char * chainEndpoints[2]
    int counter = 0;

    typedef struct node{
        char * word;
        struct node *next;
    } hashChainNode;

    hashChainNode *chainVar1 = malloc(sizeof(hashChainNode));
    hashChainNode *chainVar2 = malloc(sizeof(hashChainNode));
    hashChainNode *chainVar3 = malloc(sizeof(hashChainNode));

    srand(time(0));
 
    strcpy(word, "t");
    strcat(word, "s");

    rand()%36
 
    //generating random words and adding them to the first point of the hash chain
    //We need a random first word for the hash chain in order to proceed.
    //we pick a random character from the array characterList, that has all characters.
    char temp = characterList[rand()%36];
    //then append that character at a string.
    strncat(word, &temp, 1);

    //repeating this procedure times the word lenght.

    chainEndpoints[0] = word;


    for(counter = 0; counter < 10; counter++){
        chainVar1->(*word) = word;
        chainVar1->next = chainVar2;
        chainVar2->(*word) = sha1Transformation(chainVar1->(*word));


    }

    hashChainNode * hashChain[21] = { 0 };

    hashChain[0]->next = hashChain[1];
    hashChain[0]->(*word) = "takis"

}




char * sha1Transformation(char * plainText){
    char const expect[] = "a9993e364706816aba3e25717850c26c9cd0d89d";
    char result[21];
    char hexresult[41];
    size_t offset;

    /* calculate hash */
    SHA1( result, plainText, strlen(string) );

    /* format the hash for comparison */
    for( offset = 0; offset < 20; offset++) {
        sprintf( ( hexresult + (2*offset)), "%02x", result[offset]&0xff);
    }

    return hexresult;
}


char * reductionFuntion(char * hashValue){
    
    char hexresult[41] = hashValue;

    

}


