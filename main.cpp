#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

using namespace std;


typedef struct Node {
    char* word;
    int parentIndex;
} Node_struct;


bool inDict(char* word, char** dict, int dictSize) {
    //printf("Looking for word: %s\n", word);
    for (int i = 0; i < dictSize; ++i) {
        //printf("Checking word: %s of length: %d\n", dict[i], strlen(dict[i]));
        if (strcmp(word, dict[i]) == 0) {
            printf("Word %s found!\n", word);
            return true;
        }
    }

    return false;
}

char* getRandomWord(char** theList, int listLen) {
    char word[50];

    int randIndex = (rand() % (listLen));

    strcpy(word, theList[randIndex]);

    return word;

}

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

    printf("Total number of words parsed: %d\n", wordCount);


    return wordCount;
}

char** readWords(FILE* theFile, int lenCounts[50], int lengthChosen, int *numWords) {

    *numWords = lenCounts[lengthChosen];

    printf("Number of words of length %d: %d\n", lengthChosen, *numWords);

    char** theList = NULL;
    int i = 0;
    int currentWordLength;
    theList = (char**) malloc(sizeof(char*)*(*numWords));
    char* toAdd = NULL;
    char currentWord[50];



    while (!feof(theFile) && i < *numWords) {
        fgets(currentWord, *numWords, theFile);
        currentWordLength = strlen(currentWord);
        if (currentWord[currentWordLength-1] == '\n') { // remove trailing newline character
            currentWord[currentWordLength-1] = NULL;
        }

        if (strlen(currentWord) == lengthChosen) {
            toAdd = (char*) malloc(sizeof(char) * (lengthChosen+1));

            for (int j = 0; j < lengthChosen; ++j) { // convert word to be copied into lowercase
                currentWord[j] = tolower(currentWord[j]);
            }

            strcpy(toAdd,currentWord);



            theList[i] = toAdd;
            if (theList[i][0] < 97) { // check if copied word is uppercase
                printf("\nUh oh! Upper case word found!\n#%d Word: %s\n\n", i+1, theList[i]);
            }
            i++;
        }
    }

    printf("Number of words read was %d.\n\n", *numWords);


    return theList;
}

int promptUserForLen() {
    int length;

    printf("What length words do you want to use? ");
    scanf(" %d", &length);

    return length;
}

/*
void declareWords(char* start, char* end, int length) {
    start = end = NULL;
    start = (char*) malloc(sizeof(char) * (length+1));
    end = (char*) malloc(sizeof(char) * (length+1));

    return;
}
*/

void getStartAndEnd(char** theList, char* start, char* end, int wordLength, int listLength) {

    bool go = false;
    char *a = NULL;
    char *b = NULL;
    a = (char*) malloc(sizeof(char) * (wordLength+1));
    b = (char*) malloc(sizeof(char) * (wordLength+1));

    while (!go) {

        printf("Enter starting and ending words, or 'r' for either for a random word: ");

        scanf(" %s", a);
        scanf(" %s", b); // get second word

        printf("Word lengths: %d and %d\n", strlen(a), strlen(b));


        if (strcmp(a, "exit") == 0) { // if a is "exit", quit game
            printf("Quitting game...\n");
            break;
        } else {
            printf("First word is: %s\n", a);
            printf("Second word is: %s\n", b);
        }

        // if a is 'r', find a random number using getRandomWord(char** theList, int length)
        if (strlen(a) == 1 && a[0] == 'r') {
            printf("Finding random word...\n");
            strcpy(start,
                   getRandomWord(theList, wordLength));

        // else if a is not of correct length, continue
        } else if (strlen(a) != wordLength) {
            printf("'%s' is not of length %d. Please retry.\n\n", b, wordLength);
            continue;

        // if word not in dictionary, inform user and continue
        } else if (!inDict(a,theList,listLength)) {
            printf("'%s' is not in the dictionary. Please retry.\n\n", a);
            continue;
        // if all tests passed, copy a to start
        } else {
            strcpy(start, a);
        }

        printf("Finished parsing starting word: %s.\n", start);



        // if b is 'r', find a random number using getRandomWord(char** theList, int length)
        if (strlen(b) == 1 && b[0] == 'r') {
            strcpy(end, getRandomWord(theList, listLength));
            go = true;

        // else if b is not of correct length, continue
        } else if (strlen(b) != wordLength) {
            printf("'%s' is not of length %d. Please retry.\n\n", b, wordLength);
            continue;

        // if word not in dictionary, inform user and continue
        } else if (!inDict(b, theList, listLength)) {
            printf("'%s' is not in the dictionary. Please retry.\n\n", b);
            continue;
        // if all tests passed, copy b to end
        } else {
            strcpy(end, b);
            go = true;
        }

        printf("Finished parsing ending word: %s.\n", end);

    }

}

bool isOneCharDifferent(char* a, char *b) {
    int counter = 0;

    for (int i = 0; i < strlen(a); ++i) {
        if (a[i] != b[i]) {
            ++counter;
        }
    }

    if (counter == 1) {
        return true;
    }

    return false;
}

void theGame(char** theList, char* start, char* end, int numWords) {

    bool win = false;
    int turn = 1;
    char* input;
    input = (char*) malloc(sizeof(char) * (strlen(start)+1));

    printf("Morphing from %s to %s.\n\n", start, end);

    printf("On each move enter a word of the same length that is at\n");
    printf("most 1 character different and is also in the dictionary,\n");
    printf("or type in 'exit' to exit the interactive portion of the program.\n\n");

    while(!win) {
        printf("Previous word is '%s'.  Next word: ", start);
        scanf(" %s", input);

        if (strcmp(input, "exit") == 0) {
            break;
        } else if (strlen(input) != strlen(start)) {
            printf("Word %s is not length %d. Please try again.\n", input, strlen(start));
            continue;
        } else if (!isOneCharDifferent(start,input)) {
            printf("New word must be exactly 1 character different.  Please try again.\n");
            continue;
        } else if (!inDict(input,theList,numWords)) {
            printf("New word must be in dictionary. Please try again.\n");
            continue;
        } else if (strcmp(input,end) == 0) {
            printf("\nCongratulations, you won!\n\n");
            win = true;
            break;
        }

        strcpy(start, input);
        ++turn;
    }

    return;
}
/*
Node* addNode(Node** parent, int wordIndex) {
    Node * next = (Node*) malloc(sizeof(Node));

    if (parent->head != NULL) {
        next->head = parent->head;
    }

    parent->next = next;
    next->prev = parent;
    next->wordIndex = wordIndex;
    next->next = NULL;

    return next;
}
*/

bool isInTree(Node* tree, int index) {
    printf("Guessing... %d\n", index);
    for (Node* ptr = tree; ptr != NULL; ptr = ptr->prev) {
        if (ptr->wordIndex == index) {
            return true;
        } else {
            printf("Index %d has not been guessed!\n", ptr->wordIndex);
        }
    }
    return false;
}

int* findSolution(Node nodeList[], char** theList, char* end, int numWords, int goalIndex) {
    int currentWord = 0;
    int nodeIndex = 0;
    int dictIndex = 0;
    bool done = false;

    while (dictIndex != goalIndex) {


    }
}

/*void findSolution(Node** currentNode, char** theList, char* end, int numWords, int guessCounts[], int goalIndex) {


    if ((*currentNode)->wordIndex == goalIndex) {
        printf("Goal index: %d, currentNode index: %d\n",goalIndex,(*currentNode)->wordIndex);
        return;
    } else {
        for (int i = 0; i < numWords; ++i) {
            if (isOneCharDifferent(theList[(*currentNode)->wordIndex],theList[i])
                    && guessCounts[i] == 0) {
                guessCounts[i]++;

                findSolution(&addNode(currentNode,i), theList, end, numWords, guessCounts, goalIndex);
            }
        }
    }
}

int findWordIndex(char** theList, char* word, int numWords) {
    for (int i = 0; i < numWords; ++i) {
        if (strcmp(theList[i], word) == 0) {
            return i;
        }
    }

    return 0;
}

void readTree(Node* top, char** theList) {
    for (Node* ptr = top; ptr->next != NULL; ptr = ptr->next) {
        printf("#%d. %s\n", ptr->wordIndex, theList[ptr->wordIndex]);
    }
}
*/

int main()
{
    FILE *theFile = fopen("dictionary.txt", "r");


    int lenCounts[50] = {0};
    int lengthChosen;

    char** theList;
    char* start = NULL;
    char* end = NULL;

    int numWords;

    srand(time(0));




    if (!theFile) {
        printf("BAD FILE BAD BAD GIMME PARENT\n"); // screams for parent in case of error
        exit(-1);
    }


    getNumWords(theFile, lenCounts);

    printTopLengths(lenCounts);

    lengthChosen = promptUserForLen();

    theList = readWords(theFile, lenCounts, lengthChosen, &numWords);

//    declareWords(start, end, lengthChosen); // failed attempt at allocating memory for start/end words

    // declare start and end words (using this instead of declareWords() function)
    start = (char*) malloc(sizeof(char) * (lengthChosen+1));
    end = (char*) malloc(sizeof(char) * (lengthChosen+1));

    getStartAndEnd(theList, start, end, lengthChosen, numWords);


    //Start node search

    Node* wordTree = (Node*) malloc(sizeof(Node)*numWords);
    for (int i = 0; i < numWords; ++i) {
        wordTree[i].word = (char*) malloc( sizeof( char) * (lengthChosen+1));
        wordTree[i].parentIndex = 0;
    }
    strcpy(wordTree[0].word, start);

    int goalIndex = findWordIndex(theList, end, numWords);
    printf("Word to search for:\nWord index: %d ... word: %s\n", findWordIndex(theList, end, numWords), theList[findWordIndex(theList, end, numWords)]);

    findSolution(wordTree, theList, end, numWords, goalIndex);

    getSolution(wordTree, numWords);


//    theGame(theList, start, end, numWords);
    if (wordTree != NULL) {
        readTree(wordTree, theList);
    } else {
        printf("No winning path found!\n");
    }


    fclose(theFile);

    return 0;
}









