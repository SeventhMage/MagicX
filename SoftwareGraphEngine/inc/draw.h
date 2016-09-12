#ifndef _SGE_DRAW_H_
#define _SGE_DRAW_H_

int Draw_Clip_Line16(int x0, int y0, int x1, int y1, int color, unsigned char *dest_buffer, int lpitch);
int Draw_Line16(int x0, int y0, int x1, int y1, int color, unsigned char *vb_start, int lpitch);
int Clip_Line(int &x1, int &y1, int &x2, int &y2);

#endif