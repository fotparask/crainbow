int generate_table(){

    int counter = 0;

    char letters[26];
    char capitalLetters[26];
    char symbols[10];
    char numbers[10];


    //Initiallizing all the characters.
    for (counter = 0; counter < 26; counter++){
        letters[0][counter] = 97 + counter;
    }

    for (counter = 0; counter < 26; counter++){
        capitalLetters[0][counter] = 65 + counter;
    }

    for (counter = 0; counter < 10; counter++){
        numbers[counter] = counter;
    }

    //not all symbols are inculded
    char symbols[20] = {'!','@','#','$','%%','^','&','*','~','?','-','_','(',')','+','=',';',':','<','>'};


    //Genarating all available passwords.
    //Starting with 1 word password. 
    //Limiting password lenght to 10 characters.

    //Creating 2d array for each password lenght
    //The first column contains the password and the second the SHA1 hash on that password.
    char * oneChar[85][2];
    char * twoChars[7225][2];
    char * threeChars[614125][2];
    char * fourChars[52200625][2];
    char * fiveChars[4437053125][2];
    char * sixChars[377149515625][2];
    char * sevenChars[32057708828125][2];
    char * eightChars[2724905250390625][2];
    char * nineChars[231616946283203125][2];
    char * tenChars[19687440434072265625][2];

    int counter = 0;

    int numberOfCharacters = 1;;
    //The value of numberOfCharacters shows how many characters our word has we want to crack.
    //Maximum value is a word (a password) with 10 characters.

    int characterPosition = 0
    //characterPosition points to the characters we want to insert, from the initiallazation array 
    //we created earlier

    int stringPosition = 0;
    //stringPosition points in the character array(string) we want to insert our character.
    //depending on the variable numberOfCharacters, stringPosition meets its maximum value.
    //First goes till the value 1, namely the word with 1 character.
    //In the final repetition of while, goes till the value 10, namely the word with 10 character.



    while (numberOfCharacters < 11){
        for (characterPosition = 0; characterPosition < 26; characterPosition++){
            for (stringPosition = 0; stringPosition < numberOfCharacters; stringPosition++){
                oneChar[stringPosition][counter][0] = letters[characterPosition]
                counter ++;
                oneChar[stringPosition][counter][0] = capitalLetters[characterPosition]
                counter ++;
                if (characterPosition < 20){
                    oneChar[stringPosition][counter][0] = symbols[characterPosition]
                    counter++;
                }
                if (characterPosition < 10){
                    oneChar[stringPosition][counter][0] = numbers[characterPosition]
                    counter++;
                }
            }
        }
        numberOfCharacters++;
    }




    return 0;
}