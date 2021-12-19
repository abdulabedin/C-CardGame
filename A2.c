/*
*A2abedin, Abedin, Abdul, 501023078, section 09
*m105khan, Khan, Muhammed, 500967621, Section 01
*ncoutlee, Coutlee, Noah, 501043341, Section 02
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "list.h"

/*Prints the error for a badly formatted card and then exits*/
void badCard(char fileName[]) {
    fprintf(stderr, "%s has bad format\n", fileName);
    exit(4);
}

/*Checks the card's format*/
void testCard(char fileName[]) {
    FILE *file;
    file=fopen(fileName, "r");
    char ch;
    char lines[5][14];
    int numbers[5][5];
    int num;
    int i, j, k, m, n, o, p;
    /*Checks the length and number of the lines*/
    /*Lines are stored in an array*/
    for (i=0;i<5;i++) {
		for (j=0;j<15;j++) {
	    	ch = getc(file);
	    	if (j == 14) {
				if (ch != '\n') {
		    		badCard(fileName);
				}
				else if (i == 4) {
		    		ch = getc(file);
		    		if (ch != EOF) {
						badCard(fileName);
		    		}
				} 
	    	}
	    	else if ((ch == '\n' || ch == EOF) && j != 14) {
				badCard(fileName);
	    	}
	    	else {
				lines[i][j] = ch;
	    	}
		}
    }
    fclose(file);
    /*Checks that each line follows the pattern '## ## ## ## ##'*/
    for (k=0;k<5;k++) {
		for (m=0;m<14;m++) {
	    	if ((m + 1) % 3 == 0 && lines[k][m] != ' ') {
				badCard(fileName);
	    	}
	    	else if ((m + 1) % 3 != 0 && !isdigit(lines[k][m])) {
				badCard(fileName);
	    	}
		}
    }
    /*Stores the values from the array of lines into an array of integers*/
    for (k=0;k<5;k++) {
        for (m=0;m<14;m++) {
	    	num = lines[k][m] - '0';
	    	if (m % 3 == 0) {
				numbers[k][m / 3] = num * 10;
	    	}
	    	else if (m % 3 == 1) {
				numbers[k][m / 3] += num;
	    	}
		}
    }
    /*Ensures that the numbers in each column fall into the proper range*/
    /*Also makes sure that the center is 0*/
    for (k=0;k<5;k++) {
        for (m=0;m<5;m++) {
	    	if (k == 2 && m == 2) {
				if (numbers[k][m] != 0) {
		    		badCard(fileName);
				}
	    	}
	    	else if (numbers[k][m] < m * 15 + 1 || numbers[k][m]  > m * 15 + 15) {
				badCard(fileName);
	    	}
		}
    }
    /*Looks for duplicate numbers in each of the columns*/
    for (n=0;n<5;n++) {
		for (o=0;o<5;o++) {
	    	for (p=0;p<5;p++) {
				if (numbers[o][n] == numbers[p][n] && o != p) {
		    		badCard(fileName);
				}
	    	}
		}
    }
}

/*Checks the arguments*/
void testArguments(int numargs, char *args[]) {
    /*Checks that the right number of arguments were passed*/
    if (numargs != 3) {
		fprintf(stderr, "Usage: %s seed cardFile\n", args[0]);
		exit(1);
    }
    /*Checks that the seed a is a valid seed*/
	int i;
    for (i=0;i<strlen(args[1]);i++) {
		if (i == 0) {
			if (!isdigit(args[1][i]) && (args[1][i] != '-' || strlen(args[1]) == 1)) {
				fprintf(stderr, "Expected integer seed but got %s\n", args[1]);
            	exit(2);
			}
		}
		else if (!isdigit(args[1][i])) {
            fprintf(stderr, "Expected integer seed but got %s\n", args[1]);
            exit(2);
        }
    }
    /*Checks that the file is readable*/
    if (access(args[2], R_OK)) {
		fprintf(stderr, "%s is nonexistent or unreadable\n", args[2]);
		exit(3);
    }
}

/*Checks if there is a winner*/
int check(int marked[][5]) {
    int count;
    // check all rows
    for (int i = 0; i < 5; i++)
    {
        count = 0;
        for (int j = 0; j < 5; j++)
        {
            if (marked[i][j] == 1)
            {
                count++;
            }
            else
            {
                break;
            }

            if (count == 5)
            {
                // printf("Row %d\n", i);
                return 1;
            }
        }
    }
	
    // check all columns
    for (int i = 0; i < 5; i++)
    {
        count = 0;
        for (int j = 0; j < 5; j++)
        {
            if (marked[j][i] == 1)
            {
                count++;
            }
            else
            {
                break;
            }

            if (count == 5)
            {
                // printf("Column %d\n", i);
                return 1;
            }
        }
    }

    // check diag left to right
    count = 0;
    for (int i = 0; i < 5; i++){
        if (marked[i][i] == 1){
            count++;
        }
        else{
            break;
        }
        if (count == 5){
            // printf("Diagonal Top Left to Bottom Right\n");
            return 1;
        }
    }

    // check diag right to left
    count = 0;
    for (int i = 0; i < 5; i++){
        if (marked[4 - i][i] == 1){
            count++;
        }
        else{
            break;
        }
        if (count == 5){
            // printf("Diagonal Bottom Left to Top Right\n");
            return 1;
        }
    }
	
	// check corners
	count=0;
	if (marked[0][0] == 1 && marked[0][4] == 1 && marked[4][0] == 1 && marked[4][4] == 1) {
		return 1;
	}
    return 0;
}

//Initialize marked matrix which will be used to keep track of numbers that have been called (will help to determine the winner).
void initMarked(int marked[][5]){
    int r;
    int c;
    for (r = 0; r < 5; r++){
        for (c = 0; c < 5; c++){
            marked[r][c] = 0;
    	}
    }
	marked[2][2] = 1;
}

void updateMarked(int cardMatrix[][5],int marked[][5],int val){
    int r;
    int c;
    int k = 0;
 	if(val<16){
    	k =0;
	}
	else if (val<31){
		k =1;
	}
	else if (val<46){
		k =2; 
	}
	else if (val<61){
    	k =3;
	}
	else if (val<76){
    	k =4;
	}
	for (r = 0; r < 5; r++){
        for (c = 0; c < 5; c++){
            if (cardMatrix[r][c] == val){
                marked[r][c] =1;
            }
        }
	}
}


void initCardMatrix(char filename[], int cardMatrix[][5]) {
    int r, c;
    FILE *f;
    f = fopen(filename, "r");

    // read in the matrix
    for (r = 0; r < 5; r++){
        for (c = 0; c < 5; c++){
            fscanf(f, "%02d", &cardMatrix[r][c]); // note the extra space
    	}
    }
}

//Prints out the matrix
void printCardMatrix(int cardMatrix[][5],int marked[][5]){
    int r;
    int c;
    for (r = 0; r < 5; r++) {
        for (c = 0; c < 5; c++){   
             if (marked[r][c] == 1){
                 printf("%02dm ", cardMatrix[r][c]);
             }
             else{
                   printf("%02d  ", cardMatrix[r][c]);
             }
      
        }
        printf("\n");
    }
}

//Print out the line "LINUX" at the top of the matrix.  
void linuxPrinter(){
    char source[] = "LINUX";
    int len = strlen(source);
    for (int i = 0; i < len; i++) {
        printf("%c   ",source[i]);
    }
	printf("\n");
}

int main(int argc, char *argv[]) {
    testArguments(argc, argv);
    testCard(argv[2]);
	int size = 75;
	int calledNums[75];
	int marked[5][5];
	int cardMatrix[5][5];
	int win = 0;
	int count = 0;
	char lastIn = '\n';
	char input;
	int seed = atoi(argv[1]);
	int rNum;

	initMarked(marked);
	initCardMatrix(argv[2], cardMatrix);
	
	srand(seed);
	
	system("clear");
    printList(calledNums, count);
    printf("\n");
    linuxPrinter();
    printCardMatrix(cardMatrix, marked);
    printf("enter any non-enter key for Call (q to quit): ");
	
	while (scanf("%c", &input) != EOF) {
		if (input == 'q') {
			if (lastIn != '\n') {
				printf("\n");
			}
			exit(0);
		}
		else if (input != '\n') {
			rNum = (rand() % 75) + 1;
	    	while (!inList(calledNums, count, rNum)) {
	        	rNum = (rand() % 75) + 1;
	    	}
			addToList(calledNums, count, rNum);
		
			updateMarked(cardMatrix, marked, rNum);
		
			count++;
		}
		lastIn = input;
   		fflush(stdout);
		system("clear");
		printList(calledNums, count);
        printf("\n");
        linuxPrinter();
		printCardMatrix(cardMatrix, marked);
		if (check(marked)) {
            printf("WINNER\n");
   	        exit(0);
   		}
		printf("enter any non-enter key for Call (q to quit): ");
	}
	printf("\n");
	exit(0);
}
