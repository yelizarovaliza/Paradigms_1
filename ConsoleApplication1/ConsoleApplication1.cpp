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

        // Free previously memory
        for (int i = 0; i < MAXLENGTH; i++) {
            free(linesArray[i]);
            linesArray[i] = NULL;
            lineSizes[i] = 0;
        }

        currLine = 0;
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
            printf("Here might be text from file: ");
            break;
        case 6:
            clearConsole();
            printf("Choose line and index: ");
            break;
        case 7:
            clearConsole();
            printf("Enter text to search: ");
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
