/* hash cracker - sequential
 * Group members: Emmy woods, Chris Cornell, Brandon Roth
 */

/*compile:
 * gcc ehashs.c -o ehashs hashfun.o
 * run with hash for "bean"
 * ./ehashs 6385076027
 */


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 5
//int level = 0;
bool answer_found = false;

//Tom's function
unsigned long hash(char *str);

// global
char test_char[SIZE];
unsigned long encoded_value;

void initialize_string(char *str){
    for (int i = 0; i < (SIZE-1); i++){
        test_char[i] = 'a';
    }
    test_char[SIZE-1] = 0;
}

// return a char pointer of the charachters that match the hash val
void run_hash(int level){
    for (int i = 0; i < 26; i++){
        if (answer_found == true) return;
        //this is repeated in each loop, set to ascii value starting at charachter a
        int test_num = i + 97;
        //casting of test_num to a char type
        test_char[level] = ((char) test_num);
        // uncomment next line to print out all strings
        // printf("%s, level:  %d\n", test_char, level);

        long int test_hash = hash(test_char);

        if(test_hash == encoded_value)
        {   
            printf("The answer is: %s\n", test_char);
            answer_found = true;
            return;
        }

        if (level < (SIZE-2)){
            run_hash(level + 1);
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Please enter a hash to brute force\n");
        return -1;
    }

    encoded_value  = strtol(argv[1], NULL, 10);

    char *test_val;

    printf(" hash input = %lu\n", encoded_value);

    initialize_string(test_char);

    run_hash(0);

    //printf("hash calcd");

    return 0;
}
