/* ANA Elena-Diana - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct folder {
	char *name;
	struct folder *parent; 			   // directorul de care apartine
	struct folder *subfolders_root;    // radacina arborelui de subdirectoare
	struct file *files_root; 				   // radacina arborelui de fisiere
	struct folder *left, *right;
} Tfolder, *Tarbfld, **Aarbfld;

typedef struct file {
	char *name;
	Tfolder *parent;					// directorul de care apartine
	struct file *left, *right;
} Tfile, *Tarbfile, **Aarbfile;

Tarbfile construct_file(char *name);
int touch(Tarbfld *f, Tarbfile *a, char *name);

Tarbfld construct_folder(char *name);
int mkdir(Tarbfld *f, Tarbfld *a, char *name);

void ls(Tarbfile afile, Tarbfld afld);

void SRD_files(Tarbfile a);
void SRD_folders(Tarbfld a);

Tarbfile minimfile(Tarbfile *a);
Tarbfile rm(Tarbfile *a, char *name);

Tarbfld minimfld(Tarbfld *a);
Tarbfld rmdir(Tarbfld *a, char *name);

int findfolder(Tarbfld a, char *name);
Tarbfld returnfolder(Tarbfld a, char *name);
Tarbfld cd(Tarbfld a, char *name);

void pwd(Tarbfld a);