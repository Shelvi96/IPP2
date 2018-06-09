#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "double_ended_list.h"
#include "treefwd.h"

fwdNode* fwdSetNode () {
	fwdNode* n = (fwdNode*)malloc(sizeof(fwdNode));
	if (n != NULL) {
		for(int i = 0; i < 10; ++i)
			n->nums[i] = NULL;
		n->pointRev = NULL;
		n->numFwd = NULL;
	}
	return n;
}

fwdTree* fwdSetTree () {
	fwdTree* t = (fwdTree*)malloc(sizeof(fwdTree));
	if (t != NULL)
		t->root = fwdSetNode();
	return t;
}

void fwdDeleteSubtree (fwdNode* n) {
	for (int i = 0; i < 10; ++i) {
		if (n->nums[i] != NULL)
			fwdDeleteSubtree(n->nums[i]);
	}
	if (n->numFwd != NULL) 
		free((void*)(n->numFwd));
	free(n);
}

bool fwdAddFwd (fwdTree* t, char const* numadd, char const* number, delNode* r) {
	fwdNode* n = t->root;
	if (strcmp(numadd, number) == 0)
		return false;
	unsigned int dl = strlen(numadd);
	for (unsigned int i = 0; i < dl; ++i) {
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
	strcpy((char*)(n->numFwd), number);
	n->pointRev = r;

	return true;
}

void fwdDeleteSubfwd (fwdNode* n) {
	if (n != NULL) {
		for (int i = 0; i < 10; ++i) {
			if (n->nums[i] != NULL)
				fwdDeleteSubfwd(n->nums[i]);
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
	unsigned int i = 0;
	bool exists = true;
	unsigned int dl = strlen(number);
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
	if (exists)
		fwdDeleteSubfwd(n);
}

deList* fwdFindFwd (fwdTree* t, char const* number) {
	fwdNode* n = t->root;
	unsigned int i = 0, j = 0;
	char* f = NULL;
	unsigned int dl = strlen(number);
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
	strcpy(newNum, f);
	strcpy(newNum + strlen(f), number + j);

	delAddFront(l, newNum);
	free(newNum);

	return l;
}
