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

        if (strlen(currentWord) == lengthChosen + 1) {
            toAdd = (char*) malloc(sizeof(char) * (lengthChosen+1));

            for (int j = 0; j < lengthChosen; ++j) { // convert word to be copied into lowercase
                currentWord[j] = tolower(currentWord[j]);
            }

            strcpy(toAdd,currentWord);



            theList[i] = toAdd;
            if (theList[i][0] < 97) { // check if copied word is uppercase
                printf("\nUpper case word found!\n#%d Word: %s\n\n", i+1, theList[i]);
            }
            i++;
        }
    }

    printf("Number of words read was %d\n\n", wordsOfChosenLen);

    //printf("#%d. Last word in array: %s\n", i, theList[i-1]);

    return theList;
}

int promptUserForLen() {
    int length;

    printf("What length words do you want to use? ");
    scanf(" %d", &length);

    return length;
}


void declareWords(char* start, char* end, int length) {
    start = (char*) malloc(sizeof(char) * (length+1));
    end = (char*) malloc(sizeof(char) * (length+1));

    return;
}

void getStartAndEnd(char** theList, char* start, char* end) {

    int length = strlen(start);
    bool go = false;
    char a[length];
    char b[length];

    while (!go) {
        printf("Enter starting and ending words, or 'r' for either for a random word: ");


        scanf(" %s", &a);

        if (strcmp(a, "exit") == 0) { // if a is "exit", quit game
            break;
        }

        // if a is 'r', find a random number using getRandom(char** theList, int length)
        if (strlen(a) == 1 && a[0] == "r") {
            strcpy(start,
                   getRandom(theList, length));

        // else if a is not of correct length, continue
        } else if (strlen(a) != length) {
            printf("'%s' is not of length %d. Please retry.\n\n", b, length);
            continue;
        }


        scanf(" %s", &b); // get second word

        // if b is 'r', find a random number using getRandom(char** theList, int length)
        if (strlen(b) == 1 && b[0] == "r") {
            strcpy(end, getRandom(theList, length));

        // else if b is not of correct length, continue
        } else if (strlen(b) != length) {
            printf("'%s' is not of length %d. Please retry.\n\n", b, length);
            continue;
        }


    }

}


int main()
{
    FILE *theFile = fopen("dictionary.txt", "r");

    int lenCounts[50] = {0};
    int lengthChosen;

    char** theList;
    char* start;
    char* end;

    int numWords;

    srand(time(1));



    if (!theFile) {
        printf("BAD FILE BAD BAD GIMME PARENT\n"); // screams for parent in case of error
        exit(-1);
    }

    printTopLengths(lenCounts);

    numWords = getNumWords(theFile, lenCounts);

    lengthChosen = promptUserForLen();

    theList = readWords(theFile, lenCounts, lengthChosen);

    declareWords(start, end, lengthChosen);

    getStartAndEnd(theList, start, end);


    fclose(theFile);

    return 0;
}









