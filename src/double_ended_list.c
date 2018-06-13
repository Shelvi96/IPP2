#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "double_ended_list.h"

delNode* delSetNode(char const* x) {

	delNode* v = (delNode*)malloc(sizeof(delNode));
	if (v != NULL) {
		char* num = malloc(strlen(x)+1);
		strcpy(num, x);

		v->number = num;
		v->prev = NULL;
		v->next = NULL;
	}

	return v;
}

deList* delSetList () {

	deList* l = (deList*)malloc(sizeof(delNode));
	if (l != NULL) {
		l->first = delSetNode("");
		l->last = delSetNode("");
		(l->first)->next = l->last;
		(l->last)->prev = l->first;
	}

	return l;
}

void delAddFront (deList* l, char const* x) {

	delNode* n = delSetNode(x);
	n->prev = (l->first);
	n->next = (l->first)->next;
	((l->first)->next)->prev = n;
	(l->first)->next = n;
}

void delAddSort (deList* l, char const* x) {

	delNode* n = delSetNode(x);
	delNode* el = l->first->next;

	while (el != l->last && strcmp(x, el->number) > 0) {
		el = el->next;
	}

	if (el != l->last && strcmp(x, el->number) == 0) {
		free(n->number);
		free(n);
	}
	else {
		n->next = el;
		n->prev = (el->prev);
		(el->prev)->next = n;
		el->prev = n;
	}
}

char const* delGetIndex (deList* l, int index) {

	if ((l->last)->prev == l->first){
		return NULL;
	}

	int i = 0;
	delNode* n = l->first;
	for (i = 0; i <= index; ++i) {

		n = n->next;
		if (n == l->last){
			return NULL;
		}
	}

	return n->number;
}

void delRemoveFront (deList* l) {

	if ((l->first)->next != l->last) {

		delNode* n = l->first->next;
		free(n->number);
		(n->next)->prev = l->first;
		(l->first)->next = n->next;
		free(n);
	}
}

void delRemoveNode (delNode* n) {

	if (n != NULL) {

		n->prev->next = n->next;
		n->next->prev = n->prev;

		if (n->number != NULL){
			free(n->number);
		}

		free(n);
	}
}

void delCopyList (deList* l1, deList* l2, char const* num, unsigned int idx) {

	delNode* n = l2->first->next;
	while (n != l2->last) {

		char* f = n->number;
		char* newNum = malloc(strlen(f) + strlen(num) + 1);
		strcpy(newNum, f);
		strcpy(newNum + strlen(f), num + idx);

		delAddSort(l1, newNum);
		free(newNum);
		n = n->next;
	}
}

void delDeleteList (deList* l) {

	delNode* n = l->first->next;
	while (n != l->last) {
		n = n->next;
		delRemoveFront(l);
	}

	free(l->first->number);
	free(l->first);
	free(l->last->number);
	free(l->last);
	free(l);
}

bool delIsEmpty (deList* l) {
	
	return l->first->next == l->last;
}