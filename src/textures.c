/*
TEXTURES.C
Monday, August 23, 1993 1:47:25 PM

Friday, May 13, 1994 1:56:03 PM
	precalculate_bitmap_row_addresses() now handles the new RLE shapes, added remap_bitmap().
*/

#include "cseries.h"
#include "textures.h"

#ifdef mpwc
#pragma segment render
#endif

#define MARATHON2

/* ---------- code */

pixel8 *calculate_bitmap_origin(
	struct bitmap_definition *bitmap)
{
	pixel8 *origin;

	origin= (pixel8 *) (((byte *)bitmap) + sizeof(struct bitmap_definition));
	if (bitmap->flags&_COLUMN_ORDER_BIT)
	{
		origin+= bitmap->width*sizeof(pixel8 *);
	}
	else
	{
		origin+= bitmap->height*sizeof(pixel8 *);
	}

	return origin;
}

void erase_bitmap(
	struct bitmap_definition *bitmap,
	long pel)
{
	short rows, columns;
	short row, column;

	assert(bitmap->bytes_per_row!=NONE);

	rows= (bitmap->flags&_COLUMN_ORDER_BIT) ? bitmap->width : bitmap->height;
	columns= (bitmap->flags&_COLUMN_ORDER_BIT) ? bitmap->height : bitmap->width;

	for (row = 0; row < rows; ++row)
	{
		register void *pixels= bitmap->row_addresses[row];

		switch (bitmap->bit_depth)
		{
			case 8:
				for (column = 0; column < columns; ++column) {
					*((pixel8 *)pixels)++ = (pixel8) pel
				}
				break;
			case 16:
				for (column = 0; column < columns; ++column) {
					*((pixel16 *)pixels)++ = (pixel16) pel
				}
				break;

			default:
				halt();
		}
	}

	return;
}

void remap_bitmap(
	struct bitmap_definition *bitmap,
	pixel8 *table)
{
	short row, rows, columns;

	rows= (bitmap->flags&_COLUMN_ORDER_BIT) ? bitmap->width : bitmap->height;
	columns= (bitmap->flags&_COLUMN_ORDER_BIT) ? bitmap->height : bitmap->width;

	if (bitmap->bytes_per_row!=NONE)
	{
		for (row=0;row<rows;++row)
		{
			map_bytes(bitmap->row_addresses[row], table, sizeof(pixel8)*columns);
		}
	}
	else
	{
#ifdef MARATHON1
		short run_count;
		pixel8 *pixels;

		pixels= bitmap->row_addresses[0];
		for (row= 0; row<rows; ++row)
		{
			while (run_count= *((short*)pixels)++)
			{
				if (run_count>0)
				{
					map_bytes(pixels, table, run_count);
					pixels+= run_count;
				}
			}
		}
#endif

#ifdef MARATHON2
		pixel8 *pixels;

		pixels= bitmap->row_addresses[0];
		for (row= 0; row<rows; ++row)
		{
			short first, last;

			first= *((short *)pixels)++, last= *((short *)pixels)++;
			map_bytes(pixels, table, last-first);
			pixels+= last-first;
		}
#endif
	}

	return;
}

/* must initialize bytes_per_row, height and row_address[0] */
void precalculate_bitmap_row_addresses(
	struct bitmap_definition *bitmap)
{
	short row, rows, bytes_per_row;
	pixel8 *row_address, **table;

	rows= (bitmap->flags&_COLUMN_ORDER_BIT) ? bitmap->width : bitmap->height;

	row_address= bitmap->row_addresses[0];
	table= bitmap->row_addresses;
	if ((bytes_per_row= bitmap->bytes_per_row)!=NONE)
	{
		for (row=0;row<rows;++row)
		{
			*table++= row_address;
			row_address+= bytes_per_row;
		}
	}
	else
	{
#ifdef MARATHON1
		for (row= 0; row<rows; ++row)
		{
			short run_count;

			*table++= row_address;
			while (run_count= *((short*)row_address)++)
			{
				if (run_count>0) row_address+= run_count;
			}
		}
#endif

#ifdef MARATHON2
		for (row= 0; row<rows; ++row)
		{
			short first, last;

			*table++= row_address;

			first= *((short *)row_address)++, last= *((short *)row_address)++;
			row_address+= last-first;
		}
#endif
	}

	return;
}

void map_bytes(
	register byte *buffer,
	register byte *table,
	register long size)
{
	while ((size-=1)>=0)
	{
		*buffer= table[*buffer];
		buffer+= 1;
	}

	return;
}

#if 0
long bitmap_size(
	struct bitmap_definition *bitmap)
{
	pixel8 *read= bitmap->row_addresses[0];
	long size;

	if (bitmap->bytes_per_row==NONE)
	{
		short row;

		size= 0;
		for (row= 0; row<rows; ++row)
		{
			short first= *((short *)read)++;
			short last= *((short *)read)++;
			short run_length= last-first;

			read+= run_length;
			size+= 2*sizeof(short) + run_length;
		}
	}
	else
	{
		size= bitmap->width*bitmap->height;
	}

	return size;
}
#endif
