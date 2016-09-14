#include "tool.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>
#include <io.h>

static FILE *fp_error = NULL;

int Open_Error_File(char *filename, FILE *fp_override)
{
	// this function creates the output error file

	// is user requesting special file handle? stdout, stderr, etc.?
	if (fp_override)
	{
		fp_error = fp_override;
	}
	else
	{
		// test if this file is valid
		fopen_s(&fp_error, filename, "w");
		if (fp_error == NULL)
			return(0);
	}

	// get the current time
	struct _timeb timebuffer;
	char timeline[256];
	char timestring[256];

	_ftime_s(&timebuffer);
	ctime_s(timeline, 256, &(timebuffer.time));

	sprintf_s(timestring, 256, "%.19s.%hu, %s", timeline, timebuffer.millitm, &timeline[20]);

	// write out error header with time
	Write_Error("\nOpening Error Output File (%s) on %s\n", filename, timestring);

	// now the file is created, re-open with append mode

	if (!fp_override)
	{
		fclose(fp_error);
		fopen_s(&fp_error, filename, "a+");
		if (fp_error == NULL)
			return(0);
	}

	// return success
	return(1);

} // end Open_Error_File

///////////////////////////////////////////////////////////

int Close_Error_File(void)
{
	// this function closes the error file

	if (fp_error)
	{
		// write close file string
		Write_Error("\nClosing Error Output File.\n");

		if (fp_error != stdout || fp_error != stderr)
		{
			// close the file handle
			fclose(fp_error);
		}

		fp_error = NULL;

		// return success
		return(1);
	} // end if
	else
		return(0);

} // end Close_Error_File
///////////////////////////////////////////////////////////

int Write_Error(char *string, ...)
{
	// this function prints out the error string to the error file

	char buffer[1024]; // working buffer

	va_list arglist; // variable argument list

	// make sure both the error file and string are valid
	if (!string || !fp_error)
		return(0);

	// print out the string using the variable number of arguments on stack
	va_start(arglist, string);
	vsprintf_s(buffer, 1024, string, arglist);
	va_end(arglist);

	// write string to file
	fprintf(fp_error, buffer);

	// flush buffer incase the system bails
	fflush(fp_error);

	// return success
	return(1);
} // end Write_Error

USHORT(*RGB16Bit)(int r, int g, int b) = NULL;

// FUNCTIONS //////////////////////////////////////////////
USHORT RGB16Bit565(int r, int g, int b)
{
	// this function simply builds a 5.6.5 format 16 bit pixel
	// assumes input is RGB 0-255 each channel
	r >>= 3; g >>= 2; b >>= 3;
	return(_RGB16BIT565((r), (g), (b)));

} // end RGB16Bit565

//////////////////////////////////////////////////////////

USHORT RGB16Bit555(int r, int g, int b)
{
	// this function simply builds a 5.5.5 format 16 bit pixel
	// assumes input is RGB 0-255 each channel
	r >>= 3; g >>= 3; b >>= 3;
	return(_RGB16BIT555((r), (g), (b)));

} // end RGB16Bit555

///////////////////////////////////////////////////////////////////////////////

int Create_Bitmap(BITMAP_IMAGE_PTR image, int x, int y, int width, int height, int bpp)
{
	// this function is used to intialize a bitmap, 8 or 16 bit

	// allocate the memory
	if (!(image->buffer = (UCHAR *)malloc(width*height*(bpp >> 3))))
		return(0);

	// initialize variables
	image->state = BITMAP_STATE_ALIVE;
	image->attr = 0;
	image->width = width;
	image->height = height;
	image->bpp = bpp;
	image->x = x;
	image->y = y;
	image->num_bytes = width*height*(bpp >> 3);

	// clear memory out
	memset(image->buffer, 0, width*height*(bpp >> 3));

	// return success
	return(1);

} // end Create_Bitmap

///////////////////////////////////////////////////////////////////////////////

int Destroy_Bitmap(BITMAP_IMAGE_PTR image)
{
	// this function releases the memory associated with a bitmap

	if (image && image->buffer)
	{
		// free memory and reset vars
		free(image->buffer);

		// set all vars in structure to 0
		memset(image, 0, sizeof(BITMAP_IMAGE));

		// return success
		return(1);

	} // end if
	else  // invalid entry pointer of the object wasn't initialized
		return(0);

} // end Destroy_Bitmap

///////////////////////////////////////////////////////////

int Draw_Bitmap(BITMAP_IMAGE_PTR source_bitmap, UCHAR *dest_buffer, int lpitch, int transparent)
{
	// this function draws the bitmap onto the destination memory surface
	// if transparent is 1 then color 0 (8bit) or 0.0.0 (16bit) will be transparent
	// note this function does NOT clip, so be carefull!!!

	// test if this bitmap is loaded
	if (!(source_bitmap->attr & BITMAP_ATTR_LOADED))
		return(0);

	UCHAR *dest_addr,   // starting address of bitmap in destination
		*source_addr; // starting adddress of bitmap data in source

	UCHAR pixel;        // used to hold pixel value

	int index,          // looping vars
		pixel_x;

	// compute starting destination address
	dest_addr = dest_buffer + source_bitmap->y*lpitch + source_bitmap->x;

	// compute the starting source address
	source_addr = source_bitmap->buffer;

	// is this bitmap transparent
	if (transparent)
	{
		// copy each line of bitmap into destination with transparency
		for (index = 0; index < source_bitmap->height; index++)
		{
			// copy the memory
			for (pixel_x = 0; pixel_x < source_bitmap->width; pixel_x++)
			{
				if ((pixel = source_addr[pixel_x]) != 0)
					dest_addr[pixel_x] = pixel;

			} // end if

			// advance all the pointers
			dest_addr += lpitch;
			source_addr += source_bitmap->width;

		} // end for index
	} // end if
	else
	{
		// non-transparent version
		// copy each line of bitmap into destination

		for (index = 0; index < source_bitmap->height; index++)
		{
			// copy the memory
			memcpy(dest_addr, source_addr, source_bitmap->width);

			// advance all the pointers
			dest_addr += lpitch;
			source_addr += source_bitmap->width;

		} // end for index

	} // end else

	// return success
	return(1);

} // end Draw_Bitmap

///////////////////////////////////////////////////////////////

int Draw_Bitmap16(BITMAP_IMAGE_PTR source_bitmap, UCHAR *dest_buffer, int lpitch, int transparent)
{
	// this function draws the bitmap onto the destination memory surface
	// if transparent is 1 then color 0 (8bit) or 0.0.0 (16bit) will be transparent
	// note this function does NOT clip, so be carefull!!!

	// test if this bitmap is loaded
	if (!(source_bitmap->attr & BITMAP_ATTR_LOADED))
		return(0);

	USHORT *dest_addr,   // starting address of bitmap in destination
		*source_addr; // starting adddress of bitmap data in source

	USHORT pixel;        // used to hold pixel value

	int index,           // looping vars
		pixel_x,
		lpitch_2 = lpitch >> 1; // lpitch in USHORT terms

	// compute starting destination address
	dest_addr = ((USHORT *)dest_buffer) + source_bitmap->y*lpitch_2 + source_bitmap->x;

	// compute the starting source address
	source_addr = (USHORT *)source_bitmap->buffer;

	// is this bitmap transparent
	if (transparent)
	{
		// copy each line of bitmap into destination with transparency
		for (index = 0; index < source_bitmap->height; index++)
		{
			// copy the memory
			for (pixel_x = 0; pixel_x < source_bitmap->width; pixel_x++)
			{
				if ((pixel = source_addr[pixel_x]) != 0)
					dest_addr[pixel_x] = pixel;

			} // end if

			// advance all the pointers
			dest_addr += lpitch_2;
			source_addr += source_bitmap->width;

		} // end for index
	} // end if
	else
	{
		// non-transparent version
		// copy each line of bitmap into destination

		int source_bytes_per_line = source_bitmap->width * 2;

		for (index = 0; index < source_bitmap->height; index++)
		{
			// copy the memory
			memcpy(dest_addr, source_addr, source_bytes_per_line);

			// advance all the pointers
			dest_addr += lpitch_2;
			source_addr += source_bitmap->width;

		} // end for index

	} // end else

	// return success
	return(1);

} // end Draw_Bitmap16

///////////////////////////////////////////////////////////////////////////////

int Load_Image_Bitmap(BITMAP_IMAGE_PTR image,  // bitmap image to load with data
	BITMAP_FILE_PTR bitmap,  // bitmap to scan image data from
	int cx, int cy,   // cell or absolute pos. to scan image from
	int mode)        // if 0 then cx,cy is cell position, else 
	// cx,cy are absolute coords
{
	// this function extracts a bitmap out of a bitmap file

	// is this a valid bitmap
	if (!image)
		return(0);

	UCHAR *source_ptr,   // working pointers
		*dest_ptr;

	// test the mode of extraction, cell based or absolute
	if (mode == BITMAP_EXTRACT_MODE_CELL)
	{
		// re-compute x,y
		cx = cx*(image->width + 1) + 1;
		cy = cy*(image->height + 1) + 1;
	} // end if

	// extract bitmap data
	source_ptr = bitmap->buffer +
		cy*bitmap->bitmapinfoheader.biWidth + cx;

	// assign a pointer to the bimap image
	dest_ptr = (UCHAR *)image->buffer;

	// iterate thru each scanline and copy bitmap
	for (int index_y = 0; index_y < image->height; index_y++)
	{
		// copy next line of data to destination
		memcpy(dest_ptr, source_ptr, image->width);

		// advance pointers
		dest_ptr += image->width;
		source_ptr += bitmap->bitmapinfoheader.biWidth;
	} // end for index_y

	// set state to loaded
	image->attr |= BITMAP_ATTR_LOADED;

	// return success
	return(1);

} // end Load_Image_Bitmap

///////////////////////////////////////////////////////////

int Load_Image_Bitmap16(BITMAP_IMAGE_PTR image,  // bitmap image to load with data
	BITMAP_FILE_PTR bitmap,  // bitmap to scan image data from
	int cx, int cy,   // cell or absolute pos. to scan image from
	int mode)        // if 0 then cx,cy is cell position, else 
	// cx,cy are absolute coords
{
	// this function extracts a 16-bit bitmap out of a 16-bit bitmap file

	// is this a valid bitmap
	if (!image)
		return(0);

	// must be a 16bit bitmap
	USHORT *source_ptr,   // working pointers
		*dest_ptr;

	// test the mode of extraction, cell based or absolute
	if (mode == BITMAP_EXTRACT_MODE_CELL)
	{
		// re-compute x,y
		cx = cx*(image->width + 1) + 1;
		cy = cy*(image->height + 1) + 1;
	} // end if

	// extract bitmap data
	source_ptr = (USHORT *)bitmap->buffer +
		cy*bitmap->bitmapinfoheader.biWidth + cx;

	// assign a pointer to the bimap image
	dest_ptr = (USHORT *)image->buffer;

	int bytes_per_line = image->width * 2;

	// iterate thru each scanline and copy bitmap
	for (int index_y = 0; index_y < image->height; index_y++)
	{
		// copy next line of data to destination
		memcpy(dest_ptr, source_ptr, bytes_per_line);

		// advance pointers
		dest_ptr += image->width;
		source_ptr += bitmap->bitmapinfoheader.biWidth;
	} // end for index_y

	// set state to loaded
	image->attr |= BITMAP_ATTR_LOADED;

	// return success
	return(1);

} // end Load_Image_Bitmap16

///////////////////////////////////////////////////////////

int Scroll_Bitmap(BITMAP_IMAGE_PTR image, int dx, int dy)
{
	// this function scrolls a bitmap

	BITMAP_IMAGE temp_image; // temp image buffer

	// are the parms valid 
	if (!image || (dx == 0 && dy == 0))
		return(0);


	// scroll on x-axis first
	if (dx != 0)
	{
		// step 1: normalize scrolling amount
		dx %= image->width;

		// step 2: which way?
		if (dx > 0)
		{
			// scroll right
			// create bitmap to hold region that is scrolled around
			Create_Bitmap(&temp_image, 0, 0, dx, image->height, image->bpp);

			// copy region we are going to scroll and wrap around
			Copy_Bitmap(&temp_image, 0, 0,
				image, image->width - dx, 0,
				dx, image->height);

			// set some pointers up
			UCHAR *source_ptr = image->buffer;  // start of each line
			int shift = (image->bpp >> 3)*dx;

			// now scroll image to right "scroll" pixels
			for (int y = 0; y < image->height; y++)
			{
				// scroll the line over
				memmove(source_ptr + shift, source_ptr, (image->width - dx)*(image->bpp >> 3));

				// advance to the next line
				source_ptr += ((image->bpp >> 3)*image->width);
			} // end for

			// and now copy it back
			Copy_Bitmap(image, 0, 0, &temp_image, 0, 0,
				dx, image->height);

		} // end if
		else
		{
			// scroll left
			dx = -dx; // invert sign

			// create bitmap to hold region that is scrolled around
			Create_Bitmap(&temp_image, 0, 0, dx, image->height, image->bpp);

			// copy region we are going to scroll and wrap around
			Copy_Bitmap(&temp_image, 0, 0,
				image, 0, 0,
				dx, image->height);

			// set some pointers up
			UCHAR *source_ptr = image->buffer;  // start of each line
			int shift = (image->bpp >> 3)*dx;

			// now scroll image to left "scroll" pixels
			for (int y = 0; y < image->height; y++)
			{
				// scroll the line over
				memmove(source_ptr, source_ptr + shift, (image->width - dx)*(image->bpp >> 3));

				// advance to the next line
				source_ptr += ((image->bpp >> 3)*image->width);
			} // end for

			// and now copy it back
			Copy_Bitmap(image, image->width - dx, 0, &temp_image, 0, 0,
				dx, image->height);

		} // end else
	} // end scroll on x-axis


	// return success
	return(1);

} // end Scroll_Bitmap

///////////////////////////////////////////////////////////

int Copy_Bitmap(BITMAP_IMAGE_PTR dest_bitmap, int dest_x, int dest_y,
	BITMAP_IMAGE_PTR source_bitmap, int source_x, int source_y,
	int width, int height)
{
	// this function copies a bitmap from one source to another

	// make sure the pointers are at least valid
	if (!dest_bitmap || !source_bitmap)
		return(0);

	// do some computations
	int bytes_per_pixel = (source_bitmap->bpp >> 3);

	// create some pointers
	UCHAR *source_ptr = source_bitmap->buffer + (source_x + source_y*source_bitmap->width)*bytes_per_pixel;
	UCHAR *dest_ptr = dest_bitmap->buffer + (dest_x + dest_y  *dest_bitmap->width)  *bytes_per_pixel;

	// now copying is easy :)
	for (int y = 0; y < height; y++)
	{
		// copy this line
		memcpy(dest_ptr, source_ptr, bytes_per_pixel*width);

		// advance the pointers
		source_ptr += (source_bitmap->width*bytes_per_pixel);
		dest_ptr += (dest_bitmap->width*bytes_per_pixel);
	} // end for

	// return success
	return(1);

} // end Copy_Bitmap

///////////////////////////////////////////////////////////

int Load_Bitmap_File(BITMAP_FILE_PTR bitmap, char *filename)
{
	// this function opens a bitmap file and loads the data into bitmap

	int file_handle,  // the file handle
		index;        // looping index

	UCHAR   *temp_buffer = NULL; // used to convert 24 bit images to 16 bit
	OFSTRUCT file_data;          // the file data information

	// open the file if it exists
	if ((file_handle = OpenFile(filename, &file_data, OF_READ)) == -1)
		return(0);

	// now load the bitmap file header
	_lread(file_handle, &bitmap->bitmapfileheader, sizeof(BITMAPFILEHEADER));

	// test if this is a bitmap file
	if (bitmap->bitmapfileheader.bfType != BITMAP_ID)
	{
		// close the file
		_lclose(file_handle);

		// return error
		return(0);
	} // end if

	// now we know this is a bitmap, so read in all the sections

	// first the bitmap infoheader

	// now load the bitmap file header
	_lread(file_handle, &bitmap->bitmapinfoheader, sizeof(BITMAPINFOHEADER));

	// now load the color palette if there is one
	if (bitmap->bitmapinfoheader.biBitCount == 8)
	{
		_lread(file_handle, &bitmap->palette, MAX_COLORS_PALETTE*sizeof(PALETTEENTRY));

		// now set all the flags in the palette correctly and fix the reversed 
		// BGR RGBQUAD data format
		for (index = 0; index < MAX_COLORS_PALETTE; index++)
		{
			// reverse the red and green fields
			int temp_color = bitmap->palette[index].peRed;
			bitmap->palette[index].peRed = bitmap->palette[index].peBlue;
			bitmap->palette[index].peBlue = temp_color;

			// always set the flags word to this
			bitmap->palette[index].peFlags = PC_NOCOLLAPSE;
		} // end for index

	} // end if

	// finally the image data itself
	_lseek(file_handle, -(int)(bitmap->bitmapinfoheader.biSizeImage), SEEK_END);

	// now read in the image
	if (bitmap->bitmapinfoheader.biBitCount == 8 || bitmap->bitmapinfoheader.biBitCount == 16)
	{
		// delete the last image if there was one
		if (bitmap->buffer)
			free(bitmap->buffer);

		// allocate the memory for the image
		if (!(bitmap->buffer = (UCHAR *)malloc(bitmap->bitmapinfoheader.biSizeImage)))
		{
			// close the file
			_lclose(file_handle);

			// return error
			return(0);
		} // end if

		// now read it in
		_lread(file_handle, bitmap->buffer, bitmap->bitmapinfoheader.biSizeImage);

	} // end if
	else
	if (bitmap->bitmapinfoheader.biBitCount == 24)
	{
		// allocate temporary buffer to load 24 bit image
		if (!(temp_buffer = (UCHAR *)malloc(bitmap->bitmapinfoheader.biSizeImage)))
		{
			// close the file
			_lclose(file_handle);

			// return error
			return(0);
		} // end if

		// allocate final 16 bit storage buffer
		if (!(bitmap->buffer = (UCHAR *)malloc(2 * bitmap->bitmapinfoheader.biWidth*bitmap->bitmapinfoheader.biHeight)))
		{
			// close the file
			_lclose(file_handle);

			// release working buffer
			free(temp_buffer);

			// return error
			return(0);
		} // end if

		// now read the file in
		_lread(file_handle, temp_buffer, bitmap->bitmapinfoheader.biSizeImage);

		// now convert each 24 bit RGB value into a 16 bit value
		for (index = 0; index < bitmap->bitmapinfoheader.biWidth*bitmap->bitmapinfoheader.biHeight; index++)
		{
			// build up 16 bit color word
			USHORT color = 0;

			//// build pixel based on format of directdraw surface
			//if (dd_pixel_format == DD_PIXEL_FORMAT555)
			//{
			//	// extract RGB components (in BGR order), note the scaling
			//	UCHAR blue = (temp_buffer[index * 3 + 0] >> 3),
			//		green = (temp_buffer[index * 3 + 1] >> 3),
			//		red = (temp_buffer[index * 3 + 2] >> 3);
			//	// use the 555 macro
			//	color = _RGB16BIT555(red, green, blue);
			//} // end if 555
			//else
			//if (dd_pixel_format == DD_PIXEL_FORMAT565)
			//{
			//	// extract RGB components (in BGR order), note the scaling
			//	UCHAR blue = (temp_buffer[index * 3 + 0] >> 3),
			//		green = (temp_buffer[index * 3 + 1] >> 2),
			//		red = (temp_buffer[index * 3 + 2] >> 3);

			//	// use the 565 macro
			//	color = _RGB16BIT565(red, green, blue);

			//} // end if 565

			// write color to buffer
			((USHORT *)bitmap->buffer)[index] = color;

		} // end for index

		// finally write out the correct number of bits
		bitmap->bitmapinfoheader.biBitCount = 16;

		// release working buffer
		free(temp_buffer);

	} // end if 24 bit
	else
	{
		// serious problem
		return(0);

	} // end else

	// close the file
	_lclose(file_handle);

	// flip the bitmap
	Flip_Bitmap(bitmap->buffer,
		bitmap->bitmapinfoheader.biWidth*(bitmap->bitmapinfoheader.biBitCount / 8),
		bitmap->bitmapinfoheader.biHeight);

	// return success
	return(1);

} // end Load_Bitmap_File

///////////////////////////////////////////////////////////

int Unload_Bitmap_File(BITMAP_FILE_PTR bitmap)
{
	// this function releases all memory associated with "bitmap"
	if (bitmap->buffer)
	{
		// release memory
		free(bitmap->buffer);

		// reset pointer
		bitmap->buffer = NULL;

	} // end if

	// return success
	return(1);

} // end Unload_Bitmap_File

///////////////////////////////////////////////////////////

int Flip_Bitmap(UCHAR *image, int bytes_per_line, int height)
{
	// this function is used to flip bottom-up .BMP images

	UCHAR *buffer; // used to perform the image processing
	int index;     // looping index

	// allocate the temporary buffer
	if (!(buffer = (UCHAR *)malloc(bytes_per_line*height)))
		return(0);

	// copy image to work area
	memcpy(buffer, image, bytes_per_line*height);

	// flip vertically
	for (index = 0; index < height; index++)
		memcpy(&image[((height - 1) - index)*bytes_per_line],
		&buffer[index*bytes_per_line], bytes_per_line);

	// release the memory
	free(buffer);

	// return success
	return(1);

} // end Flip_Bitmap

///////////////////////////////////////////////////////////