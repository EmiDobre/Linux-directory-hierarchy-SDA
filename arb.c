//DOBRE EMILIA ILIANA 315CB

#include "terminal.h"

TArbFile CreateNodFile(char* name, TArbFile left, TArbFile right) {
	TArbFile aux = (TArbFile)calloc(1, sizeof(TOneFile));
	if (!aux) return NULL;
    aux->name =  calloc(51, sizeof(char));
    if ( !aux->name ) return NULL;
    memcpy(aux->name, name, strlen(name));
    aux->left = left;
    aux->right = right;
	return aux;                              //adresa nodului
}


void DistrNodeFile(TArbFile a) { //distruge nodurile arborelui de la adresa a
	if (!a) return;
	DistrNodeFile (a->left);
	DistrNodeFile (a->right);
	free (a);             
}

void DistrArb(TArbFile *a) {
	if (!(*a)) return;       
	DistrNodeFile (*a);
	*a = NULL;
}


TArbFile CreateLeafFile(char* name, TDirectory parent) {
	TArbFile aux = (TArbFile)calloc (1, sizeof(TOneFile));
	if ( !aux ) return NULL;

	aux->name =  calloc(51, sizeof(char));
    if ( !aux->name ) return NULL;
    
    memcpy(aux->name, name, strlen(name));

    aux->parent_dir = LeafDir(parent->name, NULL);
    memcpy(aux->parent_dir, parent, sizeof(TOneDir));

	return aux;
}


TArbFile InsertFile(TArbFile arb, char* name, TDirectory parent ) {
    if ( arb == NULL )  return CreateLeafFile(name, parent);

    if ( strcmp(arb->name, name) < 0 ) 
        arb->right = InsertFile(arb->right, name, parent);
    
    if ( strcmp(arb->name, name) > 0 )
        arb->left = InsertFile(arb->left, name, parent);

    return arb;
}


void RSD(TArbFile a) /*- afiseaza arborele r -*/
{
	if(!a) {printf("-"); return;}
	if(!a->left && !a->right) {
        printf(" %s ", a->name); 
        //printf("-par: %s ", a->parent_dir->name); 
        return;
    }
	printf(" %s ", a->name); //printf("-par: %s ", a->parent_dir->name);
	printf("(LEFT:");
	RSD(a->left);
	printf(",RIGHT:");
	RSD(a->right);
	printf(")");
}


void SRD(void* arb, char tip) {
    if ( tip == 'f' ) {
        TArbFile a = (TArbFile)arb; 
        if ( a != NULL ) {
            SRD(a->left, 'f');
            printf("%s ", a->name);
            //printf("-parinte: %s ", a->parent_dir->name);
            SRD(a->right, 'f');  //pot sa am frunza pe dreapta ultimului nod de stanga
        }
    }

    if ( tip == 'd' ) {
        TDirectory a = (TDirectory)arb; 
        if ( a != NULL ) {
            SRD(a->left, 'd');
            printf("%s ", a->name);
            SRD(a->right, 'd');  //pot sa am frunza pe dreapta ultimului nod de stanga
        }
    }
}

//pt director:

//alloc 
//aloc director, fara subdirectorul necesar, bag doar fisierele in dir curent
//frunza pt director + alocare

TDirectory LeafDir ( char* name, TDirectory parent) {
    TDirectory aux = (TDirectory)calloc (1, sizeof(TOneDir));
    if ( !aux ) return NULL;

	aux->name =  calloc(51, sizeof(char));
    if ( !aux->name ) return NULL;
    if ( name != NULL )
        memcpy(aux->name, name, strlen(name));

    aux->parent = parent;

    aux->files = (TArbFile)calloc (1, sizeof(TOneFile));
    aux->files->name = calloc(51, sizeof(char));
    aux->files = NULL;

    return aux;
}

TDirectory InsertInSubdir (TDirectory sub, char* name, TDirectory parent) {
    if ( sub == NULL ) {
        return LeafDir( name, parent);
    }

    if ( strcmp(sub->name, name) < 0 )
        sub->right = InsertInSubdir(sub->right, name, parent);
    
    if ( strcmp(sub->name, name) > 0 )
        sub->left = InsertInSubdir(sub->left, name, parent);
    
    return sub;
}


//fct care parcurge tot arborele director dat ca param=>folosita pt 
//cautarea directoarelor pt a nu exista vreunul cu acel nume

TDirectory SearchDir(TDirectory subdir, char* name) {
    if ( subdir == NULL ) 
        return NULL;

    if ( strcmp(subdir->name, name) < 0 )
        return SearchDir(subdir->right, name);

    if ( strcmp(subdir->name, name) > 0 ) 
        return SearchDir(subdir->left, name);

    if ( strcmp(subdir->name, name) == 0 ) 
        return subdir;
}

TArbFile SearchFile(TArbFile files, char* name ) {
    if ( files == NULL ) 
        return NULL;
    
    if ( strcmp(files->name, name) < 0 )
        return SearchFile(files->right, name);

    if ( strcmp(files->name, name) > 0 ) 
        return SearchFile(files->left, name);

    if ( strcmp(files->name, name) == 0 )
        return files;
}


//stergere fisier din arbore fis

//afla minmul dintr-un arbore, folsoit pt a afla minimul dintr un subrarbore de fisiere
//pt stergerea unui nod cu 2 copii care pot fi frunze sau subarbori
TArbFile MinimFile(TArbFile subfiles) {
    TArbFile minim = subfiles;
    while ( minim != NULL && minim->left != NULL )
        minim = minim->left;
    return minim;
}

//caut elementul de sters si ii aflu parintele
TArbFile DeleteFile(TArbFile files, char* name ) {
    TArbFile delete = SearchFile(files, name);

/*    printf("    Sterg %s\n",delete->name);
    printf("    IERARHIA ESTE ACUM: ");
    RSD(files);
    printf("\n");
*/
    TArbFile parent = ParentFile(files, name);
  
    /*if ( files == NULL ) printf("   OPA\n");
    if ( parent != NULL)
        printf("    parintele este %s:\n\n", parent->name);
    else
        printf("    este root\n\n");
    */


    //daca am radacina care are maxim 1 copil
    if ( parent == NULL && (delete->left == NULL || delete->right == NULL) ) {
        //printf("    aici\n");
        if ( delete->left == NULL && delete->right == NULL ) {
            delete = NULL;
            //printf("    radacina a devenit NULL\n");
            return delete;
        }

        if( delete->left != NULL && delete->right == NULL ) {
            delete = delete->left;
            return delete;
        }

        if ( delete->left == NULL && delete->right != NULL ) {
            delete = delete->right;
            return delete;
        }
    }

    //daca e frunza
    //aflu unde ce copil e pt parinte=>stang/drept 
    if ( delete->left == NULL && delete->right == NULL) {
        if ( parent->left == delete ) {
            parent->left = NULL;
            return files;
        }

        if ( parent->right == delete ) {
            parent->right = NULL;
            return files;
        }
    }

    //daca are doar un copil
    if ( delete->left == NULL && delete->right != NULL && parent != NULL ) {
        if ( parent->left == delete )
            parent->left = delete->right;
        if ( parent->right == delete )
            parent->right = delete->right;
        //printf("    doar un copil\n");
        return files;
    }

    if ( delete->left != NULL && delete->right == NULL && parent != NULL ) {
        if ( parent->left == delete )
            parent->left = delete->left;
        if ( parent->right == delete )
            parent->right = delete->left;
        //printf("    doar un copil\n");
        return files;
    }

    //daca are 2 copii
    //nodul se inlocuieste cu minimul din subarborele drept si apoi se elimina 
    //acest minim din subarborele drept prin functia delete
    if ( (delete->left != NULL) && (delete->right != NULL) ) {
        TArbFile minim = MinimFile(delete->right);
        //printf("    noua radacina va fi: %s\n", minim->name);
        memcpy(delete->name, minim->name, strlen(minim->name));
        delete->right = DeleteFile(delete->right, minim->name);

        /*printf("    -subarb drept: ");
        RSD(delete->right);
        printf("\n");
        printf("    delete-cat trebuie:");
        RSD(delete);
        printf("\n");
        */
    }
    
    return files;
}


//afla parintele elementului dat ca parametru, stiu ca exista elem
TArbFile ParentFile(TArbFile files, char* name) {
    if ( files == NULL ) 
        return NULL;
    
    TArbFile parent = NULL;
    while ( files != NULL ) {
        if ( strcmp(files->name, name) < 0 ) {
            parent = files;
            files = files->right;
        } else if ( strcmp(files->name, name) > 0 ) {
            parent = files;
            files = files->left;
        } else {
            break;
        }
    }
    return parent;
}


//rmdir:
void RSD_dir(TDirectory a) /*- afiseaza arborele r -*/
{
	if(!a) {printf("-"); return;}
	if(!a->left && !a->right) {
        printf(" %s ", a->name); 
        //printf("-par: %s ", a->parent_dir->name); 
        return;
    }
	printf(" %s ", a->name); //printf("-par: %s ", a->parent_dir->name);
	printf("(LEFT:");
	RSD_dir(a->left);
	printf(",RIGHT:");
	RSD_dir(a->right);
	printf(")");
}

TDirectory MinimDirectoy(TDirectory subdir) {
    TDirectory minim = subdir;
    while ( minim != NULL && minim->left != NULL )
        minim = minim->left;
    return minim;
}
//afla parintele in  ierarhia in care se afla
TDirectory ParentDir(TDirectory subdir, char* name) {
    if ( subdir == NULL ) 
        return NULL;
    
    TDirectory parent = NULL;
    while ( subdir != NULL ) {
        if ( strcmp(subdir->name, name) < 0 ) {
            parent = subdir;
            subdir = subdir->right;
        } else if ( strcmp(subdir->name, name) > 0 ) {
            parent = subdir;
            subdir = subdir->left;
        } else {
            break;
        }
    }
    return parent;
}

//de verificat daca delete are campul de subdirectoare sau files goale
//pt ca ele se sterg prima data si apoi el

TDirectory DeleteDir(TDirectory subdir, char* name ) {
    TDirectory delete = SearchDir (subdir, name);

/*    printf("    Sterg %s\n",delete->name);
    printf("    IERARHIA ESTE ACUM: ");
    RSD_dir(subdir);
    printf("\n");
*/

    //daca directorul are fisiere sau subdirectoare le sterg pe ele prima data
    if ( delete->files != NULL ) {
        while ( delete->files != NULL ) {
            delete->files = DeleteFile(delete->files, delete->files->name);
        }
    }

    if ( delete->current_subdir != NULL ) {
        while ( delete->current_subdir != NULL ) {
            delete->current_subdir = DeleteDir(delete->current_subdir, delete->current_subdir->name);
        }
    }

    TDirectory parent = ParentDir(subdir, name);
  
/*    if ( subdir == NULL ) printf("   OPA\n");
    if ( parent != NULL)
        printf("    parintele este %s:\n\n", parent->name);
    else
        printf("    este root\n\n");
*/   


    //daca am radacina care are maxim 1 copil
    if ( parent == NULL && (delete->left == NULL || delete->right == NULL) ) {
        //printf("    aici\n");
        if ( delete->left == NULL && delete->right == NULL ) {
            delete = NULL;
            //printf("    radacina a devenit NULL\n");
            return delete;
        }

        if( delete->left != NULL && delete->right == NULL ) {
            delete = delete->left;
            return delete;
        }

        if ( delete->left == NULL && delete->right != NULL ) {
            delete = delete->right;
            return delete;
        }
    }

    //daca e frunza
    //aflu unde ce copil e pt parinte=>stang/drept 
    if ( delete->left == NULL && delete->right == NULL) {
        if ( parent->left == delete ) {
            parent->left = NULL;
            return subdir;
        }

        if ( parent->right == delete ) {
            parent->right = NULL;
            return subdir;
        }
    }

    //daca are doar un copil
    if ( delete->left == NULL && delete->right != NULL && parent != NULL ) {
        if ( parent->left == delete )
            parent->left = delete->right;
        if ( parent->right == delete )
            parent->right = delete->right;
        //printf("    doar un copil\n");
        return subdir;
    }

    if ( delete->left != NULL && delete->right == NULL && parent != NULL ) {
        if ( parent->left == delete )
            parent->left = delete->left;
        if ( parent->right == delete )
            parent->right = delete->left;
        //printf("    doar un copil\n");
        return subdir;
    }

    //daca are 2 copii
    //nodul se inlocuieste cu minimul din subarborele drept si apoi se elimina 
    //acest minim din subarborele drept prin functia delete
    if ( (delete->left != NULL) && (delete->right != NULL) ) {
        TDirectory minim = MinimDirectoy(delete->right);
        //printf("    noua radacina va fi: %s\n", minim->name);
        memcpy(delete->name, minim->name, strlen(minim->name));
        delete->right = DeleteDir(delete->right, minim->name);

/*        printf("    -subarb drept: ");
        RSD_dir(delete->right);
        printf("\n");
        printf("    delete-cat trebuie:");
        RSD_dir(delete);
        printf("\n");
*/        
    }
    
    return subdir;
}

//primeste ca parametru dir curent
void PWD(TDirectory dir) {
    if ( dir->parent == NULL ) {
        printf("/%s", dir->name);
        return;
    } else {
        PWD(dir->parent);
        printf("/%s", dir->name);
    }
}

//find file, return dir in care se afla
//functia cauta in campul files al fiecarui director dintr-un subdirector
TDirectory FindFileSub(TDirectory subdir, char* name) {
    
    if ( subdir == NULL ) 
            return NULL;

    printf("        ->sunt in subdir %s cu parintele: %s\n", subdir->name, subdir->parent->name);
    if ( SearchFile(subdir->files, name) != NULL ) 
        return subdir;
    else {  //daca nu gasesc in fis caut in files din fiecare subarb
        FindFileSub(subdir->right, name);
        FindFileSub(subdir->left, name);
    }        
}

//apelez fct de cautare in subdir pt fiecare dir
TDirectory FindFile(TDirectory dir, char* name) {
    if ( dir ==  NULL ) 
        return NULL;

    printf("    ->sunt in dir: %s\n", dir->name);
    if ( SearchFile(dir->files, name) != NULL )
        return dir;
    else {

        if ( FindFileSub(dir->current_subdir, name) != NULL )
            return FindFileSub(dir->current_subdir, name);
        else {
            return FindFile(dir->left, name);
            return FindFile(dir->right, name);
        }
    }
}
