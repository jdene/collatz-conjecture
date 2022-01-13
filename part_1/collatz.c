#include "collatz.h"

unsigned int collatz(unsigned int n){
    // check if # is odd or even
    return (n & 1) ? ((3*n) + 1) : (n >> 1);
}

int main(int argc, char **argv)
{

    int num_to_calculate = 1;

    FILE *fileptr;
    FILE *fileptr_steps;
    FILE *fileptr_frequency;

    fileptr = fopen("out.txt", "w");
    fileptr_steps = fopen("steps.txt", "w");

    if(fileptr == NULL || fileptr_steps == NULL){
	printf("Error opening file.\n");
	return 1;
    }

    clock_t start, end;
    long int freq_arr[ARR_SIZE];

    for(int i = 0; i < ARR_SIZE; i++)
	freq_arr[i] = 0;

    for(num_to_calculate = 1; num_to_calculate < MAX_NUM_TO_CALC; 
	    num_to_calculate++){

	unsigned int count = 0;	

	start = clock();

	printf("\n");

	for(unsigned int long current = num_to_calculate; current > 1; 
		current = collatz(current), count++, freq_arr[current]++){
	    fprintf(fileptr, "%d %ld\n",count, current);
	}

	fprintf(fileptr, "%d 1\n\n\n",count);
	//
	//printting total steps to new .txt file
	fprintf(fileptr_steps, "%5d %5d\n", num_to_calculate, count);

	end = clock();
	printf("Total runtime: %f ms\n", ((double)(end-start)) / 
		(CLOCKS_PER_SEC / MS_PER_SEC));
	printf("%d\n", count);

    }

    fileptr_frequency = fopen("frequency.txt", "a");
    if(fileptr_frequency == NULL){
	printf("Error opening file.\n");
	return 1;
    }

    for(int i = 0; i < ARR_SIZE; i++){
	fprintf(fileptr_frequency, "%5d %5ld\n", i, freq_arr[i]);
    }
    fclose(fileptr);
    fclose(fileptr_steps);
    fclose(fileptr_frequency);
}