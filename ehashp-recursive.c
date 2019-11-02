/* hash cracker - parallel
 * Group members: Emmy woods, Chris Cornell, Brandon Roth
 */

/*compile:
 * gcc ehashp.c -o ehashp hashfun.o -fopenmp
 * run with hash for "bean"
 * ./ehashp 6385076027
 */


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>

#define SIZE 5  // the number of letters
bool answer_found = false;
// change start_char to 'A', 'a', or '0' as desired
int start_char = 'a';
// change end_char to 'Z', 'z', or '9' as desired
int end_char = 'z';

//Tom's function
unsigned long hash(char *str);

// global
char test_char[SIZE+1];
unsigned long encoded_value;

void initialize_string(char *str){
    for (int i = 0; i < (SIZE); i++){
        test_char[i] = 'a';
    }
    test_char[SIZE] = 0;
}

// return a char pointer of the charachters that match the hash val
void run_hash(char *test_char, int level){
    for (int i = start_char; i <= end_char; i++){
        if (answer_found == true) return;
        //casting of test_num to a char type
        test_char[level] = ((char) i);
        
        long int test_hash = hash(test_char);

        if(test_hash == encoded_value)
        {
            printf("The answer is: %s\n", test_char);
            answer_found = true;
            return;
        }

        if (level < (SIZE-1)){
            run_hash(test_char, level + 1);
        }
        // skip characters between Z and a
        if (i == 'Z') i = 'a' - 1;
        // skip characters between 9 and A
        if (i == '9') i = 'A' - 1;
    }
}

void parallelize()
{
    int i;
    #pragma omp parallel for private (test_char) private (i)
    for (i = start_char; i <= end_char; i++)
    {
        char test_char[SIZE+1] = {'a'};
        //initialize_string(test_char);
        test_char[0] = i;
        run_hash(test_char, 1);
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

    parallelize();

    //run_hash(0);

    //printf("hash calcd");

	return 0;
}
