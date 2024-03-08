/* ANA Elena-Diana - 311CB */
/*  rm rmdir */
#include "structures.h"

Tarbfile minimfile(Tarbfile *a) {
    Tarbfile p = (*a);
    while (p && p->left)
        p = p->left;
    return p;
}

Tarbfile rm(Tarbfile *a, char *name) {
    if ((*a) == NULL) {
    	printf("File %s doesn't exist!\n", name);
        return (*a);
    }

    int ok = 0;  // if file exists ok becomes 1	
    Tarbfile p = (*a);
    while (p){
		if (strcmp(name, p->name) == 0) {
			ok = 1;
			break;
		}
		if (strcmp(name, p->name) < 0 )
			p = p->left;
		else	
			p = p->right;
	}

	if (!ok) {
		printf("File %s doesn't exist!\n", name);
        return (*a);
	}

    if (strcmp(name, (*a)->name) < 0)
        (*a)->left = rm(&(*a)->left, name);
    else 
    	if (strcmp(name, (*a)->name) > 0)
        	(*a)->right = rm(&(*a)->right, name);
    	else {
        	// nod cu 0/1 frunze
        	if ((*a)->left == NULL) {
           		Tarbfile p = (*a)->right;
           		free((*a)->name);
            	free(*a);
            	return p;
        	}
       		else 
       			if ((*a)->right == NULL) {
            		Tarbfile p = (*a)->left;
            		free((*a)->name);
            		free(*a);
            		return p;
        		}
 
        	// nod cu 2 frunze
        	Tarbfile p = minimfile(&(*a)->right);
        	strcpy((*a)->name, p->name); 
	        (*a)->right = rm(&(*a)->right, p->name);
    	}
    return (*a);
}

Tarbfld minimfld(Tarbfld *a) {
    Tarbfld p = (*a);
    while (p && p->left)
        p = p->left;
    return p;
}

Tarbfld rmdir(Tarbfld *a, char *name) {
    if (*a == NULL) {
    	printf("Directory %s doesn't exist!\n", name);
        return (*a);
    }

    int ok = 0;  // if folder exists ok becomes 1	
    Tarbfld p = *a;
    while (p){
		if (strcmp(name, p->name) == 0) {
			ok = 1;
			break;
		}
		if (strcmp(name, p->name) < 0 )
			p = p->left;
		else	
			p = p->right;
	}

	if (!ok) {
		printf("Directory %s doesn't exist!\n", name);
        return (*a);
	}

    if (strcmp(name, (*a)->name) < 0)
        (*a)->left = rmdir(&(*a)->left, name);
    else 
    	if (strcmp(name, (*a)->name) > 0)
        	(*a)->right = rmdir(&(*a)->right, name);
    	else {
        	// node with only one child or no child
        	if ((*a)->left == NULL) {
           		Tarbfld p = (*a)->right;
           		free((*a)->name);
           		free((*a)->subfolders_root);
           		free((*a)->files_root);
            	free(*a);
            	return p;
        	}
       		else 
       			if ((*a)->right == NULL) {
            		Tarbfld p = (*a)->left;
            		free((*a)->name);
            		free((*a)->subfolders_root);
           			free((*a)->files_root);
            		free(*a);
            		return p;
        		}
 
        	// node with two children:
        	Tarbfld p = minimfld(&(*a)->right);
        	strcpy((*a)->name, p->name);
        	(*a)->subfolders_root = p->subfolders_root;
        	(*a)->files_root = p->files_root;
	        (*a)->right = rmdir(&(*a)->right, p->name);
    	}
    return (*a);
}