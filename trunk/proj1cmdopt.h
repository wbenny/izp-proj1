/**
 * @file	proj1cmdopt.h
 * 			
 * @brief	Funkce pro praci s argumenty prikazove radky		
 *
 * @author	Petr Benes (xbenes35@stud.fit.vutbr.cz)
 * 
 * @date	1.10.2012
 */

#ifndef PROJ1CMDOPT_H_
#define PROJ1CMDOPT_H_

#include "proj1types.h"

/**
 * @struct	cmdarg_t
 *
 * @brief	Struktura pro definovani vlastniho argumentu aplikace.
 * 			Priklad:
 * 			struct cmdarg_t opts[] =
 *			{
 *				{ "--help", "-h", E_OF_HELP },
 *				{ "--extra", "-e", E_OF_EXTRA }
 *			};
 */
struct cmdarg_t
{
	char* name;
	char* short_name;
	int   flag;
};

/**
 * @struct	cmdopt_t
 *
 * @brief	Struktura udrzujici aktualni skupinu parametru.
 */
struct cmdopt_t
{
	struct cmdarg_t* opt;
	int opt_count;

	char** arg_values;
	int arg_count;
	int arg_ptr;
};

/**
 * @struct	cmdoptresult_t
 *
 * @brief	Struktura reprezentujici navratovou hodnotu.
 */
struct cmdoptresult_t
{
	char** arg_values;
	int arg_count;
	int flag;
};

/**
 * @def	cmdopt_create(opt, argv, argc) _cmdopt_create(opt, IZP_COUNTOF(opt),
 * 		argv, argc);
 *
 * @brief	Vytvori instanci cmdopt_t. Makro pouzito kvuli COUNTOF.
 *
 * @param	opt 	Pole, kde jsou asociovany jednotlive argumenty s flagy.
 * @param	argv	argv z funkce main.
 * @param	argc	argc z funkce main.
 */
#define cmdopt_create(opt, argv, argc)\
	_cmdopt_create(opt, IZP_COUNTOF(opt), argv, argc)

struct cmdopt_t* _cmdopt_create(struct cmdarg_t* opt, int opt_count,
	char** arg_values, int arg_count);

/**
 * @fn	void cmdopt_clear_result(struct cmdoptresult_t* result);
 *
 * @brief	Uvolni pamet.
 *
 * @param	result	Result.
 */
void cmdopt_clear_result(struct cmdoptresult_t* result);

/**
 * @fn	void cmdopt_destroy(struct cmdopt_t* result);
 *
 * @brief	Destruktor cmdopt_t.
 *
 * @param	result	Ukazatel na strukturu cmdopt_t.
 */
void cmdopt_destroy(struct cmdopt_t* result);

/**
 * @fn	int cmdopt_get_next_occurence(struct cmdopt_t* state);
 *
 * @brief	Vrati poradi skupiny parametru.
 *
 * @param [in,out]	state	Skupina parametru.
 *
 * @return	Poradi skupiny. Kdyz zadna skupina neexistuje, vrati -1.
 */
int cmdopt_get_next_occurence(struct cmdopt_t* state);

/**
 * @fn	struct cmdoptresult_t* cmdopt_get_next(struct cmdopt_t* state);
 *
 * @brief	Vrati dalsi skupinu parametru.
 * 			
 * @return	Skupina parametru
 */
struct cmdoptresult_t* cmdopt_get_next(struct cmdopt_t* state);

#endif
