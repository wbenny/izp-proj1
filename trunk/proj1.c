/**
 * @file	proj1.c
 * 			
 * @brief	Hlavni soubor projektu. 			
 *
 * @author	Petr Benes (xbenes35@stud.fit.vutbr.cz)
 * 
 * @date	1.10.2012
 */

#ifdef _MSC_VER	// nasazeni roubiku msvc++
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 4091)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "proj1.h"
#include "proj1types.h"
#include "proj1dictionary.h"
#include "proj1error.h"
#include "proj1cmdopt.h"

void process_help(struct cmdoptresult_t* optresult)
{
	IZP_UNUSED(optresult);	// nepouzivame

	const char* help_text =
"+-----------------------------------------------------------------------+\r\n"
"| Program: Tvorba histogramu (projekt IZP #1)               ************|\r\n"
"| Autor:   Petr Benes                                          *********|\r\n"
"|                                                                 ******|\r\n"
"| Pouziti:                                                           ***|\r\n"
"|   ./proj1 [parametry]                                                *|\r\n"
"|                                                                       |\r\n"
"| Popis parametru:                                                      |\r\n"
"|   --help                               Vytiskne napovedu              |\r\n"
"|   -h                                                                  |\r\n"
"|   --extra <pocet_znaku> <pocet_radku>  Zpracovani histogramu n-tic    |\r\n"
"|   -e <pocet_znaku> <pocet_radku>                                      |\r\n"
"|   <pocet_radku>                        Vypise pouze dany pocet radku  |\r\n"
"|                                                                       |\r\n"
"| Bez parametru:                                                        |\r\n"
"|   Vypise vsechna vystupni data                                        |\r\n"
"+-----------------------------------------------------------------------+\r\n"
		;

	puts(help_text);
	exit(EXIT_SUCCESS);
}

void process_extra(struct cmdoptresult_t* optresult, int* extra_chars_to_match,
				   int* extra_lines_to_print)
{
	izp_assert(optresult && extra_chars_to_match && extra_lines_to_print,
				"Neplatny ukazatel");

	// defaultni parametry
	*extra_chars_to_match = 2;
	*extra_lines_to_print = 10;

	if (optresult->arg_count > 0)
		*extra_chars_to_match = izp_atoi(optresult->arg_values[0]);

	if (optresult->arg_count > 1)
		*extra_lines_to_print = izp_atoi(optresult->arg_values[1]);
}

void process_arguments(int argc, char** argv)
{
	struct cmdopt_t* optstate = cmdopt_create(opts, argv, argc);
	struct cmdoptresult_t* optresult = cmdopt_get_next(optstate);
	int extra_chars_to_match,
		extra_lines_to_print,
		lines_to_print = BYTE_SIZE;
	bool extra_flag = false;

	if (!optresult)
	{
		if (argc > 1)
		{
			lines_to_print = izp_atoi(argv[1]);
		}
	}
	else
	{
		switch (optresult->flag)
		{
			case E_OF_HELP:
				process_help(optresult);
				break;

			case E_OF_EXTRA:
				extra_flag = true;
				process_extra(optresult, &extra_chars_to_match,
					&extra_lines_to_print);
				break;

			default:
				izp_assert(0, "Nespravny parametr");
				break;
		}
	}

	cmdopt_clear_result(optresult);
	cmdopt_destroy(optstate);

	//////////////////////////////////////////////////////////////////////////

	!extra_flag ? get_input(lines_to_print) :
			get_input_extra(extra_lines_to_print, extra_chars_to_match);
}

void init(struct charinfo_t* chars)
{
	// pro kazdy znak dosadime pocatecni mnozstvi vyskytu na nulu
	for (int i = 0; i < BYTE_SIZE; ++i)
	{
		chars[i].character = (char)i;
		chars[i].occurence = (occurence_t)0;
	}
}

int compare_by_occurence(const void* p1, const void* p2)
{
	struct charinfo_t* s1 = (struct charinfo_t*)p1;
	struct charinfo_t* s2 = (struct charinfo_t*)p2;

	if (s1->occurence > s2->occurence)
	{
		return -1;
	}
	else if (s1->occurence == s2->occurence)
	{
		if (!((uchar)s1->character > (uchar)s2->character))
			return -1;
		else
			return 1;
	}

	return 1;
}

int compare_by_char(const void* p1, const void* p2)
{
	struct charinfo_t* s1 = (struct charinfo_t*)p1;
	struct charinfo_t* s2 = (struct charinfo_t*)p2;

	if ((uchar)s1->character > (uchar)s2->character)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

void print_stats(struct charinfo_t* chars, int lines_to_print)
{
	// seradime znaky quick-sortem
	if (lines_to_print == BYTE_SIZE)
	{
		qsort(chars, BYTE_SIZE, sizeof(struct charinfo_t), compare_by_char);
	}
	else
	{
		qsort(chars, BYTE_SIZE, sizeof(struct charinfo_t), compare_by_occurence);
	}

	for (int i = 0, lines_printed = 0; i < BYTE_SIZE && lines_printed < lines_to_print; ++i)
	{
		if (!chars[i].occurence)
		{
			continue;
		}

		if (isprint((int)((uchar)chars[i].character)))
		{
			// pokud je znak tisknutelny, vypiseme ho
			printf("%d '%c': ", (uint)((uchar)chars[i].character), chars[i].character);
		}
		else
		{
			// pokud neni, vystacime si s ordinalni hodnotou
			printf("%d: ", (uint)((uchar)chars[i].character));
		}

		if (chars[i].occurence < OCCURENCE_MAX)
		{
			printf("%d", chars[i].occurence);
		}
		else
		{
			// kdyz jsme temer dosahli integer overflow, vypiseme NNN
			printf("NNN");
		}

		printf("\r\n");
		lines_printed++;
	}
}

void print_stats_extra(struct dictionary_t* dic, int lines_to_print)
{
	for (int i = 0; i < dic->count && i < lines_to_print; ++i)
	{
		putchar('\'');
		
		// kl (key length) je vytvoren primo ve for cyklu
		for (int i2 = 0, kl = (int)strlen(dic->array[i].key); i2 < kl; ++i2)
		{
			if (isprint((int)((uchar)dic->array[i].key[i2])))
			{
				printf("%c", dic->array[i].key[i2]);
			}
			else
			{
				printf("\\x%02X", ((uint)((uchar)dic->array[i].key[i2])));
			}
		}

		putchar('\'');

		printf(": %d\r\n", dic->array[i].value);
	}
}

void get_char(struct charinfo_t* chars, int c)
{
	izp_assert(c >= 0 && c < BYTE_SIZE,
				"Neplatny rozsah ordinalni hodnoty znaku");

	if (chars[c].occurence != OCCURENCE_MAX)
		++chars[c].occurence;
}

void get_input(int lines_to_print)
{
	struct charinfo_t chars[BYTE_SIZE];
	int c;

	init(chars);

	while ((c = getchar()) != EOF)
		get_char(chars, c);

	print_stats(chars, lines_to_print);
}

void get_input_extra(int lines_to_print, int chars_to_match)
{
	int c;
	size_t buff_length = 0;
	size_t buff_size = 32;
	char* buffer = (char*)malloc(buff_size);

	izp_assert(buffer, "Nedostatek pameti");

	while ((c = getchar()) != EOF)
	{
		buffer[buff_length++] = c;

		if (buff_length >= buff_size)
		{
			buff_size *= 2;
			buffer = (char*)realloc((void*)buffer, buff_size);
			izp_assert(buffer, "Nedostatek pameti");
		}
	}

	buffer[buff_length] = '\0';

	//////////////////////////////////////////////////////////////////////////

	{
		char* substr_buff = (char*)malloc((size_t)(chars_to_match + 1));
		struct dictionary_t* dic = dictionary_create();

		izp_assert(substr_buff, "Nedostatek pameti");
		izp_assert(dic, "Nedostatek pameti");

		for (size_t i = 0; i < buff_length; ++i)
		{
			strncpy(substr_buff, &buffer[i], chars_to_match);
			substr_buff[chars_to_match] = '\0';

			if ((int)strlen(substr_buff) == chars_to_match)
				dic->increment(dic, substr_buff);
		}

		dic->sort(dic);

		print_stats_extra(dic, lines_to_print);

		dictionary_destroy(dic);

		free(substr_buff);
	}

	free(buffer);
}

int izp_atoi(const char* str)
{
	int result = 0, prev_result;

	izp_assert(str, "Neplatny ukazatel");

	while (isdigit(*str))
	{
		prev_result = result;
		result = result * 10 + *str - '0';

		izp_assert(prev_result <= result, "Integer overflow");

		str++;
	}

	return result;
}

int main(int argc, char** argv)
{
	process_arguments(argc, argv);
	return EXIT_SUCCESS;
}
