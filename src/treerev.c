#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "double_ended_list.h"
#include "treerev.h"
#include "phone_forward.h"
#include "phone_forward_main.h"
#define NUMLEN 12

revNode* revSetNode () {
	revNode* n = (revNode*)malloc(sizeof(revNode));

	// Malloc failure
    if (n == NULL) {
    	delBases();
    	fprintf(stderr, "MALLOC ERROR\n");
    	exit(1);
    }

	if (n != NULL) {
		for(int i = 0; i < NUMLEN; ++i) {
			n->nums[i] = NULL;
		}

		n->phoneNumbers = delSetList();
	}

	return n;
}

revTree* revSetTree () {
	revTree* t = (revTree*)malloc(sizeof(revTree));

	// Malloc failure
    if (t == NULL) {
    	delBases();
    	fprintf(stderr, "MALLOC ERROR\n");
    	exit(1);
    }

	if (t != NULL) {
		t->root = revSetNode();
	}

	return t;
}

void revDeleteSubtree (revNode* n) {
	for (int i = 0; i < NUMLEN; ++i) {
		if (n->nums[i] != NULL) {
			revDeleteSubtree(n->nums[i]);
		}
	}

	delDeleteList(n->phoneNumbers);
	free(n);
}

delNode* revAddRev (revTree* t, char const* numadd, char const* number) {
	revNode* n = t->root;

	size_t dl = strlen(numadd);

	for (size_t i = 0; i < dl; ++i) {
		int c = numadd[i] - '0';

		if (n->nums[c] == NULL) {
			n->nums[c] = revSetNode();

			if (n->nums[c] == NULL){
				return NULL;
			}
		}

		n = n->nums[c];
	}

	delAddFront(n->phoneNumbers, number);

	return (n->phoneNumbers)->first->next;
}

deList* revFindRev (revTree* t, char const* number) {
	revNode* n = t->root;
	deList* l = delSetList();

	size_t i = 0;
	size_t dl = strlen(number);

	while (i < dl && n->nums[(int)(number[i]-'0')] != NULL) {
		delCopyList(l, n->phoneNumbers, number, i);
		n = n->nums[(int)(number[i]-'0')];
		
		++i;
	}

	delCopyList(l, n->phoneNumbers, number, i);
	delAddSort(l, number);

	return l;
}

size_t pot(size_t a, size_t n) {
	if(n == 0) {
		return 1;
	}
	
	if(n%2 == 1) {
		return a * pot(a, n - 1);
	}
	
	size_t w = pot(a, n/2); 

	return w * w;
}
	
size_t revFindNonTrivialCountRec (revNode* n, bool* uniqueSet, size_t len,
	size_t lenCount, size_t liczbaCyfr) {
	size_t wynik = 0;

	if (!delIsEmpty(n->phoneNumbers)) {
		return pot(liczbaCyfr, (len - lenCount));
	}

	for (size_t i = 0; i < NUMLEN; ++i) {
		if (n->nums[i] != NULL && uniqueSet[i] == true && lenCount < len) {
			wynik += revFindNonTrivialCountRec(
				n->nums[i], uniqueSet, len, lenCount+1, liczbaCyfr);
		}
	}

	return wynik;
}

size_t revFindNonTrivialCount(revNode* root, bool* uniqueSet,
	size_t len, size_t liczbaCyfr) {
	return revFindNonTrivialCountRec(root, uniqueSet, len, 0, liczbaCyfr);
}
