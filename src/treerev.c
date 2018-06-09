#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "double_ended_list.h"
#include "treerev.h"

revNode* revSetNode () {
	revNode* n = (revNode*)malloc(sizeof(revNode));
	if (n != NULL) {
		for(int i = 0; i < 10; ++i)
			n->nums[i] = NULL;
		n->phoneNumbers = delSetList();
	}
	return n;
}

revTree* revSetTree () {
	revTree* t = (revTree*)malloc(sizeof(revTree));
	if (t != NULL)
		t->root = revSetNode();
	return t;
}

void revDeleteSubtree (revNode* n) {
	for (int i = 0; i < 10; ++i) {
		if (n->nums[i] != NULL)
			revDeleteSubtree(n->nums[i]);
	}
	delDeleteList(n->phoneNumbers);
	free(n);
}

delNode* revAddRev (revTree* t, char const* numadd, char const* number) {
	revNode* n = t->root;
	unsigned int dl = strlen(numadd);
	for (unsigned int i = 0; i < dl; ++i) {
		int c = numadd[i] - '0';
		if (n->nums[c] == NULL) {
			n->nums[c] = revSetNode();
			if (n->nums[c] == NULL)
				return NULL;
		}
		n = n->nums[c];
	}
	delAddFront(n->phoneNumbers, number);

	return (n->phoneNumbers)->first->next;
}

deList* revFindRev (revTree* t, char const* number) {
	revNode* n = t->root;
	deList* l = delSetList();
	unsigned int i = 0;
	unsigned int dl = strlen(number);
	while (i < dl && n->nums[(int)(number[i]-'0')] != NULL) {
		delCopyList(l, n->phoneNumbers, number, i);
		n = n->nums[(int)(number[i]-'0')];
		++i;
	}
	delCopyList(l, n->phoneNumbers, number, i);
	delAddSort(l, number);
	return l;
}
