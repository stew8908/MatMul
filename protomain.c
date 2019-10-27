/* hash cracker - sequential
 * Group members: Emmy woods, Chris Cornell, Brandon Roth
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 2

unsigned long hash(char *str);


int main()
{
	unsigned long ans;
	char string_ans[SIZE];
	unsigned long test_hash = 0;
	int i, j;
	int character_length = 26;
	int test_num = 0;
	char test_char[SIZE];

	//two lower case letters for now
	ans = hash( "cd" );
	
	for(i = 0; i< character_length; ++i)
	{
		test_num = i + 97;
		//cast test_num to a char type
	 	test_char[0] = ((char) test_num);
		for(j = 0; j < character_length; ++j)
		{
					
			test_num = j + 97;
			//cast test_num to a char type
	 		test_char[1] = ((char) test_num);
			//print all of the tried chars if you like
			//printf(" test char: %s\n", test_char);
			//pass in the test_char starting with aa then ab etc
			test_hash = hash(test_char);
		

			if(test_hash == ans)
			{
				printf("The answer is: %s\n", test_char);
			}

		}	

	}
	


	return 0;
}
