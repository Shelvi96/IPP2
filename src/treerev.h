/** @file
 * Interfejs klasy obsługującej drzewo TRIE dla odwracania przekierowań.
 *
 * @author Konrad Owsikowski
 * @copyright Uniwersytet Warszawski
 * @date 14.05.2018
 */

#ifndef TREEREV_H
#define TREEREV_H

/**
 * Struktura przechowująca wirzchołek drzewa odwracania przekierowań.
 * Zawiera listę numerów, z których następuje przekierowanie oraz
 * wskaźniki na kolejne wierzchołki drzewa.
 */
typedef struct revNode {
    deList* phoneNumbers;
    struct revNode* nums[10];
} revNode;

/**
 * Struktura przechowująca drzewo TRIE dla operacji odwracania przekierowania.
 * Przechowuje wskaźnik na korzeń drzewa.
 */
typedef struct revTree {
	revNode* root;
} revTree;

/**
 * Tworzy nowy wierzchołek drzewa.
 */
revNode* revSetNode ();
/**
 * Tworzy nowe drzewo.
 */
revTree* revSetTree ();
/** @brief Usuwa poddrzewo.
 * Usuwa poddrzewo zakorzenione w wierzchołku wskazywanym przez @p n.
 * @param[in] n	- Wskaźnik na korzeń poddrzewa.
 */
void revDeleteSubtree (revNode* n);

/** @brief Dodaje odwrotność przekierowania numeru.
 * Dodaje odwrotność przekierowania numeru @p numadd na numer @p numer.
 * @param[in] t		- wskaźnik na drzewo, do którego dodawane jest przekierowanie.
 * @param[in] numadd- wskaźnik na numer, który jest przekierowywany.
 * @param[in] number- wskaźnik na numer przekierowania.
 * @return	Wskaźnik na pozycję dodanej odwrotności przekierowania w drzewie rev,
 *			lub NULL, jeśli nie udało się dodać przekierowania.
 */
delNode* revAddRev (revTree* t, char const* numadd, char const* number);

/** @brief Znajduje przekierowanie.
 * Znajduje przekierowanie numer @p number w drzewie @p t.
 * @param[in] t		- wskaźnik na drzewo przekierowań.
 * @param[in] number- wskaźnik na numer, dla którego szukamy przekierowania.
 * @return 	Dwukierunkową listę zawierającą odwrócone przekierowanie, lub
 			pustą listę, jeśli przekierowanie nie istnieje.
 */
deList* revFindRev (revTree* t, char const* number);

#endif /* TREEREV_H */
