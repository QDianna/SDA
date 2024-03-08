/* ANA Elena-Diana - 311CB */
#include "structures.h"

int main() {
	Tarbfld arbfld = NULL;
	arbfld = construct_folder("root");

	char *instruction = NULL;
	size_t instrlen = 0;
	getline(&instruction, &instrlen, stdin);

	while (strcmp("quit", instruction)) {
		char *word1 = strtok(instruction, " \n");
	
		if(!strcmp(word1, "touch")) {
			char *word2 = strtok(NULL, " \n");
			// word2 = filename
			touch(&arbfld, &arbfld->files_root, word2);
		}

		if(!strcmp(word1, "mkdir")) {
			char *word2 = strtok(NULL, " \n");
			// word2 = foldername
			//printf("Dir: %s parent: %s\n", word2, arbfld->name);  // debugg
			mkdir(&arbfld, &arbfld->subfolders_root, word2);
		}

		if(!strcmp(word1, "ls")) {
			ls(arbfld->files_root, arbfld->subfolders_root);
		}

		if(!strcmp(word1, "rm")) {
			char *word2 = strtok(NULL, " \n");
			// word2 = filename
			arbfld->files_root = rm(&arbfld->files_root, word2);
		}

		if(!strcmp(word1, "rmdir")) {
			char *word2 = strtok(NULL, " \n");
			// word2 = foldername
			arbfld->subfolders_root = rmdir(&arbfld->subfolders_root, word2);
		}

		if(!strcmp(word1, "cd")) {
			char *word2 = strtok(NULL, " \n");
			// word2 = foldername
			arbfld = cd(arbfld, word2);
		}

		if(!strcmp(word1, "pwd")) {
			pwd(arbfld);
			printf("\n");
		}

		if(!strcmp(word1, "find")) {
			//char *word2 = strtok(NULL, " \n");
			// word2 = -f/-d
			//char *word3 = strtok(NULL, " \n");
			// word3 = filename/foldername

		}
		getline(&instruction, &instrlen, stdin);
	}
	return 0;
}