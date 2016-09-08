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

//ͨ���������Ⱦ�б����ζ�����б任
void Transform_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, MATRIX4X4_PTR mt, int coord_select);
//ͨ�������������б任
void Transform_OBJECT4DV1(OBJECT4DV1_PTR obj, MATRIX4X4_PTR mt, int coord_select, int transform_basis);
//ͨ��������������������ֲ�����ת��
void Model_To_World_OBJECT4DV1(OBJECT4DV1_PTR obj, int coord_select = TRANSFORM_LOCAL_TO_TRANS);
//�����ֲ����굽��������ı任����
void Build_Model_To_World_MATRIX4X4(VECTOR4D_PTR vpos, MATRIX4X4_PTR m);
//�任��Ⱦ�б�ľֲ����굽��������
void Model_To_World_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, POINT4D_PTR world_pos, int coord_select = TRANSFORM_LOCAL_TO_TRANS);
//ͨ������������������ת�������������
void World_To_Camera_OBJECT4DV1(CAM4DV1_PTR cam, OBJECT4DV1_PTR obj);

#endif
