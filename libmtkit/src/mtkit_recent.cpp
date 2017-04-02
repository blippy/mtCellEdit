/*
	Copyright (C) 2016-2017 Mark Tyler

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program in the file COPYING.
*/

#include "private.h"



mtKit::RecentFile::RecentFile (
	char	const * const	prefix,
	int		const	tot
	)
	:
	total		( tot ),
	prefs_prefix	( strdup ( prefix ) ),
	prefs		()
{
}

mtKit::RecentFile::~RecentFile ()
{
	free ( prefs_prefix );
}

int mtKit::RecentFile::init_prefs (
	mtKit::Prefs	* const	pr
	)
{
	if ( prefs )
	{
		return 1;
	}

	prefs = pr;


	int		i;
	char		* key;
	mtPrefTable	prefs_table[] = {
		{ "", MTKIT_PREF_TYPE_STR, "", NULL, NULL, 0, NULL, NULL },
		{ NULL, 0, NULL, NULL, NULL, 0, NULL, NULL }
		};


	for ( i = 1; i <= total; i++ )
	{
		key = create_key ( i );

		prefs_table[0].key = key;
		prefs->addTable ( prefs_table );

		free ( key );
		key = NULL;
	}

	return 0;
}

char * mtKit::RecentFile::create_key (
	int	const	idx
	)
{
	if ( idx < 1 || idx > total )
	{
		return NULL;
	}


	char		cbuf[20];


	snprintf ( cbuf, sizeof(cbuf), ".%03i", idx );

	return mtkit_string_join ( prefs_prefix, cbuf, NULL, NULL );
}

char const * mtKit::RecentFile::get_filename (
	int	const	idx
	)
{
	char		* const key = create_key ( idx );
	char	const	*	val;


	val = prefs->getString ( key );
	free ( key );

	return val;
}

void mtKit::RecentFile::set_filename (
	char	const * const	name
	)
{
	char		* key;
	char	const	* val;
	int		i;


	if ( ! name )
	{
		return;
	}

	// Search for a current use of this filename
	for ( i = 1; i <= total; i++ )
	{
		key = create_key ( i );
		if ( ! key )
		{
			return;
		}

		val = prefs->getString ( key );
		free ( key );

		if ( ! val )
		{
			return;
		}

		if ( 0 == strcmp ( val, name ) )
		{
			break;
		}
	}


	// We need to duplicate 'name' now as it may be released from prefs
	char * dnam = strdup ( name );
	if ( ! dnam )
	{
		return;
	}

	// Shift items to accommodate the new most recent item
	for ( i = i - 1; i >= 1; i-- )
	{
		key = create_key ( i );
		if ( ! key )
		{
			goto finish;
		}

		val = prefs->getString ( key );
		free ( key );

		if ( ! val )
		{
			goto finish;
		}

		set_filename_idx ( i + 1, val );
	}

	set_filename_idx ( 1, dnam );

finish:
	free ( dnam );
}

void mtKit::RecentFile::set_filename_idx (
	int		const	idx,
	char	const * const	name
	)
{
	char		* const key = create_key ( idx );


	if ( ! key )
	{
		return;
	}

	prefs->set ( key, name );
	free ( key );
}

static void trim_string (
	char		* const	buf,
	int		const	lim_tot
	)
{
	#define SNIP_LEN	5
	char	const	* snip = " ... ";	// length = SNIP_LEN

	char		* spa, * spb;
	int		res, lim_edge, slen;


	lim_edge = lim_tot / 2 - SNIP_LEN;
	slen = mtkit_utf8_len ( (unsigned char *)buf, 0 );

	if ( slen <= lim_tot )
	{
		// String is already short enough
		return;
	}

	res = mtkit_utf8_offset ( (unsigned char *)buf, lim_edge );

	if ( res < 0 )
	{
		return;
	}

	// Place snip text here later
	spa = buf + res;

	res = mtkit_utf8_offset ( (unsigned char *)spa, slen - 2 * lim_edge );

	if ( res < 0 )
	{
		return;
	}

	// Points to the last lim_edge chars in buf string
	spb = spa + res;

	// Move right hand side of snip: all chars and NUL terminator
	memmove ( spa + SNIP_LEN, spb, strlen ( spb ) + 1 );

	// Insert snip text
	memcpy ( spa, snip, SNIP_LEN );
}

int mtKit::snip_filename (
	char	const	* const	txt,
	char		* const	buf,
	size_t		const	buflen,
	int		const	lim_tot
	)
{
	char		* tmp;


	if ( ! txt || strlen ( txt ) < 2 )
	{
		return 1;		// buf not filled
	}

	tmp = mtkit_utf8_from_cstring ( txt );
	if ( ! tmp )
	{
		return 1;		// buf not filled
	}

	mtkit_strnncpy ( buf, tmp, buflen );

	free ( tmp );

	trim_string ( buf, lim_tot );

	return 0;			// buf filled
}

static int match_extension (
	char	const * const	filename,
	char	const * const	ext
	)
	// -3 = OS error
	// -2 = Arg error
	// -1 = no match, else returns offset in 'string' of first non wildcard
	// character match.
{
	char * txt = mtkit_string_join ( "*.", ext, NULL, NULL );

	if ( ! txt )
	{
		return -3;
	}

	int res = mtkit_strmatch ( filename, txt, 0 );

	free ( txt );

	return res;
}

static char * replace_extension (
	char	const	* filename,
	size_t	const	pos,	// Position of . preceding extension to replace
	char	const	* ext
	)
{
	size_t	const	extlen	= strlen ( ext );
	char	* const	nstr	= (char *)malloc ( pos + extlen + 1 + 1 );

	if ( ! nstr )
	{
		return NULL;
	}

	memcpy ( nstr, filename, pos );
	memcpy ( nstr + pos, ".", 1 );
	memcpy ( nstr + pos + 1, ext, extlen + 1 );	// ext & NUL terminator

	return nstr;
}

char * mtKit::set_filename_extension (
	char		const * const	filename,
	char		const * const	ext_a,
	char		const *	const	ext_b,
	char	const * const * const	ext_multi
	)
{
	if ( ! filename || ! ext_a )
	{
		return NULL;
	}

	{
		char const * const ext[] = { ext_a, ext_b, NULL };

		for ( char const * const * st = ext; st[0]; st++ )
		{
			int res = match_extension ( filename, st[0] );

			if ( res > -1 )
			{
				// Extension in filename
				return NULL;
			}
			else if ( res < -1 )
			{
				// Error
				return NULL;
			}
		}
	}

	// No valid extension detected so we must continue

	if ( ext_multi )
	{
		// Remove multi-tier extension, e.g. "tsv.zip"

		for ( char const * const * st = ext_multi; st[0]; st++ )
		{
			int res = match_extension ( filename, st[0] );

			if ( res > -1 )
			{
				// Extension in filename
				return replace_extension ( filename,
					(size_t)res, ext_a );
			}
			else if ( res < -1 )
			{
				// Error
				return NULL;
			}

			// res == -1 (no match) so we must continue
		}
	}

	// Replace current extension (if one exists)
	{
		char const * rchar = strrchr ( filename, '.' );

		if ( rchar )
		{
			return replace_extension ( filename,
				(size_t)(rchar - filename), ext_a );
		}
	}

	// At this point we know that there is no extension in filename
	return mtkit_string_join ( filename, ".", ext_a, NULL );
}

