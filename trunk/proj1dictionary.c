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

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 4091)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj1dictionary.h"
#include "proj1error.h"

struct dictionary_t* dictionary_create()
{
	struct dictionary_t* result = (struct dictionary_t*)
										malloc(sizeof(struct dictionary_t));
	
	izp_assert(result, "Nedostatek pameti");

	result->count = 0;
	result->array_size = 16;
	result->array = (struct dictionary_pair_t*)malloc(
			(size_t)(result->array_size) * sizeof(struct dictionary_pair_t));

	result->get       = __dictionary_get;
	result->set       = __dictionary_set;
	result->remove    = __dictionary_remove;
	result->increment = __dictionary_increment;
	result->decrement = __dictionary_decrement;
	result->sort      = __dictionary_sort;

	izp_assert(result->array, "Nedostatek pameti");

	return result;
}

void dictionary_destroy(struct dictionary_t* dic)
{
	izp_assert(dic, "Neplatny ukazatel");

	for (int i = 0; i < dic->count; ++i)
		free(dic->array[i].key);

	free((void*)(dic->array));
	free((void*)dic);
}

int __dictionary_cmpfn(const void* p1, const void* p2)
{
	izp_assert(p1 && p2, "Neplatny ukazatel");

	struct dictionary_pair_t* dp1 = (struct dictionary_pair_t*)p1;
	struct dictionary_pair_t* dp2 = (struct dictionary_pair_t*)p2;

	return (dp1->value < dp2->value) ? 1 : -1;
}

int __dictionary_get(struct dictionary_t* dic, const char* key)
{
	izp_assert(dic, "Neplatny ukazatel na dictionary_t");
	izp_assert(key, "Neplatny ukazatel na key");

	for (int i = 0; i < dic->count; ++i)
	{
		if (!strcmp(dic->array[i].key, key))
		{
			return dic->array[i].value;
		}
	}

	return -1;
}

void __dictionary_set(struct dictionary_t* dic, const char* key, int val)
{
	izp_assert(dic, "Neplatny ukazatel na dictionary_t");
	izp_assert(key, "Neplatny ukazatel na key");

	for (int i = 0; i < dic->count; ++i)
	{
		if (!strcmp(dic->array[i].key, key))
		{
			dic->array[i].value = val;
			return;
		}
	}

	if (dic->count >= dic->array_size)
	{
		dic->array_size *= 2;
		dic->array = (struct dictionary_pair_t*)realloc((void*)dic->array,
				(size_t)dic->array_size * sizeof(struct dictionary_pair_t));
		izp_assert(dic->array, "Nedostatek pameti");
	}

	dic->array[dic->count].key = (char*)malloc(strlen(key) + 1);
	izp_assert(dic->array[dic->count].key, "Nedostatek pameti");

	strcpy(dic->array[dic->count].key, key);
	dic->array[dic->count].value = val;

	++dic->count;
}

void __dictionary_remove(struct dictionary_t* dic, const char* key)
{
	izp_assert(dic, "Neplatny ukazatel na dictionary_t");
	izp_assert(key, "Neplatny ukazatel na key");

	for (int i = 0; i < dic->count; ++i)
	{
		if (!strcmp(dic->array[i].key, key))
		{
			if (i < (dic->count - 1))
				memmove(&dic->array[i], &dic->array[i + 1],
						dic->count * sizeof(struct dictionary_pair_t));
		}
	}

	--dic->count;
}

int __dictionary_increment(struct dictionary_t* dic, const char* key)
{
	izp_assert(dic, "Neplatny ukazatel na dictionary_t");
	izp_assert(key, "Neplatny ukazatel na key");

	for (int i = 0; i < dic->count; ++i)
	{
		if (!strcmp(dic->array[i].key, key))
		{
			return ++dic->array[i].value;
		}
	}

	__dictionary_set(dic, key, 1);

	return 1;
}

int __dictionary_decrement(struct dictionary_t* dic, const char* key)
{
	izp_assert(dic, "Neplatny ukazatel na dictionary_t");
	izp_assert(key, "Neplatny ukazatel na key");

	for (int i = 0; i < dic->count; ++i)
	{
		if (!strcmp(dic->array[i].key, key))
		{
			return --dic->array[i].value;
		}
	}

	return -1;
}

void __dictionary_sort(struct dictionary_t* dic)
{
	izp_assert(dic, "Neplatny ukazatel na dictionary_t");

	qsort(dic->array,
			dic->count,
			sizeof(struct dictionary_pair_t),
			__dictionary_cmpfn);
}

