#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearConsole() {
    system("cls");
}

#define INITIAL_MAX_LINES 10
#define MAX_INPUT_LENGTH 128

void addText(char*** linesArray, size_t** lineSizes, int* currLine, int* maxLines) {
    char text[MAX_INPUT_LENGTH];
    printf("Enter text to append: ");
    if (fgets(text, MAX_INPUT_LENGTH, stdin) != NULL) {
        size_t lentext = strlen(text);
        if (lentext > 0 && text[lentext - 1] == '\n') {
            text[lentext - 1] = '\0';
            lentext--;
        }
        printf("You entered: %s\n", text);

        if ((*linesArray)[*currLine] == NULL) {
            (*linesArray)[*currLine] = (char*)malloc((lentext + 1) * sizeof(char));
            if ((*linesArray)[*currLine] == NULL) {
                printf("Memory allocation failed.\n");
                return;
            }
            strcpy_s((*linesArray)[*currLine], lentext + 1, text);
            (*lineSizes)[*currLine] = lentext + 1;
        }
        else {
            size_t lineArraylen = strlen((*linesArray)[*currLine]);
            (*lineSizes)[*currLine] += (lentext + 1);
            (*linesArray)[*currLine] = (char*)realloc((*linesArray)[*currLine], (*lineSizes)[*currLine] * sizeof(char));
            if ((*linesArray)[*currLine] == NULL) {
                printf("Memory reallocation failed.\n");
                return;
            }
            strcat_s((*linesArray)[*currLine], (*lineSizes)[*currLine], " ");
            strcat_s((*linesArray)[*currLine], (*lineSizes)[*currLine], text);
        }

        printf("Current line content: %s\n", (*linesArray)[*currLine]);
    }
    else {
        printf("Error reading input.\n");
    }
}

void newLine(char*** linesArray, size_t** lineSizes, int* currLine, int* maxLines) {
    (*currLine)++;
    if (*currLine >= *maxLines) {
        *maxLines *= 2;
        *linesArray = (char**)realloc(*linesArray, (*maxLines) * sizeof(char*));
        *lineSizes = (size_t*)realloc(*lineSizes, (*maxLines) * sizeof(size_t));
        if (*linesArray == NULL || *lineSizes == NULL) {
            printf("Memory reallocation failed.\n");
            exit(EXIT_FAILURE);
        }
        for (int i = *currLine; i < *maxLines; i++) {
            (*linesArray)[i] = NULL;
            (*lineSizes)[i] = 0;
        }
    }
    printf("New line is started\n");
}

void fileSave(char** linesArray, int currLine) {
    char fileName[MAX_INPUT_LENGTH];
    printf("Enter the file name for saving: ");
    if (fgets(fileName, MAX_INPUT_LENGTH, stdin) != NULL) {
        size_t len = strlen(fileName);
        if (len > 0 && fileName[len - 1] == '\n') {
            fileName[len - 1] = '\0';
        }

        FILE* file = NULL;
        errno_t err = fopen_s(&file, fileName, "w");
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

void fileLoad(char*** linesArray, size_t** lineSizes, int* currLine, int* maxLines) {
    char fileName[MAX_INPUT_LENGTH];
    printf("Enter the file name for loading: ");
    if (fgets(fileName, MAX_INPUT_LENGTH, stdin) != NULL) {
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

        char line[MAX_INPUT_LENGTH];
        int lineIndex = *currLine + 1;  // Start appending after the current line
        while (fgets(line, MAX_INPUT_LENGTH, file) != NULL) {
            len = strlen(line);
            if (len > 0 && line[len - 1] == '\n') {
                line[len - 1] = '\0';
                len--;
            }

            if (lineIndex >= *maxLines) {
                *maxLines *= 2;
                *linesArray = (char**)realloc(*linesArray, (*maxLines) * sizeof(char*));
                *lineSizes = (size_t*)realloc(*lineSizes, (*maxLines) * sizeof(size_t));
                if (*linesArray == NULL || *lineSizes == NULL) {
                    printf("Memory reallocation failed.\n");
                    fclose(file);
                    exit(EXIT_FAILURE);
                }
                // Initialize new lines and sizes
                for (int i = lineIndex; i < *maxLines; i++) {
                    (*linesArray)[i] = NULL;
                    (*lineSizes)[i] = 0;
                }
            }

            (*linesArray)[lineIndex] = (char*)malloc((len + 1) * sizeof(char));
            if ((*linesArray)[lineIndex] == NULL) {
                printf("Memory allocation failed.\n");
                fclose(file);
                return;
            }
            strcpy_s((*linesArray)[lineIndex], len + 1, line);
            (*lineSizes)[lineIndex] = len + 1;
            lineIndex++;
        }

        fclose(file);
        *currLine = lineIndex - 1;  // Update the current line to the last line appended
        printf("Text has been loaded successfully.\n");
    }
    else {
        printf("Error reading file name.\n");
    }
}


void outputAllText(char** linesArray, int currLine) {
    int hasContent = 0;
    printf("Here is all your lines which were written down: \n");
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

void addTextCoordinates(char*** linesArray, size_t** lineSizes, int maxLines) {
    int lineIndex, charIndex;
    char insertText[MAX_INPUT_LENGTH];

    printf("Choose line and index: ");
    if (scanf_s("%d %d", &lineIndex, &charIndex) != 2) {
        printf("Invalid input. Please enter line and index as two integers.\n");
        return;
    }
    getchar();

    if (lineIndex < 0 || lineIndex >= maxLines || (*linesArray)[lineIndex] == NULL) {
        printf("Invalid line index or line is empty.\n");
        return;
    }

    printf("Enter text to insert: ");
    if (fgets(insertText, MAX_INPUT_LENGTH, stdin) != NULL) {
        size_t lenInsertText = strlen(insertText);
        if (lenInsertText > 0 && insertText[lenInsertText - 1] == '\n') {
            insertText[lenInsertText - 1] = '\0';
            lenInsertText--;
        }

        size_t lineLen = strlen((*linesArray)[lineIndex]);

        if (charIndex < 0 || (size_t)charIndex > lineLen) {
            printf("Invalid character index.\n");
            return;
        }

        (*lineSizes)[lineIndex] += lenInsertText;
        (*linesArray)[lineIndex] = (char*)realloc((*linesArray)[lineIndex], (*lineSizes)[lineIndex] * sizeof(char));
        if ((*linesArray)[lineIndex] == NULL) {
            printf("Memory reallocation failed.\n");
            return;
        }

        memmove(&(*linesArray)[lineIndex][charIndex + lenInsertText], &(*linesArray)[lineIndex][charIndex], lineLen - charIndex + 1);
        memcpy(&(*linesArray)[lineIndex][charIndex], insertText, lenInsertText);

        printf("Text has been inserted successfully.\n");
        printf("Updated line content: %s\n", (*linesArray)[lineIndex]);
    }
    else {
        printf("Error reading input.\n");
    }
}

void searchWord(char** linesArray, int currLine) {
    char searchTerm[MAX_INPUT_LENGTH];
    printf("Enter text to search: ");
    if (fgets(searchTerm, MAX_INPUT_LENGTH, stdin) != NULL) {
        size_t len = strlen(searchTerm);
        if (len > 0 && searchTerm[len - 1] == '\n') {
            searchTerm[len - 1] = '\0';
            len--;
        }

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
            printf("Has not found your phrase.\n");
        }
        else {
            printf("\n");
        }
    }
    else {
        printf("Error reading search.\n");
    }
}

int main() {
    int maxLines = INITIAL_MAX_LINES;
    int currLine = 0;
    char** linesArray = (char**)malloc(maxLines * sizeof(char*));
    size_t* lineSizes = (size_t*)malloc(maxLines * sizeof(size_t));
    if (linesArray == NULL || lineSizes == NULL) {
        printf("Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < maxLines; i++) {
        linesArray[i] = NULL;
        lineSizes[i] = 0;
    }

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
            //clearConsole();
            addText(&linesArray, &lineSizes, &currLine, &maxLines);
            break;
        case 2:
            //clearConsole();
            newLine(&linesArray, &lineSizes, &currLine, &maxLines);
            break;
        case 3:
            //clearConsole();
            fileSave(linesArray, currLine);
            break;
        case 4:
            //clearConsole();
            fileLoad(&linesArray, &lineSizes, &currLine, &maxLines);
            break;
        case 5:
            //clearConsole();
            outputAllText(linesArray, currLine);
            break;
        case 6:
            //clearConsole();
            addTextCoordinates(&linesArray, &lineSizes, maxLines);
            break;
        case 7:
            //clearConsole();
            searchWord(linesArray, currLine);
            break;
        default:
            printf("Invalid choice, please try again.\n");
        }
    }

    // Free memory
    for (int i = 0; i < maxLines; i++) {
        free(linesArray[i]);
    }
    free(linesArray);
    free(lineSizes);

    return 0;
}
