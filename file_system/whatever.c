/* ANA Elena-Diana - 311CB */
/* touch mkdir ls */
#include "structures.h"

Tarbfile construct_file(char *name) {
	Tarbfile aux = (Tarbfile)malloc (sizeof(Tfile));
	if (!aux) {
		printf("Eroare alocare\n");
		return NULL;
	}

	aux->name = (char*)malloc (50);
	if (!aux->name) {
		printf("Eroare alocare\n");
		return NULL;
	}

	strcpy(aux->name, name); 
	//aux->parent = NULL;
	aux->left = aux->right = NULL;

	return aux;
}

int touch(Tarbfld *f, Tarbfile *a, char *name) {
	Tarbfile aux, p, n;
	Tarbfld fn;
	
	fn = (*f)->subfolders_root;
	while (fn){
		if (strcmp(name, fn->name) == 0) {
			printf("Directory %s already exists!\n", name);
			return 0;
		}
		if (strcmp(name, fn->name) < 0 )
			fn = fn->left;
		else	
			fn = fn->right;
	}

	if (*a == NULL) {
		*a = construct_file(name);
		if (!*a) 
			return 0;
		(*a)->parent = (*f);
		return 1;
	}

	n = *a;
	while (n){
		p = n;
		if (strcmp(name, n->name) == 0) {
			printf("File %s already exists!\n", name);
			return 0;
		}
		if (strcmp(name, n->name) < 0 )
			n = n->left;
		else	
			n = n->right;
	}

	aux = construct_file(name);
	if(!aux)
		return 0;

	// parent directory
	aux->parent = (*f);
	
	if(strcmp(name, p->name) < 0)
		p->left = aux;
	else	
		p->right = aux;

	return 1;
}

Tarbfld construct_folder(char *name) {
	Tarbfld aux = (Tarbfld)malloc (sizeof(Tfolder));
	if (!aux) {
		printf("Eroare alocare\n");
		return NULL;
	}

	aux->name = (char*)malloc (50);
	if (!aux->name) {
		printf("Eroare alocare\n");
		return NULL;
	}

	strcpy(aux->name, name); 
	//aux->parent = NULL;
	aux->subfolders_root = NULL;
	aux->files_root = NULL;
	aux->left = aux->right = NULL;

	return aux;
}	

int mkdir(Tarbfld *f, Tarbfld *a, char *name) {
	Tarbfld aux, p, n;
	Tarbfile fn;

	fn = (*f)->files_root;
	while (fn){
		if (strcmp(name, fn->name) == 0) {
			printf("File %s already exists!\n", name);
			return 0;
		}
		if (strcmp(name, fn->name) < 0 )
			fn = fn->left;
		else	
			fn = fn->right;
	}

	if (*a == NULL) {	
		*a = construct_folder(name);
		if (!*a) 
			return 0;
		(*a)->parent = (*f);
		return 1;
	}

	n = *a;
	while (n){
		p = n;
		if (strcmp(name, n->name) == 0) {
			printf("Directory %s already exists!\n", name);
			return 0;
		}
		if (strcmp(name, n->name) < 0 )
			n = n->left;
		else	
			n = n->right;
	}

	aux = construct_folder(name);
	if(!aux)
		return 0;
	
	// parent directory
	aux->parent = (*f);
	
	if(strcmp(name, p->name) < 0)
		p->left = aux;
	else	
		p->right = aux;

	return 1;
}

void SRD_files(Tarbfile a) {
	if (!a)
		return;
	SRD_files(a->left);
	printf("%s ", a->name);
	SRD_files(a->right);
}

void SRD_folders(Tarbfld a) {
	if (!a)
		return;
	SRD_folders(a->left);
	printf("%s ", a->name);
	SRD_folders(a->right);
}

void ls(Tarbfile afile, Tarbfld afld) {
	SRD_folders(afld);
	SRD_files(afile);
	printf("\n");
}
