#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME 50+1
#define NAME 30+1
#define PROFESSION 20+1
#define TITLE 40+1
typedef struct filmS filmT;
typedef struct memberS memberT;
typedef struct professionS professionT;
struct filmS{
    char *filmName;
    int filmDuration;
    memberT *members;
    filmT *next;
};
struct memberS{
    char *memberName;
    char *memberProfession;
    int memberAge;
    filmT *films;
    memberT *next;
};
struct professionS{
    char *name;
    int count;
    professionT *next;
};
//films functions
filmT *createFilm(char *,int);
filmT *loadFilms();
filmT *findFilm(filmT *,char *);
void addFilms(memberT *,filmT *,char *);
//members functions
memberT *createMember(char *,char *,int);
memberT *loadMember();
memberT *findMember(memberT *,char *);
void addMembers(filmT *,memberT *,char *);
//professions functions
professionT *createProfession(char *);
professionT *isAlreadyPresent(professionT *,char *);
professionT *loadProfession(memberT *);
//print functions
void printFilms(filmT *);
void printMembers(memberT *);
void printProfessions(professionT *);
void printFilmsInfos(filmT *);
int main()
{
    filmT *films = loadFilms();
    memberT *members = loadMember();
    char filename[FILENAME];
    fprintf(stdout,"rent filename => ");
    fscanf(stdin,"%s",filename);
    addMembers(films,members,filename);
    addFilms(members,films,filename);
    printFilms(films);
    fprintf(stdout,"\n");
    printMembers(members);
    fprintf(stdout,"\n");
    printFilmsInfos(films);
    fprintf(stdout,"\n");
    return 0;
}
filmT *createFilm(char *filmName,int filmDuration){
    filmT *newFilm = (filmT *) malloc(sizeof(filmT));
    newFilm->filmName = (char *) malloc((strlen(filmName)+1) * sizeof(char));
    strcpy(newFilm->filmName,filmName);
    newFilm->filmDuration = filmDuration;
    newFilm->members = NULL;
    newFilm->next = NULL;
    return newFilm;
}
filmT *loadFilms(){
    filmT *filmsHead = NULL;
    char filename[FILENAME];
    fprintf(stdout,"film filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    char filmName[TITLE];
    int filmDuration;
    while(fscanf(f,"%s %d",filmName,&filmDuration) != EOF){
        filmT *newFilm = createFilm(filmName,filmDuration);
        newFilm->next = filmsHead;
        filmsHead = newFilm;
    }
    return filmsHead;
}
filmT *findFilm(filmT *films,char *filmName){
    filmT *f = films;
    while(f != NULL){
        if(strcmp(f->filmName,filmName) == 0)
            return f;
        f = f->next;
    }
    return NULL;
}
memberT *createMember(char *memberName,char *memberProfession,int memberAge){
    memberT *newMember = (memberT *) malloc(sizeof(memberT));
    newMember->memberName = (char *) malloc((strlen(memberName)+1) * sizeof(char));
    strcpy(newMember->memberName,memberName);
    newMember->memberProfession = (char *) malloc((strlen(memberProfession)+1) * sizeof(char));
    strcpy(newMember->memberProfession,memberProfession);
    newMember->memberAge = memberAge;
    newMember->films = NULL;
    newMember->next = NULL;
    return newMember;
}
memberT *loadMember(){
    memberT *membersHead = NULL;
    char filename[FILENAME];
    fprintf(stdout,"members filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    char memberName[NAME];
    char memberProfession[PROFESSION];
    int memberAge;
    while(fscanf(f,"%s %s %d",memberName,memberProfession,&memberAge) != EOF){
        memberT *newMember = createMember(memberName,memberProfession,memberAge);
        newMember->next = membersHead;
        membersHead = newMember;
    }
    return membersHead;
}
memberT *findMember(memberT *members,char *memberName){
    memberT *m = members;
    while(m != NULL){
        if(strcmp(m->memberName,memberName) == 0)
            return m;
        m = m->next;
    }
    return NULL;
}
void addFilms(memberT *members,filmT *films,char *filename){
    FILE *f = fopen(filename,"r");
    char memberName[NAME];
    char filmName[TITLE];
    while(fscanf(f,"%s %s",memberName,filmName) != EOF){
        memberT *targetMember = findMember(members,memberName);
        filmT *targetFilm = findFilm(films,filmName);
        if(targetFilm != NULL && targetMember != NULL){
            filmT *tempFilm = createFilm(targetFilm->filmName,targetFilm->filmDuration);
            tempFilm->next = targetMember->films;
            targetMember->films = tempFilm;
        }
    }
}
void addMembers(filmT *films,memberT *members,char *filename){
    FILE *f = fopen(filename,"r");
    char memberName[NAME];
    char filmName[TITLE];
    while(fscanf(f,"%s %s",memberName,filmName) != EOF){
        memberT *targetMember = findMember(members,memberName);
        filmT *targetFilm = findFilm(films,filmName);
        if(targetFilm != NULL && targetMember != NULL){
            memberT *tempMember = createMember(targetMember->memberName,targetMember->memberProfession,targetMember->memberAge);
            tempMember->next = targetFilm->members;
            targetFilm->members = tempMember;
        }
    }
}
void printFilms(filmT *films){
    filmT *f = films;
    while(f != NULL){
        fprintf(stdout,"\n%s (%d minutes)",f->filmName,f->filmDuration);
        memberT *m = f->members;
        while(m != NULL){
            fprintf(stdout,"\n  %s %s (%d years old)",m->memberName,m->memberProfession,m->memberAge);
            m = m->next;
        }
        f = f->next;
    }
}
professionT *isAlreadyPresent(professionT *professions,char *professionName){
    professionT *p = professions;
    while(p != NULL){
        if(strcmp(p->name,professionName) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}
professionT *createProfession(char *professionName){
    professionT *newProfession = (professionT *) malloc(sizeof(professionT));
    newProfession->name = (char *) malloc((strlen(professionName)+1) * sizeof(char));
    strcpy(newProfession->name,professionName);
    newProfession->count = 1;
    newProfession->next = NULL;
    return newProfession;
}
professionT *loadProfession(memberT *members){
    professionT *headProfession = NULL;
    memberT *m = members;
    while(m != NULL){
        if(isAlreadyPresent(headProfession,m->memberProfession) == NULL){
            professionT *newProfession = createProfession(m->memberProfession);
            newProfession->next = headProfession;
            headProfession = newProfession;
        }else{
            isAlreadyPresent(headProfession,m->memberProfession)->count++;
        }
        m = m->next;
    }
    return headProfession;
}
void printMembers(memberT *members){
    memberT *m = members;
    while(m != NULL){
        fprintf(stdout,"\n%s %s %d",m->memberName,m->memberProfession,m->memberAge);
        filmT *f = m->films;
        while(f != NULL){
            fprintf(stdout,"\n  %s %d",f->filmName,f->filmDuration);
            f = f->next;
        }
        m = m->next;
    }
}
void printProfessions(professionT *professions){
    professionT *p = professions;
    while(p != NULL){
        fprintf(stdout," %s %d",p->name,p->count);
        p = p->next;
    }
}
void printFilmsInfos(filmT *films){
    filmT *f = films;
    while(f != NULL){
        int count = 0;
        float averageAge = 0;
        memberT *m = f->members;
        while(m != NULL){
            count++;
            m = m->next;
        }
        m = f->members;
        while(m != NULL){
            averageAge += m->memberAge;
            m = m->next;
        }
        averageAge /= count;
        fprintf(stdout,"\n%s (%d minutes) %d %f -> ",f->filmName,f->filmDuration,count,averageAge);
        professionT *professions = loadProfession(f->members);
        printProfessions(professions);
        f = f->next;
    }
}
