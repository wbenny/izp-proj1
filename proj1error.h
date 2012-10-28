/**
 * @file	proj1error.h
 * 			
 * @brief	Funkce pro osetreni chyb, atd...
 *
 * @author	Petr Benes (xbenes35@stud.fit.vutbr.cz)
 * 
 * @date	1.10.2012
 */

#ifndef PROJ1ERROR_H_
#define PROJ1ERROR_H_

#include <stdarg.h>

// platform-dependent __func__ makro
// [inspirace: Libmysql - libmysql/include/my_global.h]
#if defined(__GNUC__)
#  if __GNUC__ >= 2
#    define __func__ __FUNCTION__
#  else
#    define __func__ "<unknown>"
#  endif
#elif defined(_MSC_VER)
#  if _MSC_VER < 1300
#    define __func__ "<unknown>"
#  else
#    define __func__ __FUNCTION__
#  endif
#elif defined(__BORLANDC__)
#  define __func__ __FUNC__
#else
#  define __func__ "<unknown>"
#endif

/**
 * @def	izp_assert(expr, msg) __izp_assert(!!(expr), __FILE__, __LINE__,
 * 	__func__, (#expr), msg);
 *
 * @brief	Vlastni a lepsi assert funkce. Vyraz se vyhodnocuje v makru
 * 			a je predan funkci __izp_assert. Dvojity vykricnik funguje jako
 * 			prevod na bool (dvojita negace,
 * 			vysledek nalezi jednomu prvku z [0,1]).
 * 			Plati, ze:	!n    => { n = N \ 0 } = 0
 * 						!n    => { n = 0 } = 1
 * 			Tim padem:	!(!n) => { n = N \ 0 } = 1
 * 						!(!n) => { n = 0 } = 0
 * 			
 * 			Pro lepsi pochopeni:
 * 			+---+----+-----+
 * 			| n | !n | !!n |
 * 			+---+----+-----+
 * 			| 0 | 1  | 0   |
 * 			+---+----+-----+
 * 			| 1 | 0  | 1   |
 * 			+---+----+-----+
 * 			| 2 | 0  | 1   |
 * 			+---+----+-----+
 * 			|-1 | 0  | 1   |
 * 			+---+----+-----+ 
 * 			Dale je funkci predan nazev souboru, cislo radku a nazev funkce,
 * 			ktera assert vola.
 * 			Diky makru neni nutne tyto parametry rucne zadavat.
 * 			V pripade, ze je definovano makro NDEBUG, toto makro nic neprovede.
 *
 * @param	expr	Vyraz k vyhodnoceni.
 * @param	msg 	Zprava, ktera bude zobrazena, pokud vyraz skonci neuspechem.
 */
#ifdef NDEBUG
#define izp_assert(expr, msg)
#else
#define izp_assert(expr, msg)	__izp_assert(!!(expr), __FILE__, __LINE__,\
	__func__, (#expr), msg)
#endif

/**
 * @fn	void print_error(const char* format, ...);
 *
 * @brief	Vytiskne formatovane chybovou hlasku na stderr podobne,
 * 			jako printf().
 *
 * @param	format	Format vystupniho retezce. Podobny jako u printf().
 */
void print_error(const char* format, ...);

/**
 * @fn	void __izp_assert(int expression, const char *filename, int line,
 * 	const char *fn, const char *expr, const char *msg);
 *
 * @brief	Hlavni funkce assertu.
 *
 * @param	expression	Vysledek vyrazu.
 * @param	filename  	Nazev souboru.
 * @param	line	  	Cislo radku.
 * @param	fn		  	Nazev funkce.
 * @param	expr	  	Vyraz jako string.
 * @param	msg		  	Zprava.
 */
void __izp_assert(int expression, const char* filename, int line,
				  const char* fn, const char* expr, const char* msg);

#endif
