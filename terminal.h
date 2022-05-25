#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

//arbore fis
typedef struct nodFile {
    char* name;
    struct nodFile * left;
    struct nodFile * right;
    struct directory* parent_dir;
} TOneFile, *TArbFile;

//director
typedef struct directory {
    char* name;
    struct directory* parent;
    struct directory* current_subdir; //directories, tot ce e in subdirect dir adaugat,
                                   // daca se face cd si se adauga in el nu va mai fi null
    TArbFile files;
    struct directory* right; 
    struct directory* left;

} TOneDir,*TDirectory;


//fct arb file:
TArbFile CreateNodFile(char* name, TArbFile left, TArbFile right);

void DistrNodeFile(TArbFile a);
void DistrArb(TArbFile *a);

TArbFile CreateLeafFile(char* name, TDirectory parent);
TArbFile InsertFile(TArbFile arb, char* name, TDirectory parent );


//TDirectory InsertDir(TDirectory dir_parent, TArbFile files, char* name, TDirectory subdir);
TDirectory InitParent (TDirectory parent, char* name);
void SRD(void* a, char tip);

TDirectory LeafDir ( char* name, TDirectory parent);
TDirectory InsertInSubdir (TDirectory sub, char* name, TDirectory parent);

TDirectory SearchDir(TDirectory subdir, char* name);
TArbFile SearchFile(TArbFile files, char* name );

TArbFile DeleteFile(TArbFile files, char* name );
TArbFile ParentFile(TArbFile files, char* name);
TArbFile MinimFile(TArbFile subfiles);

TDirectory DeleteDir(TDirectory subdir, char* name );
TDirectory MinimDirectoy(TDirectory subdir);
TDirectory ParentDir(TDirectory subdir, char* name);

void PWD(TDirectory dir);
TDirectory FindFileSub(TDirectory subdir, char* name) ;
TDirectory FindFile(TDirectory dir, char* name);

//de sters
void RSD(TArbFile a);
void RSD_dir(TDirectory a);
