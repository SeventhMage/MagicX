#ifndef _SGE_DRAW_H_
#define _SGE_DRAW_H_

#include "tool.h"

int Clip_Line(int &x1, int &y1, int &x2, int &y2);
int Draw_Clip_Line16(int x0, int y0, int x1, int y1, int color, unsigned char *dest_buffer, int lpitch);
//Bresenham光栅化直线算法
int Draw_Line16(int x0, int y0, int x1, int y1, int color, unsigned char *vb_start, int lpitch);
int Draw_Clip_Line(int x0, int y0, int x1, int y1, int color, unsigned char *dest_buffer, int lpitch);
//Bresenham光栅化直线算法
int Draw_Line(int x0, int y0, int x1, int y1, int color, unsigned char *vb_start, int lpitch);
//以固定颜色画三角形
void Draw_Triangle_2D(int x1, int y1, int x2, int y2, int x3, int y3, int color, unsigned char *dest_buffer, int mempitch);
void Draw_Top_Tri(int x1, int y1, int x2, int y2, int x3, int y3, int color, unsigned char *dest_buffer, int mempitch);
void Draw_Bottom_Tri(int x1, int y1, int x2, int y2, int x3, int y3, int color, unsigned char *dest_buffer, int mempitch);

void Draw_Top_Tri2_16(float x1, float y1,
	float x2, float y2,
	float x3, float y3,
	int color,
	UCHAR *_dest_buffer, int mempitch);

void Draw_Bottom_Tri2_16(float x1, float y1,
	float x2, float y2,
	float x3, float y3,
	int color,
	UCHAR *_dest_buffer, int mempitch);

void Draw_Triangle_2D2_16(float x1, float y1,
	float x2, float y2,
	float x3, float y3,
	int color,
	UCHAR *dest_buffer, int mempitch);


void Draw_Top_Tri2(float x1, float y1,
	float x2, float y2,
	float x3, float y3,
	int color,
	UCHAR *_dest_buffer, int mempitch);

void Draw_Bottom_Tri2(float x1, float y1,
	float x2, float y2,
	float x3, float y3,
	int color,
	UCHAR *_dest_buffer, int mempitch);

void Draw_Triangle_2D2(float x1, float y1,
	float x2, float y2,
	float x3, float y3,
	int color,
	UCHAR *dest_buffer, int mempitch);
#endif