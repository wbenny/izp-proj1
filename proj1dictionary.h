/**
 * @file	proj1dictionary.c
 * 			
 * @brief	Funkce reprezentujici slovnik, ktery mapuje textovy retezec
 * 			na cislo.
 *
 * @author	Petr Benes (xbenes35@stud.fit.vutbr.cz)
 * 
 * @date	1.10.2012
 */

#ifndef PROJ1DICTIONARY_H_
#define PROJ1DICTIONARY_H_

/**
 * @struct	dictionary_pair_t
 *
 * @brief	Slovnikovy zaznam. Textovy retezec nalezi prirazenemu cislu.
 */

struct dictionary_pair_t
{
	char* key;	///< Klic
	int value;	///< Hodnota
};

/**
 * @struct	dictionary_t
 *
 * @brief	Pseudo-trida pro slovnik mapujici textove retezce na cela cisla.
 */
struct dictionary_t
{
	struct dictionary_pair_t* array;	///< Ukazatel na pole zaznamu (paru).
	int array_size;						///< Velikost alokovaneho mista v poli.
	int count;							///< Pocet prvku v poli.

	/**
	 * @fn	int (*get) (struct dictionary_t*, const char*);
	 *
	 * @brief	Vrati hodnotu daneho klice.
	 *
	 * @param [in,out]	parameter1	Ukazatel na slovnik.
	 * @param	parameter2		  	Ukazatel na klic.
	 *
	 * @return	Hodnota klice.
	 */
	int  (*get)      (struct dictionary_t*, const char*);

	/**
	 * @fn	void (*set) (struct dictionary_t*, const char*, int);
	 *
	 * @brief	Nastavi hodnotu daneho klice.
	 *
	 * @param [in,out]	parameter1	Ukazatel na slovnik.
	 * @param	parameter2		  	Ukazatel na klic.
	 * @param	parameter3		  	Hodnota klice.
	 */
	void (*set)      (struct dictionary_t*, const char*, int);

	/**
	 * @fn	void (*remove) (struct dictionary_t*, const char*);
	 *
	 * @brief	Odstrani zaznam ze slovniku.
	 *
	 * @param [in,out]	parameter1	Ukazatel na slovnik.
	 * @param	parameter2		  	Ukazatel na klic.
	 */
	void (*remove)   (struct dictionary_t*, const char*);

	/**
	 * @fn	int (*increment)(struct dictionary_t*, const char*);
	 *
	 * @brief	Inkrementuje hodnotu daneho klice.
	 *
	 * @param [in,out]	parameter1	Ukazatel na slovnik.
	 * @param	parameter2		  	Ukazatel na klic.
	 *
	 * @return	Inkrementovana hodnota klice.
	 */
	int  (*increment)(struct dictionary_t*, const char*);

	/**
	 * @fn	int (*decrement)(struct dictionary_t*, const char*);
	 *
	 * @brief	Dekrementuje hodnotu daneho klice.
	 *
	 * @param [in,out]	parameter1	Ukazatel na slovnik.
	 * @param	parameter2		  	Ukazatel na klic.
	 *
	 * @return	Dekrementovana hodnota klice.
	 */
	int  (*decrement)(struct dictionary_t*, const char*);

	/**
	 * @fn	void (*sort) (struct dictionary_t*);
	 *
	 * @brief	Setridi klice podle hodnot.
	 *
	 * @param [in,out]	parameter1	Ukazatel na slovnik
	 */

	void (*sort)     (struct dictionary_t*);
};

/**
 * @fn	struct dictionary_t* dictionary_create ();
 *
 * @brief	Vytvori instanci slovniku.
 * 			
 * @return	Instance slovniku.
 */

struct dictionary_t* dictionary_create ();

/**
 * @fn	void dictionary_destroy(struct dictionary_t* dic);
 *
 * @brief	Destruktor slovniku.
 *
 * @param [in,out]	dic	Ukazatel na slovnik.
 */
void dictionary_destroy(struct dictionary_t* dic);

// funkce jsou namapovane na ukazatele funkci ve strukture dictionary_t
int		__dictionary_cmpfn    (const void* p1, const void* p2);
int		__dictionary_get      (struct dictionary_t* dic, const char* key);
void	__dictionary_set      (struct dictionary_t* dic, const char* key,
							   int val);
void	__dictionary_remove   (struct dictionary_t* dic, const char* key);
int		__dictionary_increment(struct dictionary_t* dic, const char* key);
int		__dictionary_decrement(struct dictionary_t* dic, const char* key);
void	__dictionary_sort     (struct dictionary_t* dic);

#endif
