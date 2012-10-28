/**
 * @file	proj1types.h
 * 			
 * @brief	Definovani pomocnych typu a maker.
 *
 * @author	Petr Benes (xbenes35@stud.fit.vutbr.cz)
 * 
 * @date	1.10.2012
 */

#ifndef PROJ1TYPES_H_
#define PROJ1TYPES_H_

// definovani vlastnich unsigned typu + pointer
typedef unsigned char		uchar;
typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned long		ulong;
typedef unsigned long long	ulonglong;
typedef void*				ptr_t;

#ifndef __cplusplus
/**
 * @typedef	uchar bool
 *
 * @brief	Vytvorime si v C vlastni datovy typ bool, jako alias
 * 			na neznamenkovy char.
 */
typedef uchar				bool;
#	define true				((bool)1)
#	define false			((bool)0)
#endif

// nejake makra, ktere se v zivote muzou hodit
#define IZP_COUNTOF(x)		(sizeof(x) / sizeof((x)[0]))
#define IZP_MIN(a, b)		((a) < (b) ? (a) : (b))
#define IZP_MAX(a, b)		((a) > (b) ? (a) : (b))
#define IZP_UNUSED(x)		(void)(x)

#endif
