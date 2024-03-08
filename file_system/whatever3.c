/* ANA Elena-Diana - 311CB */
/*  cd pwd find */
#include "structures.h"

int findfolder(Tarbfld a, char *name) {
	if (!a)
		return 0;
	if (strcmp(name, a->name) == 0)
		return 1;
	if (strcmp(name, a->name) < 0)
		return findfolder(a->left, name);
	return findfolder(a->right, name);
}

Tarbfld returnfolder(Tarbfld a, char *name) {
	if (strcmp(name, a->name) == 0) {
		return a;
	}
	if (strcmp(name, a->name) < 0)
		return returnfolder(a->left, name);
	return returnfolder(a->right, name);
}

Tarbfld cd(Tarbfld a, char *name) {
	if (strcmp(name, "..") == 0) {
		return a->parent;
	}

	if (findfolder(a->subfolders_root, name) == 0) {
		printf("Directory not found!\n");
		return a;
	}
	return returnfolder(a->subfolders_root, name);
}

void pwd(Tarbfld a) {
	if (strcmp(a->name, "root") != 0)
		pwd(a->parent);
	printf("/%s", a->name);
}