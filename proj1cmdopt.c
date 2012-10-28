/**
 * @file	proj1cmdopt.c
 * 			
 * @brief	Funkce pro praci s argumenty prikazove radky		
 *
 * @author	Petr Benes (xbenes35@stud.fit.vutbr.cz)
 * 
 * @date	1.10.2012
 */

#include <stdlib.h>
#include <string.h>
#include "proj1error.h"
#include "proj1cmdopt.h"

struct cmdopt_t* _cmdopt_create(struct cmdarg_t* opt, int opt_count, 
								char** arg_values, int arg_count)
{
	struct cmdopt_t* result = (struct cmdopt_t*)malloc(sizeof(struct cmdopt_t));

	result->opt = opt;
	result->opt_count = opt_count;
	result->arg_values = arg_values;
	result->arg_count = arg_count;
	result->arg_ptr = 1;

	return result;
}

void cmdopt_clear_result(struct cmdoptresult_t* result)
{
	if (result)
		free(result);
}

void cmdopt_destroy(struct cmdopt_t* result)
{
	if (result)
		free(result);
}

int cmdopt_get_next_occurence(struct cmdopt_t* state)
{
	izp_assert(state && state->opt && state->arg_values && state->arg_ptr,
				"Neplatny ukazatel");
	izp_assert(state->arg_ptr < state->arg_count, "Index mimo rozsah");

	for (int i = 0; i < state->opt_count; ++i)
	{
		if ((state->opt[i].name && !strcmp(state->opt[i].name,
										  state->arg_values[state->arg_ptr])) ||
			(state->opt[i].short_name && !strcmp(state->opt[i].short_name,
										  state->arg_values[state->arg_ptr])))
		{
			return i;
		}
	}

	return -1;
}

struct cmdoptresult_t* cmdopt_get_next(struct cmdopt_t* state)
{
	izp_assert(state && state->opt && state->arg_values && state->arg_ptr,
				"Neplatny ukazatel");

	if (state->arg_ptr < state->arg_count)
	{
		int arg_ptr_tmp = state->arg_ptr;
		struct cmdoptresult_t* result =
			(struct cmdoptresult_t*)malloc(sizeof(struct cmdoptresult_t));

		int next_occurence;

		if ((next_occurence = cmdopt_get_next_occurence(state)) != -1)
		{
			result->arg_values = (state->arg_ptr + 1) < state->arg_count ?
								&state->arg_values[state->arg_ptr + 1] : NULL;

			// dalsi vyskyt
			while (++state->arg_ptr < state->arg_count &&
					cmdopt_get_next_occurence(state) == -1)
				;

			result->arg_count = state->arg_ptr - arg_ptr_tmp - 1;
			result->flag = state->opt[next_occurence].flag;

			return result;
		}
	}

	return NULL;
}
