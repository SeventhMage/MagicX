#ifndef _SGE_RENDERER_H_
#define _SGE_RENDERER_H_

#include "polygon.h"
#include "camera.h"

#define TRANSFORM_LOCAL_ONLY       0	// perform the transformation in place on the
										// local/world vertex list 
#define TRANSFORM_TRANS_ONLY       1	// perfrom the transformation in place on the 
										// "transformed" vertex list

#define TRANSFORM_LOCAL_TO_TRANS   2	// perform the transformation to the local
										// vertex list, but store the results in the
										// transformed vertex list

//通过矩阵对渲染列表多边形顶点进行变换
void Transform_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, MATRIX4X4_PTR mt, int coord_select);
//通过矩阵对物体进行变换
void Transform_OBJECT4DV1(OBJECT4DV1_PTR obj, MATRIX4X4_PTR mt, int coord_select, int transform_basis);
//通过物体的世界坐标对物体局部坐标转换
void Model_To_World_OBJECT4DV1(OBJECT4DV1_PTR obj, int coord_select = TRANSFORM_LOCAL_TO_TRANS);
//创建局部坐标到世界坐标的变换矩阵
void Build_Model_To_World_MATRIX4X4(VECTOR4D_PTR vpos, MATRIX4X4_PTR m);
//变换渲染列表的局部坐标到世界坐标
void Model_To_World_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, POINT4D_PTR world_pos, int coord_select = TRANSFORM_LOCAL_TO_TRANS);
//通过矩阵将物体从世界矩阵转换到摄像机矩阵
void World_To_Camera_OBJECT4DV1(CAM4DV1_PTR cam, OBJECT4DV1_PTR obj);

#endif
