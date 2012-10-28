/**
 * @file	proj1error.c
 * 			
 * @brief	Funkce pro osetreni chyb, atd...
 *
 * @author	Petr Benes (xbenes35@stud.fit.vutbr.cz)
 * 
 * @date	1.10.2012
 */

#include <stdio.h>
#include <stdlib.h>
#include "proj1error.h"

void print_error(const char* format, ...)
{
	va_list args;

	va_start(args, format);

	vfprintf(stderr, format, args);

	va_end(args);

	exit(EXIT_FAILURE);
}

void __izp_assert(int expression, const char* filename, int line,
				  const char* fn, const char* expr, const char* msg)
{
	if (!expression)
	{
		if (msg)
		{
			print_error("[!] Nastala chyba v aplikaci!\n"
				"[!] Popis chyby: %s\n"
				"[!] Funkce: %s\n"
				"[!] Soubor: \"%s\"\n"
				"[!] Radek: %d\n"
				"[!] Vyraz (%s) vratil hodnotu false\n",
				msg, fn, filename, line, expr);
		}
		else
		{
			print_error("[!] Nastala chyba v aplikaci!\n"
				"[!] Funkce: %s\n"
				"[!] Soubor: \"%s\"\n"
				"[!] Radek: %d\n"
				"[!] Vyraz (%s) vratil hodnotu false\n",
				fn, filename, line, expr);
		}
	}
}
