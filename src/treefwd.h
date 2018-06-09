/** @file
 * Interfejs klasy obsługującej drzewo TRIE dla przekierowań.
 *
 * @author Konrad Owsikowski
 * @copyright Uniwersytet Warszawski
 * @date 14.05.2018
 */

#ifndef TREEFWD_H
#define TREEFWD_H

/**
 * Struktura przechowująca wirzchołek drzewa przekierowań.
 * Zawiera wskaźnik na numer, na który następuje przekierowanie, wskaźnik
 * na odpowiadającą pozycję numeru w drzewie rev (przyspiesza usuwanie
 * przekierowania) oraz wskaźniki na kolejne wierzchołki drzewa.
 */
typedef struct fwdNode {
    char const* numFwd;
    delNode* pointRev;
    struct fwdNode* nums[10];
} fwdNode;

/**
 * Struktura przechowująca drzewo TRIE dla operacji przekierowania.
 * Przechowuje wskaźnik na korzeń drzewa.
 */
typedef struct fwdTree {
	fwdNode* root;
} fwdTree;

/**
 * Tworzy nowy wierzchołek drzewa.
 */
fwdNode* fwdSetNode ();
/**
 * Tworzy nowe drzewo.
 */
fwdTree* fwdSetTree ();
/** @brief Usuwa poddrzewo.
 * Usuwa poddrzewo zakorzenione w wierzchołku wskazywanym przez @p n.
 * @param[in] n	- Wskaźnik na korzeń poddrzewa.
 */
void fwdDeleteSubtree (fwdNode* n);

/** @brief Dodaje przekierowanie numeru.
 * Dodaje przekierowanie numeru @p numadd na numer @p numer. Zapamiętuje
 * pozycję odwrotności przekierowania numeru w drzewie rev.
 * @param[in] t		- wskaźnik na drzewo, do którego dodawane jest przekierowanie.
 * @param[in] numadd- wskaźnik na numer, który jest przekierowywany.
 * @param[in] number- wskaźnik na numer przekierowania.
 * @param[in] r		- wskaźnik na pozycję odwrotności przekierowania.
 * @return	True, jeśli udało się dodać przekierowanie lub
 * 			false w przeciwnym wypadku
 */
bool fwdAddFwd (fwdTree* t, char const* numadd, char const* number, delNode* r);
/** @brief Usuwa przekierowanie.
 * Usuwa przekierowania numerów, których prefiksem jest numer @p number.
 * @param[in] t		- wskaźnik na drzewo, z którego usuwane jest przekierowanie.
 * @param[in] number- wskaźnik na numer przekierowania, które usuwamy.
 */
void fwdRemoveFwd (fwdTree* t, char const* number);

/** @brief Znajduje przekierowanie.
 * Znajduje przekierowanie numer @p number w drzewie @p t.
 * @param[in] t		- wskaźnik na drzewo przekierowań.
 * @param[in] number- wskaźnik na numer, dla którego szukamy przekierowania.
 * @return 	Dwukierunkową listę zawierającą przekierowanie, lub pustą listę,
 			jeśli przekierowanie nie istnieje.
 */
deList* fwdFindFwd (fwdTree* t, char const* number);

#endif /* TREEFWD_H */
