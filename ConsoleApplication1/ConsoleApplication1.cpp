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
        }
        printf("You entered: %s\n", text);

        // Додаємо введений текст до першого рядка масиву
        if (linesArray[0] == NULL) {
            linesArray[0] = (char*)malloc((lentext + 1) * sizeof(char));
            if (linesArray[0] == NULL) {
                printf("Memory allocation failed.\n");
                return;
            }
            strcpy_s(linesArray[0], lentext + 1, text);
            lineSizes[0] = lentext + 1;
        }
        else {
            size_t lineArraylen = strlen(linesArray[0]);
            lineSizes[0] += lentext;
            linesArray[0] = (char*)realloc(linesArray[0], lineSizes[0] * sizeof(char));
            if (linesArray[0] == NULL) {
                printf("Memory reallocation failed.\n");
                return;
            }
            strcat_s(linesArray[0], lineSizes[0] + 1, " ");
            strcat_s(linesArray[0], lineSizes[0], text );
        }

        printf("Current line content: %s\n", linesArray[0]);
    }
    else {
        printf("Error reading input.\n");
    }
}

void newLine(){

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
            newLine();0
            printf("New line is started\n");
            break;
        case 3:
            clearConsole();
            printf("Enter the file name for saving: ");
            break;
        case 4:
            clearConsole();
            printf("Enter the file name for loading: ");
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

    // Звільняємо виділену пам'ять
    for (int i = 0; i < MAXLENGTH; i++) {
        free(linesArray[i]);
    }

    return 0;
}
