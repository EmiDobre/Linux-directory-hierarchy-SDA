//DOBRE EMILIA ILIANA 315CB

#include "arb.h"

TArbFile CreateLeafFile(char* name, TDirectory parent) {
	TArbFile aux = (TArbFile)calloc (1, sizeof(TOneFile));
	if ( !aux ) return NULL;

	aux->name =  calloc(51, sizeof(char));
    if ( !aux->name ) return NULL;
    
    memcpy(aux->name, name, strlen(name));
    aux->parent_dir = parent;

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


void SRD(void* arb, char tip) {
    if ( tip == 'f' ) {
        TArbFile a = (TArbFile)arb; 
        if ( a != NULL ) {
            SRD(a->left, 'f');
            printf("%s ", a->name);
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
//afla minmul dintr-un arbore, folosit pt a afla minimul dintr un subarbore de fisiere
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
    TArbFile parent = ParentFile(files, name);
 
    //daca am radacina care are maxim 1 copil

    if ( parent == NULL && (delete->left == NULL || delete->right == NULL) ) {

        if ( delete->left == NULL && delete->right == NULL ) {
            delete = NULL;
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

    //nu e radacina=> daca e frunza
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
        return files;
    }

    if ( delete->left != NULL && delete->right == NULL && parent != NULL ) {
        if ( parent->left == delete )
            parent->left = delete->left;
        if ( parent->right == delete )
            parent->right = delete->left;
        return files;
    }

    //daca are 2 copii
    //nodul se inlocuieste cu minimul din subarborele drept si apoi se elimina 
    //acest minim din subarborele drept prin functia delete

    if ( (delete->left != NULL) && (delete->right != NULL) ) {
        TArbFile minim = MinimFile(delete->right);
        memcpy(delete->name, minim->name, strlen(minim->name));
        delete->right = DeleteFile(delete->right, minim->name);
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

//idem rmdir:

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

TDirectory DeleteDir(TDirectory subdir, char* name, TDirectory all_dir ) {
    TDirectory delete = SearchDir (subdir, name);

    //daca directorul are fisiere sau subdirectoare le sterg pe ele prima data

    if ( delete->files != NULL ) {
        while ( delete->files != NULL ) {
            delete->files = DeleteFile(delete->files, delete->files->name);
        }
    }

    if ( delete->current_subdir != NULL ) {
        while ( delete->current_subdir != NULL ) {
            delete->current_subdir = DeleteDir(delete->current_subdir, delete->current_subdir->name, all_dir);
        }
    }

    TDirectory parent = ParentDir(subdir, name);
  
    if ( parent == NULL && (delete->left == NULL || delete->right == NULL) ) {
        if ( delete->left == NULL && delete->right == NULL ) {
            delete = NULL;
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

    if ( delete->left == NULL && delete->right != NULL && parent != NULL ) {
        if ( parent->left == delete )
            parent->left = delete->right;
        if ( parent->right == delete )
            parent->right = delete->right;
        return subdir;
    }

    if ( delete->left != NULL && delete->right == NULL && parent != NULL ) {
        if ( parent->left == delete )
            parent->left = delete->left;
        if ( parent->right == delete )
            parent->right = delete->left;
        return subdir;
    }

    if ( (delete->left != NULL) && (delete->right != NULL) ) {
        TDirectory minim = MinimDirectoy(delete->right);
        memcpy(delete->name, minim->name, strlen(minim->name));
        delete->right = DeleteDir(delete->right, minim->name, all_dir);
    }
    
    return subdir;
}
