/** @file
 * Interfejs klasy przetwarzającej wejście
 *
 * @author Konrad Owsikowski
 * @copyright Uniwersytet Warszawski
 * @date 14.05.2018
 */

#ifndef PARSER_H
#define PARSER_H

/** @brief Struktura przechowująca pojedynczy leksem.
 * Struktura przechowująca pojedynczy leksem.
 * Leksemem może być operator, numer lub identyfikator.
 * Każdy leksem ma swój numer wskazujący jakiego rodzaju leksemem jest.
 */
typedef struct Lexeme {
	int type; 	// numer - 0 | identyfikator - 1 | operator > - 2 | operator ? - 3
				// operator NEW - 4 | operator DEL - 5 | operator @ - 6 
				// ERROR - -1 | EOF - -2
	char* content;
	int startChar;
} Lexeme;

/** 
 * Porównuje dwa ciągi znaków.
 * @retun true, gdy ciągi znaków są równe lub false, w przeciwnym przypadku.
 */
bool equals (char* a, char* b);

/** @brief Pomija komentarz.
 * Pomija wszystkie znaki, dopóki nie napotka znaku końca komentarza '$$'.
 */
void ignoreComment ();

/** Pomija białe znaki.
 * Pomija białe znaki do momentu napotkania znaku innego niż biały.
 * @return true, jeśli został pominięty jakiś znak, false w przeciwnym przypadku.
 */
bool ignoreWhitespaces ();

/**
 * Sprawdza czy znak @p c jest cyfrą.
 * @param[in] c	-	znak, który jest sprawdzany.
 * @return true, jeśli znak jest cyfrą, false w przeciwnym przypadku.
 */
bool isDigit (char c);

/**
 * Sprawdza czy znak @p c jest literą.
 * @param[in] c	-	znak, który jest sprawdzany.
 * @return true, jeśli znak jest literą, false w przeciwnym przypadku.
 */
bool isLetter (char c);

 /**
 * Sprawdza czy ciąg znaków @p lexeme jest ciągiem cyfr.
 * @param[in] lexeme	-	ciąg znaków, który jest sprawdzany.
 * @return true, jeśli składa się tylko z cyfr, false w przeciwnym przypadku.
 */
bool isNumber (char* lexeme);

/**
 * Sprawdza czy ciąg znaków @p lexeme jest ciągiem alfanumerycznym.
 * @param[in] lexeme	-	ciąg znaków, który jest sprawdzany.
 * @return true, jeśli ciąg jest alfanumeryczny, false w przeciwnym przypadku.
 */
bool isId (char* lexeme);

/**
 * Znajduje typ leksemu dla zadanego ciągu znaków.
 * @param[in] lexeme	- ciąg znaków, dla którego szukany jest typ.
 * @return wartość wskazująca rodzaj leksemu.
 */
int findLexemeType (char* lexeme);

/**
 * Tworzy leksem z zadanego ciągu znaków.
 * @param[in] lexeme	- ciąg znaków, z którego tworzymy leksem.
 * @param[in] sc 		- numer pierwszego znaku tego leksemu.
 * @return nowy leksem złożony z ciągu znaków @p lexeme oraz odpowiedniego typu.
 */
Lexeme makeLexeme(char* lexeme, int sc);

/** @brief Wypisuje błąd.
 * Jeśli podczas przetwarzania wejścia pojawił się jakiś błąd, to zostaje on
 * wypisany na wyjście diagnostyczne.
 */
void printError ();

/** @brief Sprawdza, czy istnieje kolejny leksem.
 * Sprawdza, czy istnieje kolejny leksem. W tym celu odczytuje stan zmiennych
 * isError oraz isProblem. Gdy któraś z nich jest ustawiona na true, to nie ma
 * kolejnego leksemu.
 * @return true, jeśli wystąpił błąd, false w przeciwnym wypadku.
 */
bool hasNext ();

/** @brief Zwraca kolejny leksem.
 * Wyszukuje w pliku wejściowym leksem spełniający założenia zadania.
 * @return kolejny leksem.
 */
Lexeme getNextLexeme ();

#endif /* PARSER_H */