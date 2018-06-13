#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "phone_forward.h"
#include "parser.h"
#include "main.h"

FwdBase** Base;
int baseSize;
int numOfBases;
FwdBase* currentBase;

FwdBase* makeBase (char* id) {

    FwdBase* fb = malloc(sizeof(FwdBase));

    char* name = malloc(sizeof(char)*strlen(id) + 1);
    strcpy(name, id);

    fb->id = name;
    fb->base = phfwdNew();

    return fb;
}

bool setBase (char* b) {

    FwdBase* newBase;
    bool isBase = false;

    for (int i = 0; i < numOfBases; ++i) {

        if (equals(b, Base[i]->id)) {
            newBase = Base[i];
            isBase = true;
            break;
        }
    }
    
    if (isBase) {
        currentBase = newBase;
    }
    else {
        Base[numOfBases++] = makeBase(b);
        if (Base[numOfBases-1] == NULL)
            return false;
        currentBase = Base[numOfBases-1];
    }   

    return true;
}

bool delBase (char* b, int sc) {

    int ind = -1;

    for (int i = 0; i < numOfBases; ++i) {

        if (equals(b, Base[i]->id)) {
            ind = i;
            break;
        }
    }

    if (ind != -1) {
        phfwdDelete(Base[ind]->base);
        free(Base[ind]->id);
        free(Base[ind]);
        Base[ind] = Base[--numOfBases];
    }
    else {
        fprintf(stderr, "ERROR DEL %d\n", sc);
        return false;
    }

    return true;
}

void delBases () {

    for (int i = 0; i < numOfBases; ++i) {
        free(Base[i]->id);
        phfwdDelete(Base[i]->base);
        free(Base[i]);
    }       

    free(Base);
}

void checkIsEOF (Lexeme l) {

    char c = getchar();

    if (c == EOF) {
        fprintf(stderr, "ERROR EOF\n");
        free(l.content);
        delBases();
        exit(1);
    }

    ungetc(c, stdin);
}

void exit1 (Lexeme l, Lexeme l1) {

    free(l1.content);
    free(l.content);
    delBases();
    exit(1);
}

int main() {

    baseSize = 16;
    numOfBases = 0;
    currentBase = NULL;
    Base = malloc(baseSize * sizeof(FwdBase*));

    while(hasNext()) {

        Lexeme l = getNextLexeme();

        if (l.type == 4) { // wczytano NEW

            checkIsEOF(l);

            if (hasNext()) {

                Lexeme l1 = getNextLexeme();

                if (l1.type == 1) { // wczytano id
                    if (!setBase(l1.content)) {
                        fprintf(stderr, "ERROR NEW %d\n", l.startChar);
                        exit1(l, l1);
                    }
                }
                else {
                    fprintf(stderr, "ERROR %d\n", l1.startChar);
                    exit1(l, l1);
                }

                free(l1.content);
            }
        }
        else if (l.type == 5) { // wczytano DEL

            checkIsEOF(l);

            if (hasNext()) {

                Lexeme l1 = getNextLexeme();

                if (l1.type == 1) { // wczytano id

                    if (currentBase != NULL && equals(l1.content, currentBase->id)) {
                        currentBase = NULL;
                    }

                    delBase(l1.content, l.startChar);
                }
                else if (l1.type == 0 && currentBase != NULL) { // wczytano numer
                    phfwdRemove(currentBase->base, l1.content);
                }
                else {
                    fprintf(stderr, "ERROR %d\n", l1.startChar);
                    exit1(l, l1);
                }

                free(l1.content);
            }
        }
        else if (l.type == 0) { // wczytano numer

            checkIsEOF(l);

            if (hasNext()) {

                Lexeme l1 = getNextLexeme();

                if (l1.type == 3) { // wczytano ?

                    if (currentBase != NULL) {
                        PhoneNumbers* pnum = (PhoneNumbers*)phfwdGet(currentBase->base, l.content);
                        printf("%s\n", phnumGet(pnum, 0));
                        phnumDelete(pnum);
                    }
                    else if (currentBase == NULL) {
                        fprintf(stderr, "ERROR ? %d\n", l1.startChar);
                        exit1(l, l1);
                    }
                    else {
                        fprintf(stderr, "ERROR %d\n", l1.startChar);
                        exit1(l, l1);
                    }
                }
                else if (l1.type == 2) { // wczytano >

                    checkIsEOF(l);

                    if (hasNext()) {

                        Lexeme l2 = getNextLexeme();

                        if (l2.type == 0 && currentBase != NULL) { // wczytano numer

                            if(!phfwdAdd(currentBase->base, l.content, l2.content)) {
                                fprintf(stderr, "ERROR > %d\n", l1.startChar);
                                free(l2.content);
                                exit1(l, l1);
                            }
                        }
                        else if (currentBase == NULL) {
                            fprintf(stderr, "ERROR > %d\n", l1.startChar);
                            free(l2.content);
                            exit1(l, l1);
                        }
                        else {
                            fprintf(stderr, "ERROR %d\n", l2.startChar);
                            free(l2.content);
                            exit1(l, l1);
                        }

                        free(l2.content);
                    }
                }
                else {
                    fprintf(stderr, "ERROR %d\n", l1.startChar);
                    exit1(l, l1);
                }

                free(l1.content);
            }
        }
        else if (l.type == 3) { // wczytano ?

            checkIsEOF(l);

            if (hasNext()) {

                Lexeme l1 = getNextLexeme();

                if (l1.type == 0 && currentBase != NULL) { // wczytano numer

                    char const *num;
                    int idx = 0;
                    PhoneNumbers* pnum = (PhoneNumbers*)phfwdReverse(currentBase->base, l1.content);

                    while ((num = phnumGet(pnum, idx++)) != NULL) {
                        printf("%s\n", num);
                    }

                    phnumDelete(pnum);
                }
                else if (currentBase == NULL) {
                    fprintf(stderr, "ERROR ? %d\n", l.startChar);
                    exit1(l, l1);
                }
                else {
                    fprintf(stderr, "ERROR %d\n", l1.startChar);
                    exit1(l, l1);
                }

                free(l1.content);
            }
        }
        else if (l.type == 6) {
            checkIsEOF(l);

            if (hasNext()) {

                Lexeme l1 = getNextLexeme();

                if (l1.type == 0 && currentBase != NULL) { // wczytano numer
                    int len = strlen(l1.content) - 12;
                    if (len < 0) len = 0;
                    printf("%zu\n", phfwdNonTrivialCount(currentBase->base, l1.content, len));
                }
                else if (currentBase == NULL) {
                    fprintf(stderr, "ERROR ? %d\n", l.startChar);
                    exit1(l, l1);
                }
                else {
                    fprintf(stderr, "ERROR %d\n", l1.startChar);
                    exit1(l, l1);
                }

                free(l1.content);
            }
        }
        else if (l.type >= 0) {
            fprintf(stderr, "ERROR %d\n", l.startChar);
            free(l.content);
            delBases();
            exit(1);
        }

        free(l.content);

        // Jeśli skończyło się miejsce w bazie, to powiększam ją
        if (numOfBases == baseSize - 1) {
            Base = realloc(Base, sizeof(FwdBase*) * (baseSize *= 2));
        }
    }

    delBases();
    printError();

    return 0;
}
