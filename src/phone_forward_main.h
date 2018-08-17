/** @file
 * Interfejs klasy kończącej parsowanie i wypisującej wyniki.
 *
 * @author Konrad Owsikowski
 * @copyright Uniwersytet Warszawski
 * @date 14.05.2018
 */

#ifndef __PHONE_FORWARD_MAIN_H__
#define __PHONE_FORWARD_MAIN_H__

 /**
 * Struktura przechowująca pojedynczą bazę przekierowań.
 */
typedef struct FwdBase {
    char* id;
    PhoneForward* base;
} FwdBase;

/** @brief Tworzy nową bazę przekierowań
 * Tworzy nową bazę przekierowań o nazwie @p id.
 * @param[in] id	- nazwa nowej bazy.
 * @return wskaźnik na nowo stworzoną bazę.
 */
FwdBase* makeBase (char* id);

/** @brief Ustawia baze.
 * Ustawia bazę przekierowań o podanej nazwie. Tworzy nową bazę, jeśli jeszcze
 * taka nie istnieje, lub ustawia wskaźnik na bazę o tej nazwie
 * @param[in] b	- nazwa bazy.
 * @return false, gdy nie udało się zarezerwować pamięci, true gdy wszystko ok.
 */
bool setBase (char* b);

/** @brief Usuwa bazę przekierowań.
 * Szuka wskazaną bazę przekierowań i usuwa ją. Przestawia elementy w tablicy
 * tak, by nie tworzyły się niepotrzebne dziury.
 * @param[in] b		- nazwa bazy.
 * @param[in] sc	- numer pierwszego znaku bieżącej operacji.
 * @return false, gdy baza nie istnieje lub true, gdy
 * usuwanie przebiegło pomyślnie.
 */
bool delBase (char* b, int sc);

/** @brief Usuwa wszystkie bazy.
 * Usuwa wszystkie istniejące bazy przekierowań numerów.
 */
void delBases ();

#endif /* __PHONE_FORWARD_MAIN_H__ */