#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int getNumWords(FILE* theFile) {
    int count;
    int c;
    while(!feof(theFile)) {
        c = fgetc(theFile);
        if (c == '\n') {
            count++;
        }

    }

    rewind(theFile);


    return count;
}

char** readWords(FILE* theFile, int numWords) {

    char** theList = NULL;
    theList = (char**) malloc(sizeof(char*)*numWords);
    char* currentWord = NULL;
    int wordCount = 0;

    do {
        wordCount++;
        currentWord = (char*) malloc(sizeof(char) * strlen(currentWord)+1);

        fscanf(theFile, " %s", &currentWord);

    } while (!feof(theFile));



}


int main()
{
    FILE *theFile = fopen("dictionary.txt", "r");

    char* currentWord;
    char* newWord;

    /* theList holds memory address of first char in first word,
     * *theList is pointer to pointer of first char in first word in array,
     * while **theList is pointer to first char in
     *
     */




    char** theList;
    int wordLen;

    int numWords;




    if (!theFile) {
        printf("BAD FILE BAD BAD GIMME PARENT\n"); // screams for parent in case of error
        exit(-1);
    }

    numWords = getNumWords(theFile);
    theList = readWords(theFile, numWords);

/*
    while (currentWord != EOF) {

        newWord = NULL;
        newWord = (char*) malloc(sizeof(char)*(wordLen+1));
        *theList = newWord;

        currentWord = fgets(" %s", theFile);
    }


*/
    fclose(theFile);

    return 0;
}



