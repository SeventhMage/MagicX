#include "draw.h"
#include "config.h"
#include "typedef.h"

#include <string.h>
#include <algorithm>
#include "tool.h"

UCHAR logbase2ofx[513] =
{
	0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,

	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,

};

int Draw_Clip_Line16(int x0, int y0, int x1, int y1, int color, unsigned char *dest_buffer, int lpitch)
{
	if (Clip_Line(x0, y0, x1, y1))
		Draw_Line16(x0, y0, x1, y1, color, dest_buffer, lpitch);
	return 1;
}

int Draw_Line16(int x0, int y0, int x1, int y1, int color, unsigned char *vb_start, int lpitch)
{
	int dx,             // difference in x's
		dy,             // difference in y's
		dx2,            // dx,dy * 2
		dy2,
		x_inc,          // amount in pixel space to move during drawing
		y_inc,          // amount in pixel space to move during drawing
		error,          // the discriminant i.e. error i.e. decision variable
		index;          // used for looping

	int lpitch_2 = lpitch; // UINT strided lpitch

	// pre-compute first pixel address in video buffer based on 16bit data
	UINT *vb_start2 = (UINT *)vb_start + x0 + y0*lpitch_2;

	// compute horizontal and vertical deltas
	dx = x1 - x0;
	dy = y1 - y0;

	// test which direction the line is going in i.e. slope angle
	if (dx >= 0)
	{
		x_inc = 1;

	} // end if line is moving right
	else
	{
		x_inc = -1;
		dx = -dx;  // need absolute value

	} // end else moving left

	// test y component of slope

	if (dy >= 0)
	{
		y_inc = lpitch_2;
	} // end if line is moving down
	else
	{
		y_inc = -lpitch_2;
		dy = -dy;  // need absolute value

	} // end else moving up

	// compute (dx,dy) * 2
	dx2 = dx << 1;
	dy2 = dy << 1;

	// now based on which delta is greater we can draw the line
	if (dx > dy)
	{
		// initialize error term
		error = dy2 - dx;

		// draw the line
		for (index = 0; index <= dx; index++)
		{
			// set the pixel
			*vb_start2 = (UINT)color;

			// test if error has overflowed
			if (error >= 0)
			{
				error -= dx2;

				// move to next line
				vb_start2 += y_inc;

			} // end if error overflowed

			// adjust the error term
			error += dy2;

			// move to the next pixel
			vb_start2 += x_inc;

		} // end for

	} // end if |slope| <= 1
	else
	{
		// initialize error term
		error = dx2 - dy;

		// draw the line
		for (index = 0; index <= dy; index++)
		{
			// set the pixel
			*vb_start2 = (UINT)color;

			// test if error overflowed
			if (error >= 0)
			{
				error -= dy2;

				// move to next line
				vb_start2 += x_inc;

			} // end if error overflowed

			// adjust the error term
			error += dx2;

			// move to the next pixel
			vb_start2 += y_inc;

		} // end for

	} // end else |slope| > 1

	// return success
	return(1);

}

int Clip_Line(int &x1, int &y1, int &x2, int &y2)
{
#define CLIP_CODE_C  0x0000
#define CLIP_CODE_N  0x0008
#define CLIP_CODE_S  0x0004
#define CLIP_CODE_E  0x0002
#define CLIP_CODE_W  0x0001

#define CLIP_CODE_NE 0x000a
#define CLIP_CODE_SE 0x0006
#define CLIP_CODE_NW 0x0009 
#define CLIP_CODE_SW 0x0005

	int xc1 = x1,
		yc1 = y1,
		xc2 = x2,
		yc2 = y2;

	int p1_code = 0,
		p2_code = 0;

	// determine codes for p1 and p2
	if (y1 < min_clip_y)
		p1_code |= CLIP_CODE_N;
	else
	if (y1 > max_clip_y)
		p1_code |= CLIP_CODE_S;

	if (x1 < min_clip_x)
		p1_code |= CLIP_CODE_W;
	else
	if (x1 > max_clip_x)
		p1_code |= CLIP_CODE_E;

	if (y2 < min_clip_y)
		p2_code |= CLIP_CODE_N;
	else
	if (y2 > max_clip_y)
		p2_code |= CLIP_CODE_S;

	if (x2 < min_clip_x)
		p2_code |= CLIP_CODE_W;
	else
	if (x2 > max_clip_x)
		p2_code |= CLIP_CODE_E;

	// try and trivially reject
	if ((p1_code & p2_code))
		return(0);

	// test for totally visible, if so leave points untouched
	if (p1_code == 0 && p2_code == 0)
		return(1);

	// determine end clip point for p1
	switch (p1_code)
	{
	case CLIP_CODE_C: break;

	case CLIP_CODE_N:
	{
						yc1 = min_clip_y;
						xc1 = x1 + 0.5 + (min_clip_y - y1)*(x2 - x1) / (y2 - y1);
	} break;
	case CLIP_CODE_S:
	{
						yc1 = max_clip_y;
						xc1 = x1 + 0.5 + (max_clip_y - y1)*(x2 - x1) / (y2 - y1);
	} break;

	case CLIP_CODE_W:
	{
						xc1 = min_clip_x;
						yc1 = y1 + 0.5 + (min_clip_x - x1)*(y2 - y1) / (x2 - x1);
	} break;

	case CLIP_CODE_E:
	{
						xc1 = max_clip_x;
						yc1 = y1 + 0.5 + (max_clip_x - x1)*(y2 - y1) / (x2 - x1);
	} break;

	// these cases are more complex, must compute 2 intersections
	case CLIP_CODE_NE:
	{
						 // north hline intersection
						 yc1 = min_clip_y;
						 xc1 = x1 + 0.5 + (min_clip_y - y1)*(x2 - x1) / (y2 - y1);

						 // test if intersection is valid, of so then done, else compute next
						 if (xc1 < min_clip_x || xc1 > max_clip_x)
						 {
							 // east vline intersection
							 xc1 = max_clip_x;
							 yc1 = y1 + 0.5 + (max_clip_x - x1)*(y2 - y1) / (x2 - x1);
						 } // end if

	} break;

	case CLIP_CODE_SE:
	{
						 // south hline intersection
						 yc1 = max_clip_y;
						 xc1 = x1 + 0.5 + (max_clip_y - y1)*(x2 - x1) / (y2 - y1);

						 // test if intersection is valid, of so then done, else compute next
						 if (xc1 < min_clip_x || xc1 > max_clip_x)
						 {
							 // east vline intersection
							 xc1 = max_clip_x;
							 yc1 = y1 + 0.5 + (max_clip_x - x1)*(y2 - y1) / (x2 - x1);
						 } // end if

	} break;

	case CLIP_CODE_NW:
	{
						 // north hline intersection
						 yc1 = min_clip_y;
						 xc1 = x1 + 0.5 + (min_clip_y - y1)*(x2 - x1) / (y2 - y1);

						 // test if intersection is valid, of so then done, else compute next
						 if (xc1 < min_clip_x || xc1 > max_clip_x)
						 {
							 xc1 = min_clip_x;
							 yc1 = y1 + 0.5 + (min_clip_x - x1)*(y2 - y1) / (x2 - x1);
						 } // end if

	} break;

	case CLIP_CODE_SW:
	{
						 // south hline intersection
						 yc1 = max_clip_y;
						 xc1 = x1 + 0.5 + (max_clip_y - y1)*(x2 - x1) / (y2 - y1);

						 // test if intersection is valid, of so then done, else compute next
						 if (xc1 < min_clip_x || xc1 > max_clip_x)
						 {
							 xc1 = min_clip_x;
							 yc1 = y1 + 0.5 + (min_clip_x - x1)*(y2 - y1) / (x2 - x1);
						 } // end if

	} break;

	default:break;

	} // end switch

	// determine clip point for p2
	switch (p2_code)
	{
	case CLIP_CODE_C: break;

	case CLIP_CODE_N:
	{
						yc2 = min_clip_y;
						xc2 = x2 + (min_clip_y - y2)*(x1 - x2) / (y1 - y2);
	} break;

	case CLIP_CODE_S:
	{
						yc2 = max_clip_y;
						xc2 = x2 + (max_clip_y - y2)*(x1 - x2) / (y1 - y2);
	} break;

	case CLIP_CODE_W:
	{
						xc2 = min_clip_x;
						yc2 = y2 + (min_clip_x - x2)*(y1 - y2) / (x1 - x2);
	} break;

	case CLIP_CODE_E:
	{
						xc2 = max_clip_x;
						yc2 = y2 + (max_clip_x - x2)*(y1 - y2) / (x1 - x2);
	} break;

	// these cases are more complex, must compute 2 intersections
	case CLIP_CODE_NE:
	{
						 // north hline intersection
						 yc2 = min_clip_y;
						 xc2 = x2 + 0.5 + (min_clip_y - y2)*(x1 - x2) / (y1 - y2);

						 // test if intersection is valid, of so then done, else compute next
						 if (xc2 < min_clip_x || xc2 > max_clip_x)
						 {
							 // east vline intersection
							 xc2 = max_clip_x;
							 yc2 = y2 + 0.5 + (max_clip_x - x2)*(y1 - y2) / (x1 - x2);
						 } // end if

	} break;

	case CLIP_CODE_SE:
	{
						 // south hline intersection
						 yc2 = max_clip_y;
						 xc2 = x2 + 0.5 + (max_clip_y - y2)*(x1 - x2) / (y1 - y2);

						 // test if intersection is valid, of so then done, else compute next
						 if (xc2 < min_clip_x || xc2 > max_clip_x)
						 {
							 // east vline intersection
							 xc2 = max_clip_x;
							 yc2 = y2 + 0.5 + (max_clip_x - x2)*(y1 - y2) / (x1 - x2);
						 } // end if

	} break;

	case CLIP_CODE_NW:
	{
						 // north hline intersection
						 yc2 = min_clip_y;
						 xc2 = x2 + 0.5 + (min_clip_y - y2)*(x1 - x2) / (y1 - y2);

						 // test if intersection is valid, of so then done, else compute next
						 if (xc2 < min_clip_x || xc2 > max_clip_x)
						 {
							 xc2 = min_clip_x;
							 yc2 = y2 + 0.5 + (min_clip_x - x2)*(y1 - y2) / (x1 - x2);
						 } // end if

	} break;

	case CLIP_CODE_SW:
	{
						 // south hline intersection
						 yc2 = max_clip_y;
						 xc2 = x2 + 0.5 + (max_clip_y - y2)*(x1 - x2) / (y1 - y2);

						 // test if intersection is valid, of so then done, else compute next
						 if (xc2 < min_clip_x || xc2 > max_clip_x)
						 {
							 xc2 = min_clip_x;
							 yc2 = y2 + 0.5 + (min_clip_x - x2)*(y1 - y2) / (x1 - x2);
						 } // end if

	} break;

	default:break;

	} // end switch

	// do bounds check
	if ((xc1 < min_clip_x) || (xc1 > max_clip_x) ||
		(yc1 < min_clip_y) || (yc1 > max_clip_y) ||
		(xc2 < min_clip_x) || (xc2 > max_clip_x) ||
		(yc2 < min_clip_y) || (yc2 > max_clip_y))
	{
		return(0);
	} // end if

	// store vars back
	x1 = xc1;
	y1 = yc1;
	x2 = xc2;
	y2 = yc2;

	return(1);
}

int Draw_Clip_Line(int x0, int y0, int x1, int y1, int color, unsigned char *dest_buffer, int lpitch)
{
	if (Clip_Line(x0, y0, x1, y1))
		Draw_Line(x0, y0, x1, y1, color, dest_buffer, lpitch);
	return 1;
}

int Draw_Line(int x0, int y0, int x1, int y1, int color, unsigned char *vb_start, int lpitch)
{
	int dx,             // difference in x's
		dy,             // difference in y's
		dx2,            // dx,dy * 2
		dy2,
		x_inc,          // amount in pixel space to move during drawing
		y_inc,          // amount in pixel space to move during drawing
		error,          // the discriminant i.e. error i.e. decision variable
		index;          // used for looping
	

	// pre-compute first pixel address in video buffer based on 16bit data
	UINT *vb_start2 = (UINT *)vb_start + x0 + y0*lpitch;

	// compute horizontal and vertical deltas
	dx = x1 - x0;
	dy = y1 - y0;

	// test which direction the line is going in i.e. slope angle
	if (dx >= 0)
	{
		x_inc = 1;

	} // end if line is moving right
	else
	{
		x_inc = -1;
		dx = -dx;  // need absolute value

	} // end else moving left

	// test y component of slope

	if (dy >= 0)
	{
		y_inc = lpitch;
	} // end if line is moving down
	else
	{
		y_inc = -lpitch;
		dy = -dy;  // need absolute value

	} // end else moving up

	// compute (dx,dy) * 2
	dx2 = dx << 1;
	dy2 = dy << 1;

	// now based on which delta is greater we can draw the line
	if (dx > dy)
	{
		// initialize error term
		error = dy2 - dx;

		// draw the line
		for (index = 0; index <= dx; index++)
		{
			// set the pixel
			*vb_start2 = (UINT)color;

			// test if error has overflowed
			if (error >= 0)
			{
				error -= dx2;

				// move to next line
				vb_start2 += y_inc;

			} // end if error overflowed

			// adjust the error term
			error += dy2;

			// move to the next pixel
			vb_start2 += x_inc;

		} // end for

	} // end if |slope| <= 1
	else
	{
		// initialize error term
		error = dx2 - dy;

		// draw the line
		for (index = 0; index <= dy; index++)
		{
			// set the pixel
			*vb_start2 = (UINT)color;

			// test if error overflowed
			if (error >= 0)
			{
				error -= dy2;

				// move to next line
				vb_start2 += x_inc;

			} // end if error overflowed

			// adjust the error term
			error += dx2;

			// move to the next pixel
			vb_start2 += y_inc;

		} // end for

	} // end else |slope| > 1

	// return success
	return(1);

}

void Draw_Triangle_2D(int x1, int y1, int x2, int y2, int x3, int y3, int color, UCHAR *dest_buffer, int mempitch)
{
	// this function draws a triangle on the destination buffer
	// it decomposes all triangles into a pair of flat top, flat bottom

	int temp_x, // used for sorting
		temp_y,
		new_x;

	// test for h lines and v lines
	if ((x1 == x2 && x2 == x3) || (y1 == y2 && y2 == y3))
		return;

	// sort p1,p2,p3 in ascending y order
	if (y2 < y1)
	{
		temp_x = x2;
		temp_y = y2;
		x2 = x1;
		y2 = y1;
		x1 = temp_x;
		y1 = temp_y;
	} // end if

	// now we know that p1 and p2 are in order
	if (y3 < y1)
	{
		temp_x = x3;
		temp_y = y3;
		x3 = x1;
		y3 = y1;
		x1 = temp_x;
		y1 = temp_y;
	} // end if

	// finally test y3 against y2
	if (y3 < y2)
	{
		temp_x = x3;
		temp_y = y3;
		x3 = x2;
		y3 = y2;
		x2 = temp_x;
		y2 = temp_y;

	} // end if

	// do trivial rejection tests for clipping
	if (y3<min_clip_y || y1>max_clip_y ||
		(x1<min_clip_x && x2<min_clip_x && x3<min_clip_x) ||
		(x1>max_clip_x && x2>max_clip_x && x3>max_clip_x))
		return;

	// test if top of triangle is flat
	if (y1 == y2)
	{
		Draw_Top_Tri(x1, y1, x2, y2, x3, y3, color, dest_buffer, mempitch);
	} // end if
	else
	if (y2 == y3)
	{
		Draw_Bottom_Tri(x1, y1, x2, y2, x3, y3, color, dest_buffer, mempitch);
	} // end if bottom is flat
	else
	{
		// general triangle that's needs to be broken up along long edge
		new_x = x1 + (int)(0.5 + (float)(y2 - y1)*(float)(x3 - x1) / (float)(y3 - y1));

		// draw each sub-triangle
		Draw_Bottom_Tri(x1, y1, new_x, y2, x2, y2, color, dest_buffer, mempitch);
		Draw_Top_Tri(x2, y2, new_x, y2, x3, y3, color, dest_buffer, mempitch);

	} // end else

}

void Draw_Top_Tri(int x1, int y1, int x2, int y2, int x3, int y3, int color, unsigned char *_dest_buffer, int mempitch)
{
	// this function draws a triangle that has a flat top

	float dx_right,    // the dx/dy ratio of the right edge of line
		dx_left,     // the dx/dy ratio of the left edge of line
		xs, xe,       // the starting and ending points of the edges
		height;      // the height of the triangle

	int temp_x,        // used during sorting as temps
		temp_y,
		right,         // used by clipping
		left;

	// cast dest buffer to UINT
	UINT *dest_buffer = (UINT *)_dest_buffer;

	// destination address of next scanline
	UINT *dest_addr = NULL;

	//// recompute mempitch in 16-bit words
	//mempitch = (mempitch >> 1);

	// test order of x1 and x2
	if (x2 < x1)
	{
		temp_x = x2;
		x2 = x1;
		x1 = temp_x;
	} // end if swap

	// compute delta's
	height = y3 - y1;

	dx_left = (x3 - x1) / height;
	dx_right = (x3 - x2) / height;

	// set starting points
	xs = (float)x1;
	xe = (float)x2; // +(float)0.5;

	// perform y clipping
	if (y1 < min_clip_y)
	{
		// compute new xs and ys
		xs = xs + dx_left*(float)(-y1 + min_clip_y);
		xe = xe + dx_right*(float)(-y1 + min_clip_y);

		// reset y1
		y1 = min_clip_y;

	} // end if top is off screen

	if (y3 > max_clip_y)
		y3 = max_clip_y;

	// compute starting address in video memory
	dest_addr = (UINT *)dest_buffer + y1*mempitch;

	// test if x clipping is needed
	if (x1 >= min_clip_x && x1 <= max_clip_x &&
		x2 >= min_clip_x && x2 <= max_clip_x &&
		x3 >= min_clip_x && x3 <= max_clip_x)
	{
		// draw the triangle
		for (temp_y = y1; temp_y <= y3; temp_y++, dest_addr += mempitch)
		{
			// draw the line
			//memset(dest_addr + (UINT)(xs), color, ((UINT)((int)xe - (int)xs + 1)) * sizeof(UINT));
			
			std::fill_n((dest_addr + (UINT)(xs)), ((UINT)((int)xe - (int)xs) + 1), color);
			// adjust starting point and ending point
			xs += dx_left;
			xe += dx_right;

		} // end for

	} // end if no x clipping needed
	else
	{
		// clip x axis with slower version

		// draw the triangle
		for (temp_y = y1; temp_y <= y3; temp_y++, dest_addr += mempitch)
		{
			// do x clip
			left = (int)xs;
			right = (int)xe;

			// adjust starting point and ending point
			xs += dx_left;
			xe += dx_right;

			// clip line
			if (left < min_clip_x)
			{
				left = min_clip_x;

				if (right < min_clip_x)
					continue;
			}

			if (right > max_clip_x)
			{
				right = max_clip_x;

				if (left > max_clip_x)
					continue;
			}

			// draw the line
			//memset(dest_addr + (UINT)(left), color, (UINT)(right - left + 1) * sizeof(UINT));
			std::fill_n((dest_addr + (UINT)(left)), ((UINT)((int)right - (int)left) + 1), color);
		} // end for

	} // end else x clipping needed

}

void Draw_Bottom_Tri(int x1, int y1, int x2, int y2, int x3, int y3, int color, unsigned char *_dest_buffer, int mempitch)
{
	// this function draws a triangle that has a flat bottom

	float dx_right,    // the dx/dy ratio of the right edge of line
		dx_left,     // the dx/dy ratio of the left edge of line
		xs, xe,       // the starting and ending points of the edges
		height;      // the height of the triangle

	int temp_x,        // used during sorting as temps
		temp_y,
		right,         // used by clipping
		left;

	// cast dest buffer to UINT
	UINT *dest_buffer = (UINT *)_dest_buffer;

	// destination address of next scanline
	UINT  *dest_addr = NULL;

	// recompute mempitch in 16-bit words
	//mempitch = (mempitch >> 1);

	// test order of x1 and x2
	if (x3 < x2)
	{
		temp_x = x2;
		x2 = x3;
		x3 = temp_x;
	} // end if swap

	// compute delta's
	height = y3 - y1;

	dx_left = (x2 - x1) / height;
	dx_right = (x3 - x1) / height;

	// set starting points
	xs = (float)x1;
	xe = (float)x1; // +(float)0.5;

	// perform y clipping
	if (y1 < min_clip_y)
	{
		// compute new xs and ys
		xs = xs + dx_left*(float)(-y1 + min_clip_y);
		xe = xe + dx_right*(float)(-y1 + min_clip_y);

		// reset y1
		y1 = min_clip_y;

	} // end if top is off screen

	if (y3 > max_clip_y)
		y3 = max_clip_y;

	// compute starting address in video memory
	dest_addr = (UINT *)dest_buffer + y1*mempitch;

	// test if x clipping is needed
	if (x1 >= min_clip_x && x1 <= max_clip_x &&
		x2 >= min_clip_x && x2 <= max_clip_x &&
		x3 >= min_clip_x && x3 <= max_clip_x)
	{
		// draw the triangle
		for (temp_y = y1; temp_y <= y3; temp_y++, dest_addr += mempitch)
		{
			// draw the line
			//memset(dest_addr + (unsigned int)(xs), color, (unsigned int)((int)xe - (int)xs + 1) * sizeof(unsigned int));
			std::fill_n((dest_addr + (UINT)(xs)), ((UINT)((int)xe - (int)xs) + 1), color);
			// adjust starting point and ending point
			xs += dx_left;
			xe += dx_right;

		} // end for

	} // end if no x clipping needed
	else
	{
		// clip x axis with slower version

		// draw the triangle
		for (temp_y = y1; temp_y <= y3; temp_y++, dest_addr += mempitch)
		{
			// do x clip
			left = (int)xs;
			right = (int)xe;

			// adjust starting point and ending point
			xs += dx_left;
			xe += dx_right;

			// clip line
			if (left < min_clip_x)
			{
				left = min_clip_x;

				if (right < min_clip_x)
					continue;
			}

			if (right > max_clip_x)
			{
				right = max_clip_x;

				if (left > max_clip_x)
					continue;
			}
			// draw the line
			//memset(dest_addr + (unsigned int)(left), color, (unsigned int)(right - left + 1) * sizeof(unsigned int));
			std::fill_n((dest_addr + (UINT)(left)), ((UINT)((int)right - (int)left) + 1), color);
		} // end for

	} // end else x clipping needed

}

void Draw_Top_Tri2_16(float x1, float y1,
	float x2, float y2,
	float x3, float y3,
	int color,
	UCHAR *_dest_buffer, int mempitch)
{
	// this function draws a triangle that has a flat top

	float dx_right,    // the dx/dy ratio of the right edge of line
		dx_left,     // the dx/dy ratio of the left edge of line
		xs, xe,       // the starting and ending points of the edges
		height,      // the height of the triangle
		temp_x,        // used during sorting as temps
		temp_y,
		right,         // used by clipping
		left;

	int iy1, iy3, loop_y; // integers for y looping

	// cast dest buffer to UINT
	UINT *dest_buffer = (UINT *)_dest_buffer;

	// destination address of next scanline
	UINT *dest_addr = NULL;

	// recompute mempitch in 16-bit words
	//mempitch = (mempitch >> 1);//now 32-bit

	// test order of x1 and x2
	if (x2 < x1)
	{
		SWAP(x1, x2, temp_x);
	} // end if swap

	// compute delta's
	height = y3 - y1;

	dx_left = (x3 - x1) / height;
	dx_right = (x3 - x2) / height;

	// set starting points
	xs = x1;
	xe = x2;

#if (RASTERIZER_MODE==RASTERIZER_ACCURATE)

	// perform y clipping
	if (y1 < min_clip_y)
	{
		// compute new xs and ys
		xs = xs + dx_left*(-y1 + min_clip_y);
		xe = xe + dx_right*(-y1 + min_clip_y);

		// reset y1
		y1 = min_clip_y;

		// make sure top left fill convention is observed
		iy1 = y1;
	} // end if top is off screen
	else
	{
		// make sure top left fill convention is observed
		iy1 = ceil(y1);

		// bump xs and xe appropriately
		xs = xs + dx_left*(iy1 - y1);
		xe = xe + dx_right*(iy1 - y1);
	} // end else

	if (y3 > max_clip_y)
	{
		// clip y
		y3 = max_clip_y;

		// make sure top left fill convention is observed
		iy3 = y3 - 1;
	} // end if
	else
	{
		// make sure top left fill convention is observed
		iy3 = ceil(y3) - 1;
	} // end else
#endif

#if ( (RASTERIZER_MODE==RASTERIZER_FAST) || (RASTERIZER_MODE==RASTERIZER_FASTEST) )
	// perform y clipping
	if (y1 < min_clip_y)
	{
		// compute new xs and ys
		xs = xs + dx_left*(-y1 + min_clip_y);
		xe = xe + dx_right*(-y1 + min_clip_y);

		// reset y1
		y1 = min_clip_y;
	} // end if top is off screen

	if (y3 > max_clip_y)
		y3 = max_clip_y;

	// make sure top left fill convention is observed
	iy1 = ceil(y1);
	iy3 = ceil(y3) - 1;
#endif 

	//Write_Error("\nTri-Top: xs=%f, xe=%f, y1=%f, y3=%f, iy1=%d, iy3=%d", xs,xe,y1,y3,iy1,iy3);

	// compute starting address in video memory
	dest_addr = dest_buffer + iy1*mempitch;

	// test if x clipping is needed
	if (x1 >= min_clip_x && x1 <= max_clip_x &&
		x2 >= min_clip_x && x2 <= max_clip_x &&
		x3 >= min_clip_x && x3 <= max_clip_x)
	{
		// draw the triangle
		for (loop_y = iy1; loop_y <= iy3; loop_y++, dest_addr += mempitch)
		{
			//Write_Error("\nxs=%f, xe=%f", xs,xe);
			// draw the line
			//Mem_Set_WORD(dest_addr + (unsigned int)(xs), color, (unsigned int)((int)xe - (int)xs + 1));
			std::fill_n((dest_addr + (UINT)(xs)), ((UINT)((int)xe - (int)xs) + 1), color);

			// adjust starting point and ending point
			xs += dx_left;
			xe += dx_right;
		} // end for

	} // end if no x clipping needed
	else
	{
		// clip x axis with slower version

		// draw the triangle
		for (loop_y = iy1; loop_y <= iy3; loop_y++, dest_addr += mempitch)
		{
			// do x clip
			left = xs;
			right = xe;

			// adjust starting point and ending point
			xs += dx_left;
			xe += dx_right;

			// clip line
			if (left < min_clip_x)
			{
				left = min_clip_x;

				if (right < min_clip_x)
					continue;
			}

			if (right > max_clip_x)
			{
				right = max_clip_x;

				if (left > max_clip_x)
					continue;
			}
			//Write_Error("\nleft=%f, right=%f", left,right);
			// draw the line
			//Mem_Set_WORD(dest_addr + (unsigned int)(left), color, (unsigned int)((int)right - (int)left + 1));
			std::fill_n((dest_addr + (UINT)(xs)), ((UINT)((int)xe - (int)xs) + 1), color);
		} // end for

	} // end else x clipping needed

} // end Draw_Top_Tri2_16

/////////////////////////////////////////////////////////////////////////////

void Draw_Bottom_Tri2_16(float x1, float y1,
	float x2, float y2,
	float x3, float y3,
	int color,
	UCHAR *_dest_buffer, int mempitch)
{
	// this function draws a triangle that has a flat bottom

	float dx_right,    // the dx/dy ratio of the right edge of line
		dx_left,     // the dx/dy ratio of the left edge of line
		xs, xe,       // the starting and ending points of the edges
		height,      // the height of the triangle
		temp_x,      // used during sorting as temps
		temp_y,
		right,       // used by clipping
		left;

	int iy1, iy3, loop_y;

	// cast dest buffer to uint
	UINT *dest_buffer = (UINT *)_dest_buffer;

	// destination address of next scanline
	UINT  *dest_addr = NULL;

	// recompute mempitch in 16-bit words
	//mempitch = (mempitch >> 1); //now 32-bit

	// test order of x1 and x2
	if (x3 < x2)
	{
		SWAP(x2, x3, temp_x);
	} // end if swap

	// compute delta's
	height = y3 - y1;

	dx_left = (x2 - x1) / height;
	dx_right = (x3 - x1) / height;

	// set starting points
	xs = x1;
	xe = x1;

#if (RASTERIZER_MODE==RASTERIZER_ACCURATE)
	// perform y clipping
	if (y1 < min_clip_y)
	{
		// compute new xs and ys
		xs = xs + dx_left*(-y1 + min_clip_y);
		xe = xe + dx_right*(-y1 + min_clip_y);

		// reset y1
		y1 = min_clip_y;

		// make sure top left fill convention is observed
		iy1 = y1;
	} // end if top is off screen
	else
	{
		// make sure top left fill convention is observed
		iy1 = ceil(y1);

		// bump xs and xe appropriately
		xs = xs + dx_left*(iy1 - y1);
		xe = xe + dx_right*(iy1 - y1);
	} // end else

	if (y3 > max_clip_y)
	{
		// clip y
		y3 = max_clip_y;

		// make sure top left fill convention is observed
		iy3 = y3 - 1;
	} // end if
	else
	{
		// make sure top left fill convention is observed
		iy3 = ceil(y3) - 1;
	} // end else
#endif

#if ( (RASTERIZER_MODE==RASTERIZER_FAST) || (RASTERIZER_MODE==RASTERIZER_FASTEST) )
	// perform y clipping
	if (y1 < min_clip_y)
	{
		// compute new xs and ys
		xs = xs + dx_left*(-y1 + min_clip_y);
		xe = xe + dx_right*(-y1 + min_clip_y);

		// reset y1
		y1 = min_clip_y;
	} // end if top is off screen

	if (y3 > max_clip_y)
		y3 = max_clip_y;

	// make sure top left fill convention is observed
	iy1 = ceil(y1);
	iy3 = ceil(y3) - 1;
#endif 

	//Write_Error("\nTri-Bottom: xs=%f, xe=%f, y1=%f, y3=%f, iy1=%d, iy3=%d", xs,xe,y1,y3,iy1,iy3);

	// compute starting address in video memory
	dest_addr = dest_buffer + iy1*mempitch;

	// test if x clipping is needed
	if (x1 >= min_clip_x && x1 <= max_clip_x &&
		x2 >= min_clip_x && x2 <= max_clip_x &&
		x3 >= min_clip_x && x3 <= max_clip_x)
	{
		// draw the triangle
		for (loop_y = iy1; loop_y <= iy3; loop_y++, dest_addr += mempitch)
		{
			//Write_Error("\nxs=%f, xe=%f", xs,xe);
			// draw the line
			//Mem_Set_WORD(dest_addr + (unsigned int)(xs), color, (unsigned int)((int)xe - (int)xs + 1));
			std::fill_n((dest_addr + (UINT)(xs)), ((UINT)((int)xe - (int)xs) + 1), color);
			// adjust starting point and ending point
			xs += dx_left;
			xe += dx_right;
		} // end for

	} // end if no x clipping needed
	else
	{
		// clip x axis with slower version

		// draw the triangle
		for (loop_y = iy1; loop_y <= iy3; loop_y++, dest_addr += mempitch)
		{
			// do x clip
			left = xs;
			right = xe;

			// adjust starting point and ending point
			xs += dx_left;
			xe += dx_right;

			// clip line
			if (left < min_clip_x)
			{
				left = min_clip_x;

				if (right < min_clip_x)
					continue;
			}

			if (right > max_clip_x)
			{
				right = max_clip_x;

				if (left > max_clip_x)
					continue;
			}

			//Write_Error("\nleft=%f, right=%f", left,right);
			// draw the line
			//Mem_Set_WORD(dest_addr + (unsigned int)(left), color, (unsigned int)((int)right - (int)left + 1));
			std::fill_n((dest_addr + (UINT)(xs)), ((UINT)((int)xe - (int)xs) + 1), color);
		} // end for

	} // end else x clipping needed

} // end Draw_Bottom_Tri2_16

///////////////////////////////////////////////////////////////////////////////

void Draw_Triangle_2D2_16(float x1, float y1,
	float x2, float y2,
	float x3, float y3,
	int color,
	UCHAR *dest_buffer, int mempitch)
{
	// this function draws a triangle on the destination buffer
	// it decomposes all triangles into a pair of flat top, flat bottom

	float temp_x, // used for sorting
		temp_y,
		new_x;

#ifdef DEBUG_ON
	// track rendering stats
	debug_polys_rendered_per_frame++;
#endif


	// test for h lines and v lines
	if ((FCMP(x1, x2) && FCMP(x2, x3)) || (FCMP(y1, y2) && FCMP(y2, y3)))
		return;

	// sort p1,p2,p3 in ascending y order
	if (y2 < y1)
	{
		SWAP(x1, x2, temp_x);
		SWAP(y1, y2, temp_y);
	} // end if

	// now we know that p1 and p2 are in order
	if (y3 < y1)
	{
		SWAP(x1, x3, temp_x);
		SWAP(y1, y3, temp_y);
	} // end if

	// finally test y3 against y2
	if (y3 < y2)
	{
		SWAP(x2, x3, temp_x);
		SWAP(y2, y3, temp_y);
	} // end if

	// do trivial rejection tests for clipping
	if (y3 < min_clip_y || y1 > max_clip_y ||
		(x1 < min_clip_x && x2 < min_clip_x && x3 < min_clip_x) ||
		(x1 > max_clip_x && x2 > max_clip_x && x3 > max_clip_x))
		return;

	// test if top of triangle is flat
	if (FCMP(y1, y2))
	{
		Draw_Top_Tri2_16(x1, y1, x2, y2, x3, y3, color, dest_buffer, mempitch);
	} // end if
	else
	if (FCMP(y2, y3))
	{
		Draw_Bottom_Tri2_16(x1, y1, x2, y2, x3, y3, color, dest_buffer, mempitch);
	} // end if bottom is flat
	else
	{
		// general triangle that's needs to be broken up along long edge
		new_x = x1 + (y2 - y1)*(x3 - x1) / (y3 - y1);

		// draw each sub-triangle
		Draw_Bottom_Tri2_16(x1, y1, new_x, y2, x2, y2, color, dest_buffer, mempitch);
		Draw_Top_Tri2_16(x2, y2, new_x, y2, x3, y3, color, dest_buffer, mempitch);
	} // end else

} // end Draw_Triangle_2D2_16

///////////////////////////////////////////////////////////////////////////////

void Draw_Top_Tri2(float x1, float y1,
	float x2, float y2,
	float x3, float y3,
	int color,
	UCHAR *dest_buffer, int mempitch)
{
	// this function draws a triangle that has a flat top

	float dx_right,    // the dx/dy ratio of the right edge of line
		dx_left,     // the dx/dy ratio of the left edge of line
		xs, xe,       // the starting and ending points of the edges
		height,      // the height of the triangle
		temp_x,      // used during sorting as temps
		temp_y,
		right,       // used by clipping
		left;

	int iy1, iy3, loop_y; // integers for y loops

	// destination address of next scanline
	UCHAR  *dest_addr = NULL;

	// test order of x1 and x2
	if (x2 < x1)
	{
		SWAP(x1, x2, temp_x);
	} // end if swap

	// compute delta's
	height = y3 - y1;

	dx_left = (x3 - x1) / height;
	dx_right = (x3 - x2) / height;

	// set starting points
	xs = x1;
	xe = x2;

#if (RASTERIZER_MODE==RASTERIZER_ACCURATE)
	// perform y clipping
	if (y1 < min_clip_y)
	{
		// compute new xs and ys
		xs = xs + dx_left*(-y1 + min_clip_y);
		xe = xe + dx_right*(-y1 + min_clip_y);

		// reset y1
		y1 = min_clip_y;

		// make sure top left fill convention is observed
		iy1 = y1;
	} // end if top is off screen
	else
	{
		// make sure top left fill convention is observed
		iy1 = ceil(y1);

		// bump xs and xe appropriately
		xs = xs + dx_left*(iy1 - y1);
		xe = xe + dx_right*(iy1 - y1);
	} // end else

	if (y3 > max_clip_y)
	{
		// clip y
		y3 = max_clip_y;

		// make sure top left fill convention is observed
		iy3 = y3 - 1;
	} // end if
	else
	{
		// make sure top left fill convention is observed
		iy3 = ceil(y3) - 1;
	} // end else
#endif

#if ( (RASTERIZER_MODE==RASTERIZER_FAST) || (RASTERIZER_MODE==RASTERIZER_FASTEST) )
	// perform y clipping
	if (y1 < min_clip_y)
	{
		// compute new xs and ys
		xs = xs + dx_left*(-y1 + min_clip_y);
		xe = xe + dx_right*(-y1 + min_clip_y);

		// reset y1
		y1 = min_clip_y;
	} // end if top is off screen

	if (y3 > max_clip_y)
		y3 = max_clip_y;

	// make sure top left fill convention is observed
	iy1 = ceil(y1);
	iy3 = ceil(y3) - 1;
#endif 

	// compute starting address in video memory
	dest_addr = dest_buffer + iy1*mempitch;

	// test if x clipping is needed
	if (x1 >= min_clip_x && x1 <= max_clip_x &&
		x2 >= min_clip_x && x2 <= max_clip_x &&
		x3 >= min_clip_x && x3 <= max_clip_x)
	{
		// draw the triangle
		for (loop_y = iy1; loop_y <= iy3; loop_y++, dest_addr += mempitch)
		{
			// draw the line
			memset((UCHAR *)dest_addr + (unsigned int)xs, color, (unsigned int)((int)xe - (int)xs + 1));

			// adjust starting point and ending point
			xs += dx_left;
			xe += dx_right;
		} // end for

	} // end if no x clipping needed
	else
	{
		// clip x axis with slower version

		// draw the triangle
		for (temp_y = iy1; temp_y <= iy3; temp_y++, dest_addr += mempitch)
		{
			// do x clip
			left = xs;
			right = xe;

			// adjust starting point and ending point
			xs += dx_left;
			xe += dx_right;

			// clip line
			if (left < min_clip_x)
			{
				left = min_clip_x;

				if (right < min_clip_x)
					continue;
			}

			if (right > max_clip_x)
			{
				right = max_clip_x;

				if (left > max_clip_x)
					continue;
			}
			// draw the line
			memset((UCHAR  *)dest_addr + (unsigned int)left, color, (unsigned int)((int)right - (int)left + 1));
		} // end for

	} // end else x clipping needed

} // end Draw_Top_Tri2

/////////////////////////////////////////////////////////////////////////////

void Draw_Bottom_Tri2(float x1, float y1,
	float x2, float y2,
	float x3, float y3,
	int color,
	UCHAR *dest_buffer, int mempitch)
{
	// this function draws a triangle that has a flat bottom

	float dx_right,    // the dx/dy ratio of the right edge of line
		dx_left,     // the dx/dy ratio of the left edge of line
		xs, xe,       // the starting and ending points of the edges
		height,      // the height of the triangle
		temp_x,      // used during sorting as temps
		temp_y,
		right,       // used by clipping
		left;

	int iy1, iy3, loop_y; // integers for y loops

	// destination address of next scanline
	UCHAR  *dest_addr;

	// test order of x1 and x2
	if (x3 < x2)
	{
		SWAP(x2, x3, temp_x);
	} // end if swap

	// compute delta's
	height = y3 - y1;

	dx_left = (x2 - x1) / height;
	dx_right = (x3 - x1) / height;

	// set starting points
	xs = x1;
	xe = x1;

#if (RASTERIZER_MODE==RASTERIZER_ACCURATE)
	// perform y clipping
	if (y1 < min_clip_y)
	{
		// compute new xs and ys
		xs = xs + dx_left*(-y1 + min_clip_y);
		xe = xe + dx_right*(-y1 + min_clip_y);

		// reset y1
		y1 = min_clip_y;

		// make sure top left fill convention is observed
		iy1 = y1;
	} // end if top is off screen
	else
	{
		// make sure top left fill convention is observed
		iy1 = ceil(y1);

		// bump xs and xe appropriately
		xs = xs + dx_left*(iy1 - y1);
		xe = xe + dx_right*(iy1 - y1);
	} // end else

	if (y3 > max_clip_y)
	{
		// clip y
		y3 = max_clip_y;

		// make sure top left fill convention is observed
		iy3 = y3 - 1;
	} // end if
	else
	{
		// make sure top left fill convention is observed
		iy3 = ceil(y3) - 1;
	} // end else
#endif

#if ( (RASTERIZER_MODE==RASTERIZER_FAST) || (RASTERIZER_MODE==RASTERIZER_FASTEST) )
	// perform y clipping
	if (y1 < min_clip_y)
	{
		// compute new xs and ys
		xs = xs + dx_left*(-y1 + min_clip_y);
		xe = xe + dx_right*(-y1 + min_clip_y);

		// reset y1
		y1 = min_clip_y;
	} // end if top is off screen

	if (y3 > max_clip_y)
		y3 = max_clip_y;

	// make sure top left fill convention is observed
	iy1 = ceil(y1);
	iy3 = ceil(y3) - 1;
#endif 

	// compute starting address in video memory
	dest_addr = dest_buffer + iy1*mempitch;

	// test if x clipping is needed
	if (x1 >= min_clip_x && x1 <= max_clip_x &&
		x2 >= min_clip_x && x2 <= max_clip_x &&
		x3 >= min_clip_x && x3 <= max_clip_x)
	{
		// draw the triangle
		for (loop_y = iy1; loop_y <= iy3; loop_y++, dest_addr += mempitch)
		{
			// fill the line
			memset((UCHAR *)dest_addr + (unsigned int)xs, color, (unsigned int)((int)xe - (int)xs + 1));

			// adjust starting point and ending point
			xs += dx_left;
			xe += dx_right;
		} // end for

	} // end if no x clipping needed
	else
	{
		// clip x axis with slower version

		// draw the triangle

		for (loop_y = iy1; loop_y <= iy3; loop_y++, dest_addr += mempitch)
		{
			// do x clip
			left = xs;
			right = xe;

			// adjust starting point and ending point
			xs += dx_left;
			xe += dx_right;

			// clip line
			if (left < min_clip_x)
			{
				left = min_clip_x;

				if (right < min_clip_x)
					continue;
			}

			if (right > max_clip_x)
			{
				right = max_clip_x;

				if (left > max_clip_x)
					continue;
			}
			// fill the line
			memset((UCHAR *)dest_addr + (unsigned int)left, color, (unsigned int)((int)right - (int)left + 1));
		} // end for

	} // end else x clipping needed

} // end Draw_Bottom_Tri2

///////////////////////////////////////////////////////////////////////////////

void Draw_Triangle_2D2(float x1, float y1,
	float x2, float y2,
	float x3, float y3,
	int color,
	UCHAR *dest_buffer, int mempitch)
{
	// this function draws a triangle on the destination buffer
	// it decomposes all triangles into a pair of flat top, flat bottom

	float temp_x, // used for sorting
		temp_y,
		new_x;

#ifdef DEBUG_ON
	// track rendering stats
	debug_polys_rendered_per_frame++;
#endif


	// test for h lines and v lines
	if ((FCMP(x1, x2) && FCMP(x2, x3)) || (FCMP(y1, y2) && FCMP(y2, y3)))
		return;

	// sort p1,p2,p3 in ascending y order
	if (y2 < y1)
	{
		SWAP(x1, x2, temp_x);
		SWAP(y1, y2, temp_y);
	} // end if

	// now we know that p1 and p2 are in order
	if (y3 < y1)
	{
		SWAP(x1, x3, temp_x);
		SWAP(y1, y3, temp_y);
	} // end if

	// finally test y3 against y2
	if (y3 < y2)
	{
		SWAP(x2, x3, temp_x);
		SWAP(y2, y3, temp_y);
	} // end if

	// do trivial rejection tests for clipping
	if (y3 < min_clip_y || y1 > max_clip_y ||
		(x1 < min_clip_x && x2 < min_clip_x && x3<min_clip_x) ||
		(x1 > max_clip_x && x2 > max_clip_x && x3>max_clip_x))
		return;

	// test if top of triangle is flat
	if (FCMP(y1, y2))
	{
		Draw_Top_Tri2(x1, y1, x2, y2, x3, y3, color, dest_buffer, mempitch);
	} // end if
	else
	if (FCMP(y2, y3))
	{
		Draw_Bottom_Tri2(x1, y1, x2, y2, x3, y3, color, dest_buffer, mempitch);
	} // end if bottom is flat
	else
	{
		// general triangle that's needs to be broken up along long edge
		new_x = x1 + (y2 - y1)*(x3 - x1) / (y3 - y1);

		// draw each sub-triangle
		Draw_Bottom_Tri2(x1, y1, new_x, y2, x2, y2, color, dest_buffer, mempitch);
		Draw_Top_Tri2(x2, y2, new_x, y2, x3, y3, color, dest_buffer, mempitch);

	} // end else

} // end Draw_Triangle_2D2

////////////////////////////////////////////////////////////////////////////

void Draw_Textured_Triangle(POLYF4DV2_PTR face,   // ptr to face
	UCHAR *dest_buffer,   // pointer to video buffer
	int mem_pitch)        // bytes per line, 320, 640 etc.
{
	// this function draws a textured triangle in 8-bit mode

	int v0 = 0,
		v1 = 1,
		v2 = 2,
		temp = 0,
		tri_type = TRI_TYPE_NONE,
		irestart = INTERP_LHS;

	int dx, dy, dyl, dyr,          // general deltas
		u, v,
		du, dv,
		xi, yi,                  // the current interpolated x,y
		ui, vi,              // the current interpolated u,v
		index_x, index_y,    // looping vars
		x, y,                // hold general x,y
		xstart,
		xend,
		ystart,
		yrestart,
		yend,
		xl,
		dxdyl,
		xr,
		dxdyr,
		dudyl,
		ul,
		dvdyl,
		vl,
		dudyr,
		ur,
		dvdyr,
		vr;

	int x0, y0, tu0, tv0,    // cached vertices
		x1, y1, tu1, tv1,
		x2, y2, tu2, tv2;

	UCHAR *screen_ptr = NULL,
		*screen_line = NULL,
		*textmap = NULL;

#ifdef DEBUG_ON
	// track rendering stats
	debug_polys_rendered_per_frame++;
#endif

	// extract texture map
	textmap = face->texture->buffer;

	// extract base 2 of texture width
	int texture_shift2 = logbase2ofx[face->texture->width];

	// first trivial clipping rejection tests 
	if (((face->tvlist[0].y < min_clip_y) &&
		(face->tvlist[1].y < min_clip_y) &&
		(face->tvlist[2].y < min_clip_y)) ||

		((face->tvlist[0].y > max_clip_y) &&
		(face->tvlist[1].y > max_clip_y) &&
		(face->tvlist[2].y > max_clip_y)) ||

		((face->tvlist[0].x < min_clip_x) &&
		(face->tvlist[1].x < min_clip_x) &&
		(face->tvlist[2].x < min_clip_x)) ||

		((face->tvlist[0].x > max_clip_x) &&
		(face->tvlist[1].x > max_clip_x) &&
		(face->tvlist[2].x > max_clip_x)))
		return;

	// degenerate triangle
	if (((face->tvlist[0].x == face->tvlist[1].x) && (face->tvlist[1].x == face->tvlist[2].x)) ||
		((face->tvlist[0].y == face->tvlist[1].y) && (face->tvlist[1].y == face->tvlist[2].y)))
		return;

	// sort vertices
	if (face->tvlist[v1].y < face->tvlist[v0].y)
	{
		SWAP(v0, v1, temp);
	}

	if (face->tvlist[v2].y < face->tvlist[v0].y)
	{
		SWAP(v0, v2, temp);
	}

	if (face->tvlist[v2].y < face->tvlist[v1].y)
	{
		SWAP(v1, v2, temp);
	}

	// now test for trivial flat sided cases
	if (face->tvlist[v0].y == face->tvlist[v1].y)
	{
		// set triangle type
		tri_type = TRI_TYPE_FLAT_TOP;

		// sort vertices left to right
		if (face->tvlist[v1].x < face->tvlist[v0].x)
		{
			SWAP(v0, v1, temp);
		}

	} // end if
	else
		// now test for trivial flat sided cases
	if (face->tvlist[v1].y == face->tvlist[v2].y)
	{
		// set triangle type
		tri_type = TRI_TYPE_FLAT_BOTTOM;

		// sort vertices left to right
		if (face->tvlist[v2].x < face->tvlist[v1].x)
		{
			SWAP(v1, v2, temp);
		}

	} // end if
	else
	{
		// must be a general triangle
		tri_type = TRI_TYPE_GENERAL;

	} // end else

	// extract vertices for processing, now that we have order
	x0 = (int)(face->tvlist[v0].x + 0.5);
	y0 = (int)(face->tvlist[v0].y + 0.5);
	tu0 = (int)(face->tvlist[v0].u0);
	tv0 = (int)(face->tvlist[v0].v0);

	x1 = (int)(face->tvlist[v1].x + 0.5);
	y1 = (int)(face->tvlist[v1].y + 0.5);
	tu1 = (int)(face->tvlist[v1].u0);
	tv1 = (int)(face->tvlist[v1].v0);

	x2 = (int)(face->tvlist[v2].x + 0.5);
	y2 = (int)(face->tvlist[v2].y + 0.5);
	tu2 = (int)(face->tvlist[v2].u0);
	tv2 = (int)(face->tvlist[v2].v0);

	// set interpolation restart value
	yrestart = y1;

	// what kind of triangle
	if (tri_type & TRI_TYPE_FLAT_MASK)
	{

		if (tri_type == TRI_TYPE_FLAT_TOP)
		{
			// compute all deltas
			dy = (y2 - y0);

			dxdyl = ((x2 - x0) << FIXP16_SHIFT) / dy;
			dudyl = ((tu2 - tu0) << FIXP16_SHIFT) / dy;
			dvdyl = ((tv2 - tv0) << FIXP16_SHIFT) / dy;

			dxdyr = ((x2 - x1) << FIXP16_SHIFT) / dy;
			dudyr = ((tu2 - tu1) << FIXP16_SHIFT) / dy;
			dvdyr = ((tv2 - tv1) << FIXP16_SHIFT) / dy;

			// test for y clipping
			if (y0 < min_clip_y)
			{
				// compute overclip
				dy = (min_clip_y - y0);

				// computer new LHS starting values
				xl = dxdyl*dy + (x0 << FIXP16_SHIFT);
				ul = dudyl*dy + (tu0 << FIXP16_SHIFT);
				vl = dvdyl*dy + (tv0 << FIXP16_SHIFT);

				// compute new RHS starting values
				xr = dxdyr*dy + (x1 << FIXP16_SHIFT);
				ur = dudyr*dy + (tu1 << FIXP16_SHIFT);
				vr = dvdyr*dy + (tv1 << FIXP16_SHIFT);

				// compute new starting y
				ystart = min_clip_y;

			} // end if
			else
			{
				// no clipping

				// set starting values
				xl = (x0 << FIXP16_SHIFT);
				xr = (x1 << FIXP16_SHIFT);

				ul = (tu0 << FIXP16_SHIFT);
				vl = (tv0 << FIXP16_SHIFT);

				ur = (tu1 << FIXP16_SHIFT);
				vr = (tv1 << FIXP16_SHIFT);

				// set starting y
				ystart = y0;

			} // end else

		} // end if flat top
		else
		{
			// must be flat bottom

			// compute all deltas
			dy = (y1 - y0);

			dxdyl = ((x1 - x0) << FIXP16_SHIFT) / dy;
			dudyl = ((tu1 - tu0) << FIXP16_SHIFT) / dy;
			dvdyl = ((tv1 - tv0) << FIXP16_SHIFT) / dy;

			dxdyr = ((x2 - x0) << FIXP16_SHIFT) / dy;
			dudyr = ((tu2 - tu0) << FIXP16_SHIFT) / dy;
			dvdyr = ((tv2 - tv0) << FIXP16_SHIFT) / dy;

			// test for y clipping
			if (y0 < min_clip_y)
			{
				// compute overclip
				dy = (min_clip_y - y0);

				// computer new LHS starting values
				xl = dxdyl*dy + (x0 << FIXP16_SHIFT);
				ul = dudyl*dy + (tu0 << FIXP16_SHIFT);
				vl = dvdyl*dy + (tv0 << FIXP16_SHIFT);

				// compute new RHS starting values
				xr = dxdyr*dy + (x0 << FIXP16_SHIFT);
				ur = dudyr*dy + (tu0 << FIXP16_SHIFT);
				vr = dvdyr*dy + (tv0 << FIXP16_SHIFT);

				// compute new starting y
				ystart = min_clip_y;

			} // end if
			else
			{
				// no clipping

				// set starting values
				xl = (x0 << FIXP16_SHIFT);
				xr = (x0 << FIXP16_SHIFT);

				ul = (tu0 << FIXP16_SHIFT);
				vl = (tv0 << FIXP16_SHIFT);

				ur = (tu0 << FIXP16_SHIFT);
				vr = (tv0 << FIXP16_SHIFT);

				// set starting y
				ystart = y0;

			} // end else	

		} // end else flat bottom

		// test for bottom clip, always
		if ((yend = y2) > max_clip_y)
			yend = max_clip_y;

		// test for horizontal clipping
		if ((x0 < min_clip_x) || (x0 > max_clip_x) ||
			(x1 < min_clip_x) || (x1 > max_clip_x) ||
			(x2 < min_clip_x) || (x2 > max_clip_x))
		{
			// clip version

			// point screen ptr to starting line
			screen_ptr = dest_buffer + (ystart * mem_pitch);

			for (yi = ystart; yi <= yend; yi++)
			{
				// compute span endpoints
				xstart = ((xl + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
				xend = ((xr + FIXP16_ROUND_UP) >> FIXP16_SHIFT);

				// compute starting points for u,v interpolants
				ui = ul + FIXP16_ROUND_UP;
				vi = vl + FIXP16_ROUND_UP;

				// compute u,v interpolants
				if ((dx = (xend - xstart)) > 0)
				{
					du = (ur - ul) / dx;
					dv = (vr - vl) / dx;
				} // end if
				else
				{
					du = (ur - ul);
					dv = (vr - vl);
				} // end else

				///////////////////////////////////////////////////////////////////////

				// test for x clipping, LHS
				if (xstart < min_clip_x)
				{
					// compute x overlap
					dx = min_clip_x - xstart;

					// slide interpolants over
					ui += dx*du;
					vi += dx*dv;

					// reset vars
					xstart = min_clip_x;

				} // end if

				// test for x clipping RHS
				if (xend > max_clip_x)
					xend = max_clip_x;

				///////////////////////////////////////////////////////////////////////

				// draw span
				for (xi = xstart; xi <= xend; xi++)
				{
					// write textel
					screen_ptr[xi] = textmap[(ui >> FIXP16_SHIFT) + ((vi >> FIXP16_SHIFT) << texture_shift2)];

					// interpolate u,v
					ui += du;
					vi += dv;
				} // end for xi

				// interpolate u,v,x along right and left edge
				xl += dxdyl;
				ul += dudyl;
				vl += dvdyl;

				xr += dxdyr;
				ur += dudyr;
				vr += dvdyr;

				// advance screen ptr
				screen_ptr += mem_pitch;

			} // end for y

		} // end if clip
		else
		{
			// non-clip version

			// point screen ptr to starting line
			screen_ptr = dest_buffer + (ystart * mem_pitch);

			for (yi = ystart; yi <= yend; yi++)
			{
				// compute span endpoints
				xstart = ((xl + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
				xend = ((xr + FIXP16_ROUND_UP) >> FIXP16_SHIFT);

				// compute starting points for u,v interpolants
				ui = ul + FIXP16_ROUND_UP;
				vi = vl + FIXP16_ROUND_UP;

				// compute u,v interpolants
				if ((dx = (xend - xstart)) > 0)
				{
					du = (ur - ul) / dx;
					dv = (vr - vl) / dx;
				} // end if
				else
				{
					du = (ur - ul);
					dv = (vr - vl);
				} // end else

				// draw span
				for (xi = xstart; xi <= xend; xi++)
				{
					// write textel
					screen_ptr[xi] = textmap[(ui >> FIXP16_SHIFT) + ((vi >> FIXP16_SHIFT) << texture_shift2)];

					// interpolate u,v
					ui += du;
					vi += dv;
				} // end for xi

				// interpolate u,v,x along right and left edge
				xl += dxdyl;
				ul += dudyl;
				vl += dvdyl;

				xr += dxdyr;
				ur += dudyr;
				vr += dvdyr;

				// advance screen ptr
				screen_ptr += mem_pitch;

			} // end for y

		} // end if non-clipped

	} // end if
	else
	if (tri_type == TRI_TYPE_GENERAL)
	{

		// first test for bottom clip, always
		if ((yend = y2) > max_clip_y)
			yend = max_clip_y;

		// pre-test y clipping status
		if (y1 < min_clip_y)
		{
			// compute all deltas
			// LHS
			dyl = (y2 - y1);

			dxdyl = ((x2 - x1) << FIXP16_SHIFT) / dyl;
			dudyl = ((tu2 - tu1) << FIXP16_SHIFT) / dyl;
			dvdyl = ((tv2 - tv1) << FIXP16_SHIFT) / dyl;

			// RHS
			dyr = (y2 - y0);

			dxdyr = ((x2 - x0) << FIXP16_SHIFT) / dyr;
			dudyr = ((tu2 - tu0) << FIXP16_SHIFT) / dyr;
			dvdyr = ((tv2 - tv0) << FIXP16_SHIFT) / dyr;

			// compute overclip
			dyr = (min_clip_y - y0);
			dyl = (min_clip_y - y1);

			// computer new LHS starting values
			xl = dxdyl*dyl + (x1 << FIXP16_SHIFT);
			ul = dudyl*dyl + (tu1 << FIXP16_SHIFT);
			vl = dvdyl*dyl + (tv1 << FIXP16_SHIFT);

			// compute new RHS starting values
			xr = dxdyr*dyr + (x0 << FIXP16_SHIFT);
			ur = dudyr*dyr + (tu0 << FIXP16_SHIFT);
			vr = dvdyr*dyr + (tv0 << FIXP16_SHIFT);

			// compute new starting y
			ystart = min_clip_y;

			// test if we need swap to keep rendering left to right
			if (dxdyr > dxdyl)
			{
				SWAP(dxdyl, dxdyr, temp);
				SWAP(dudyl, dudyr, temp);
				SWAP(dvdyl, dvdyr, temp);
				SWAP(xl, xr, temp);
				SWAP(ul, ur, temp);
				SWAP(vl, vr, temp);
				SWAP(x1, x2, temp);
				SWAP(y1, y2, temp);
				SWAP(tu1, tu2, temp);
				SWAP(tv1, tv2, temp);

				// set interpolation restart
				irestart = INTERP_RHS;

			} // end if

		} // end if
		else
		if (y0 < min_clip_y)
		{
			// compute all deltas
			// LHS
			dyl = (y1 - y0);

			dxdyl = ((x1 - x0) << FIXP16_SHIFT) / dyl;
			dudyl = ((tu1 - tu0) << FIXP16_SHIFT) / dyl;
			dvdyl = ((tv1 - tv0) << FIXP16_SHIFT) / dyl;

			// RHS
			dyr = (y2 - y0);

			dxdyr = ((x2 - x0) << FIXP16_SHIFT) / dyr;
			dudyr = ((tu2 - tu0) << FIXP16_SHIFT) / dyr;
			dvdyr = ((tv2 - tv0) << FIXP16_SHIFT) / dyr;

			// compute overclip
			dy = (min_clip_y - y0);

			// computer new LHS starting values
			xl = dxdyl*dy + (x0 << FIXP16_SHIFT);
			ul = dudyl*dy + (tu0 << FIXP16_SHIFT);
			vl = dvdyl*dy + (tv0 << FIXP16_SHIFT);

			// compute new RHS starting values
			xr = dxdyr*dy + (x0 << FIXP16_SHIFT);
			ur = dudyr*dy + (tu0 << FIXP16_SHIFT);
			vr = dvdyr*dy + (tv0 << FIXP16_SHIFT);

			// compute new starting y
			ystart = min_clip_y;

			// test if we need swap to keep rendering left to right
			if (dxdyr < dxdyl)
			{
				SWAP(dxdyl, dxdyr, temp);
				SWAP(dudyl, dudyr, temp);
				SWAP(dvdyl, dvdyr, temp);
				SWAP(xl, xr, temp);
				SWAP(ul, ur, temp);
				SWAP(vl, vr, temp);
				SWAP(x1, x2, temp);
				SWAP(y1, y2, temp);
				SWAP(tu1, tu2, temp);
				SWAP(tv1, tv2, temp);

				// set interpolation restart
				irestart = INTERP_RHS;

			} // end if

		} // end if
		else
		{
			// no initial y clipping

			// compute all deltas
			// LHS
			dyl = (y1 - y0);

			dxdyl = ((x1 - x0) << FIXP16_SHIFT) / dyl;
			dudyl = ((tu1 - tu0) << FIXP16_SHIFT) / dyl;
			dvdyl = ((tv1 - tv0) << FIXP16_SHIFT) / dyl;

			// RHS
			dyr = (y2 - y0);

			dxdyr = ((x2 - x0) << FIXP16_SHIFT) / dyr;
			dudyr = ((tu2 - tu0) << FIXP16_SHIFT) / dyr;
			dvdyr = ((tv2 - tv0) << FIXP16_SHIFT) / dyr;

			// no clipping y

			// set starting values
			xl = (x0 << FIXP16_SHIFT);
			xr = (x0 << FIXP16_SHIFT);

			ul = (tu0 << FIXP16_SHIFT);
			vl = (tv0 << FIXP16_SHIFT);

			ur = (tu0 << FIXP16_SHIFT);
			vr = (tv0 << FIXP16_SHIFT);

			// set starting y
			ystart = y0;

			// test if we need swap to keep rendering left to right
			if (dxdyr < dxdyl)
			{
				SWAP(dxdyl, dxdyr, temp);
				SWAP(dudyl, dudyr, temp);
				SWAP(dvdyl, dvdyr, temp);
				SWAP(xl, xr, temp);
				SWAP(ul, ur, temp);
				SWAP(vl, vr, temp);
				SWAP(x1, x2, temp);
				SWAP(y1, y2, temp);
				SWAP(tu1, tu2, temp);
				SWAP(tv1, tv2, temp);

				// set interpolation restart
				irestart = INTERP_RHS;

			} // end if

		} // end else


		// test for horizontal clipping
		if ((x0 < min_clip_x) || (x0 > max_clip_x) ||
			(x1 < min_clip_x) || (x1 > max_clip_x) ||
			(x2 < min_clip_x) || (x2 > max_clip_x))
		{
			// clip version
			// x clipping	

			// point screen ptr to starting line
			screen_ptr = dest_buffer + (ystart * mem_pitch);

			for (yi = ystart; yi <= yend; yi++)
			{
				// compute span endpoints
				xstart = ((xl + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
				xend = ((xr + FIXP16_ROUND_UP) >> FIXP16_SHIFT);

				// compute starting points for u,v interpolants
				ui = ul + FIXP16_ROUND_UP;
				vi = vl + FIXP16_ROUND_UP;

				// compute u,v interpolants
				if ((dx = (xend - xstart)) > 0)
				{
					du = (ur - ul) / dx;
					dv = (vr - vl) / dx;
				} // end if
				else
				{
					du = (ur - ul);
					dv = (vr - vl);
				} // end else

				///////////////////////////////////////////////////////////////////////

				// test for x clipping, LHS
				if (xstart < min_clip_x)
				{
					// compute x overlap
					dx = min_clip_x - xstart;

					// slide interpolants over
					ui += dx*du;
					vi += dx*dv;

					// set x to left clip edge
					xstart = min_clip_x;

				} // end if

				// test for x clipping RHS
				if (xend > max_clip_x)
					xend = max_clip_x;

				///////////////////////////////////////////////////////////////////////

				// draw span
				for (xi = xstart; xi <= xend; xi++)
				{
					// write textel
					screen_ptr[xi] = textmap[(ui >> FIXP16_SHIFT) + ((vi >> FIXP16_SHIFT) << texture_shift2)];

					// interpolate u,v
					ui += du;
					vi += dv;
				} // end for xi

				// interpolate u,v,x along right and left edge
				xl += dxdyl;
				ul += dudyl;
				vl += dvdyl;

				xr += dxdyr;
				ur += dudyr;
				vr += dvdyr;

				// advance screen ptr
				screen_ptr += mem_pitch;

				// test for yi hitting second region, if so change interpolant
				if (yi == yrestart)
				{

					// test interpolation side change flag

					if (irestart == INTERP_LHS)
					{
						// LHS
						dyl = (y2 - y1);

						dxdyl = ((x2 - x1) << FIXP16_SHIFT) / dyl;
						dudyl = ((tu2 - tu1) << FIXP16_SHIFT) / dyl;
						dvdyl = ((tv2 - tv1) << FIXP16_SHIFT) / dyl;

						// set starting values
						xl = (x1 << FIXP16_SHIFT);
						ul = (tu1 << FIXP16_SHIFT);
						vl = (tv1 << FIXP16_SHIFT);

						// interpolate down on LHS to even up
						xl += dxdyl;
						ul += dudyl;
						vl += dvdyl;
					} // end if
					else
					{
						// RHS
						dyr = (y1 - y2);

						dxdyr = ((x1 - x2) << FIXP16_SHIFT) / dyr;
						dudyr = ((tu1 - tu2) << FIXP16_SHIFT) / dyr;
						dvdyr = ((tv1 - tv2) << FIXP16_SHIFT) / dyr;

						// set starting values
						xr = (x2 << FIXP16_SHIFT);
						ur = (tu2 << FIXP16_SHIFT);
						vr = (tv2 << FIXP16_SHIFT);

						// interpolate down on RHS to even up
						xr += dxdyr;
						ur += dudyr;
						vr += dvdyr;

					} // end else


				} // end if

			} // end for y

		} // end if
		else
		{
			// no x clipping
			// point screen ptr to starting line
			screen_ptr = dest_buffer + (ystart * mem_pitch);

			for (yi = ystart; yi <= yend; yi++)
			{
				// compute span endpoints
				xstart = ((xl + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
				xend = ((xr + FIXP16_ROUND_UP) >> FIXP16_SHIFT);

				// compute starting points for u,v interpolants
				ui = ul + FIXP16_ROUND_UP;
				vi = vl + FIXP16_ROUND_UP;

				// compute u,v interpolants
				if ((dx = (xend - xstart)) > 0)

				{
					du = (ur - ul) / dx;
					dv = (vr - vl) / dx;
				} // end if
				else
				{
					du = (ur - ul);
					dv = (vr - vl);
				} // end else

				// draw span
				for (xi = xstart; xi <= xend; xi++)
				{
					// write textel
					screen_ptr[xi] = textmap[(ui >> FIXP16_SHIFT) + ((vi >> FIXP16_SHIFT) << texture_shift2)];

					// interpolate u,v
					ui += du;
					vi += dv;
				} // end for xi

				// interpolate u,v,x along right and left edge
				xl += dxdyl;
				ul += dudyl;
				vl += dvdyl;

				xr += dxdyr;
				ur += dudyr;
				vr += dvdyr;

				// advance screen ptr
				screen_ptr += mem_pitch;

				// test for yi hitting second region, if so change interpolant
				if (yi == yrestart)
				{
					// test interpolation side change flag

					if (irestart == INTERP_LHS)
					{
						// LHS
						dyl = (y2 - y1);

						dxdyl = ((x2 - x1) << FIXP16_SHIFT) / dyl;
						dudyl = ((tu2 - tu1) << FIXP16_SHIFT) / dyl;
						dvdyl = ((tv2 - tv1) << FIXP16_SHIFT) / dyl;

						// set starting values
						xl = (x1 << FIXP16_SHIFT);
						ul = (tu1 << FIXP16_SHIFT);
						vl = (tv1 << FIXP16_SHIFT);

						// interpolate down on LHS to even up
						xl += dxdyl;
						ul += dudyl;
						vl += dvdyl;
					} // end if
					else
					{
						// RHS
						dyr = (y1 - y2);

						dxdyr = ((x1 - x2) << FIXP16_SHIFT) / dyr;
						dudyr = ((tu1 - tu2) << FIXP16_SHIFT) / dyr;
						dvdyr = ((tv1 - tv2) << FIXP16_SHIFT) / dyr;

						// set starting values
						xr = (x2 << FIXP16_SHIFT);
						ur = (tu2 << FIXP16_SHIFT);
						vr = (tv2 << FIXP16_SHIFT);

						// interpolate down on RHS to even up
						xr += dxdyr;
						ur += dudyr;
						vr += dvdyr;

					} // end else

				} // end if

			} // end for y

		} // end else	

	} // end if

} // end Draw_Textured_Triangle

//////////////////////////////////////////////////////////////////////

void Draw_Textured_Triangle16(POLYF4DV2_PTR face,   // ptr to face
	UCHAR *_dest_buffer,   // pointer to video buffer
	int mem_pitch)        // bytes per line, 320, 640 etc.
{
	// this function draws a textured triangle in 16-bit mode

	int v0 = 0,
		v1 = 1,
		v2 = 2,
		temp = 0,
		tri_type = TRI_TYPE_NONE,
		irestart = INTERP_LHS;

	int dx, dy, dyl, dyr,      // general deltas
		u, v,
		du, dv,
		xi, yi,              // the current interpolated x,y
		ui, vi,              // the current interpolated u,v
		index_x, index_y,    // looping vars
		x, y,                // hold general x,y
		xstart,
		xend,
		ystart,
		yrestart,
		yend,
		xl,
		dxdyl,
		xr,
		dxdyr,
		dudyl,
		ul,
		dvdyl,
		vl,
		dudyr,
		ur,
		dvdyr,
		vr;

	int x0, y0, tu0, tv0,    // cached vertices
		x1, y1, tu1, tv1,
		x2, y2, tu2, tv2;

	UINT *screen_ptr = NULL,
		*screen_line = NULL,
		*textmap = NULL,
		*dest_buffer = (UINT *)_dest_buffer;

#ifdef DEBUG_ON
	// track rendering stats
	debug_polys_rendered_per_frame++;
#endif

	// extract texture map
	textmap = (UINT *)face->texture->buffer;

	// extract base 2 of texture width
	int texture_shift2 = logbase2ofx[face->texture->width];

	// adjust memory pitch to words, divide by 2
	//mem_pitch >>= 1;

	// first trivial clipping rejection tests 
	if (((face->tvlist[0].y < min_clip_y) &&
		(face->tvlist[1].y < min_clip_y) &&
		(face->tvlist[2].y < min_clip_y)) ||

		((face->tvlist[0].y > max_clip_y) &&
		(face->tvlist[1].y > max_clip_y) &&
		(face->tvlist[2].y > max_clip_y)) ||

		((face->tvlist[0].x < min_clip_x) &&
		(face->tvlist[1].x < min_clip_x) &&
		(face->tvlist[2].x < min_clip_x)) ||

		((face->tvlist[0].x > max_clip_x) &&
		(face->tvlist[1].x > max_clip_x) &&
		(face->tvlist[2].x > max_clip_x)))
		return;

	// degenerate triangle
	if (((face->tvlist[0].x == face->tvlist[1].x) && (face->tvlist[1].x == face->tvlist[2].x)) ||
		((face->tvlist[0].y == face->tvlist[1].y) && (face->tvlist[1].y == face->tvlist[2].y)))
		return;

	// sort vertices
	if (face->tvlist[v1].y < face->tvlist[v0].y)
	{
		SWAP(v0, v1, temp);
	}

	if (face->tvlist[v2].y < face->tvlist[v0].y)
	{
		SWAP(v0, v2, temp);
	}

	if (face->tvlist[v2].y < face->tvlist[v1].y)
	{
		SWAP(v1, v2, temp);
	}

	// now test for trivial flat sided cases
	if (face->tvlist[v0].y == face->tvlist[v1].y)
	{
		// set triangle type
		tri_type = TRI_TYPE_FLAT_TOP;

		// sort vertices left to right
		if (face->tvlist[v1].x < face->tvlist[v0].x)
		{
			SWAP(v0, v1, temp);
		}

	} // end if
	else
		// now test for trivial flat sided cases
	if (face->tvlist[v1].y == face->tvlist[v2].y)
	{
		// set triangle type
		tri_type = TRI_TYPE_FLAT_BOTTOM;

		// sort vertices left to right
		if (face->tvlist[v2].x < face->tvlist[v1].x)
		{
			SWAP(v1, v2, temp);
		}

	} // end if
	else
	{
		// must be a general triangle
		tri_type = TRI_TYPE_GENERAL;

	} // end else

	// extract vertices for processing, now that we have order
	x0 = (int)(face->tvlist[v0].x + 0.5);
	y0 = (int)(face->tvlist[v0].y + 0.5);
	tu0 = (int)(face->tvlist[v0].u0);
	tv0 = (int)(face->tvlist[v0].v0);

	x1 = (int)(face->tvlist[v1].x + 0.5);
	y1 = (int)(face->tvlist[v1].y + 0.5);
	tu1 = (int)(face->tvlist[v1].u0);
	tv1 = (int)(face->tvlist[v1].v0);

	x2 = (int)(face->tvlist[v2].x + 0.5);
	y2 = (int)(face->tvlist[v2].y + 0.5);
	tu2 = (int)(face->tvlist[v2].u0);
	tv2 = (int)(face->tvlist[v2].v0);

	// set interpolation restart value
	yrestart = y1;

	// what kind of triangle
	if (tri_type & TRI_TYPE_FLAT_MASK)
	{

		if (tri_type == TRI_TYPE_FLAT_TOP)
		{
			// compute all deltas
			dy = (y2 - y0);

			dxdyl = ((x2 - x0) << FIXP16_SHIFT) / dy;
			dudyl = ((tu2 - tu0) << FIXP16_SHIFT) / dy;
			dvdyl = ((tv2 - tv0) << FIXP16_SHIFT) / dy;

			dxdyr = ((x2 - x1) << FIXP16_SHIFT) / dy;
			dudyr = ((tu2 - tu1) << FIXP16_SHIFT) / dy;
			dvdyr = ((tv2 - tv1) << FIXP16_SHIFT) / dy;

			// test for y clipping
			if (y0 < min_clip_y)
			{
				// compute overclip
				dy = (min_clip_y - y0);

				// computer new LHS starting values
				xl = dxdyl*dy + (x0 << FIXP16_SHIFT);
				ul = dudyl*dy + (tu0 << FIXP16_SHIFT);
				vl = dvdyl*dy + (tv0 << FIXP16_SHIFT);

				// compute new RHS starting values
				xr = dxdyr*dy + (x1 << FIXP16_SHIFT);
				ur = dudyr*dy + (tu1 << FIXP16_SHIFT);
				vr = dvdyr*dy + (tv1 << FIXP16_SHIFT);

				// compute new starting y
				ystart = min_clip_y;

			} // end if
			else
			{
				// no clipping

				// set starting values
				xl = (x0 << FIXP16_SHIFT);
				xr = (x1 << FIXP16_SHIFT);

				ul = (tu0 << FIXP16_SHIFT);
				vl = (tv0 << FIXP16_SHIFT);

				ur = (tu1 << FIXP16_SHIFT);
				vr = (tv1 << FIXP16_SHIFT);

				// set starting y
				ystart = y0;

			} // end else

		} // end if flat top
		else
		{
			// must be flat bottom

			// compute all deltas
			dy = (y1 - y0);

			dxdyl = ((x1 - x0) << FIXP16_SHIFT) / dy;
			dudyl = ((tu1 - tu0) << FIXP16_SHIFT) / dy;
			dvdyl = ((tv1 - tv0) << FIXP16_SHIFT) / dy;

			dxdyr = ((x2 - x0) << FIXP16_SHIFT) / dy;
			dudyr = ((tu2 - tu0) << FIXP16_SHIFT) / dy;
			dvdyr = ((tv2 - tv0) << FIXP16_SHIFT) / dy;

			// test for y clipping
			if (y0 < min_clip_y)
			{
				// compute overclip
				dy = (min_clip_y - y0);

				// computer new LHS starting values
				xl = dxdyl*dy + (x0 << FIXP16_SHIFT);
				ul = dudyl*dy + (tu0 << FIXP16_SHIFT);
				vl = dvdyl*dy + (tv0 << FIXP16_SHIFT);

				// compute new RHS starting values
				xr = dxdyr*dy + (x0 << FIXP16_SHIFT);
				ur = dudyr*dy + (tu0 << FIXP16_SHIFT);
				vr = dvdyr*dy + (tv0 << FIXP16_SHIFT);

				// compute new starting y
				ystart = min_clip_y;

			} // end if
			else
			{
				// no clipping

				// set starting values
				xl = (x0 << FIXP16_SHIFT);
				xr = (x0 << FIXP16_SHIFT);

				ul = (tu0 << FIXP16_SHIFT);
				vl = (tv0 << FIXP16_SHIFT);

				ur = (tu0 << FIXP16_SHIFT);
				vr = (tv0 << FIXP16_SHIFT);

				// set starting y
				ystart = y0;

			} // end else	

		} // end else flat bottom

		// test for bottom clip, always
		if ((yend = y2) > max_clip_y)
			yend = max_clip_y;

		// test for horizontal clipping
		if ((x0 < min_clip_x) || (x0 > max_clip_x) ||
			(x1 < min_clip_x) || (x1 > max_clip_x) ||
			(x2 < min_clip_x) || (x2 > max_clip_x))
		{
			// clip version

			// point screen ptr to starting line
			screen_ptr = dest_buffer + (ystart * mem_pitch);

			for (yi = ystart; yi <= yend; yi++)
			{
				// compute span endpoints
				xstart = ((xl + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
				xend = ((xr + FIXP16_ROUND_UP) >> FIXP16_SHIFT);

				// compute starting points for u,v interpolants
				ui = ul + FIXP16_ROUND_UP;
				vi = vl + FIXP16_ROUND_UP;

				// compute u,v interpolants
				if ((dx = (xend - xstart)) > 0)
				{
					du = (ur - ul) / dx;
					dv = (vr - vl) / dx;
				} // end if
				else
				{
					du = (ur - ul);
					dv = (vr - vl);
				} // end else

				///////////////////////////////////////////////////////////////////////

				// test for x clipping, LHS
				if (xstart < min_clip_x)
				{
					// compute x overlap
					dx = min_clip_x - xstart;

					// slide interpolants over
					ui += dx*du;
					vi += dx*dv;

					// reset vars
					xstart = min_clip_x;

				} // end if

				// test for x clipping RHS
				if (xend > max_clip_x)
					xend = max_clip_x;

				///////////////////////////////////////////////////////////////////////

				// draw span
				for (xi = xstart; xi <= xend; xi++)
				{
					// write textel
					screen_ptr[xi] = textmap[(ui >> FIXP16_SHIFT) + ((vi >> FIXP16_SHIFT) << texture_shift2)];

					// interpolate u,v
					ui += du;
					vi += dv;
				} // end for xi

				// interpolate u,v,x along right and left edge
				xl += dxdyl;
				ul += dudyl;
				vl += dvdyl;

				xr += dxdyr;
				ur += dudyr;
				vr += dvdyr;

				// advance screen ptr
				screen_ptr += mem_pitch;

			} // end for y

		} // end if clip
		else
		{
			// non-clip version

			// point screen ptr to starting line
			screen_ptr = dest_buffer + (ystart * mem_pitch);

			for (yi = ystart; yi <= yend; yi++)
			{
				// compute span endpoints
				xstart = ((xl + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
				xend = ((xr + FIXP16_ROUND_UP) >> FIXP16_SHIFT);

				// compute starting points for u,v interpolants
				ui = ul + FIXP16_ROUND_UP;
				vi = vl + FIXP16_ROUND_UP;

				// compute u,v interpolants
				if ((dx = (xend - xstart)) > 0)
				{
					du = (ur - ul) / dx;
					dv = (vr - vl) / dx;
				} // end if
				else
				{
					du = (ur - ul);
					dv = (vr - vl);
				} // end else

				// draw span
				for (xi = xstart; xi <= xend; xi++)
				{
					// write textel
					screen_ptr[xi] = textmap[(ui >> FIXP16_SHIFT) + ((vi >> FIXP16_SHIFT) << texture_shift2)];

					// interpolate u,v
					ui += du;
					vi += dv;
				} // end for xi

				// interpolate u,v,x along right and left edge
				xl += dxdyl;
				ul += dudyl;
				vl += dvdyl;

				xr += dxdyr;
				ur += dudyr;
				vr += dvdyr;

				// advance screen ptr
				screen_ptr += mem_pitch;

			} // end for y

		} // end if non-clipped

	} // end if
	else
	if (tri_type == TRI_TYPE_GENERAL)
	{

		// first test for bottom clip, always
		if ((yend = y2) > max_clip_y)
			yend = max_clip_y;

		// pre-test y clipping status
		if (y1 < min_clip_y)
		{
			// compute all deltas
			// LHS
			dyl = (y2 - y1);

			dxdyl = ((x2 - x1) << FIXP16_SHIFT) / dyl;
			dudyl = ((tu2 - tu1) << FIXP16_SHIFT) / dyl;
			dvdyl = ((tv2 - tv1) << FIXP16_SHIFT) / dyl;

			// RHS
			dyr = (y2 - y0);

			dxdyr = ((x2 - x0) << FIXP16_SHIFT) / dyr;
			dudyr = ((tu2 - tu0) << FIXP16_SHIFT) / dyr;
			dvdyr = ((tv2 - tv0) << FIXP16_SHIFT) / dyr;

			// compute overclip
			dyr = (min_clip_y - y0);
			dyl = (min_clip_y - y1);

			// computer new LHS starting values
			xl = dxdyl*dyl + (x1 << FIXP16_SHIFT);
			ul = dudyl*dyl + (tu1 << FIXP16_SHIFT);
			vl = dvdyl*dyl + (tv1 << FIXP16_SHIFT);

			// compute new RHS starting values
			xr = dxdyr*dyr + (x0 << FIXP16_SHIFT);
			ur = dudyr*dyr + (tu0 << FIXP16_SHIFT);
			vr = dvdyr*dyr + (tv0 << FIXP16_SHIFT);

			// compute new starting y
			ystart = min_clip_y;

			// test if we need swap to keep rendering left to right
			if (dxdyr > dxdyl)
			{
				SWAP(dxdyl, dxdyr, temp);
				SWAP(dudyl, dudyr, temp);
				SWAP(dvdyl, dvdyr, temp);
				SWAP(xl, xr, temp);
				SWAP(ul, ur, temp);
				SWAP(vl, vr, temp);
				SWAP(x1, x2, temp);
				SWAP(y1, y2, temp);
				SWAP(tu1, tu2, temp);
				SWAP(tv1, tv2, temp);

				// set interpolation restart
				irestart = INTERP_RHS;

			} // end if

		} // end if
		else
		if (y0 < min_clip_y)
		{
			// compute all deltas
			// LHS
			dyl = (y1 - y0);

			dxdyl = ((x1 - x0) << FIXP16_SHIFT) / dyl;
			dudyl = ((tu1 - tu0) << FIXP16_SHIFT) / dyl;
			dvdyl = ((tv1 - tv0) << FIXP16_SHIFT) / dyl;

			// RHS
			dyr = (y2 - y0);

			dxdyr = ((x2 - x0) << FIXP16_SHIFT) / dyr;
			dudyr = ((tu2 - tu0) << FIXP16_SHIFT) / dyr;
			dvdyr = ((tv2 - tv0) << FIXP16_SHIFT) / dyr;

			// compute overclip
			dy = (min_clip_y - y0);

			// computer new LHS starting values
			xl = dxdyl*dy + (x0 << FIXP16_SHIFT);
			ul = dudyl*dy + (tu0 << FIXP16_SHIFT);
			vl = dvdyl*dy + (tv0 << FIXP16_SHIFT);

			// compute new RHS starting values
			xr = dxdyr*dy + (x0 << FIXP16_SHIFT);
			ur = dudyr*dy + (tu0 << FIXP16_SHIFT);
			vr = dvdyr*dy + (tv0 << FIXP16_SHIFT);

			// compute new starting y
			ystart = min_clip_y;

			// test if we need swap to keep rendering left to right
			if (dxdyr < dxdyl)
			{
				SWAP(dxdyl, dxdyr, temp);
				SWAP(dudyl, dudyr, temp);
				SWAP(dvdyl, dvdyr, temp);
				SWAP(xl, xr, temp);
				SWAP(ul, ur, temp);
				SWAP(vl, vr, temp);
				SWAP(x1, x2, temp);
				SWAP(y1, y2, temp);
				SWAP(tu1, tu2, temp);
				SWAP(tv1, tv2, temp);

				// set interpolation restart
				irestart = INTERP_RHS;

			} // end if

		} // end if
		else
		{
			// no initial y clipping

			// compute all deltas
			// LHS
			dyl = (y1 - y0);

			dxdyl = ((x1 - x0) << FIXP16_SHIFT) / dyl;
			dudyl = ((tu1 - tu0) << FIXP16_SHIFT) / dyl;
			dvdyl = ((tv1 - tv0) << FIXP16_SHIFT) / dyl;

			// RHS
			dyr = (y2 - y0);

			dxdyr = ((x2 - x0) << FIXP16_SHIFT) / dyr;
			dudyr = ((tu2 - tu0) << FIXP16_SHIFT) / dyr;
			dvdyr = ((tv2 - tv0) << FIXP16_SHIFT) / dyr;

			// no clipping y

			// set starting values
			xl = (x0 << FIXP16_SHIFT);
			xr = (x0 << FIXP16_SHIFT);

			ul = (tu0 << FIXP16_SHIFT);
			vl = (tv0 << FIXP16_SHIFT);

			ur = (tu0 << FIXP16_SHIFT);
			vr = (tv0 << FIXP16_SHIFT);

			// set starting y
			ystart = y0;

			// test if we need swap to keep rendering left to right
			if (dxdyr < dxdyl)
			{
				SWAP(dxdyl, dxdyr, temp);
				SWAP(dudyl, dudyr, temp);
				SWAP(dvdyl, dvdyr, temp);
				SWAP(xl, xr, temp);
				SWAP(ul, ur, temp);
				SWAP(vl, vr, temp);
				SWAP(x1, x2, temp);
				SWAP(y1, y2, temp);
				SWAP(tu1, tu2, temp);
				SWAP(tv1, tv2, temp);

				// set interpolation restart
				irestart = INTERP_RHS;

			} // end if

		} // end else


		// test for horizontal clipping
		if ((x0 < min_clip_x) || (x0 > max_clip_x) ||
			(x1 < min_clip_x) || (x1 > max_clip_x) ||
			(x2 < min_clip_x) || (x2 > max_clip_x))
		{
			// clip version
			// x clipping	

			// point screen ptr to starting line
			screen_ptr = dest_buffer + (ystart * mem_pitch);

			for (yi = ystart; yi <= yend; yi++)
			{
				// compute span endpoints
				xstart = ((xl + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
				xend = ((xr + FIXP16_ROUND_UP) >> FIXP16_SHIFT);

				// compute starting points for u,v interpolants
				ui = ul + FIXP16_ROUND_UP;
				vi = vl + FIXP16_ROUND_UP;

				// compute u,v interpolants
				if ((dx = (xend - xstart)) > 0)
				{
					du = (ur - ul) / dx;
					dv = (vr - vl) / dx;
				} // end if
				else
				{
					du = (ur - ul);
					dv = (vr - vl);
				} // end else

				///////////////////////////////////////////////////////////////////////

				// test for x clipping, LHS
				if (xstart < min_clip_x)
				{
					// compute x overlap
					dx = min_clip_x - xstart;

					// slide interpolants over
					ui += dx*du;
					vi += dx*dv;

					// set x to left clip edge
					xstart = min_clip_x;

				} // end if

				// test for x clipping RHS
				if (xend > max_clip_x)
					xend = max_clip_x;

				///////////////////////////////////////////////////////////////////////

				// draw span
				for (xi = xstart; xi <= xend; xi++)
				{
					// write textel
					screen_ptr[xi] = textmap[(ui >> FIXP16_SHIFT) + ((vi >> FIXP16_SHIFT) << texture_shift2)];

					// interpolate u,v
					ui += du;
					vi += dv;
				} // end for xi

				// interpolate u,v,x along right and left edge
				xl += dxdyl;
				ul += dudyl;
				vl += dvdyl;

				xr += dxdyr;
				ur += dudyr;
				vr += dvdyr;

				// advance screen ptr
				screen_ptr += mem_pitch;

				// test for yi hitting second region, if so change interpolant
				if (yi == yrestart)
				{

					// test interpolation side change flag

					if (irestart == INTERP_LHS)
					{
						// LHS
						dyl = (y2 - y1);

						dxdyl = ((x2 - x1) << FIXP16_SHIFT) / dyl;
						dudyl = ((tu2 - tu1) << FIXP16_SHIFT) / dyl;
						dvdyl = ((tv2 - tv1) << FIXP16_SHIFT) / dyl;

						// set starting values
						xl = (x1 << FIXP16_SHIFT);
						ul = (tu1 << FIXP16_SHIFT);
						vl = (tv1 << FIXP16_SHIFT);

						// interpolate down on LHS to even up
						xl += dxdyl;
						ul += dudyl;
						vl += dvdyl;
					} // end if
					else
					{
						// RHS
						dyr = (y1 - y2);

						dxdyr = ((x1 - x2) << FIXP16_SHIFT) / dyr;
						dudyr = ((tu1 - tu2) << FIXP16_SHIFT) / dyr;
						dvdyr = ((tv1 - tv2) << FIXP16_SHIFT) / dyr;

						// set starting values
						xr = (x2 << FIXP16_SHIFT);
						ur = (tu2 << FIXP16_SHIFT);
						vr = (tv2 << FIXP16_SHIFT);

						// interpolate down on RHS to even up
						xr += dxdyr;
						ur += dudyr;
						vr += dvdyr;

					} // end else


				} // end if

			} // end for y

		} // end if
		else
		{
			// no x clipping
			// point screen ptr to starting line
			screen_ptr = dest_buffer + (ystart * mem_pitch);

			for (yi = ystart; yi <= yend; yi++)
			{
				// compute span endpoints
				xstart = ((xl + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
				xend = ((xr + FIXP16_ROUND_UP) >> FIXP16_SHIFT);

				// compute starting points for u,v interpolants
				ui = ul + FIXP16_ROUND_UP;
				vi = vl + FIXP16_ROUND_UP;

				// compute u,v interpolants
				if ((dx = (xend - xstart)) > 0)

				{
					du = (ur - ul) / dx;
					dv = (vr - vl) / dx;
				} // end if
				else
				{
					du = (ur - ul);
					dv = (vr - vl);
				} // end else

				// draw span
				for (xi = xstart; xi <= xend; xi++)
				{
					// write textel
					screen_ptr[xi] = textmap[(ui >> FIXP16_SHIFT) + ((vi >> FIXP16_SHIFT) << texture_shift2)];

					// interpolate u,v
					ui += du;
					vi += dv;
				} // end for xi

				// interpolate u,v,x along right and left edge
				xl += dxdyl;
				ul += dudyl;
				vl += dvdyl;

				xr += dxdyr;
				ur += dudyr;
				vr += dvdyr;

				// advance screen ptr
				screen_ptr += mem_pitch;

				// test for yi hitting second region, if so change interpolant
				if (yi == yrestart)
				{
					// test interpolation side change flag

					if (irestart == INTERP_LHS)
					{
						// LHS
						dyl = (y2 - y1);

						dxdyl = ((x2 - x1) << FIXP16_SHIFT) / dyl;
						dudyl = ((tu2 - tu1) << FIXP16_SHIFT) / dyl;
						dvdyl = ((tv2 - tv1) << FIXP16_SHIFT) / dyl;

						// set starting values
						xl = (x1 << FIXP16_SHIFT);
						ul = (tu1 << FIXP16_SHIFT);
						vl = (tv1 << FIXP16_SHIFT);

						// interpolate down on LHS to even up
						xl += dxdyl;
						ul += dudyl;
						vl += dvdyl;
					} // end if
					else
					{
						// RHS
						dyr = (y1 - y2);

						dxdyr = ((x1 - x2) << FIXP16_SHIFT) / dyr;
						dudyr = ((tu1 - tu2) << FIXP16_SHIFT) / dyr;
						dvdyr = ((tv1 - tv2) << FIXP16_SHIFT) / dyr;

						// set starting values
						xr = (x2 << FIXP16_SHIFT);
						ur = (tu2 << FIXP16_SHIFT);
						vr = (tv2 << FIXP16_SHIFT);

						// interpolate down on RHS to even up
						xr += dxdyr;
						ur += dudyr;
						vr += dvdyr;

					} // end else

				} // end if

			} // end for y

		} // end else	

	} // end if

} // end Draw_Textured_Triangle16

///////////////////////////////////////////////////////////////////////////////

void Draw_Textured_TriangleFS16(POLYF4DV2_PTR face,   // ptr to face
	UCHAR *_dest_buffer,   // pointer to video buffer
	int mem_pitch)        // bytes per line, 320, 640 etc.
{
	// this function draws a textured triangle in 16-bit mode with flat shading

	int v0 = 0,
		v1 = 1,
		v2 = 2,
		temp = 0,
		tri_type = TRI_TYPE_NONE,
		irestart = INTERP_LHS;

	int dx, dy, dyl, dyr,      // general deltas
		u, v,
		du, dv,
		xi, yi,              // the current interpolated x,y
		ui, vi,              // the current interpolated u,v
		index_x, index_y,    // looping vars
		x, y,                // hold general x,y
		xstart,
		xend,
		ystart,
		yrestart,
		yend,
		xl,
		dxdyl,
		xr,
		dxdyr,
		dudyl,
		ul,
		dvdyl,
		vl,
		dudyr,
		ur,
		dvdyr,
		vr;

	UINT r_base, g_base, b_base,
		r_textel, g_textel, b_textel, textel;

	int x0, y0, tu0, tv0,    // cached vertices
		x1, y1, tu1, tv1,
		x2, y2, tu2, tv2;

	UINT *screen_ptr = NULL,
		*screen_line = NULL,
		*textmap = NULL,
		*dest_buffer = (UINT *)_dest_buffer;

#ifdef DEBUG_ON
	// track rendering stats
	debug_polys_rendered_per_frame++;
#endif

	// extract texture map
	textmap = (UINT *)face->texture->buffer;

	// extract base 2 of texture width
	int texture_shift2 = logbase2ofx[face->texture->width];

	// adjust memory pitch to words, divide by 2
	mem_pitch >>= 1;

	// first trivial clipping rejection tests 
	if (((face->tvlist[0].y < min_clip_y) &&
		(face->tvlist[1].y < min_clip_y) &&
		(face->tvlist[2].y < min_clip_y)) ||

		((face->tvlist[0].y > max_clip_y) &&
		(face->tvlist[1].y > max_clip_y) &&
		(face->tvlist[2].y > max_clip_y)) ||

		((face->tvlist[0].x < min_clip_x) &&
		(face->tvlist[1].x < min_clip_x) &&
		(face->tvlist[2].x < min_clip_x)) ||

		((face->tvlist[0].x > max_clip_x) &&
		(face->tvlist[1].x > max_clip_x) &&
		(face->tvlist[2].x > max_clip_x)))
		return;

	// degenerate triangle
	if (((face->tvlist[0].x == face->tvlist[1].x) && (face->tvlist[1].x == face->tvlist[2].x)) ||
		((face->tvlist[0].y == face->tvlist[1].y) && (face->tvlist[1].y == face->tvlist[2].y)))
		return;

	// sort vertices
	if (face->tvlist[v1].y < face->tvlist[v0].y)
	{
		SWAP(v0, v1, temp);
	}

	if (face->tvlist[v2].y < face->tvlist[v0].y)
	{
		SWAP(v0, v2, temp);
	}

	if (face->tvlist[v2].y < face->tvlist[v1].y)
	{
		SWAP(v1, v2, temp);
	}

	// now test for trivial flat sided cases
	if (face->tvlist[v0].y == face->tvlist[v1].y)
	{
		// set triangle type
		tri_type = TRI_TYPE_FLAT_TOP;

		// sort vertices left to right
		if (face->tvlist[v1].x < face->tvlist[v0].x)
		{
			SWAP(v0, v1, temp);
		}

	} // end if
	else
		// now test for trivial flat sided cases
	if (face->tvlist[v1].y == face->tvlist[v2].y)
	{
		// set triangle type
		tri_type = TRI_TYPE_FLAT_BOTTOM;

		// sort vertices left to right
		if (face->tvlist[v2].x < face->tvlist[v1].x)
		{
			SWAP(v1, v2, temp);
		}

	} // end if
	else
	{
		// must be a general triangle
		tri_type = TRI_TYPE_GENERAL;

	} // end else

	// extract base color of lit poly, so we can modulate texture a bit
	// for lighting
	_RGB565FROM16BIT(face->lit_color[0], &r_base, &g_base, &b_base);

	// extract vertices for processing, now that we have order
	x0 = (int)(face->tvlist[v0].x + 0.5);
	y0 = (int)(face->tvlist[v0].y + 0.5);
	tu0 = (int)(face->tvlist[v0].u0);
	tv0 = (int)(face->tvlist[v0].v0);

	x1 = (int)(face->tvlist[v1].x + 0.5);
	y1 = (int)(face->tvlist[v1].y + 0.5);
	tu1 = (int)(face->tvlist[v1].u0);
	tv1 = (int)(face->tvlist[v1].v0);

	x2 = (int)(face->tvlist[v2].x + 0.5);
	y2 = (int)(face->tvlist[v2].y + 0.5);
	tu2 = (int)(face->tvlist[v2].u0);
	tv2 = (int)(face->tvlist[v2].v0);

	// set interpolation restart value
	yrestart = y1;

	// what kind of triangle
	if (tri_type & TRI_TYPE_FLAT_MASK)
	{

		if (tri_type == TRI_TYPE_FLAT_TOP)
		{
			// compute all deltas
			dy = (y2 - y0);

			dxdyl = ((x2 - x0) << FIXP16_SHIFT) / dy;
			dudyl = ((tu2 - tu0) << FIXP16_SHIFT) / dy;
			dvdyl = ((tv2 - tv0) << FIXP16_SHIFT) / dy;

			dxdyr = ((x2 - x1) << FIXP16_SHIFT) / dy;
			dudyr = ((tu2 - tu1) << FIXP16_SHIFT) / dy;
			dvdyr = ((tv2 - tv1) << FIXP16_SHIFT) / dy;

			// test for y clipping
			if (y0 < min_clip_y)
			{
				// compute overclip
				dy = (min_clip_y - y0);

				// computer new LHS starting values
				xl = dxdyl*dy + (x0 << FIXP16_SHIFT);
				ul = dudyl*dy + (tu0 << FIXP16_SHIFT);
				vl = dvdyl*dy + (tv0 << FIXP16_SHIFT);

				// compute new RHS starting values
				xr = dxdyr*dy + (x1 << FIXP16_SHIFT);
				ur = dudyr*dy + (tu1 << FIXP16_SHIFT);
				vr = dvdyr*dy + (tv1 << FIXP16_SHIFT);

				// compute new starting y
				ystart = min_clip_y;

			} // end if
			else
			{
				// no clipping

				// set starting values
				xl = (x0 << FIXP16_SHIFT);
				xr = (x1 << FIXP16_SHIFT);

				ul = (tu0 << FIXP16_SHIFT);
				vl = (tv0 << FIXP16_SHIFT);

				ur = (tu1 << FIXP16_SHIFT);
				vr = (tv1 << FIXP16_SHIFT);

				// set starting y
				ystart = y0;

			} // end else

		} // end if flat top
		else
		{
			// must be flat bottom

			// compute all deltas
			dy = (y1 - y0);

			dxdyl = ((x1 - x0) << FIXP16_SHIFT) / dy;
			dudyl = ((tu1 - tu0) << FIXP16_SHIFT) / dy;
			dvdyl = ((tv1 - tv0) << FIXP16_SHIFT) / dy;

			dxdyr = ((x2 - x0) << FIXP16_SHIFT) / dy;
			dudyr = ((tu2 - tu0) << FIXP16_SHIFT) / dy;
			dvdyr = ((tv2 - tv0) << FIXP16_SHIFT) / dy;

			// test for y clipping
			if (y0 < min_clip_y)
			{
				// compute overclip
				dy = (min_clip_y - y0);

				// computer new LHS starting values
				xl = dxdyl*dy + (x0 << FIXP16_SHIFT);
				ul = dudyl*dy + (tu0 << FIXP16_SHIFT);
				vl = dvdyl*dy + (tv0 << FIXP16_SHIFT);

				// compute new RHS starting values
				xr = dxdyr*dy + (x0 << FIXP16_SHIFT);
				ur = dudyr*dy + (tu0 << FIXP16_SHIFT);
				vr = dvdyr*dy + (tv0 << FIXP16_SHIFT);

				// compute new starting y
				ystart = min_clip_y;

			} // end if
			else
			{
				// no clipping

				// set starting values
				xl = (x0 << FIXP16_SHIFT);
				xr = (x0 << FIXP16_SHIFT);

				ul = (tu0 << FIXP16_SHIFT);
				vl = (tv0 << FIXP16_SHIFT);

				ur = (tu0 << FIXP16_SHIFT);
				vr = (tv0 << FIXP16_SHIFT);

				// set starting y
				ystart = y0;

			} // end else	

		} // end else flat bottom

		// test for bottom clip, always
		if ((yend = y2) > max_clip_y)
			yend = max_clip_y;

		// test for horizontal clipping
		if ((x0 < min_clip_x) || (x0 > max_clip_x) ||
			(x1 < min_clip_x) || (x1 > max_clip_x) ||
			(x2 < min_clip_x) || (x2 > max_clip_x))
		{
			// clip version

			// point screen ptr to starting line
			screen_ptr = dest_buffer + (ystart * mem_pitch);

			for (yi = ystart; yi <= yend; yi++)
			{
				// compute span endpoints
				xstart = ((xl + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
				xend = ((xr + FIXP16_ROUND_UP) >> FIXP16_SHIFT);

				// compute starting points for u,v interpolants
				ui = ul + FIXP16_ROUND_UP;
				vi = vl + FIXP16_ROUND_UP;

				// compute u,v interpolants
				if ((dx = (xend - xstart)) > 0)
				{
					du = (ur - ul) / dx;
					dv = (vr - vl) / dx;
				} // end if
				else
				{
					du = (ur - ul);
					dv = (vr - vl);
				} // end else

				///////////////////////////////////////////////////////////////////////

				// test for x clipping, LHS
				if (xstart < min_clip_x)
				{
					// compute x overlap
					dx = min_clip_x - xstart;

					// slide interpolants over
					ui += dx*du;
					vi += dx*dv;

					// reset vars
					xstart = min_clip_x;

				} // end if

				// test for x clipping RHS
				if (xend > max_clip_x)
					xend = max_clip_x;

				///////////////////////////////////////////////////////////////////////

				// draw span
				for (xi = xstart; xi <= xend; xi++)
				{
					// write textel
					// get textel first
					textel = textmap[(ui >> FIXP16_SHIFT) + ((vi >> FIXP16_SHIFT) << texture_shift2)];

					// extract rgb components
					r_textel = ((textel >> 11));
					g_textel = ((textel >> 5) & 0x3f);
					b_textel = (textel & 0x1f);

					// modulate textel with lit background color
					r_textel *= r_base;
					g_textel *= g_base;
					b_textel *= b_base;

					// finally write pixel, note that we did the math such that the results are r*32, g*64, b*32
					// hence we need to divide the results by 32,64,32 respetively, BUT since we need to shift
					// the results to fit into the destination 5.6.5 word, we can take advantage of the shifts
					// and they all cancel out for the most part, but we will need logical anding, we will do
					// it later when we optimize more...
					screen_ptr[xi] = ((b_textel >> 5) + ((g_textel >> 6) << 5) + ((r_textel >> 5) << 11));

					// interpolate u,v
					ui += du;
					vi += dv;
				} // end for xi

				// interpolate u,v,x along right and left edge
				xl += dxdyl;
				ul += dudyl;
				vl += dvdyl;

				xr += dxdyr;
				ur += dudyr;
				vr += dvdyr;

				// advance screen ptr
				screen_ptr += mem_pitch;

			} // end for y

		} // end if clip
		else
		{
			// non-clip version

			// point screen ptr to starting line
			screen_ptr = dest_buffer + (ystart * mem_pitch);

			for (yi = ystart; yi <= yend; yi++)
			{
				// compute span endpoints
				xstart = ((xl + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
				xend = ((xr + FIXP16_ROUND_UP) >> FIXP16_SHIFT);

				// compute starting points for u,v interpolants
				ui = ul + FIXP16_ROUND_UP;
				vi = vl + FIXP16_ROUND_UP;

				// compute u,v interpolants
				if ((dx = (xend - xstart)) > 0)
				{
					du = (ur - ul) / dx;
					dv = (vr - vl) / dx;
				} // end if
				else
				{
					du = (ur - ul);
					dv = (vr - vl);
				} // end else

				// draw span
				for (xi = xstart; xi <= xend; xi++)
				{
					// write textel
					// get textel first
					textel = textmap[(ui >> FIXP16_SHIFT) + ((vi >> FIXP16_SHIFT) << texture_shift2)];

					// extract rgb components
					r_textel = ((textel >> 11));
					g_textel = ((textel >> 5) & 0x3f);
					b_textel = (textel & 0x1f);

					// modulate textel with lit background color
					r_textel *= r_base;
					g_textel *= g_base;
					b_textel *= b_base;

					// finally write pixel, note that we did the math such that the results are r*32, g*64, b*32
					// hence we need to divide the results by 32,64,32 respetively, BUT since we need to shift
					// the results to fit into the destination 5.6.5 word, we can take advantage of the shifts
					// and they all cancel out for the most part, but we will need logical anding, we will do
					// it later when we optimize more...
					screen_ptr[xi] = ((b_textel >> 5) + ((g_textel >> 6) << 5) + ((r_textel >> 5) << 11));

					// interpolate u,v
					ui += du;
					vi += dv;
				} // end for xi

				// interpolate u,v,x along right and left edge
				xl += dxdyl;
				ul += dudyl;
				vl += dvdyl;

				xr += dxdyr;
				ur += dudyr;
				vr += dvdyr;

				// advance screen ptr
				screen_ptr += mem_pitch;

			} // end for y

		} // end if non-clipped

	} // end if
	else
	if (tri_type == TRI_TYPE_GENERAL)
	{

		// first test for bottom clip, always
		if ((yend = y2) > max_clip_y)
			yend = max_clip_y;

		// pre-test y clipping status
		if (y1 < min_clip_y)
		{
			// compute all deltas
			// LHS
			dyl = (y2 - y1);

			dxdyl = ((x2 - x1) << FIXP16_SHIFT) / dyl;
			dudyl = ((tu2 - tu1) << FIXP16_SHIFT) / dyl;
			dvdyl = ((tv2 - tv1) << FIXP16_SHIFT) / dyl;

			// RHS
			dyr = (y2 - y0);

			dxdyr = ((x2 - x0) << FIXP16_SHIFT) / dyr;
			dudyr = ((tu2 - tu0) << FIXP16_SHIFT) / dyr;
			dvdyr = ((tv2 - tv0) << FIXP16_SHIFT) / dyr;

			// compute overclip
			dyr = (min_clip_y - y0);
			dyl = (min_clip_y - y1);

			// computer new LHS starting values
			xl = dxdyl*dyl + (x1 << FIXP16_SHIFT);
			ul = dudyl*dyl + (tu1 << FIXP16_SHIFT);
			vl = dvdyl*dyl + (tv1 << FIXP16_SHIFT);

			// compute new RHS starting values
			xr = dxdyr*dyr + (x0 << FIXP16_SHIFT);
			ur = dudyr*dyr + (tu0 << FIXP16_SHIFT);
			vr = dvdyr*dyr + (tv0 << FIXP16_SHIFT);

			// compute new starting y
			ystart = min_clip_y;

			// test if we need swap to keep rendering left to right
			if (dxdyr > dxdyl)
			{
				SWAP(dxdyl, dxdyr, temp);
				SWAP(dudyl, dudyr, temp);
				SWAP(dvdyl, dvdyr, temp);
				SWAP(xl, xr, temp);
				SWAP(ul, ur, temp);
				SWAP(vl, vr, temp);
				SWAP(x1, x2, temp);
				SWAP(y1, y2, temp);
				SWAP(tu1, tu2, temp);
				SWAP(tv1, tv2, temp);

				// set interpolation restart
				irestart = INTERP_RHS;

			} // end if

		} // end if
		else
		if (y0 < min_clip_y)
		{
			// compute all deltas
			// LHS
			dyl = (y1 - y0);

			dxdyl = ((x1 - x0) << FIXP16_SHIFT) / dyl;
			dudyl = ((tu1 - tu0) << FIXP16_SHIFT) / dyl;
			dvdyl = ((tv1 - tv0) << FIXP16_SHIFT) / dyl;

			// RHS
			dyr = (y2 - y0);

			dxdyr = ((x2 - x0) << FIXP16_SHIFT) / dyr;
			dudyr = ((tu2 - tu0) << FIXP16_SHIFT) / dyr;
			dvdyr = ((tv2 - tv0) << FIXP16_SHIFT) / dyr;

			// compute overclip
			dy = (min_clip_y - y0);

			// computer new LHS starting values
			xl = dxdyl*dy + (x0 << FIXP16_SHIFT);
			ul = dudyl*dy + (tu0 << FIXP16_SHIFT);
			vl = dvdyl*dy + (tv0 << FIXP16_SHIFT);

			// compute new RHS starting values
			xr = dxdyr*dy + (x0 << FIXP16_SHIFT);
			ur = dudyr*dy + (tu0 << FIXP16_SHIFT);
			vr = dvdyr*dy + (tv0 << FIXP16_SHIFT);

			// compute new starting y
			ystart = min_clip_y;

			// test if we need swap to keep rendering left to right
			if (dxdyr < dxdyl)
			{
				SWAP(dxdyl, dxdyr, temp);
				SWAP(dudyl, dudyr, temp);
				SWAP(dvdyl, dvdyr, temp);
				SWAP(xl, xr, temp);
				SWAP(ul, ur, temp);
				SWAP(vl, vr, temp);
				SWAP(x1, x2, temp);
				SWAP(y1, y2, temp);
				SWAP(tu1, tu2, temp);
				SWAP(tv1, tv2, temp);

				// set interpolation restart
				irestart = INTERP_RHS;

			} // end if

		} // end if
		else
		{
			// no initial y clipping

			// compute all deltas
			// LHS
			dyl = (y1 - y0);

			dxdyl = ((x1 - x0) << FIXP16_SHIFT) / dyl;
			dudyl = ((tu1 - tu0) << FIXP16_SHIFT) / dyl;
			dvdyl = ((tv1 - tv0) << FIXP16_SHIFT) / dyl;

			// RHS
			dyr = (y2 - y0);

			dxdyr = ((x2 - x0) << FIXP16_SHIFT) / dyr;
			dudyr = ((tu2 - tu0) << FIXP16_SHIFT) / dyr;
			dvdyr = ((tv2 - tv0) << FIXP16_SHIFT) / dyr;

			// no clipping y

			// set starting values
			xl = (x0 << FIXP16_SHIFT);
			xr = (x0 << FIXP16_SHIFT);

			ul = (tu0 << FIXP16_SHIFT);
			vl = (tv0 << FIXP16_SHIFT);

			ur = (tu0 << FIXP16_SHIFT);
			vr = (tv0 << FIXP16_SHIFT);

			// set starting y
			ystart = y0;

			// test if we need swap to keep rendering left to right
			if (dxdyr < dxdyl)
			{
				SWAP(dxdyl, dxdyr, temp);
				SWAP(dudyl, dudyr, temp);
				SWAP(dvdyl, dvdyr, temp);
				SWAP(xl, xr, temp);
				SWAP(ul, ur, temp);
				SWAP(vl, vr, temp);
				SWAP(x1, x2, temp);
				SWAP(y1, y2, temp);
				SWAP(tu1, tu2, temp);
				SWAP(tv1, tv2, temp);

				// set interpolation restart
				irestart = INTERP_RHS;

			} // end if

		} // end else


		// test for horizontal clipping
		if ((x0 < min_clip_x) || (x0 > max_clip_x) ||
			(x1 < min_clip_x) || (x1 > max_clip_x) ||
			(x2 < min_clip_x) || (x2 > max_clip_x))
		{
			// clip version
			// x clipping	

			// point screen ptr to starting line
			screen_ptr = dest_buffer + (ystart * mem_pitch);

			for (yi = ystart; yi <= yend; yi++)
			{
				// compute span endpoints
				xstart = ((xl + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
				xend = ((xr + FIXP16_ROUND_UP) >> FIXP16_SHIFT);

				// compute starting points for u,v interpolants
				ui = ul + FIXP16_ROUND_UP;
				vi = vl + FIXP16_ROUND_UP;

				// compute u,v interpolants
				if ((dx = (xend - xstart)) > 0)
				{
					du = (ur - ul) / dx;
					dv = (vr - vl) / dx;
				} // end if
				else
				{
					du = (ur - ul);
					dv = (vr - vl);
				} // end else

				///////////////////////////////////////////////////////////////////////

				// test for x clipping, LHS
				if (xstart < min_clip_x)
				{
					// compute x overlap
					dx = min_clip_x - xstart;

					// slide interpolants over
					ui += dx*du;
					vi += dx*dv;

					// set x to left clip edge
					xstart = min_clip_x;

				} // end if

				// test for x clipping RHS
				if (xend > max_clip_x)
					xend = max_clip_x;

				///////////////////////////////////////////////////////////////////////

				// draw span
				for (xi = xstart; xi <= xend; xi++)
				{
					// write textel
					//screen_ptr[xi] = textmap[(ui >> FIXP16_SHIFT) + ((vi >> FIXP16_SHIFT) << texture_shift2)];
					// get textel first
					textel = textmap[(ui >> FIXP16_SHIFT) + ((vi >> FIXP16_SHIFT) << texture_shift2)];

					// extract rgb components
					r_textel = ((textel >> 11));
					g_textel = ((textel >> 5) & 0x3f);
					b_textel = (textel & 0x1f);

					// modulate textel with lit background color
					r_textel *= r_base;
					g_textel *= g_base;
					b_textel *= b_base;

					// finally write pixel, note that we did the math such that the results are r*32, g*64, b*32
					// hence we need to divide the results by 32,64,32 respetively, BUT since we need to shift
					// the results to fit into the destination 5.6.5 word, we can take advantage of the shifts
					// and they all cancel out for the most part, but we will need logical anding, we will do
					// it later when we optimize more...
					screen_ptr[xi] = ((b_textel >> 5) + ((g_textel >> 6) << 5) + ((r_textel >> 5) << 11));

					// interpolate u,v
					ui += du;
					vi += dv;
				} // end for xi

				// interpolate u,v,x along right and left edge
				xl += dxdyl;
				ul += dudyl;
				vl += dvdyl;

				xr += dxdyr;
				ur += dudyr;
				vr += dvdyr;

				// advance screen ptr
				screen_ptr += mem_pitch;

				// test for yi hitting second region, if so change interpolant
				if (yi == yrestart)
				{
					// test interpolation side change flag

					if (irestart == INTERP_LHS)
					{
						// LHS
						dyl = (y2 - y1);

						dxdyl = ((x2 - x1) << FIXP16_SHIFT) / dyl;
						dudyl = ((tu2 - tu1) << FIXP16_SHIFT) / dyl;
						dvdyl = ((tv2 - tv1) << FIXP16_SHIFT) / dyl;

						// set starting values
						xl = (x1 << FIXP16_SHIFT);
						ul = (tu1 << FIXP16_SHIFT);
						vl = (tv1 << FIXP16_SHIFT);

						// interpolate down on LHS to even up
						xl += dxdyl;
						ul += dudyl;
						vl += dvdyl;
					} // end if
					else
					{
						// RHS
						dyr = (y1 - y2);

						dxdyr = ((x1 - x2) << FIXP16_SHIFT) / dyr;
						dudyr = ((tu1 - tu2) << FIXP16_SHIFT) / dyr;
						dvdyr = ((tv1 - tv2) << FIXP16_SHIFT) / dyr;

						// set starting values
						xr = (x2 << FIXP16_SHIFT);
						ur = (tu2 << FIXP16_SHIFT);
						vr = (tv2 << FIXP16_SHIFT);

						// interpolate down on RHS to even up
						xr += dxdyr;
						ur += dudyr;
						vr += dvdyr;

					} // end else


				} // end if

			} // end for y

		} // end if
		else
		{
			// no x clipping
			// point screen ptr to starting line
			screen_ptr = dest_buffer + (ystart * mem_pitch);

			for (yi = ystart; yi <= yend; yi++)
			{
				// compute span endpoints
				xstart = ((xl + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
				xend = ((xr + FIXP16_ROUND_UP) >> FIXP16_SHIFT);

				// compute starting points for u,v interpolants
				ui = ul + FIXP16_ROUND_UP;
				vi = vl + FIXP16_ROUND_UP;

				// compute u,v interpolants
				if ((dx = (xend - xstart)) > 0)

				{
					du = (ur - ul) / dx;
					dv = (vr - vl) / dx;
				} // end if
				else
				{
					du = (ur - ul);
					dv = (vr - vl);
				} // end else

				// draw span
				for (xi = xstart; xi <= xend; xi++)
				{
					// write textel
					// get textel first
					textel = textmap[(ui >> FIXP16_SHIFT) + ((vi >> FIXP16_SHIFT) << texture_shift2)];

					// extract rgb components
					r_textel = ((textel >> 11));
					g_textel = ((textel >> 5) & 0x3f);
					b_textel = (textel & 0x1f);

					// modulate textel with lit background color
					r_textel *= r_base;
					g_textel *= g_base;
					b_textel *= b_base;

					// finally write pixel, note that we did the math such that the results are r*32, g*64, b*32
					// hence we need to divide the results by 32,64,32 respetively, BUT since we need to shift
					// the results to fit into the destination 5.6.5 word, we can take advantage of the shifts
					// and they all cancel out for the most part, but we will need logical anding, we will do
					// it later when we optimize more...
					screen_ptr[xi] = ((b_textel >> 5) + ((g_textel >> 6) << 5) + ((r_textel >> 5) << 11));

					// interpolate u,v
					ui += du;
					vi += dv;
				} // end for xi

				// interpolate u,v,x along right and left edge
				xl += dxdyl;
				ul += dudyl;
				vl += dvdyl;

				xr += dxdyr;
				ur += dudyr;
				vr += dvdyr;

				// advance screen ptr
				screen_ptr += mem_pitch;

				// test for yi hitting second region, if so change interpolant
				if (yi == yrestart)
				{
					// test interpolation side change flag

					if (irestart == INTERP_LHS)
					{
						// LHS
						dyl = (y2 - y1);

						dxdyl = ((x2 - x1) << FIXP16_SHIFT) / dyl;
						dudyl = ((tu2 - tu1) << FIXP16_SHIFT) / dyl;
						dvdyl = ((tv2 - tv1) << FIXP16_SHIFT) / dyl;

						// set starting values
						xl = (x1 << FIXP16_SHIFT);
						ul = (tu1 << FIXP16_SHIFT);
						vl = (tv1 << FIXP16_SHIFT);

						// interpolate down on LHS to even up
						xl += dxdyl;
						ul += dudyl;
						vl += dvdyl;
					} // end if
					else
					{
						// RHS
						dyr = (y1 - y2);

						dxdyr = ((x1 - x2) << FIXP16_SHIFT) / dyr;
						dudyr = ((tu1 - tu2) << FIXP16_SHIFT) / dyr;
						dvdyr = ((tv1 - tv2) << FIXP16_SHIFT) / dyr;

						// set starting values
						xr = (x2 << FIXP16_SHIFT);
						ur = (tu2 << FIXP16_SHIFT);
						vr = (tv2 << FIXP16_SHIFT);

						// interpolate down on RHS to even up
						xr += dxdyr;
						ur += dudyr;
						vr += dvdyr;

					} // end else

				} // end if

			} // end for y

		} // end else	

	} // end if

} // end Draw_Textured_TriangleFS16

/////////////////////////////////////////////////////////////////////////////

void Draw_Gouraud_Triangle16(POLYF4DV2_PTR face,   // ptr to face
	UCHAR *_dest_buffer, // pointer to video buffer
	int mem_pitch)       // bytes per line, 320, 640 etc.
{
	// this function draws a gouraud shaded polygon, based on the affine texture mapper, instead
	// of interpolating the texture coordinates, we simply interpolate the (R,G,B) values across
	// the polygons, I simply needed at another interpolant, I have mapped u->red, v->green, w->blue

	int v0 = 0,
		v1 = 1,
		v2 = 2,
		temp = 0,
		tri_type = TRI_TYPE_NONE,
		irestart = INTERP_LHS;

	int dx, dy, dyl, dyr,      // general deltas
		u, v, w,
		du, dv, dw,
		xi, yi,              // the current interpolated x,y
		ui, vi, wi,           // the current interpolated u,v
		index_x, index_y,    // looping vars
		x, y,                // hold general x,y
		xstart,
		xend,
		ystart,
		yrestart,
		yend,
		xl,
		dxdyl,
		xr,
		dxdyr,
		dudyl,
		ul,
		dvdyl,
		vl,
		dwdyl,
		wl,
		dudyr,
		ur,
		dvdyr,
		vr,
		dwdyr,
		wr;

	int x0, y0, tu0, tv0, tw0,    // cached vertices
		x1, y1, tu1, tv1, tw1,
		x2, y2, tu2, tv2, tw2;

	int r_base0, g_base0, b_base0,
		r_base1, g_base1, b_base1,
		r_base2, g_base2, b_base2;

	UINT *screen_ptr = NULL,
		*screen_line = NULL,
		*textmap = NULL,
		*dest_buffer = (UINT *)_dest_buffer;

#ifdef DEBUG_ON
	// track rendering stats
	debug_polys_rendered_per_frame++;
#endif

	// adjust memory pitch to words, divide by 2
	//mem_pitch >>= 1;

	// first trivial clipping rejection tests 
	if (((face->tvlist[0].y < min_clip_y) &&
		(face->tvlist[1].y < min_clip_y) &&
		(face->tvlist[2].y < min_clip_y)) ||

		((face->tvlist[0].y > max_clip_y) &&
		(face->tvlist[1].y > max_clip_y) &&
		(face->tvlist[2].y > max_clip_y)) ||

		((face->tvlist[0].x < min_clip_x) &&
		(face->tvlist[1].x < min_clip_x) &&
		(face->tvlist[2].x < min_clip_x)) ||

		((face->tvlist[0].x > max_clip_x) &&
		(face->tvlist[1].x > max_clip_x) &&
		(face->tvlist[2].x > max_clip_x)))
		return;

	// degenerate triangle
	if (((face->tvlist[0].x == face->tvlist[1].x) && (face->tvlist[1].x == face->tvlist[2].x)) ||
		((face->tvlist[0].y == face->tvlist[1].y) && (face->tvlist[1].y == face->tvlist[2].y)))
		return;


	// sort vertices
	if (face->tvlist[v1].y < face->tvlist[v0].y)
	{
		SWAP(v0, v1, temp);
	}

	if (face->tvlist[v2].y < face->tvlist[v0].y)
	{
		SWAP(v0, v2, temp);
	}

	if (face->tvlist[v2].y < face->tvlist[v1].y)
	{
		SWAP(v1, v2, temp);
	}

	// now test for trivial flat sided cases
	if (face->tvlist[v0].y == face->tvlist[v1].y)
	{
		// set triangle type
		tri_type = TRI_TYPE_FLAT_TOP;

		// sort vertices left to right
		if (face->tvlist[v1].x < face->tvlist[v0].x)
		{
			SWAP(v0, v1, temp);
		}

	} // end if
	else
		// now test for trivial flat sided cases
	if (face->tvlist[v1].y == face->tvlist[v2].y)
	{
		// set triangle type
		tri_type = TRI_TYPE_FLAT_BOTTOM;

		// sort vertices left to right
		if (face->tvlist[v2].x < face->tvlist[v1].x)
		{
			SWAP(v1, v2, temp);
		}

	} // end if
	else
	{
		// must be a general triangle
		tri_type = TRI_TYPE_GENERAL;

	} // end else

	// assume 5.6.5 format -- sorry!
	// we can't afford a function call in the inner loops, so we must write 
	// two hard coded versions, if we want support for both 5.6.5, and 5.5.5
	_RGB565FROM16BIT(face->lit_color[v0], &r_base0, &g_base0, &b_base0);
	_RGB565FROM16BIT(face->lit_color[v1], &r_base1, &g_base1, &b_base1);
	_RGB565FROM16BIT(face->lit_color[v2], &r_base2, &g_base2, &b_base2);

	// scale to 8 bit 
	r_base0 <<= 3;
	g_base0 <<= 2;
	b_base0 <<= 3;

	// scale to 8 bit 
	r_base1 <<= 3;
	g_base1 <<= 2;
	b_base1 <<= 3;

	// scale to 8 bit 
	r_base2 <<= 3;
	g_base2 <<= 2;
	b_base2 <<= 3;

	// extract vertices for processing, now that we have order
	x0 = (int)(face->tvlist[v0].x + 0.5);
	y0 = (int)(face->tvlist[v0].y + 0.5);

	tu0 = r_base0;
	tv0 = g_base0;
	tw0 = b_base0;

	x1 = (int)(face->tvlist[v1].x + 0.5);
	y1 = (int)(face->tvlist[v1].y + 0.5);

	tu1 = r_base1;
	tv1 = g_base1;
	tw1 = b_base1;

	x2 = (int)(face->tvlist[v2].x + 0.5);
	y2 = (int)(face->tvlist[v2].y + 0.5);

	tu2 = r_base2;
	tv2 = g_base2;
	tw2 = b_base2;

	// set interpolation restart value
	yrestart = y1;

	// what kind of triangle
	if (tri_type & TRI_TYPE_FLAT_MASK)
	{

		if (tri_type == TRI_TYPE_FLAT_TOP)
		{
			// compute all deltas
			dy = (y2 - y0);

			dxdyl = ((x2 - x0) << FIXP16_SHIFT) / dy;
			dudyl = ((tu2 - tu0) << FIXP16_SHIFT) / dy;
			dvdyl = ((tv2 - tv0) << FIXP16_SHIFT) / dy;
			dwdyl = ((tw2 - tw0) << FIXP16_SHIFT) / dy;

			dxdyr = ((x2 - x1) << FIXP16_SHIFT) / dy;
			dudyr = ((tu2 - tu1) << FIXP16_SHIFT) / dy;
			dvdyr = ((tv2 - tv1) << FIXP16_SHIFT) / dy;
			dwdyr = ((tw2 - tw1) << FIXP16_SHIFT) / dy;

			// test for y clipping
			if (y0 < min_clip_y)
			{
				// compute overclip
				dy = (min_clip_y - y0);

				// computer new LHS starting values
				xl = dxdyl*dy + (x0 << FIXP16_SHIFT);
				ul = dudyl*dy + (tu0 << FIXP16_SHIFT);
				vl = dvdyl*dy + (tv0 << FIXP16_SHIFT);
				wl = dwdyl*dy + (tw0 << FIXP16_SHIFT);

				// compute new RHS starting values
				xr = dxdyr*dy + (x1 << FIXP16_SHIFT);
				ur = dudyr*dy + (tu1 << FIXP16_SHIFT);
				vr = dvdyr*dy + (tv1 << FIXP16_SHIFT);
				wr = dwdyr*dy + (tw1 << FIXP16_SHIFT);

				// compute new starting y
				ystart = min_clip_y;

			} // end if
			else
			{
				// no clipping

				// set starting values
				xl = (x0 << FIXP16_SHIFT);
				xr = (x1 << FIXP16_SHIFT);

				ul = (tu0 << FIXP16_SHIFT);
				vl = (tv0 << FIXP16_SHIFT);
				wl = (tw0 << FIXP16_SHIFT);

				ur = (tu1 << FIXP16_SHIFT);
				vr = (tv1 << FIXP16_SHIFT);
				wr = (tw1 << FIXP16_SHIFT);

				// set starting y
				ystart = y0;

			} // end else

		} // end if flat top
		else
		{
			// must be flat bottom

			// compute all deltas
			dy = (y1 - y0);

			dxdyl = ((x1 - x0) << FIXP16_SHIFT) / dy;
			dudyl = ((tu1 - tu0) << FIXP16_SHIFT) / dy;
			dvdyl = ((tv1 - tv0) << FIXP16_SHIFT) / dy;
			dwdyl = ((tw1 - tw0) << FIXP16_SHIFT) / dy;

			dxdyr = ((x2 - x0) << FIXP16_SHIFT) / dy;
			dudyr = ((tu2 - tu0) << FIXP16_SHIFT) / dy;
			dvdyr = ((tv2 - tv0) << FIXP16_SHIFT) / dy;
			dwdyr = ((tw2 - tw0) << FIXP16_SHIFT) / dy;

			// test for y clipping
			if (y0 < min_clip_y)
			{
				// compute overclip
				dy = (min_clip_y - y0);

				// computer new LHS starting values
				xl = dxdyl*dy + (x0 << FIXP16_SHIFT);
				ul = dudyl*dy + (tu0 << FIXP16_SHIFT);
				vl = dvdyl*dy + (tv0 << FIXP16_SHIFT);
				wl = dwdyl*dy + (tw0 << FIXP16_SHIFT);

				// compute new RHS starting values
				xr = dxdyr*dy + (x0 << FIXP16_SHIFT);
				ur = dudyr*dy + (tu0 << FIXP16_SHIFT);
				vr = dvdyr*dy + (tv0 << FIXP16_SHIFT);
				wr = dwdyr*dy + (tw0 << FIXP16_SHIFT);

				// compute new starting y
				ystart = min_clip_y;

			} // end if
			else
			{
				// no clipping

				// set starting values
				xl = (x0 << FIXP16_SHIFT);
				xr = (x0 << FIXP16_SHIFT);

				ul = (tu0 << FIXP16_SHIFT);
				vl = (tv0 << FIXP16_SHIFT);
				wl = (tw0 << FIXP16_SHIFT);

				ur = (tu0 << FIXP16_SHIFT);
				vr = (tv0 << FIXP16_SHIFT);
				wr = (tw0 << FIXP16_SHIFT);

				// set starting y
				ystart = y0;

			} // end else	

		} // end else flat bottom

		// test for bottom clip, always
		if ((yend = y2) > max_clip_y)
			yend = max_clip_y;

		// test for horizontal clipping
		if ((x0 < min_clip_x) || (x0 > max_clip_x) ||
			(x1 < min_clip_x) || (x1 > max_clip_x) ||
			(x2 < min_clip_x) || (x2 > max_clip_x))
		{
			// clip version

			// point screen ptr to starting line
			screen_ptr = dest_buffer + (ystart * mem_pitch);

			for (yi = ystart; yi <= yend; yi++)
			{
				// compute span endpoints
				xstart = ((xl + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
				xend = ((xr + FIXP16_ROUND_UP) >> FIXP16_SHIFT);

				// compute starting points for u,v,w interpolants
				ui = ul + FIXP16_ROUND_UP;
				vi = vl + FIXP16_ROUND_UP;
				wi = wl + FIXP16_ROUND_UP;

				// compute u,v interpolants
				if ((dx = (xend - xstart)) > 0)
				{
					du = (ur - ul) / dx;
					dv = (vr - vl) / dx;
					dw = (wr - wl) / dx;
				} // end if
				else
				{
					du = (ur - ul);
					dv = (vr - vl);
					dw = (wr - wl);
				} // end else

				///////////////////////////////////////////////////////////////////////

				// test for x clipping, LHS
				if (xstart < min_clip_x)
				{
					// compute x overlap
					dx = min_clip_x - xstart;

					// slide interpolants over
					ui += dx*du;
					vi += dx*dv;
					wi += dx*dw;

					// reset vars
					xstart = min_clip_x;

				} // end if

				// test for x clipping RHS
				if (xend > max_clip_x)
					xend = max_clip_x;

				///////////////////////////////////////////////////////////////////////

				// draw span
				for (xi = xstart; xi <= xend; xi++)
				{
					// write textel assume 5.6.5
					screen_ptr[xi] = ((ui >> (FIXP16_SHIFT + 3)) << 11) + ((vi >> (FIXP16_SHIFT + 2)) << 5) + (wi >> (FIXP16_SHIFT + 3));

					// interpolate u,v
					ui += du;
					vi += dv;
					wi += dw;
				} // end for xi

				// interpolate u,v,w,x along right and left edge
				xl += dxdyl;
				ul += dudyl;
				vl += dvdyl;
				wl += dwdyl;

				xr += dxdyr;
				ur += dudyr;
				vr += dvdyr;
				wr += dwdyr;

				// advance screen ptr
				screen_ptr += mem_pitch;

			} // end for y

		} // end if clip
		else
		{
			// non-clip version

			// point screen ptr to starting line
			screen_ptr = dest_buffer + (ystart * mem_pitch);

			for (yi = ystart; yi <= yend; yi++)
			{
				// compute span endpoints
				xstart = ((xl + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
				xend = ((xr + FIXP16_ROUND_UP) >> FIXP16_SHIFT);

				// compute starting points for u,v,w interpolants
				ui = ul + FIXP16_ROUND_UP;
				vi = vl + FIXP16_ROUND_UP;
				wi = wl + FIXP16_ROUND_UP;

				// compute u,v interpolants
				if ((dx = (xend - xstart)) > 0)
				{
					du = (ur - ul) / dx;
					dv = (vr - vl) / dx;
					dw = (wr - wl) / dx;
				} // end if
				else
				{
					du = (ur - ul);
					dv = (vr - vl);
					dw = (wr - wl);
				} // end else

				// draw span
				for (xi = xstart; xi <= xend; xi++)
				{
					// write textel 5.6.5
					screen_ptr[xi] = ((ui >> (FIXP16_SHIFT + 3)) << 11) + ((vi >> (FIXP16_SHIFT + 2)) << 5) + (wi >> (FIXP16_SHIFT + 3));

					// interpolate u,v
					ui += du;
					vi += dv;
					wi += dw;
				} // end for xi

				// interpolate u,v,w,x along right and left edge
				xl += dxdyl;
				ul += dudyl;
				vl += dvdyl;
				wl += dwdyl;

				xr += dxdyr;
				ur += dudyr;
				vr += dvdyr;
				wr += dwdyr;

				// advance screen ptr
				screen_ptr += mem_pitch;

			} // end for y

		} // end if non-clipped

	} // end if
	else
	if (tri_type == TRI_TYPE_GENERAL)
	{

		// first test for bottom clip, always
		if ((yend = y2) > max_clip_y)
			yend = max_clip_y;

		// pre-test y clipping status
		if (y1 < min_clip_y)
		{
			// compute all deltas
			// LHS
			dyl = (y2 - y1);

			dxdyl = ((x2 - x1) << FIXP16_SHIFT) / dyl;
			dudyl = ((tu2 - tu1) << FIXP16_SHIFT) / dyl;
			dvdyl = ((tv2 - tv1) << FIXP16_SHIFT) / dyl;
			dwdyl = ((tw2 - tw1) << FIXP16_SHIFT) / dyl;

			// RHS
			dyr = (y2 - y0);

			dxdyr = ((x2 - x0) << FIXP16_SHIFT) / dyr;
			dudyr = ((tu2 - tu0) << FIXP16_SHIFT) / dyr;
			dvdyr = ((tv2 - tv0) << FIXP16_SHIFT) / dyr;
			dwdyr = ((tw2 - tw0) << FIXP16_SHIFT) / dyr;

			// compute overclip
			dyr = (min_clip_y - y0);
			dyl = (min_clip_y - y1);

			// computer new LHS starting values
			xl = dxdyl*dyl + (x1 << FIXP16_SHIFT);

			ul = dudyl*dyl + (tu1 << FIXP16_SHIFT);
			vl = dvdyl*dyl + (tv1 << FIXP16_SHIFT);
			wl = dwdyl*dyl + (tw1 << FIXP16_SHIFT);

			// compute new RHS starting values
			xr = dxdyr*dyr + (x0 << FIXP16_SHIFT);

			ur = dudyr*dyr + (tu0 << FIXP16_SHIFT);
			vr = dvdyr*dyr + (tv0 << FIXP16_SHIFT);
			wr = dwdyr*dyr + (tw0 << FIXP16_SHIFT);

			// compute new starting y
			ystart = min_clip_y;

			// test if we need swap to keep rendering left to right
			if (dxdyr > dxdyl)
			{
				SWAP(dxdyl, dxdyr, temp);
				SWAP(dudyl, dudyr, temp);
				SWAP(dvdyl, dvdyr, temp);
				SWAP(dwdyl, dwdyr, temp);
				SWAP(xl, xr, temp);
				SWAP(ul, ur, temp);
				SWAP(vl, vr, temp);
				SWAP(wl, wr, temp);
				SWAP(x1, x2, temp);
				SWAP(y1, y2, temp);
				SWAP(tu1, tu2, temp);
				SWAP(tv1, tv2, temp);
				SWAP(tw1, tw2, temp);

				// set interpolation restart
				irestart = INTERP_RHS;

			} // end if

		} // end if
		else
		if (y0 < min_clip_y)
		{
			// compute all deltas
			// LHS
			dyl = (y1 - y0);

			dxdyl = ((x1 - x0) << FIXP16_SHIFT) / dyl;
			dudyl = ((tu1 - tu0) << FIXP16_SHIFT) / dyl;
			dvdyl = ((tv1 - tv0) << FIXP16_SHIFT) / dyl;
			dwdyl = ((tw1 - tw0) << FIXP16_SHIFT) / dyl;

			// RHS
			dyr = (y2 - y0);

			dxdyr = ((x2 - x0) << FIXP16_SHIFT) / dyr;
			dudyr = ((tu2 - tu0) << FIXP16_SHIFT) / dyr;
			dvdyr = ((tv2 - tv0) << FIXP16_SHIFT) / dyr;
			dwdyr = ((tw2 - tw0) << FIXP16_SHIFT) / dyr;

			// compute overclip
			dy = (min_clip_y - y0);

			// computer new LHS starting values
			xl = dxdyl*dy + (x0 << FIXP16_SHIFT);
			ul = dudyl*dy + (tu0 << FIXP16_SHIFT);
			vl = dvdyl*dy + (tv0 << FIXP16_SHIFT);
			wl = dwdyl*dy + (tw0 << FIXP16_SHIFT);

			// compute new RHS starting values
			xr = dxdyr*dy + (x0 << FIXP16_SHIFT);
			ur = dudyr*dy + (tu0 << FIXP16_SHIFT);
			vr = dvdyr*dy + (tv0 << FIXP16_SHIFT);
			wr = dwdyr*dy + (tw0 << FIXP16_SHIFT);

			// compute new starting y
			ystart = min_clip_y;

			// test if we need swap to keep rendering left to right
			if (dxdyr < dxdyl)
			{
				SWAP(dxdyl, dxdyr, temp);
				SWAP(dudyl, dudyr, temp);
				SWAP(dvdyl, dvdyr, temp);
				SWAP(dwdyl, dwdyr, temp);
				SWAP(xl, xr, temp);
				SWAP(ul, ur, temp);
				SWAP(vl, vr, temp);
				SWAP(wl, wr, temp);
				SWAP(x1, x2, temp);
				SWAP(y1, y2, temp);
				SWAP(tu1, tu2, temp);
				SWAP(tv1, tv2, temp);
				SWAP(tw1, tw2, temp);

				// set interpolation restart
				irestart = INTERP_RHS;

			} // end if

		} // end if
		else
		{
			// no initial y clipping

			// compute all deltas
			// LHS
			dyl = (y1 - y0);

			dxdyl = ((x1 - x0) << FIXP16_SHIFT) / dyl;
			dudyl = ((tu1 - tu0) << FIXP16_SHIFT) / dyl;
			dvdyl = ((tv1 - tv0) << FIXP16_SHIFT) / dyl;
			dwdyl = ((tw1 - tw0) << FIXP16_SHIFT) / dyl;

			// RHS
			dyr = (y2 - y0);

			dxdyr = ((x2 - x0) << FIXP16_SHIFT) / dyr;
			dudyr = ((tu2 - tu0) << FIXP16_SHIFT) / dyr;
			dvdyr = ((tv2 - tv0) << FIXP16_SHIFT) / dyr;
			dwdyr = ((tw2 - tw0) << FIXP16_SHIFT) / dyr;

			// no clipping y

			// set starting values
			xl = (x0 << FIXP16_SHIFT);
			xr = (x0 << FIXP16_SHIFT);

			ul = (tu0 << FIXP16_SHIFT);
			vl = (tv0 << FIXP16_SHIFT);
			wl = (tw0 << FIXP16_SHIFT);

			ur = (tu0 << FIXP16_SHIFT);
			vr = (tv0 << FIXP16_SHIFT);
			wr = (tw0 << FIXP16_SHIFT);

			// set starting y
			ystart = y0;

			// test if we need swap to keep rendering left to right
			if (dxdyr < dxdyl)
			{
				SWAP(dxdyl, dxdyr, temp);
				SWAP(dudyl, dudyr, temp);
				SWAP(dvdyl, dvdyr, temp);
				SWAP(dwdyl, dwdyr, temp);
				SWAP(xl, xr, temp);
				SWAP(ul, ur, temp);
				SWAP(vl, vr, temp);
				SWAP(wl, wr, temp);
				SWAP(x1, x2, temp);
				SWAP(y1, y2, temp);
				SWAP(tu1, tu2, temp);
				SWAP(tv1, tv2, temp);
				SWAP(tw1, tw2, temp);

				// set interpolation restart
				irestart = INTERP_RHS;

			} // end if

		} // end else

		// test for horizontal clipping
		if ((x0 < min_clip_x) || (x0 > max_clip_x) ||
			(x1 < min_clip_x) || (x1 > max_clip_x) ||
			(x2 < min_clip_x) || (x2 > max_clip_x))
		{
			// clip version
			// x clipping	

			// point screen ptr to starting line
			screen_ptr = dest_buffer + (ystart * mem_pitch);

			for (yi = ystart; yi <= yend; yi++)
			{
				// compute span endpoints
				xstart = ((xl + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
				xend = ((xr + FIXP16_ROUND_UP) >> FIXP16_SHIFT);

				// compute starting points for u,v,w interpolants
				ui = ul + FIXP16_ROUND_UP;
				vi = vl + FIXP16_ROUND_UP;
				wi = wl + FIXP16_ROUND_UP;

				// compute u,v interpolants
				if ((dx = (xend - xstart)) > 0)
				{
					du = (ur - ul) / dx;
					dv = (vr - vl) / dx;
					dw = (wr - wl) / dx;
				} // end if
				else
				{
					du = (ur - ul);
					dv = (vr - vl);
					dw = (wr - wl);
				} // end else

				///////////////////////////////////////////////////////////////////////

				// test for x clipping, LHS
				if (xstart < min_clip_x)
				{
					// compute x overlap
					dx = min_clip_x - xstart;

					// slide interpolants over
					ui += dx*du;
					vi += dx*dv;
					wi += dx*dw;

					// set x to left clip edge
					xstart = min_clip_x;

				} // end if

				// test for x clipping RHS
				if (xend > max_clip_x)
					xend = max_clip_x;

				///////////////////////////////////////////////////////////////////////

				// draw span
				for (xi = xstart; xi <= xend; xi++)
				{
					// write textel assume 5.6.5
					screen_ptr[xi] = ((ui >> (FIXP16_SHIFT + 3)) << 11) + ((vi >> (FIXP16_SHIFT + 2)) << 5) + (wi >> (FIXP16_SHIFT + 3));

					// interpolate u,v
					ui += du;
					vi += dv;
					wi += dw;
				} // end for xi

				// interpolate u,v,w,x along right and left edge
				xl += dxdyl;
				ul += dudyl;
				vl += dvdyl;
				wl += dwdyl;

				xr += dxdyr;
				ur += dudyr;
				vr += dvdyr;
				wr += dwdyr;

				// advance screen ptr
				screen_ptr += mem_pitch;

				// test for yi hitting second region, if so change interpolant
				if (yi == yrestart)
				{
					// test interpolation side change flag

					if (irestart == INTERP_LHS)
					{
						// LHS
						dyl = (y2 - y1);

						dxdyl = ((x2 - x1) << FIXP16_SHIFT) / dyl;
						dudyl = ((tu2 - tu1) << FIXP16_SHIFT) / dyl;
						dvdyl = ((tv2 - tv1) << FIXP16_SHIFT) / dyl;
						dwdyl = ((tw2 - tw1) << FIXP16_SHIFT) / dyl;

						// set starting values
						xl = (x1 << FIXP16_SHIFT);
						ul = (tu1 << FIXP16_SHIFT);
						vl = (tv1 << FIXP16_SHIFT);
						wl = (tw1 << FIXP16_SHIFT);

						// interpolate down on LHS to even up
						xl += dxdyl;
						ul += dudyl;
						vl += dvdyl;
						wl += dwdyl;
					} // end if
					else
					{
						// RHS
						dyr = (y1 - y2);

						dxdyr = ((x1 - x2) << FIXP16_SHIFT) / dyr;
						dudyr = ((tu1 - tu2) << FIXP16_SHIFT) / dyr;
						dvdyr = ((tv1 - tv2) << FIXP16_SHIFT) / dyr;
						dwdyr = ((tw1 - tw2) << FIXP16_SHIFT) / dyr;

						// set starting values
						xr = (x2 << FIXP16_SHIFT);
						ur = (tu2 << FIXP16_SHIFT);
						vr = (tv2 << FIXP16_SHIFT);
						wr = (tw2 << FIXP16_SHIFT);

						// interpolate down on RHS to even up
						xr += dxdyr;
						ur += dudyr;
						vr += dvdyr;
						wr += dwdyr;

					} // end else

				} // end if

			} // end for y

		} // end if
		else
		{
			// no x clipping
			// point screen ptr to starting line
			screen_ptr = dest_buffer + (ystart * mem_pitch);

			for (yi = ystart; yi <= yend; yi++)
			{
				// compute span endpoints
				xstart = ((xl + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
				xend = ((xr + FIXP16_ROUND_UP) >> FIXP16_SHIFT);

				// compute starting points for u,v,w interpolants
				ui = ul + FIXP16_ROUND_UP;
				vi = vl + FIXP16_ROUND_UP;
				wi = wl + FIXP16_ROUND_UP;

				// compute u,v interpolants
				if ((dx = (xend - xstart)) > 0)
				{
					du = (ur - ul) / dx;
					dv = (vr - vl) / dx;
					dw = (wr - wl) / dx;
				} // end if
				else
				{
					du = (ur - ul);
					dv = (vr - vl);
					dw = (wr - wl);
				} // end else

				// draw span
				for (xi = xstart; xi <= xend; xi++)
				{
					// write textel assume 5.6.5
					screen_ptr[xi] = ((ui >> (FIXP16_SHIFT + 3)) << 11) + ((vi >> (FIXP16_SHIFT + 2)) << 5) + (wi >> (FIXP16_SHIFT + 3));

					// interpolate u,v
					ui += du;
					vi += dv;
					wi += dw;
				} // end for xi

				// interpolate u,v,w,x along right and left edge
				xl += dxdyl;
				ul += dudyl;
				vl += dvdyl;
				wl += dwdyl;

				xr += dxdyr;
				ur += dudyr;
				vr += dvdyr;
				wr += dwdyr;

				// advance screen ptr
				screen_ptr += mem_pitch;

				// test for yi hitting second region, if so change interpolant
				if (yi == yrestart)
				{
					// test interpolation side change flag

					if (irestart == INTERP_LHS)
					{
						// LHS
						dyl = (y2 - y1);

						dxdyl = ((x2 - x1) << FIXP16_SHIFT) / dyl;
						dudyl = ((tu2 - tu1) << FIXP16_SHIFT) / dyl;
						dvdyl = ((tv2 - tv1) << FIXP16_SHIFT) / dyl;
						dwdyl = ((tw2 - tw1) << FIXP16_SHIFT) / dyl;

						// set starting values
						xl = (x1 << FIXP16_SHIFT);
						ul = (tu1 << FIXP16_SHIFT);
						vl = (tv1 << FIXP16_SHIFT);
						wl = (tw1 << FIXP16_SHIFT);

						// interpolate down on LHS to even up
						xl += dxdyl;
						ul += dudyl;
						vl += dvdyl;
						wl += dwdyl;
					} // end if
					else
					{
						// RHS
						dyr = (y1 - y2);

						dxdyr = ((x1 - x2) << FIXP16_SHIFT) / dyr;
						dudyr = ((tu1 - tu2) << FIXP16_SHIFT) / dyr;
						dvdyr = ((tv1 - tv2) << FIXP16_SHIFT) / dyr;
						dwdyr = ((tw1 - tw2) << FIXP16_SHIFT) / dyr;

						// set starting values
						xr = (x2 << FIXP16_SHIFT);
						ur = (tu2 << FIXP16_SHIFT);
						vr = (tv2 << FIXP16_SHIFT);
						wr = (tw2 << FIXP16_SHIFT);

						// interpolate down on RHS to even up
						xr += dxdyr;
						ur += dudyr;
						vr += dvdyr;
						wr += dwdyr;
					} // end else

				} // end if

			} // end for y

		} // end else	

	} // end if

} // end Draw_Gouraud_Triangle16

///////////////////////////////////////////////////////////////////////////////