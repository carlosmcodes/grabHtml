/*
 ============================================================================
 Name        : CLopezHtmlSrcList.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *pSrc = NULL;

char *pQ1 = NULL;

char *pQ2 = NULL;

int distanceFrom = 0;

char catString[99999];

char curl[99999] = { "curl -s " };

// create file pointer
FILE* preFixFileString;

// declare methods to be used
void getTags(char tempFixString[], FILE * preFixFileString);

void getC(char tempFixString[], FILE * preFixFileString);

void getURL(char tempFixString[], FILE *preFixFileString);

void getFreq(char tempFixString[], FILE * preFixFileString);

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
	char fileName[300];

	char tempFixString[BUFSIZ];

	char userInputInquiry[50];

	puts("URL: ");

	// stores user input to readstringfilename
	fgets(fileName, 300, stdin);

	// clears name from new line char
	fileName[strlen(fileName) - 1] = '\0';

	//combine curl w filename
	strcat(curl, fileName);

	// if popen decides to suck
	if (curl == NULL)
		puts("File Not Found");

	// checks first index
	while (userInputInquiry[0] != 'q') {

		// std
		puts("Ready");

		//takes in user request
		fgets(userInputInquiry, 50, stdin);

		// grabs request from position zero
		switch (userInputInquiry[0]) {
		case 'u':
			getURL(tempFixString, preFixFileString);
			break;
		case 'c':
			getC(tempFixString, preFixFileString);
			break;
		case 't':
			getTags(tempFixString, preFixFileString);
			break;
		case 'f':
			getFreq(tempFixString, preFixFileString);
			break;
		case 'q':
			puts("Complete");
			break;

		}
	}

	// check for q
	if (userInputInquiry[0] != 'q')
		puts("Complete");

	// closing for future use
	pclose(preFixFileString);

	return EXIT_SUCCESS;
}

void getC(char tempFixString[], FILE * preFixFileString) {
	int counter = 0;

	// accessing the 'curl'
	preFixFileString = popen(curl, "r");

	// reads in everyline and stores in tempFixString
	while (fgets(tempFixString, BUFSIZ, preFixFileString) != NULL) {

		// tack on to catonated string
		strcat(catString, tempFixString);

		// finding 'needle in the haystack
		pSrc = strstr(catString, "src=\"");

		// if found do this
		if (pSrc != NULL) {

			// take a step back
			pSrc--;

			// if found set a new line
			if (*pSrc == '.') {
				strncpy(catString, pSrc, 1);
				catString[1] = '\0';

			}
			// if spaces exist, states true
			if (*pSrc == ' ' || *pSrc == '\t' || *pSrc == '\r'
					|| *pSrc == '\n') {

				// move back up since it is valid
				pSrc++;

				//asign
				pQ1 = pSrc;

				// move up till find this
				while (*pQ1 != '\"') {
					pQ1++;
				}

				// set other pointer
				pQ2 = pQ1 + 1;

				// move while this is found
				while (*pQ2 != '\"') {
					pQ2++;
				}

				// gets distance
				distanceFrom = pQ2 - pQ1;

				// algo cont.
				strncpy(catString, pQ1 + 1, distanceFrom);
				catString[distanceFrom - 1] = '\0';
				counter++;

			}
		}

	}

	printf("%d\n", counter);

}

void getTags(char tempFixString[], FILE * preFixFileString) {

	// accessing the 'curl'
	preFixFileString = popen(curl, "r");

	// reads in everyline and stores in tempFixString
	while (fgets(tempFixString, BUFSIZ, preFixFileString) != NULL) {

		// tack on to catonated string
		strcat(catString, tempFixString);

		// finding 'needle in the haystack
		pSrc = strstr(catString, "src=\"");

		// if found do this
		if (pSrc != NULL) {
			pSrc--;
			if (*pSrc == '.') {
				strncpy(catString, pQ1, 1);
				catString[1] = '\0';

			}
			if (*pSrc == ' ' || *pSrc == '\t' || *pSrc == '\r'
					|| *pSrc == '\n') {
				pSrc++;
				pQ1 = pSrc;

				while (*pQ1 != '<') {
					pQ1--;
				}
				pQ2 = pQ1 + 1;
				while (*pQ2 != ' ' && *pQ2 != '\t' && *pQ2 != '\r'
						&& *pQ2 != '\n') {
					pQ2++;

				}
				distanceFrom = pQ2 - pQ1 - 1;
				// algo cont.
				strncpy(catString, pQ1 + 1, distanceFrom);
				catString[distanceFrom] = '\0';
				puts(catString);
			}
		}
	}
}
void getURL(char tempFixString[], FILE * preFixFileString) {

	// accessing the 'curl'
	preFixFileString = popen(curl, "r");

	// reads in everyline and stores in tempFixString
	while (fgets(tempFixString, BUFSIZ, preFixFileString) != NULL) {

		strcat(catString, tempFixString);
		pSrc = strstr(catString, "src=\"");
		if (pSrc != NULL) {
			pSrc--;
			if (*pSrc == '.') {
				strncpy(catString, pSrc, 1);
				catString[1] = '\0';

			}
			if (*pSrc == ' ' || *pSrc == '\t' || *pSrc == '\r'
					|| *pSrc == '\n') {
				pSrc++;
				pQ1 = pSrc;
				while (*pQ1 != '\"') {
					pQ1++;

				}
				pQ2 = pQ1 + 1;
				while (*pQ2 != '\"') {
					pQ2++;
				}

				// gets distance
				distanceFrom = pQ2 - pQ1;

				// algo cont.
				strncpy(catString, pQ1 + 1, distanceFrom);
				catString[distanceFrom - 1] = '\0';
				puts(catString);

			}
		}

	}
}

void getFreq(char tempFixString[], FILE * preFixFileString) {

	// creating tag types and counters for them
	int frameCount = 0;

	char iframe[] = "iframe";

	char img[] = "img";

	int imgCount = 0;

	char script[] = "script";

	int scriptCount = 0;

	// accessing the 'curl'
	preFixFileString = popen(curl, "r");

	// same as tag method
	while (fgets(tempFixString, BUFSIZ, preFixFileString) != NULL) {

		strcat(catString, tempFixString);

		pSrc = strstr(catString, "src=\"");

		if (pSrc != NULL) {
			pSrc--;
			if (*pSrc == '.') {
				strncpy(catString, pQ1, 1);
				catString[1] = '\0';

			}
			if (*pSrc == ' ' || *pSrc == '\t' || *pSrc == '\r'
					|| *pSrc == '\n') {
				pSrc++;
				pQ1 = pSrc;

				while (*pQ1 != '<') {
					pQ1--;
				}
				pQ2 = pQ1 + 1;
				while (*pQ2 != ' ' && *pQ2 != '\t' && *pQ2 != '\r'
						&& *pQ2 != '\n') {
					pQ2++;

				}
				distanceFrom = pQ2 - pQ1 - 1;
				// algo cont.
				strncpy(catString, pQ1 + 1, distanceFrom);
				catString[distanceFrom] = '\0';

				// if either match, increment

				if (strcmp(iframe, catString) == 0) {
					frameCount++;

				}
				if (strcmp(img, catString) == 0) {
					imgCount++;

				}

				if (strcmp(script, catString) == 0) {
					scriptCount++;

				}

			}
		}
	}
	// kinda sorta mickey moused this  :)
	printf("%s\t%d\n", script, scriptCount);
	printf("%s\t%d\n", iframe, frameCount);
	printf("%s\t%d\n", img, imgCount);

}
