#include <stdio.h>
#include <stdlib.h>
#include <time.h>
///---------------------------------------------------------
///--------------- Author: Kyle Krueger --------------------
///------- Course: Advanced Programming Languages ----------
///----------------- Date: 2-14-2023 -----------------------
///---------------------------------------------------------
///-------------------- OBJECTIVE --------------------------
///Crunch is a program that randomly combines words from its
///input stream and outputs them to the terminal. Input will
///be taken from the input stream. Additional flags may be 
///entered by the user, and will be described below
///
///Words must meet a minimum length [-m] to be selected.
///Spaces are omitted unless told to do otherwise [-s]
///
///---------------------------------------------------------
///---------------------- FLAGS ----------------------------
///[-d]<degree> Number of words from input stream to combine
///		in each crunched output.
///[-m]<size>	The minimum length of each word used
///[-n]<count>	Number of output strings to produce
///[-s]		Indicates to insert a space between the 
///		output words
///---------------------------------------------------------
///--------------------- EXAMPLE ---------------------------
/// ./crunch -d 4 -m 2 -n 6 -s <Input.txt
///---------------------------------------------------------

///--FUNCTION PROTOTYPES--

//Loops through each argument provided and updates necessary flags. Exiting the program if flag incorrect
void updateFlags(int argc, char *argv[]);

//Checks a single argument and returns its number, or a -1 if it is not a positive int
int numCheck(char *argv);

//Takes from stdin, populates the wordbank with words until EOF is reached
void wordBankPopulate();

//Debugging use to print the entire word bank
void printWordBank();

//Implementing a function to compare two strings
int compareString(const char *s1, const char *s2);

//Implementing a function to copy one string to another
void copyString(char *out, const char *in);

//Compares the input string to the global word bank, returning a 0 if unique, or a 1 if not
int checkUnique(const char *s);

//returns the length of a string
int strLen(char *in);

//Populates the Random array with unique random numbers
int populateRandomArray(int *in);

//Loops through arr to check if in is contained within. Returns 0 if in is unique, or 1 if not.
int uniqueInt(int *arr, int in, int size);

///---GLOBAL VARIABLES---
#define MAX_LEN 1000
char wordBank[MAX_LEN][MAX_LEN];
char outputBank[MAX_LEN][MAX_LEN];
int wc = 0; //Word count 
int debugMode = 0; //0 for production, 1 for debugMode


//FLAGS
int D = 4;
int M = 6;
int N = 1;
char S = 'F'; //F for False, T for true. No Bool type in C

	



int main(int argc, char *argv[])
{
	int i,j,k;
	//Process arguments.
	if (argc > 1){
		updateFlags(argc,argv);
	}

	//Populate wordBank
	wordBankPopulate();

	//Create an array to store the random numbers (Locations of the nums)
	int randomLocations[D];
	if (debugMode == 1) printWordBank(); // Used for Debugging	
	
	//Loop through however many outputs we need and print the random words
	for (i = 0; i < N;i++){
	
		populateRandomArray(randomLocations);
		if (debugMode == 1){
			for (k =0; k < D; k++){
				printf("%d ",randomLocations[k]);
			}
			printf("\n");
		}

		for(j=0;j<D;j++){
			printf("%s",wordBank[randomLocations[j]]);
		}
		printf("\n");
	}
	//Populating our array
	

	
	


	return EXIT_SUCCESS;
}

void updateFlags(int argc, char *argv[]){
//Scans through the arguments and updates flags accordingly. 	
	int i;
	char currentChar, lastArg;
	char *arginput;
	int stringLength = 0;
	for (i = 1; i < argc; i++){
		//Find the length of the argument
		FILE *nf = fopen("/dev/null", "w");
		stringLength= fprintf(nf,"%s\n", argv[i]) - 1;
		fclose(nf);
		//Checks if the argument is a flag
		//if it is a flag, raise the lastArg flag and continue. 
		//if the last arg flag is raised, check the flag to modify
		if (lastArg != '0'){
			//Test to see if the argument is a number, then update the corresponding flag
			
			if (lastArg == 'D'){
			D = numCheck(argv[i]);
			}
			if (lastArg == 'M'){
				M = numCheck(argv[i]);
			}
			if (lastArg == 'N'){
				N = numCheck(argv[i]);
			}

			lastArg = '0';
		}
		if (stringLength == 2 && argv[i][0] == '-'){
			// Update the flag type, for d,m,n the next argument will be considered
				if (argv[i][1] == 's'){
					S = 'T';
					lastArg = '0';
				}
				else if (argv[i][1] == 'd'){
					D = argv[i][2];
					lastArg = 'D';
				}
				else if (argv[i][1] == 'm'){
					M = argv[i][2];
					lastArg = 'M';
				}
				else if (argv[i][1] == 'n'){
					N = argv[i][2];
					lastArg = 'N';
				}
				else {
				printf("ERROR: Invalid Flag\n");
				exit(-4);
				}
					
		}
		
	}
	if (debugMode == 1) printf("Flags updated: S = %c; D = %d; M = %d; N = %d",S,D,M,N);
}

int numCheck(char *var){
	long val;
	char *next;

	val = strtol(var, &next, 10);

	if ((next == var) || (*next != '\0')) {
		//strtol did not give us the full value, meaning it encounterd an invalid character.
		printf("ERROR: Invalid Argument after flag");
		exit (-5);
	}
	else{
	return (int)val;
	}
}

void wordBankPopulate(){
	//Checks if the 
	int isUnique,i;
	char buffer[MAX_LEN];

	while(scanf("%s",buffer) == 1){
		
		isUnique = 1;
		for (i = 0; i <wc; i++){
			if (compareString(wordBank[i], buffer) == 0){
				isUnique = 0;
				break;
			}
		}
		// If the token is unique, add it to the wordbank and incriment the variable. 

		if (isUnique == 1 && strLen(buffer) >= 6){
			copyString(wordBank[wc], buffer);
			//check if our S flag is set to T
			if (S == 'T'){
			sprintf(wordBank[wc], "%s%s",wordBank[wc]," ");
			}
			wc++;
		}

		//Checking for token limit
		if (wc == MAX_LEN){
			//Break the loop if the word count is reached (MAX_LEN is a pretty high number for unique tokens)
			break;
		}
	}

	//Check if the
	
	if (debugMode == 1) printf("Word bank populated\n");

}

void printWordBank(){
	int i,j;
	for (i = 0; i<wc; i++){
		for (j = 0; j<MAX_LEN; j++){
			printf("%c",wordBank[i][j]);
		}
		printf("\n");
	}
}

int compareString(const char *s1, const char *s2){
	int matchedChars = 0;
	//While there is a character at the pointer, and while the two character match
	
	while (*s1 && (*s1 == *s2)){
		s1++;
		s2++;
		
	}

	//compare the characters at the end, they should match and return a 0 if the strings are the same. Non 0 if they are different
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

void copyString(char *out, const char *in){
	//Simple while loop to copy the contents of the in array into the out array
	while ((*out++ = *in++));
}

int strLen(char *in){
	//Loops through given input and incriments the length until the null terminator is found
	int len = 0;
	while (in[len] != '\0'){
		len++;
	}
	return len;
}

int populateRandomArray(int *in){
	int i = 0;
	int temp;
	int doneFlag = 0;
	srand(time(NULL));
	//error Checking
	if (wc < D){
		printf("ERROR: Amount of unique words is less than minimum length of crunch\n");
		return -1;
	}
	for (i = 0; i < D; i++){
		//populates the number with a random array index for the word bank
		if (debugMode == 1) printf("About to populate Array element\n");
		doneFlag = 0;
		while (doneFlag != 1){
			temp = rand() % wc;
			if (uniqueInt(in, temp, D) == 1);
			else{
				in[i] = temp;
				doneFlag = 1;
			}
				
		}
		if (debugMode == 1) printf("Finished populating array element\n");
	}
	return 0;
}

int uniqueInt(int *arr, int in, int size){
	int i = 0;
	for (i=0; i < size; i++){
		if (in == arr[i]){
			return 1;
		}
	}
	return 0;
}


