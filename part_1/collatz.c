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

// plot "output.txt" using 2:1 with lp
// 
// need an array, whose indicides correspond to the current variable
// every time you run with different target number, increment the corresponding
// entry in the array
//
// could either do the loop in the bash file within the program
//
// or have another program that opens the file and constructs the histogram
//
// open it, read the file line by line, then use the first number as the index
// and increment it
//
//
// right now, using fprintf inside the start and end for clk time
// can also save the current var in another array, and then write to the file
// all in one shot at the end, note inpact on runtime
//
//
//
//look at corey shaffer on yt
//book - jake vanderplas
//
// -------------8/22-----------
// set up #DEFINE for magic numbers
// right now, saving all the data into one file (o2.txt) -- try saving it into
// on.txt, n is the input number to the program
// need to print out current arr at the end of the program to a file and then
// plot
// compile and run above, try to fix errors
//
//----------------8/23------------
//
//look at gnuplot documentation, print new line after each number
//
//create file name using string stuff
//
//8/25----
//create two files, one for the path and one for the total count of steps
//for each number
//----------------8/26---------
// change all variables to standard int
// implement collatz function using ?: syntax
//	also return directly, dont use n = 
// convert while loop, in the middle of the main for loop, into a for loop
// check return value of fopen, make sure it is not NULL
// for warehouse project -- draw a diagram of the system
// ARTICLE:
//
// write in markdown
// 	in markdown, can use latex to typset math equations
// 
// incformation on collatz already exists, but this doesn't give me a feel 
// for how it actually works -- implementing it helped me learn a lot more
// about collatz, and about programming
//
// two levels - about collatz specifically, show plots etc.
// 2nd level - what can be learned from this
// what did i learn when implementing - from the math and from the proramming side
//
// end with so what?, what was the outcome, what was the impact
//
// for implementation, show the code
//
//
//
// 
