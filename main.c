#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 50


typedef struct directory {
    char name[SIZE];
    struct directory *firstChild;
    struct directory *nextSibling;
}DIR;



void program(DIR*);
void mkdir(DIR*,char *);
void chdir(DIR*,char *);
void rmdir(DIR*,char *);
void dir(DIR*);
void count(DIR*);
DIR* createDirectory(char*);




int main(int argc, char **argv)
{
    DIR *root;
    root=createDirectory("Root");
    program(root);

	return 0;
}

void program(DIR *current) {
    char *komut,*girdi;
    while(1) {
        scanf("%s %s",komut,girdi);
        if(!strcmp(komut,"mkdir")) {
            mkdir(current,girdi);
        }
        else if(!strcmp(komut,"chdir")) {
            if(!strcmp(girdi,"..") && strcmp(current->name,"Root")) {
                return;
            }
            else if(!strcmp(girdi,"..") && !strcmp(current->name,"Root"))  {
                printf("ROOT'DA OLDUGUNUZ ICIN DAHA UST DOSYALARA ERISEMEZSINIZ");
            }
            else {
                chdir(current,girdi);
            }
        }
        else if(!strcmp(komut,"rmdir")) {
            rmdir(current,girdi);
        }
        else if(!strcmp(komut,"dir")) {
            dir(current);
        }
        else if(!strcmp(komut,"count")) {
            count(current);
        }
    }
}

DIR* createDirectory(char *name) {
    DIR *tmp;
    tmp=(DIR*)malloc(sizeof(DIR));
    strcpy(tmp->name,name);
    tmp->firstChild=NULL;
    tmp->nextSibling=NULL;
    return tmp;
}


void mkdir(DIR *current,char *girdi) {
    DIR *tmp;
    int control=1;
    if(current->firstChild == NULL) {
        current->firstChild = createDirectory(girdi);
    }
    else {
        tmp = current->firstChild;
        if(!strcmp(tmp->name,girdi))
            control = 0;
        while(control && tmp->nextSibling != NULL) {
            tmp = tmp->nextSibling;
            if(!strcmp(tmp->name,girdi))
                control = 0;
        }
        if(control)
            tmp->nextSibling = createDirectory(girdi);
        else 
            printf("AYNI ISIMDE BASKA BIR DIRECTORY BULUNMAKTADIR!");
    }    
}


void chdir(DIR *current,char *girdi) {
    DIR *tmp;
    tmp = current->firstChild;
    while(tmp != NULL && strcmp(tmp->name,girdi)) {
        tmp = tmp->nextSibling;
    }
    if(tmp != NULL) {
        program(tmp);
    }
    else {
        printf("BOYLE BIR DIRECTORY BULUNAMAMISTIR!");
    }
}


void rmdir(DIR *current, char *girdi) {
    DIR *tmp;
    DIR *parent;
    
    parent = current;
    tmp = current ->firstChild;
    
    
    if(tmp != NULL && !strcmp(tmp->name,girdi)) {
        if(tmp->firstChild != NULL) {
            printf("SILMEK ISTEDIGINIZ DIRECTORY ALTINDA BASKA DIRECTORYLER BULUNMAKTADIR!");
        }
        else {
            parent->firstChild = tmp->nextSibling;
            free(tmp);
        }
    }
    
    while(tmp != NULL && strcmp(tmp->name,girdi)) {
        parent = tmp;
        tmp = tmp->nextSibling;
    }
    if(tmp != NULL) {
        if(tmp->firstChild != NULL) {
            printf("SILMEK ISTEDIGINIZ DIRECTORY ALTINDA BASKA DIRECTORYLER BULUNMAKTADIR!");
        }
        else {
            parent->nextSibling = tmp->nextSibling;
            free(tmp);
        }
    }
    else {
        printf("BOYLE BIR DIRECTORY BULUNAMAMISTIR!");
    }
}

void dir(DIR *current) {
    
    DIR *tmp;
    
    if(current->firstChild != NULL) {
        printf("%s",current->firstChild->name);
        tmp=current->firstChild;
        while(tmp->nextSibling) {
            printf("%s",tmp->nextSibling->name);
            tmp=tmp->firstChild;
        }
    }
    else {
        printf("HICBIR ALT DIRECTORY BULUNMAMAKTADIR");
    }
}

void count(DIR *current) {
    DIR *tmp;
    int counter = 0;
    if(current->firstChild != NULL) {
        counter++;
        tmp=current->firstChild;
        while(tmp->nextSibling) {
            counter++;
            tmp=tmp->firstChild;
        }
    }
    printf("%d",counter);
} 