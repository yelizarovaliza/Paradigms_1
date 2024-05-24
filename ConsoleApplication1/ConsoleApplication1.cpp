#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearConsole() {
    system("cls");
}

#define MAXLENGTH 100
int currLine = 0;

void addText(char** linesArray, size_t* lineSizes) {
    char text[MAXLENGTH];
    printf("Enter text to append: ");
    if (fgets(text, MAXLENGTH, stdin) != NULL) {
        size_t lentext = strlen(text);
        if (lentext > 0 && text[lentext - 1] == '\n') {
            text[lentext - 1] = '\0';
            lentext--;
        }
        printf("You entered: %s\n", text);

        if (linesArray[currLine] == NULL) {
            linesArray[currLine] = (char*)malloc((lentext + 1) * sizeof(char));
            if (linesArray[currLine] == NULL) {
                printf("Memory allocation failed.\n");
                return;
            }
            strcpy_s(linesArray[currLine], lentext + 1, text);
            lineSizes[currLine] = lentext + 1;
        }
        else {
            size_t lineArraylen = strlen(linesArray[currLine]);
            lineSizes[currLine] += (lentext + 1);
            linesArray[currLine] = (char*)realloc(linesArray[currLine], lineSizes[currLine] * sizeof(char));
            if (linesArray[currLine] == NULL) {
                printf("Memory reallocation failed.\n");
                return;
            }
            strcat_s(linesArray[currLine], lineSizes[currLine], " ");
            strcat_s(linesArray[currLine], lineSizes[currLine], text);
        }

        printf("Current line content: %s\n", linesArray[currLine]);
    }
    else {
        printf("Error reading input.\n");
    }
}

void newLine(char** linesArray, size_t* lineSizes) {
    if (currLine < MAXLENGTH - 1) {
        currLine++;
        linesArray[currLine] = NULL;
        lineSizes[currLine] = 0;
        printf("New line is started\n");
    }
    else {
        printf("Maximum number of lines reached\n");
    }
}

void fileSave(char** linesArray, int currLine) {
    char fileName[MAXLENGTH];
    printf("Enter the file name for saving: ");
    if (fgets(fileName, MAXLENGTH, stdin) != NULL) {
        size_t len = strlen(fileName);
        if (len > 0 && fileName[len - 1] == '\n') {
            fileName[len - 1] = '\0';
        }

        FILE* file = NULL;
        errno_t err = fopen_s(&file, fileName, "a");
        if (err != 0 || file == NULL) {
            printf("Error opening file for writing.\n");
            return;
        }

        for (int i = 0; i <= currLine; i++) {
            if (linesArray[i] != NULL) {
                fprintf(file, "%s\n", linesArray[i]);
            }
        }

        fclose(file);
        printf("Text has been saved successfully.\n");
    }
    else {
        printf("Error reading file name.\n");
    }
}

void fileLoad(char** linesArray, size_t* lineSizes) {
    char fileName[MAXLENGTH];
    printf("Enter the file name for loading: ");
    if (fgets(fileName, MAXLENGTH, stdin) != NULL) {
        size_t len = strlen(fileName);
        if (len > 0 && fileName[len - 1] == '\n') {
            fileName[len - 1] = '\0';
        }

        FILE* file = NULL;
        errno_t err = fopen_s(&file, fileName, "r");
        if (err != 0 || file == NULL) {
            printf("Error opening file for reading.\n");
            return;
        }

        char line[MAXLENGTH];
        while (fgets(line, MAXLENGTH, file) != NULL && currLine < MAXLENGTH) {
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n') {
                line[len - 1] = '\0';
                len--;
            }

            linesArray[currLine] = (char*)malloc((len + 1) * sizeof(char));
            if (linesArray[currLine] == NULL) {
                printf("Memory allocation failed.\n");
                fclose(file);
                return;
            }
            strcpy_s(linesArray[currLine], len + 1, line);
            lineSizes[currLine] = len + 1;
            currLine++;
        }

        fclose(file);
        printf("Text has been loaded successfully.\n");
    }
    else {
        printf("Error reading file name.\n");
    }
}


void outputAllText(char** linesArray) {
    int hasContent = 0;
    printf("Here is all your lines which where written down: \n");
    for (int i = 0; i <= currLine; i++) {
        if (linesArray[i] != NULL && strlen(linesArray[i]) > 0) {
            
            printf("%s\n", linesArray[i]);
            hasContent = 1;
        }
    }

    if (!hasContent) {
        printf("No non-empty lines found.\n");
    }
}

void addTextCoordinates(char** linesArray, size_t* lineSizes) {
    int lineIndex, charIndex;
    char insertText[MAXLENGTH];

    printf("Choose line and index: ");
    if (scanf_s("%d %d", &lineIndex, &charIndex) != 2) {
        printf("Invalid input. Please enter line and index as two integers.\n");
        return;
    }
    getchar(); // clear the newline character left by scanf_s

    if (lineIndex < 0 || lineIndex >= MAXLENGTH || linesArray[lineIndex] == NULL) {
        printf("Invalid line index or line is empty.\n");
        return;
    }

    printf("Enter text to insert: ");
    if (fgets(insertText, MAXLENGTH, stdin) != NULL) {
        size_t lenInsertText = strlen(insertText);
        if (lenInsertText > 0 && insertText[lenInsertText - 1] == '\n') {
            insertText[lenInsertText - 1] = '\0';
            lenInsertText--;
        }

        size_t lineLen = strlen(linesArray[lineIndex]);

        if (charIndex < 0 || charIndex > lineLen) {
            printf("Invalid character index.\n");
            return;
        }

        lineSizes[lineIndex] += lenInsertText;
        linesArray[lineIndex] = (char*)realloc(linesArray[lineIndex], lineSizes[lineIndex] * sizeof(char));
        if (linesArray[lineIndex] == NULL) {
            printf("Memory reallocation failed.\n");
            return;
        }

        memmove(&linesArray[lineIndex][charIndex + lenInsertText], &linesArray[lineIndex][charIndex], lineLen - charIndex + 1);
        memcpy(&linesArray[lineIndex][charIndex], insertText, lenInsertText);

        printf("Text has been inserted successfully.\n");
        printf("Updated line content: %s\n", linesArray[lineIndex]);
    }
    else {
        printf("Error reading input.\n");
    }
}

void searchWord(char** linesArray, size_t* lineSizes) {
    char searchTerm[MAXLENGTH];
    printf("Enter text to search: ");
    if (fgets(searchTerm, MAXLENGTH, stdin) != NULL) {
        size_t len = strlen(searchTerm);
        if (len > 0 && searchTerm[len - 1] == '\n') {
            searchTerm[len - 1] = '\0';
            len--;
        }

        printf("Searching for: %s\n", searchTerm);
        int found = 0;

        for (int i = 0; i <= currLine; i++) {
            if (linesArray[i] != NULL) {
                char* pos = strstr(linesArray[i], searchTerm);
                while (pos != NULL) {
                    int index = (int)(pos - linesArray[i]);
                    if (found) {
                        printf(", ");
                    }
                    printf("%d %d", i, index);
                    found = 1;
                    pos = strstr(pos + 1, searchTerm);
                }
            }
        }

        if (!found) {
            printf("Text not found.\n");
        }
        else {
            printf("\n");
        }
    }
    else {
        printf("Error reading search term.\n");
    }
}



int main() {
    char* linesArray[MAXLENGTH] = { NULL };
    size_t lineSizes[MAXLENGTH] = { 0 };
    int userChoice = -1;
    while (userChoice != 0) {
        printf("Choose the command:\n");
        scanf_s("%d", &userChoice);
        getchar();

        switch (userChoice) {
        case 0:
            printf("Exiting program.\n");
            break;
        case 1:
            clearConsole();
            addText(linesArray, lineSizes);
            break;
        case 2:
            clearConsole();
            newLine(linesArray, lineSizes);
            break;
        case 3:
            clearConsole();
            fileSave(linesArray, currLine);
            break;
        case 4:
            clearConsole();
            fileLoad(linesArray, lineSizes);
            break;
        case 5:
            clearConsole();
            outputAllText(linesArray);
            break;
        case 6:
            clearConsole();
            addTextCoordinates(linesArray, lineSizes);
            break;
        case 7:
            clearConsole();
            searchWord(linesArray, lineSizes);
            break;
        default:
            printf("Invalid choice, please try again.\n");
        }
    }

    // Free memory
    for (int i = 0; i < MAXLENGTH; i++) {
        free(linesArray[i]);
    }

    return 0;
}
