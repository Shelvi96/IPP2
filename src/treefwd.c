#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "double_ended_list.h"
#include "treefwd.h"
#include "phone_forward.h"
#include "phone_forward_main.h"
#define NUMLEN 12

fwdNode* fwdSetNode () {
	fwdNode* n = (fwdNode*)malloc(sizeof(fwdNode));

	// Malloc failure
    if (n == NULL) {
    	delBases();
    	fprintf(stderr, "MALLOC ERROR\n");
    	exit(1);
    }

	if (n != NULL) {
		for(size_t i = 0; i < NUMLEN; ++i) {
			n->nums[i] = NULL;
		}

		n->pointRev = NULL;
		n->numFwd = NULL;
	}

	return n;
}

fwdTree* fwdSetTree () {
	fwdTree* t = (fwdTree*)malloc(sizeof(fwdTree));

	// Malloc failure
    if (t == NULL) {
    	delBases();
    	fprintf(stderr, "MALLOC ERROR\n");
    	exit(1);
    }

	if (t != NULL) {
		t->root = fwdSetNode();
	}

	return t;
}

void fwdDeleteSubtree (fwdNode* n) {
	for (size_t i = 0; i < NUMLEN; ++i) {
		if (n->nums[i] != NULL) {
			fwdDeleteSubtree(n->nums[i]);
		}
	}

	if (n->numFwd != NULL) {
		free((void*)(n->numFwd));
	}

	free(n);
}

bool fwdAddFwd (fwdTree* t, char const* numadd, char const* number, delNode* r) {
	fwdNode* n = t->root;

	if (strcmp(numadd, number) == 0) {
		return false;
	}

	size_t dl = strlen(numadd);

	for (size_t i = 0; i < dl; ++i) {
		int c = numadd[i] - '0';

		if (n->nums[c] == NULL) {
			n->nums[c] = fwdSetNode();
		}

		n = n->nums[c];
	}

	if (n->pointRev != NULL) {
		delRemoveNode(n->pointRev);
		n->pointRev = NULL;
	}

	if (n->numFwd != NULL) {
		free((void*)n->numFwd);
		n->numFwd = NULL;
	}

	n->numFwd = malloc(strlen(number) + 1);

	// Malloc failure
    if (n->numFwd == NULL) {
    	delBases();
    	fprintf(stderr, "MALLOC ERROR\n");
    	exit(1);
    }

	strcpy((char*)(n->numFwd), number);
	n->pointRev = r;

	return true;
}

void fwdDeleteSubfwd (fwdNode* n) {
	if (n != NULL) {
		for (size_t i = 0; i < NUMLEN; ++i) {
			if (n->nums[i] != NULL) {
				fwdDeleteSubfwd(n->nums[i]);
			}
		}

		if (n->numFwd != NULL) {
			free((void*)n->numFwd);
			n->numFwd = NULL;
		}
		if (n->pointRev != NULL) {
			delRemoveNode(n->pointRev);
			n->pointRev = NULL;
		}
	}
}

void fwdRemoveFwd (fwdTree* t, char const* number) {
	fwdNode* n = t->root;
	bool exists = true;
	size_t i = 0;
	size_t dl = strlen(number);

	for (i = 0; i < dl; ++i) {
		int c = number[i] - '0';

		if (n->nums[c] == NULL) {
			exists = false;
			break;
		}
		else {
			n = n->nums[c];
		}
	}

	if (exists){
		fwdDeleteSubfwd(n);
	}
}

deList* fwdFindFwd (fwdTree* t, char const* number) {
	fwdNode* n = t->root;
	char* f = NULL;
	size_t i = 0, j = 0;
	size_t dl = strlen(number);

	while (i < dl && n->nums[(int)(number[i]-'0')] != NULL) {
		if (n->numFwd != NULL) {
			f = (char*)(n->numFwd);
			j = i;
		}
		
		n = n->nums[(int)(number[i]-'0')];
		++i;
	}

	if (n->numFwd != NULL) {
		f = (char*)(n->numFwd);
		j = i;
	}

	deList* l = delSetList();

	if (i == 0 || f == NULL) {
		delAddFront(l, number);
		return l;
	}

	char* newNum = malloc(strlen(f) + strlen(number) + 1);

	// Malloc failure
    if (newNum == NULL) {
    	delBases();
    	fprintf(stderr, "MALLOC ERROR\n");
    	exit(1);
    }

	strcpy(newNum, f);
	strcpy(newNum + strlen(f), number + j);

	delAddFront(l, newNum);
	free(newNum);

	return l;
}
