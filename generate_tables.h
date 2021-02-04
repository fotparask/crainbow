int generate_table(){

    int counter = 0;

    char letters[26];
    char capitalLetters[26];
    char * symbols[10];
    int numbers[10];

    for (counter = 0; counter < 26; counter++){
        letters[counter] = 97 + counter;
    }

    for (counter = 0; counter < 26; counter++){
        capitalLetters[counter] = 65 + counter;
    }

    for (counter = 0; counter < 10; counter++){
        numbers[counter] = counter;
    }

    char symbols[10] = {'!','@','#','$','\%','^','&','*','~','?'};



    return 0;
}