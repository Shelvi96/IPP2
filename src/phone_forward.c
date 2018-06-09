#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "double_ended_list.h"
#include "treefwd.h"
#include "treerev.h"
#include "phone_forward.h"


PhoneForward* phfwdNew () {
	PhoneForward* pf = (PhoneForward*)malloc(sizeof(PhoneForward));
	if (pf != NULL) {
		pf->fwd = fwdSetTree();
		pf->rev = revSetTree();
	}
	return pf;
}

void phfwdDelete (PhoneForward* pf) {
	if (pf != NULL) {
		fwdDeleteSubtree(pf->fwd->root);
		revDeleteSubtree(pf->rev->root);
		free(pf->fwd);
	    free(pf->rev);
	    free(pf);
	}
}

bool isNum(char const* num) {
	if (strlen(num) == 0)
		return false;
	unsigned int c = 0;
		for (unsigned int i = 0; i < strlen(num); ++i) {
    		if ( '0' <= num[i] && num[i] <= '9')
	      	c++;
	  	}
  	if (c == strlen(num))
	    return true;
	return false;
}

bool phfwdAdd (PhoneForward* pf, char const* num1, char const* num2) {
	if (num1 == NULL || num2 == NULL || !isNum(num1) || !isNum(num2))
		return false;
	delNode* n = revAddRev(pf->rev, num2, num1);
	if (n == NULL)
		return false;
	return fwdAddFwd(pf->fwd, num1, num2, n);
}

void phfwdRemove(PhoneForward* pf, char const *num) {
	if (num != NULL && isNum(num))
		fwdRemoveFwd(pf->fwd, num);
}

PhoneNumbers const* phfwdGet(PhoneForward* pf, char const* num) {
	PhoneNumbers* pnum = (PhoneNumbers*)malloc(sizeof(PhoneNumbers));
	if (num != NULL && isNum(num)) {
		pnum->pnums = fwdFindFwd(pf->fwd, num);
		return (PhoneNumbers const*)pnum;
	}
	pnum->pnums = delSetList();
	return pnum;
}

PhoneNumbers const* phfwdReverse(PhoneForward *pf, char const *num) {
	PhoneNumbers* pnum = (PhoneNumbers*)malloc(sizeof(PhoneNumbers));
		if (num != NULL && isNum(num)) {
			pnum->pnums = revFindRev(pf->rev, num);
			return (PhoneNumbers const*)pnum;
	}
	pnum->pnums = delSetList();
	return pnum;
}

void phnumDelete(PhoneNumbers const* pnum) {
	if (pnum != NULL) {
		delDeleteList(pnum->pnums);
		free((void*)pnum);
	}
}

char const* phnumGet(PhoneNumbers const* pnum, size_t idx) {
	if (pnum == NULL)
		return NULL;
	return delGetIndex(pnum->pnums, idx);
}
