#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;


void printTopLengths(int lengths[50]) {

    printf("Word lengths where there are more than 2000 words:\n");
    printf("Length  How Many\n");
    for (int i = 0; i < 50; ++i) {
        if (lengths[i] > 2000) {
            printf("%d  %d\n", i, lengths[i]);
        }
    }

    return;
}

int getNumWords(FILE* theFile, int lengths[50]) {
    int charCount = 0;
    int wordCount = 0;
    int c;
    while(!feof(theFile)) {
        c = fgetc(theFile);
        if (c == '\n') {
            wordCount++;
            lengths[charCount]++;
            charCount = 0;
        } else {
            charCount++;
        }

    }

    rewind(theFile);


    return wordCount;
}

char** readWords(FILE* theFile, int numWords) {

    char** theList = NULL;
    int i = 0;
    theList = (char**) malloc(sizeof(char*)*numWords);
    char* toAdd = NULL;
    char currentWord[50];



    while (!feof(theFile)) {
        fgets(currentWord, sizeof(currentWord), theFile);
        toAdd = (char*) malloc(sizeof(char) * strlen(currentWord)+1);
        strcpy(toAdd,currentWord);


        theList[i] = toAdd;
        //printf("Current word: %s\n", theList[i]);

        i++;
    }
    for (int i = 0; i < 1000; ++i) {
        printf("Current word: %s\n", theList[i]);
    }

}


int main()
{
    FILE *theFile = fopen("dictionary.txt", "r");

    int lenCounts[50] = {0};

    char* currentWord;
    char* newWord;

    /* theList holds memory address of first char in first word,
   * *theList is pointer to pointer of first char in first word in array,
   * while **theList is pointer to first char in
   *
   */




    char** theList;
    int numWords;




    if (!theFile) {
        printf("BAD FILE BAD BAD GIMME PARENT\n"); // screams for parent in case of error
        exit(-1);
    }

    numWords = getNumWords(theFile, lenCounts);
    theList = readWords(theFile, numWords);

    printTopLengths(lenCounts);

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









