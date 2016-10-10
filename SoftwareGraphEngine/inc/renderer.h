#ifndef _SGE_RENDERER_H_
#define _SGE_RENDERER_H_

#include "polygon.h"
#include "camera.h"
#include "typedef.h"
#include "light.h"

#define TRANSFORM_LOCAL_ONLY       0
#define TRANSFORM_TRANS_ONLY       1
#define TRANSFORM_LOCAL_TO_TRANS   2

#define CULL_OBJECT_X_PLANE			0x0001
#define CULL_OBJECT_Y_PLANE			0x0002
#define CULL_OBJECT_Z_PLANE			0x0004
#define CULL_OBJECT_XYZ_PLANES		(CULL_OBJECT_X_PLANE | CULL_OBJECT_Y_PLANE | CULL_OBJECT_Z_PLANE)

//z������
#define SORT_POLYLIST_AVGZ			0	//ƽ��zֵ����
#define SORT_POLYLIST_NEARZ			1	//��Сzֵ����
#define SORT_POLYLIST_FARZ			2	//���zֵ����

void Rotate_XYZ_OBJECT4DV1(OBJECT4DV1_PTR obj, // object to rotate
	float theta_x,      // euler angles
	float theta_y,
	float theta_z);

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
void World_To_Camera_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam);
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
void Draw_OBJECT4DV1_Wire(OBJECT4DV1_PTR obj, unsigned char *video_buffer, int lpitch);
//�����߿���Ⱦ�б�
void Draw_RENDERLIST4DV1_Wire(RENDERLIST4DV1_PTR rend_list, unsigned char *video_buffer, int lpitch);
//����ʵ������
void Draw_OBJECT4DV1_Solid(OBJECT4DV1_PTR obj, UCHAR *video_buffer, int lpitch);
//����ʵ����Ⱦ�б�
void Draw_RENDERLIST4DV1_Solid(RENDERLIST4DV1_PTR rend_list, UCHAR *video_buffer, int lpitch);
//�������ε���Ⱦ�б�
int Insert_POLY4DV1_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, POLY4DV1_PTR poly);
//���������Ⱦ�б�
int Insert_OBJECT4DV1_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, OBJECT4DV1_PTR obj, int insert_local = 0);
//��Ⱦ�б�����
void Sort_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, int sort_method);
//������Ⱦ�б�
void Light_RENDERLIST4DV1_World(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam, LIGHTV1_PTR	lights, int max_lights);


//////////////////////////////////////////////////////////////////////////
//V2																	//
//////////////////////////////////////////////////////////////////////////
int Set_OBJECT4DV2_Frame(OBJECT4DV2_PTR obj, int frame);

void Translate_OBJECT4DV2(OBJECT4DV2_PTR obj, VECTOR4D_PTR vt);

void Scale_OBJECT4DV2(OBJECT4DV2_PTR obj, VECTOR4D_PTR vs, int all_frames = 0);

void Transform_OBJECT4DV2(OBJECT4DV2_PTR obj, MATRIX4X4_PTR mt, int coord_select, int transform_basis, int all_frames = 0);

void Rotate_XYZ_OBJECT4DV2(OBJECT4DV2_PTR obj,
	float theta_x,
	float theta_y,
	float theta_z,
	int all_frames);

void Model_To_World_OBJECT4DV2(OBJECT4DV2_PTR obj, int coord_select = TRANSFORM_LOCAL_TO_TRANS, int all_frames = 0);

int Cull_OBJECT4DV2(OBJECT4DV2_PTR obj, CAM4DV1_PTR cam, int cull_flags);

void Remove_Backfaces_OBJECT4DV2(OBJECT4DV2_PTR obj, CAM4DV1_PTR cam);

void Remove_Backfaces_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list, CAM4DV1_PTR cam);

void World_To_Camera_OBJECT4DV2(OBJECT4DV2_PTR obj, CAM4DV1_PTR cam);

void Camera_To_Perspective_OBJECT4DV2(OBJECT4DV2_PTR obj, CAM4DV1_PTR cam);

void Perspective_To_Screen_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list,
	CAM4DV1_PTR cam);

void Camera_To_Perspective_Screen_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list,
	CAM4DV1_PTR cam);

void Camera_To_Perspective_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list,
	CAM4DV1_PTR cam);

void Camera_To_Perspective_Screen_OBJECT4DV2(OBJECT4DV2_PTR obj, CAM4DV1_PTR cam);

void Perspective_To_Screen_OBJECT4DV2(OBJECT4DV2_PTR obj, CAM4DV1_PTR cam);

void Convert_From_Homogeneous4D_OBJECT4DV1(OBJECT4DV1_PTR obj);

int Insert_POLY4DV2_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list,
	POLY4DV2_PTR poly);

int Insert_POLYF4DV2_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list,
	POLYF4DV2_PTR poly);

int Insert_OBJECT4DV2_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list,
	OBJECT4DV2_PTR obj,
	int insert_local);

void Reset_OBJECT4DV2(OBJECT4DV2_PTR obj);

int Compute_OBJECT4DV2_Poly_Normals(OBJECT4DV2_PTR obj);

void Draw_OBJECT4DV2_Wire(OBJECT4DV2_PTR obj, UCHAR *video_buffer, int lpitch);

void Draw_OBJECT4DV2_Wire16(OBJECT4DV2_PTR obj, UCHAR *video_buffer, int lpitch);

void Draw_RENDERLIST4DV2_Wire(RENDERLIST4DV2_PTR rend_list,
	UCHAR *video_buffer, int lpitch);


void Draw_RENDERLIST4DV2_Wire16(RENDERLIST4DV2_PTR rend_list,
	UCHAR *video_buffer, int lpitch);


void Draw_RENDERLIST4DV2_Solid(RENDERLIST4DV2_PTR rend_list,
	UCHAR *video_buffer, int lpitch);

void Draw_RENDERLIST4DV2_Solid16(RENDERLIST4DV2_PTR rend_list,
	UCHAR *video_buffer, int lpitch);

void Draw_OBJECT4DV2_Textured(OBJECT4DV2_PTR obj, UCHAR *video_buffer, int lpitch);

void Draw_RENDERLIST4DV2_Textured(RENDERLIST4DV2_PTR rend_list,
	UCHAR *video_buffer, int lpitch, BITMAP_IMAGE_PTR texture);

void Draw_RENDERLIST4DV2_Textured16(RENDERLIST4DV2_PTR rend_list,
	UCHAR *video_buffer, int lpitch, BITMAP_IMAGE_PTR texture);

void Draw_OBJECT4DV1_Solid2_16(OBJECT4DV1_PTR obj,
	UCHAR *video_buffer, int lpitch);

void Draw_RENDERLIST4DV1_Solid2(RENDERLIST4DV1_PTR rend_list,
	UCHAR *video_buffer, int lpitch);

void Draw_OBJECT4DV1_Solid2(OBJECT4DV1_PTR obj,
	UCHAR *video_buffer, int lpitch);

void World_To_Camera_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list,
	CAM4DV1_PTR cam);

void Draw_OBJECT4DV1_Solid2_16(OBJECT4DV1_PTR obj,
	UCHAR *video_buffer, int lpitch);

void Draw_RENDERLIST4DV1_Solid2(RENDERLIST4DV1_PTR rend_list,
	UCHAR *video_buffer, int lpitch);

void Draw_OBJECT4DV1_Solid2(OBJECT4DV1_PTR obj,
	UCHAR *video_buffer, int lpitch);

void Draw_OBJECT4DV1_Textured(OBJECT4DV1_PTR obj, UCHAR *video_buffer, int lpitch);

void Draw_RENDERLIST4DV1_Textured(RENDERLIST4DV1_PTR rend_list,
	UCHAR *video_buffer, int lpitch, BITMAP_IMAGE_PTR texture);

void Draw_RENDERLIST4DV1_Textured16(RENDERLIST4DV1_PTR rend_list,
	UCHAR *video_buffer, int lpitch, BITMAP_IMAGE_PTR texture);

void Draw_RENDERLIST4DV2_Gouraud16(RENDERLIST4DV2_PTR rend_list,
	UCHAR *video_buffer, int lpitch);

void Draw_RENDERLIST4DV1_Solid2_16(RENDERLIST4DV1_PTR rend_list,
	UCHAR *video_buffer, int lpitch);

void Draw_OBJECT4DV1_Solid2_16(OBJECT4DV1_PTR obj,
	UCHAR *video_buffer, int lpitch);

void Draw_RENDERLIST4DV1_Solid2_16(RENDERLIST4DV1_PTR rend_list,
	UCHAR *video_buffer, int lpitch);

void Draw_OBJECT4DV1_Solid2_16(OBJECT4DV1_PTR obj,
	UCHAR *video_buffer, int lpitch);


void Draw_RENDERLIST4DV1_Solid2(RENDERLIST4DV1_PTR rend_list,
	UCHAR *video_buffer, int lpitch);

void Draw_OBJECT4DV1_Solid2(OBJECT4DV1_PTR obj,
	UCHAR *video_buffer, int lpitch);

float Compute_OBJECT4DV2_Radius(OBJECT4DV2_PTR obj);

int Compute_OBJECT4DV2_Vertex_Normals(OBJECT4DV2_PTR obj);

void Reset_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list);

int Light_OBJECT4DV2_World(OBJECT4DV2_PTR obj, CAM4DV1_PTR cam, LIGHTV1_PTR lights, int max_lights);

int Light_RENDERLIST4DV2_World(RENDERLIST4DV2_PTR rend_list, CAM4DV1_PTR cam, LIGHTV1_PTR lights, int max_lights);

void Sort_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list, int sort_method);

void Draw_Textured_Triangle(POLYF4DV2_PTR face, UCHAR *dest_buffer, int mem_pitch);

void Draw_Textured_TriangleFS(POLYF4DV2_PTR face, UCHAR *_dest_buffer, int mem_pitch/*bytes per line*/);

void Draw_Textured_Triangle16(POLYF4DV2_PTR face, UCHAR *dest_buffer, int mem_pitch);

void Draw_Textured_TriangleFS16(POLYF4DV2_PTR face, UCHAR *_dest_buffer, int mem_pitch);

void Draw_Gouraud_Triangle16(POLYF4DV2_PTR face, UCHAR *_dest_buffer, int mem_pitch);

void Draw_Gouraud_Triangle(POLYF4DV2_PTR face, UCHAR *dest_buffer, int mem_pitch);

#endif
