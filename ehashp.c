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
#include <omp.h>

#define SIZE 5
#define NUMBER_OF_THREADS 12 
//Tom's function
unsigned long hash(char *str);

// return a char pointer of the charachters that match the hash val
char * run_hash(unsigned long encoded_value)
{
	unsigned long test_hash = 0;
	int i, j,k, x;
	int character_length = 26;
	int test_num = 0;
	static char found_char[SIZE] = "fail";
	char test_char[SIZE];
	int found = 0;

	#pragma omp parallel for schedule(static,1) private(test_num,test_char,test_hash,j,k,x,i) num_threads(NUMBER_OF_THREADS) 
	for(i = 0; i< character_length; i ++)
	{
		//this is repeated in each loop, set to ascii value starting at charachter a
			
		int threadId = omp_get_thread_num();
		test_num = i + 'a';
		//casting of test_num to a char type
	 	test_char[0] = ((char) test_num);
	       	//printf("%d is working on i = %c\n",threadId,test_char[0]);	

		for(j = 0;(found ==0) && (j < character_length); ++j)
		{
			test_num = j + 97;
			test_char[1] = ((char) test_num);

			for(k = 0;(found ==0) && (k < character_length); ++k)
			{
				test_num = k + 97;
				test_char[2] = ((char) test_num);

				for(x = 0;(found ==0) && (x < character_length); ++x)
				{
				
					test_num = x + 97;
					//cast test_num to a char type
					test_char[3] = ((char) test_num);
					//uncomment the line below to see all the tests happen
					//if(test_char[0] == 'b')					
					//printf(" test char: %s on thread %d \n", test_char,threadId);
					//pass in the test_char starting at "aaaa"
					test_hash = hash(test_char);
					if(test_hash == encoded_value)
					{	
						memcpy(found_char,test_char,SIZE);
						printf("found!!\n");
						found = 1;
					}				

				}

			}

		}	
		if(found)
		{
			#pragma omp cancel for
		}

	}
return found_char;
}


int main(int argc, char *argv[])
{

	if(argc < 2)
	{
		printf("Please enter a 3 character, lower case string\n");
		return -1;
	}
	

	unsigned long ans  = strtol(argv[1], NULL, 10);

	char *test_val;


	printf(" hash input = %lu\n", ans);

	test_val = run_hash(ans);

	if(test_val != "fail")
	{
		printf("The answer is: %s\n", test_val);
	}
	else
	{
		printf("Unable to find the answer\n");
	}
	
	return 0;
}
