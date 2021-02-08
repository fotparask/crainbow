#include <stdio.h>
#define SUCCESS 0

void drawline();
void testvec1();


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
    

    testvec1();

    
    //generate_table();

    return 0;
}

//test

void drawline(){

    printf("-------------------------------------------------------------\n");

}


void testvec1(){
    char const string[] = "abc";
    char const expect[] = "a9993e364706816aba3e25717850c26c9cd0d89d";
    char result[21];
    char hexresult[41];
    size_t offset;

    /* calculate hash */
    SHA1( result, string, strlen(string) );

    /* format the hash for comparison */
    for( offset = 0; offset < 20; offset++) {
        sprintf( ( hexresult + (2*offset)), "%02x", result[offset]&0xff);
    }

    printf("sha1 value of abc is: %s\n",hexresult);
}