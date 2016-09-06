#ifndef _SGE_RENDERER_H_
#define _SGE_RENDERER_H_

#include "polygon.h"

#define TRANSFORM_LOCAL_ONLY       0	// perform the transformation in place on the
										// local/world vertex list 
#define TRANSFORM_TRANS_ONLY       1	// perfrom the transformation in place on the 
										// "transformed" vertex list

#define TRANSFORM_LOCAL_TO_TRANS   2	// perform the transformation to the local
										// vertex list, but store the results in the
										// transformed vertex list

//通过矩阵对渲染列表多边形顶点进行变换
void Transform_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, MATRIX4X4_PTR mt, int coord_select);

#endif
