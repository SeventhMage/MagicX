#ifndef _SGE_DRAW_H_
#define _SGE_DRAW_H_

int Clip_Line(int &x1, int &y1, int &x2, int &y2);
int Draw_Clip_Line16(int x0, int y0, int x1, int y1, int color, unsigned char *dest_buffer, int lpitch);
//Bresenham光栅化直线算法
int Draw_Line16(int x0, int y0, int x1, int y1, int color, unsigned char *vb_start, int lpitch);
int Draw_Clip_Line(int x0, int y0, int x1, int y1, int color, unsigned char *dest_buffer, int lpitch);
//Bresenham光栅化直线算法
int Draw_Line(int x0, int y0, int x1, int y1, int color, unsigned char *vb_start, int lpitch);

#endif