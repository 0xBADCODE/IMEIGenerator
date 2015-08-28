/*  IMEI Generator
 *  Xeon Feb 2015
 *  gcc imei.c -o imei -ggdb -W -std=c99 -m64 -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define LENGTH 15

int main(int argc, char *argv[]){

	srand(time(NULL));

	int imei[LENGTH]  = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	array[LENGTH] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//	array[LENGTH] = {4,9,0,1,5,4,2,0,3,2,3,7,5,1,0}; // test: check digit == 8

	static int rbi[17][2] = {	{0,1},{1,0},{3,0},{3,3},{3,5},{4,4},
					{4,5},{4,9},{5,0},{5,1},{5,2},{5,3},
					{5,4},{8,6},{9,1},{9,8},{9,9}	};

	// Select Reporting Body Identifier
	int i = rand() % 17, sum = 0;
	array[0] = rbi[i][0];
	array[1] = rbi[i][1];

	// Generate random array
	for (i = 2; i < LENGTH - 1; i++){
		array[i] = rand() % 10;
	};

	//cp array to imei
	for (i = 0; i < LENGTH - 1; i++){
		imei[i] = array[i];
	};

	// Calculate Luhn checksum
	char tmp[2] = {0,0};

	for (i = LENGTH - 2; i > 0; i -= 2){
		array[i] *= 2;

		if (array[i] > 9){
			sprintf(tmp, "%d", array[i]);
			array[i] = (tmp[0] - '0') + (tmp[1] - '0');
		};
	};

	for (i = 0; i < LENGTH - 1; i++){
		sum += array[i];
	};

	// Calculate check_digit
	imei[LENGTH - 1] = 10 - (sum % 10);

	// Print IMEI
	printf("\nValid IMEI: ");

	for(i = 0; i <= LENGTH - 1; i++){
		printf("%d", imei[i]);
	};

	printf("\n\n");

	return 0;
}

