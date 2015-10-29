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

char** readWords(FILE* theFile, int lenCounts[50], int lengthChosen) {

    int wordsOfChosenLen = lenCounts[lengthChosen];

    printf("Number of words of length %d: %d\n", lengthChosen, wordsOfChosenLen);

    char** theList = NULL;
    int i = 0;
    theList = (char**) malloc(sizeof(char*)*wordsOfChosenLen);
    char* toAdd = NULL;
    char currentWord[50];



    while (!feof(theFile) && i < wordsOfChosenLen) {
        fgets(currentWord, wordsOfChosenLen, theFile);

        if (strlen(currentWord) == lengthChosen +1) {
            toAdd = (char*) malloc(sizeof(char) * (lengthChosen+1));
            strcpy(toAdd,currentWord);


            theList[i] = toAdd;
            i++;
        }
    }

    printf("%d. Current word: %s\n", i, theList[i-1]);

    return theList;
}

int promptUserForLen() {
    int length;

    printf("What length words do you want to use? ");
    scanf(" %d", &length);

    return length;
}


int main()
{
    FILE *theFile = fopen("dictionary.txt", "r");

    int lenCounts[50] = {0};
    int lengthChosen;

    char** theList;
    int numWords;




    if (!theFile) {
        printf("BAD FILE BAD BAD GIMME PARENT\n"); // screams for parent in case of error
        exit(-1);
    }

    numWords = getNumWords(theFile, lenCounts);

    lengthChosen = promptUserForLen();

    theList = readWords(theFile, lenCounts, lengthChosen);

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









