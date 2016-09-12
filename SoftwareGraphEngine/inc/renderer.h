#ifndef _SGE_RENDERER_H_
#define _SGE_RENDERER_H_

#include "polygon.h"
#include "camera.h"

#define TRANSFORM_LOCAL_ONLY       0
#define TRANSFORM_TRANS_ONLY       1
#define TRANSFORM_LOCAL_TO_TRANS   2

#define CULL_OBJECT_X_PLANE			0x0001
#define CULL_OBJECT_Y_PLANE			0x0002
#define CULL_OBJECT_Z_PLANE			0x0004
#define CULL_OBJECT_XYZ_PLANE		(CULL_OBJECT_X_PLANE | CULL_OBJECT_Y_PLANE | CULL_OBJECT_Z_PLANE)


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
//ͨ�������������������ת�������������
void World_To_Camera_OBJECT4DV1(CAM4DV1_PTR cam, OBJECT4DV1_PTR obj);
//ͨ��������Ⱦ�б����������ת�������������
void World_To_Camera_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam);
//�����޳�
bool Cull_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam, int cull_flags);
//���屳���޳�
void Remove_Backfaces_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam);
//��Ⱦ�б����޳�
void Remove_Backfaces_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam);
//��������ü�
void Reset_OBJECT4DV1(OBJECT4DV1_PTR obj);
//�ֶ���ʽ������ת����͸������
void Camera_To_Perspective_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam);
//����͸�Ӿ���
void Build_Camera_To_Perspective_MATRIX4X4(CAM4DV1_PTR cam, MATRIX4X4_PTR m);
//4D������굽3D����
void Convert_From_Homogeneous4D_OBJECT4DV1(OBJECT4DV1_PTR obj);
//�ֶ���ʽ����Ⱦ�б�ת����͸������
void Camera_To_Perspective_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam);
//4D������굽3D����
void Convert_From_Homogeneous4D_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list);
//�ֶ�������ִ��͸�����굽��Ļ����
void Perspective_To_Screen_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam);
//4D͸�����굽��Ļ�������
void Build_Perspective_To_Screen_4D_MATRIX4X4(CAM4DV1_PTR cam, MATRIX4X4_PTR m);
//3D͸�����굽��Ļ�������
void Build_Camera_To_Screen_MATRIX4X4(CAM4DV1_PTR cam, MATRIX4X4_PTR m);
//��Ⱦ�б�͸�����굽��Ļ����ı任
void Perspective_To_Screen_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam);
//�����������굽��Ļ����ı任
void Camera_To_Perspective_Screen_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam);
//��Ⱦ�б��������굽��Ļ����ı任
void Camera_To_Perspective_Screen_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam);
//�����߿�����
void Draw_OBJECT4DV1_Wire16(OBJECT4DV1_PTR obj, unsigned char *video_buffer, int lpitch);
//�����߿���Ⱦ�б�
void Draw_RENDERLIST4DV1_Wire16(RENDERLIST4DV1_PTR rend_list, unsigned char *video_buffer, int lpitch);

#endif
