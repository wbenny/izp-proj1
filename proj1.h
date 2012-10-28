/**
 * @file	proj1.h
 * 			
 * @brief	Hlavni soubor projektu. 			
 *
 * @author	Petr Benes (xbenes35@stud.fit.vutbr.cz)
 * 
 * @date	1.10.2012
 */

#ifndef PROJ1_H_
#define PROJ1_H_

#include "proj1types.h"
#include "proj1dictionary.h"
#include "proj1cmdopt.h"
#include <limits.h>

/**
 * @enum	optflag_t
 *
 * @brief	Flagy pro argumenty prikazove radky. Kazdy flag odpovida prave
 * 			jednomu argumentu.
 */
enum optflag_t
{
	E_OF_NONE    = 0x00,
	E_OF_HELP    = 0x01,
	E_OF_EXTRA   = 0x02	
};

/**
 * @brief	Udrzuje pole struktury cmdarg_t, ktere ma za ukol asociovat
 * 			jednotlive argumenty k flagum.
 */
static struct cmdarg_t opts[] = 
{
	{ "--help", "-h", E_OF_HELP },
	{ "--extra", "-e", E_OF_EXTRA }
}; 

/**
 * @typedef	uchar occurence_t
 *
 * @brief	Definovani datoveho typu "vyskyt".
 */
typedef uchar			occurence_t;

/**
 * @def	OCCURENCE_MAX
 *
 * @brief	Makro definujici maximalni mnozstvi vyskytu.
 * 			Vyuzijeme faktu, ze nejmensi zaporne signed cislo je nejvetsi
 * 			unsigned cislo (dvojkovy doplnek).
 */
#define OCCURENCE_MAX	((occurence_t)(-1))

/**
 * @def	BYTE_SIZE
 *
 * @brief	Makro definujici pocet kombinaci bitu v datovem typu char.
 */
#define BYTE_SIZE		(1 << CHAR_BIT)

/**
 * @struct	charinfo_t
 *
 * @brief	Struktura udrzujici pocet vyskytu ke konkretnimu znaku.
 */
struct charinfo_t
{
	char character;			///< Znak.
	occurence_t occurence;	///< Pocet vyskytu.
};

/**
 * @fn	void process_help(struct cmdoptresult_t* optresult)
 *
 * @brief	Vypise napovedu.
 *
 * @param 	optresult	Nepouzivany.
 */
void process_help(struct cmdoptresult_t* optresult);

/**
 * @fn	void process_extra(struct cmdoptresult_t* optresult,
 * 	int* extra_chars_to_match, int* extra_lines_to_print)
 *
 * @brief	Zpracuje argumenty prikazove radky predane v promenne optresult.
 * 			Zpracovane hodnoty vrati v parametrech extra_chars_to_match
 * 			a extra_lines_to_print.
 *
 * @param [in]	optresult				Struktura obsahujici parametry
 * 										z prikazove radky.
 * @param [out]	extra_chars_to_match	Vystupni parametr, kde bude uvedeno,
 * 										jak budou n-tice velke.
 * @param [out]	extra_lines_to_print	Vystupni parametr, udava, kolik radku
 * 										budeme tisknout.
 */
void process_extra(struct cmdoptresult_t* optresult, int* extra_chars_to_match,
				   int* extra_lines_to_print);

/**
 * @fn	void process_arguments(int argc, char** argv)
 *
 * @brief	Zpracuje argumenty prikazove radky.
 *
 * @param	argc			Pocet parametru.
 * @param	argv			Pole parametru.
 */
void process_arguments(int argc, char** argv);

/**
 * @fn	void init(struct charinfo_t* chars)
 *
 * @brief	Inicializuje strukturu znaku.
 *
 * @param	chars	Pole znaku.
 */
void init(struct charinfo_t* chars);

/**
 * @fn	int compare_by_occurence(const void* p1, const void* p2)
 *
 * @brief	Porovnavaci funkce.
 *
 * @param	p1	Ukazatel na element.
 * @param	p2	Ukazatel na element.
 *
 * @return	Vraci -1 pro posun vyse, 1 pro posun nize.
 */
int compare_by_occurence(const void* p1, const void* p2);

/**
 * @fn	int compare_by_char(const void* p1, const void* p2)
 *
 * @brief	Porovnavaci funkce.
 *
 * @param	p1	Ukazatel na element.
 * @param	p2	Ukazatel na element.
 *
 * @return	Vraci -1 pro posun vyse, 1 pro posun nize.
 */
int compare_by_char(const void* p1, const void* p2);

/**
 * @fn	void print_stats(struct charinfo_t* chars, int lines_to_print)
 *
 * @brief	Vytiskne histogram.
 *
 * @param 	chars 			Pole znaku.
 * @param	lines_to_print	Pocet radku k tisku.
 */
void print_stats(struct charinfo_t* chars, int lines_to_print);

/**
 * @fn	void print_stats_extra(struct dictionary_t* dic, int lines_to_print)
 *
 * @brief	Vytiskne histogram n-tic.
 *
 * @param 	dic   			Slovnik mapujici textove retezce na cisla.
 * @param	lines_to_print	Pocet radku k tisku.
 */
void print_stats_extra(struct dictionary_t* dic, int lines_to_print);

/**
 * @fn	void get_char(struct charinfo_t* chars, int c)
 *
 * @brief	Zpracuje znak a aktualizuje data histogramu.
 *
 * @param [in,out]	chars	Pole znaku.
 * @param	c			 	Novy znak.
 */
void get_char(struct charinfo_t* chars, int c);

/**
 * @fn	void get_input(int lines_to_print)
 *
 * @brief	Funkce k sejmuti znaku ze standardniho vstupu.
 *
 * @param	lines_to_print	Pocet radku k tisku histogramu.
 */
void get_input(int lines_to_print);

/**
 * @fn	void get_input_extra(int lines_to_print, int chars_to_match)
 *
 * @brief	Funkce k sejmuti znaku ze standardniho vstupu pro vytvoreni
 * 			histogramu n-tic.
 *
 * @param	lines_to_print	Pocet radku k tisknuti histogramu.
 * @param	chars_to_match	Velikost n-tice.
 */
void get_input_extra(int lines_to_print, int chars_to_match);

/**
 * @fn	int izp_atoi(const char* str)
 *
 * @brief	Prevede textovy retezec na cele cislo. Nebere v potaz zaporna cisla.
 * 			Bere ohled na mozny integer overflow.
 *
 * @param	str	Textovy retezec urceny k prevodu na celociselny typ.
 *
 * @return	Prevedene cislo.
 */
int izp_atoi(const char* str);

/**
 * @fn	int main(int argc, char** argv)
 *
 * @brief	Entry-point.
 *
 * @param	argc	Pocet parametru.
 * @param	argv	Pole parametru.
 *
 * @return	Exit-code - 0 = uspech, cokoliv jineho = chyba.
 */
int main(int argc, char** argv);


#endif
