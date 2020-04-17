#include <stdio.h>
#include <stdlib.h>
int main(int fileCount, char* fileName[]) {
	char* lineInput = (char*)malloc(0);
	int eofState;
	int appendState;
	FILE* tempFile;
	if (fileCount > 1) {
		printf("Editing the Following Files: ");
		for (int i = 1; i < fileCount; i++) {
			printf("%s ", fileName[i]);
		}
		for (int i = 1; i < fileCount; i++) {
			printf("\nEditing %s\n", fileName[i]);
			tempFile = fopen(".temp", "w+");
			eofState = 0;
			appendState = 0;
			do {
				scanf("%[^\n]%*c", lineInput);
				if (lineInput[0] == 'a' && lineInput[1] == '\0' && appendState == 0) {
					printf("Beginning Append\n");
					appendState = 1;
				}
				else if (lineInput[0] == '.' && lineInput[1] == '\0') {
					printf("\nFile Marked as EOF");
					eofState = 1;
				}
				else if (appendState == 0) {
					printf("Add a New Line with only \"a\" to Enter Append Mode\n");
					printf("Add a New Line with only \".\" to Mark File as EOF\n");
				}
				else if (appendState == 1) {
					fputs(lineInput, tempFile);
					fputs("\n", tempFile);
				}
			} while (eofState == 0);
			printf("\nWriting File\n");
			rename(".temp", fileName[i]);
			fclose(tempFile);
		}
	}
	else {
		printf("No Files Selected\n");
		printf("Please Re-run the Program with the Files You Want to Edit as Arguments\n");
	}
	free(lineInput);
}
