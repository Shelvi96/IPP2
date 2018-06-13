/** @file
 * Interfejs klasy obsługującej listy dwukierunkowe.
 *
 * @author Konrad Owsikowski
 * @copyright Uniwersytet Warszawski
 * @date 14.05.2018
 */

#ifndef DOUBLE_ENDED_LIST_H
#define DOUBLE_ENDED_LIST_H

/**
 * Struktura przechowująca pojedyncze elementy listy dwustronnej.
 * Zawiera wskaźniki na sąsiadów oraz wartość, którą przechowuje.
 */
typedef struct delNode {
    char* number;
    struct delNode* prev;
    struct delNode* next;
} delNode;

/**
 * Struktura przechowująca dwukierunkową listę elementów.
 * Inicjalizowana pustymi Node'ami wskazującymi na siebie.
 * Są to strażnicy listy.
 */
typedef struct deList {
	delNode* first;
	delNode* last;
} deList;

/** @brief Tworzy nowy element listy.
 * Tworzy nowy element listy i inicjalizuje go wartością x.
 * @param[in] x -	wskaźnik na napis, którym ma zostać zainicjalizowany
 *					nowy element listy.
 * @return Wskaźnik na utworzony element listy.
 */
delNode* delSetNode(char const* x);

/** @brief Tworzy nową listę.
 * Tworzy nową listę i inicjalizuje strażników.
 * @return Nowa lista lub NULL, gdy zabrakło pamięci.
 */
deList* delSetList ();

/** @brief Dodaje element do listy.
 * Dodaje element na początek listy.
 * @param[in] l - wskaźnik na listę, do której ma zostać dodany element.
 * @param[in] x	- wskaźnik na element, który chcemy dodać.
 */
void delAddFront (deList* l, char const* x);

/** @brief Dodaje element do listy.
 * Dodaje element tak, by lista była posortowana leksykograficznie.
 * @param[in] l - wskaźnik na listę, do której ma zostać dodany element.
 * @param[in] x	- wskaźnik na element, który chcemy dodać.
 */
void delAddSort (deList* l, char const* x);

/** @brief Odczytuje element.
 * Odczytuje z listy element na wskazanej pozycji.
 * @param[in] l 	- wskaźnik na listę, z której chcemy odczytać element.
 * @param[in] index - numer elementu, który chcemy odczytać z listy.
 * @return Wskaźnik na znaleziony element lub NULL, gdy nie udało się go znaleźć
 */
char const* delGetIndex (deList* l, int index);

/** @brief Usuwa element.
 * Usuwa element z początku listy.
 * @param[in] l - wskaźnik na listę, z której chcemy usunąć element
 */
void delRemoveFront (deList* l);
/** @brief Usuwa wskazany element z listy.
 * Usuwa element wskazywany przez @p n.
 * @param[in] n - wskaźnik na element, który chcemy usunąć.
 */
void delRemoveNode (delNode* n);

/** @brief Kopiuje listę.
 * Kopiuje listę @p l2 do listy @p l1. Dokonuje zamiany prefiksu
 * długości @p idx ze wszystkich elementów listy @p l2 na prefiksy @p num.
 * Ustawia nowo utworzone numery w porządku leksykograficznym.
 * @param[in] l1	- lista, do której kopiowane są elementy.
 * @param[in] l2	- lista, z której kopiowane są elementy.
 * @param[in] num	- numer, który jest podmieniany za prefiksy.
 * @param[in] idx 	- długość prefiksu, który należy podmienić.
 */
void delCopyList (deList* l1, deList* l2, char const* num, unsigned int idx);
/** @brief Usuwa listę.
 * Usuwa listę wskazywaną przez @p l.
 * @param[in] l	- wskaźnik na listę, która zostanie usunięta.
 */
void delDeleteList (deList* l);

/** @brief Sprawdza, czy list jest pusta
 * @return true, jeśli lista @p l jest pusta, false w przeciwnym wypadku.
 */
bool delIsEmpty (deList* l);

#endif /* DOUBLE_ENDED_LIST_H */
