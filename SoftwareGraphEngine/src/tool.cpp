#include "tool.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>

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