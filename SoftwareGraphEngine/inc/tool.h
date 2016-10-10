#ifndef _SGE_TOOL_H_
#define _SGE_TOOL_H_

#include <Windows.h>
#include <stdio.h>
#include "sgemath.h"

// pi defines
#define PI         ((float)3.141592654f)
#define PI2        ((float)6.283185307f)
#define PI_DIV_2   ((float)1.570796327f)
#define PI_DIV_4   ((float)0.785398163f) 
#define PI_INV     ((float)0.318309886f) 

#define FIXP16_SHIFT     16
#define FIXP16_MAG       65536
#define FIXP16_DP_MASK   0x0000ffff
#define FIXP16_WP_MASK   0xffff0000
#define FIXP16_ROUND_UP  0x00008000

// these read the keyboard asynchronously
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

// this builds a 16 bit color value in 5.5.5 format (1-bit alpha mode)
#define _RGB16BIT555(r,g,b) ((b & 31) + ((g & 31) << 5) + ((r & 31) << 10))

// this builds a 16 bit color value in 5.6.5 format (green dominate mode)
#define _RGB16BIT565(r,g,b) ((b & 31) + ((g & 63) << 5) + ((r & 31) << 11))

// this builds a 24 bit color value in 8.8.8 format 
#define _RGB24BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) )

// this builds a 32 bit color value in A.8.8.8 format (8-bit alpha mode)
#define _ARGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))

#define _RGBA32BIT(r, g, b, a) ((a) + ((b) << 8) + ((g) << 16) + ((r) << 24))

#define SET_BIT(word,bit_flag)   ((word)=((word) | (bit_flag)))
#define RESET_BIT(word,bit_flag) ((word)=((word) & (~bit_flag)))

// used to compute the min and max of two expresions
#define MIN(a, b)  (((a) < (b)) ? (a) : (b)) 
#define MAX(a, b)  (((a) > (b)) ? (a) : (b)) 

// used for swapping algorithm
#define SWAP(a,b,t) {t=a; a=b; b=t;}

// some math macros
#define DEG_TO_RAD(ang) ((ang)*PI/180.0)
#define RAD_TO_DEG(rads) ((rads)*180.0/PI)

#define RAND_RANGE(x,y) ( (x) + (rand()%((y)-(x)+1)))


//日志文件
int Open_Error_File(char *filename, FILE *fp_override = 0);
int Close_Error_File(void);
int Write_Error(char *string, ...);

// function ptr to RGB16 builder
extern USHORT(*RGB16Bit)(int r, int g, int b);

// root functions
extern USHORT RGB16Bit565(int r, int g, int b);
extern USHORT RGB16Bit555(int r, int g, int b);

typedef struct RGBAV1_TYPE
{
	union
	{
		int rgba;
		unsigned char rgba_M[4];
		struct
		{
			unsigned char a;
			unsigned char b;
			unsigned char g;
			unsigned char r;
		};
	};
}RGBAV1, *RGBAV1_PTR;

typedef struct ARGBV1_TYPE
{
	union
	{
		int argb;
		unsigned char rgba_M[4];
		struct
		{
			unsigned char b;
			unsigned char g;
			unsigned char r;
			unsigned char a;
		};
	};
}ARGBV1, *ARGBV1_PTR;

// container structure for bitmaps .BMP file
typedef struct BITMAP_FILE_TAG
{
	BITMAPFILEHEADER bitmapfileheader;  // this contains the bitmapfile header
	BITMAPINFOHEADER bitmapinfoheader;  // this is all the info including the palette
	PALETTEENTRY     palette[256];      // we will store the palette here
	UCHAR            *buffer;           // this is a pointer to the data

} BITMAP_FILE, *BITMAP_FILE_PTR;

// the simple bitmap image
typedef struct BITMAP_IMAGE_TYP
{
	int state;          // state of bitmap
	int attr;           // attributes of bitmap
	int x, y;            // position of bitmap
	int width, height;  // size of bitmap
	int num_bytes;      // total bytes of bitmap
	int bpp;            // bits per pixel
	UCHAR *buffer;      // pixels of bitmap

} BITMAP_IMAGE, *BITMAP_IMAGE_PTR;

// blinking light structure
typedef struct BLINKER_TYP
{
	// user sets these
	int color_index;         // index of color to blink
	PALETTEENTRY on_color;   // RGB value of "on" color
	PALETTEENTRY off_color;  // RGB value of "off" color
	int on_time;             // number of frames to keep "on" 
	int off_time;            // number of frames to keep "off"

	// internal member
	int counter;             // counter for state transitions
	int state;               // state of light, -1 off, 1 on, 0 dead
} BLINKER, *BLINKER_PTR;

// bitmap defines
#define BITMAP_ID            0x4D42 // universal id for a bitmap
#define BITMAP_STATE_DEAD    0
#define BITMAP_STATE_ALIVE   1
#define BITMAP_STATE_DYING   2 
#define BITMAP_ATTR_LOADED   128

#define BITMAP_EXTRACT_MODE_CELL  0
#define BITMAP_EXTRACT_MODE_ABS   1

#define MAX_COLORS_PALETTE  256

// simple bitmap image functions
int Create_Bitmap(BITMAP_IMAGE_PTR image, int x, int y, int width, int height, int bpp = 8);
int Destroy_Bitmap(BITMAP_IMAGE_PTR image);
int Draw_Bitmap(BITMAP_IMAGE_PTR source_bitmap, UCHAR *dest_buffer, int lpitch, int transparent);
int Draw_Bitmap16(BITMAP_IMAGE_PTR source_bitmap, UCHAR *dest_buffer, int lpitch, int transparent);
int Load_Image_Bitmap(BITMAP_IMAGE_PTR image, BITMAP_FILE_PTR bitmap, int cx, int cy, int mode);
int Load_Image_Bitmap16(BITMAP_IMAGE_PTR image, BITMAP_FILE_PTR bitmap, int cx, int cy, int mode);
int Scroll_Bitmap(BITMAP_IMAGE_PTR image, int dx, int dy = 0);

int Copy_Bitmap(BITMAP_IMAGE_PTR dest_bitmap, int dest_x, int dest_y,
	BITMAP_IMAGE_PTR source_bitmap, int source_x, int source_y,
	int width, int height);

int Flip_Bitmap(UCHAR *image, int bytes_per_line, int height);

// bitmap file functions
int Load_Bitmap_File(BITMAP_FILE_PTR bitmap, char *filename);
int Unload_Bitmap_File(BITMAP_FILE_PTR bitmap);

int Load_Bitmap_File2(BITMAP_FILE_PTR bitmap, char *filename);

int Load_Bitmap_PCX_File(BITMAP_FILE_PTR bitmap, char *filename);

char *Extract_Filename_From_Path(char *filepath, char *filename);

#endif