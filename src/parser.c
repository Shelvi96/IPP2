#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

int numOfChar = 1;
int errorChar = -2;
bool isError = false;
bool isComment = false;
bool isDollar = false;
bool isEOF = false;
bool isNums = false;

bool equals (char* a, char* b) {

	if (strlen(a) != strlen(b))
		return false;

	int len = strlen(a);
	for (int i = 0; i < len; ++i) {
		if (a[i] != b[i])
			return false;
	}

	return true;

}

void ignoreComment () {

	char c = getchar();
	char d = getchar();

	int l = 4;
	while (d != EOF && (c != '$' || d != '$')) {
		c = d;
		d = getchar();
		l++;
	}	

	if (d == EOF) {
		isError = true;
		errorChar = -1;
		l -= 2;
	}

	numOfChar += l;
	isDollar = false;
	isComment = false;

}

bool ignoreWhitespaces () {

	char c = getchar();

	int l = 0;
	while (isspace(c) != 0) {
		c = getchar();
		l++;
	}

	numOfChar += l;
	if (c == EOF)
		isEOF = true;
	ungetc(c, stdin);

	if(l > 0)
		return true;
	return false;
}

bool isDigit (char c) {

	if (c >= '0' && c <= '9')
		return true;

	return false;

}

bool isLetter (char c) {

	if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return true;

	return false;

}

bool isNumber (char* lexeme) {

	int len = strlen(lexeme);

	for (int i = 0; i < len; ++i) {
		if (!isDigit(lexeme[i]))
			return false;
	}

	return true;

}

bool isId (char* lexeme) {

	if (isLetter(lexeme[0])) {

		int len = strlen(lexeme);

		for (int i = 1; i < len; ++i) {
			if (!isDigit(lexeme[i]) && !isLetter(lexeme[i]))
				return false;
		}

		return true;

	}

	return false;

}

int findLexemeType (char* lexeme) {

	if (strlen(lexeme) == 0) return -2;
	if (equals(lexeme,"NEW")) return 4;
	if (equals(lexeme,"DEL")) return 5;
	if (equals(lexeme,">")) return 2;
	if (equals(lexeme,"?")) return 3;
	if (isNumber(lexeme)) return 0;
	if (isId(lexeme)) return 1;
	isError = true;
	errorChar = numOfChar;
	return -1;

}

Lexeme makeLexeme(char* lexeme, int sc) {

	Lexeme l;
	l.type = findLexemeType(lexeme);
	l.content = lexeme;
	l.startChar = sc;

	return l;

}

Lexeme getNextLexeme () {

	char c;
	int size = 16, i = 0;
	int sc = 0;
	char* lexeme = malloc(size*sizeof(char));
	lexeme[0] = '\0';

	sc = numOfChar;

	// pojedynczy leksem konczy sie, gdy pojawi sie bialy znak, komentarz lub koniec pliku
	while (true) {

	    // Jesli pojawil sie bialy znak, to ignorujemy je wszystkie i zwracamy
    	// wczytany do tej pory leksem
		if(ignoreWhitespaces() && i > 0)
			break;

		// Wczytujemy kolejny znak, sprawdzamy czy to nie EOF
		c = getchar();
// printf("Aktualny znak: %c ", c);
// printf("numer: %d\n", numOfChar);
		if (c == EOF) {
			isEOF = true;
			break;
		}

		/* ************************************ */
		/*         OBSŁUGA KOMENATRZY           */
		/* ************************************ */
		dolar:
		if (c == '$') {
			c = getchar();

			if (c == EOF) {
				fprintf(stderr, "ERROR EOF\n");
				isEOF = true;
				break;
			}

			if (c != '$') {
				fprintf(stderr, "ERROR %d\n", numOfChar + i);
				isError = true;
				break;
			}

			ignoreComment();
			ignoreWhitespaces();

			if(strlen(lexeme) != 0)
				break;

			sc = numOfChar;
			c = getchar();
			if (c == '$') {
				goto dolar;
			}
			if (c == EOF)
				break;

		}
		else {
			// jak pojawił się jeden dollar ale po nim nie było dollara, to błąd
			if (isDollar) {
				lexeme[--i] = '\0';
				isError = true;
				isDollar = false;
				errorChar = numOfChar + i;	
				break;
			}
		}

		/* ************************************ */

		// Jesli do tej pory pojawil sie TYLKO operator, to bierzemy go
		if (c == '>' && i == 0) {
			lexeme[0] = c;
			lexeme[1] = '\0';
			numOfChar++;
			break;
		}
		if (c == '?' && i == 0) {
			lexeme[0] = c;
			lexeme[1] = '\0';
			numOfChar++;
			break;
		}
		// Jesli pojawil sie teraz operator, ale mamy juz jakies symbole,
		// to zwracamy leksem i odkladamy operator na pozniej
		if (c == '>' && i > 0) {
			ungetc(c, stdin);
			break;
		}
		if (c == '?' && i > 0) {
			ungetc(c, stdin);
			break;
		}
		// Jesli mamy teraz bialy znak, a wczesniej bylo NEW lub DEL,
		// to wczytujemy je jako operator
		if(isspace(c) != 0 && equals(lexeme,"NEW")) {
			break;
		}
		if(isspace(c) != 0 && equals(lexeme,"DEL")) {
			break;
		}
		// Jesli pierwszy znak to cyfra, to znaczy ze wczytujemy numer
		if (i == 0 && isDigit(c)) {
			isNums = true;
		}
		// Jak w trakcie wczytywania numeru pojawi sie litera to przerywamy
		if (isNums && !isDigit(c)) {
			ungetc(c, stdin);
			break;
		}

		// Jesli obecny znak jest prawidlowy, dodajemy go do leksemu,
		// jesli zas jest niedopuszczalny, to przerywamy
		if (isLetter(c) || isDigit(c) || c == '>' || c == '?' || c == '$') {
			lexeme[i++] = c;
			lexeme[i] = '\0';
		}
		else {
			isError = true;
			errorChar = numOfChar + i;
			break;			
		}

		// Jesli leksem nie miesci sie, to powiekszamy pamiec
		if (i == size-1) {
			lexeme = realloc(lexeme, sizeof(char)*(size *= 2));
		}

	}

	Lexeme l = makeLexeme(lexeme, sc);
	isNums = false;

	ignoreWhitespaces();

// printf("Leksem: %s\n", lexeme);

	numOfChar += i;

	return l;

}

void printError () {

	if (errorChar != -2) {

		if (errorChar == -1)
			fprintf(stderr, "ERROR EOF\n");
		else
			fprintf(stderr, "ERROR %d\n", errorChar);

	}

}

bool hasNext () {
	return !isEOF && !isError;
}
