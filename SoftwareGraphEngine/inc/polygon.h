#ifndef _SGE_POLYGON_H_
#define _SGE_POLYGON_H_

#include "sgemath.h"

//����κͶ�����������
#define POLY4DV1_ATTR_2SIDED		0x0001
#define POLY4DV1_ATTR_TRANSPARENT	0x0002
#define POLY4DV1_ATTR_8BITCOLOR     0x0004
#define POLY4DV1_ATTR_RGB16			0x0008
#define POLY4DV1_ATTR_RGB24			0x0010

#define POLY4DV1_ATTR_SHADE_MODE_PURE		0x0020
#define POLY4DV1_ATTR_SHADE_MODE_FLAT		0x0040
#define POLY4DV1_ATTR_SHADE_MODE_GOURAUD	0x0080
#define POLY4DV1_ATTR_SHADE_MODE_PHONG		0x0100

//����κ����״ֵ̬
#define POLY4DV1_STATE_ACTIVE		0x0001
#define POLY4DV1_STATE_CLIPPED		0x0002
#define POLY4DV1_STATE_BACKFACE		0x0004

//��󶥵������������
#define OBJECT4DV1_MAX_VERTICES           1024  // 64
#define OBJECT4DV1_MAX_POLYS              1024 // 128

// ����״̬
#define OBJECT4DV1_STATE_ACTIVE           0x0001
#define OBJECT4DV1_STATE_VISIBLE          0x0002 
#define OBJECT4DV1_STATE_CULLED           0x0004

//��Ⱦ�б��ж������
#define RENDERLIST4DV1_MAX_POLYS          32768

typedef struct POLY_EX_TYP_1
{
	POINT3D v[3];
}POLY_EX_1, *POLY_EX_1_PTR;

typedef struct POLY_EX_TYP_2
{
	POINT3D_PTR vlist;
	int vertices[3];
}POLY_EX_2, *POLY_EX_2_PTR;

typedef struct POLY4DV1_TYP
{
	int state;	//״̬��Ϣ
	int attr;	//����ε���������
	int color;	//����ε���ɫ

	POINT4D_PTR vlist;	//�����б�
	int vert[3];		//�����б������
}POLY4DV1, *POLY4DV1_PTR;

typedef struct POLYF4DV1_TYP
{
	int state;	//״̬��Ϣ
	int attr;	//����ε���������
	int color;	//����ε���ɫ

	POINT4D vlist[3];	//�����εĶ���
	POINT4D tvlist[3];	//��ú�Ķ���
	POLYF4DV1_TYP *next;	//ָ���б�����һ������ε�ָ��
	POLYF4DV1_TYP *prev;	//ָ���б���ǰһ������ε�ָ��	
}POLYF4DV1, *POLYF4DV1_PTR;

typedef struct OBJECT4DV1_TYP
{
	int id;		//�������ֵID
	char name[64];	//������ַ�������
	int state;	//�����״̬
	int attr;	//���������
       	float avg_radius;	//�����ƽ���뾶����ײ���
	float max_radius;	//�������뾶

	POINT4D world_pos;	//���������������е�λ��
	VECTOR4D dir;		//�����ھֲ������µ���ת�Ƕ�	
	VECTOR4D ux, uy, uz;	//���峯��ľֲ������ᣬ������תʱ��Ӧ��ת

	int num_vertices;	//���嶥����
	POINT4D vlist_local[OBJECT4DV1_MAX_VERTICES];	//�洢����ֲ����������
	POINT4D vlist_trans[OBJECT4DV1_MAX_VERTICES];	//�洢����仯�����������

	int num_polys;			//����Ķ������	
	POLY4DV1 plist[OBJECT4DV1_MAX_POLYS];		//�洢����ε�����		
}OBJECT4DV1, *OBJECT4DV1_PTR;

typedef struct RENDERLIST4DV1_TYP
{
	int state;	//��Ⱦ�б��״̬
	int attr;	//��Ⱦ�б������

	POLYF4DV1_PTR poly_ptrs[RENDERLIST4DV1_MAX_POLYS];	//��Ⱦ�б�
	POLYF4DV1 poly_data;					//���������
	int num_polys;						//��Ⱦ�б��а����Ķ������Ŀ
}RENDERLIST4DV1, *RENDERLIST4DV1_PTR;
 
void Reset_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list);

float Compute_OBJECT4DV1_Radius(OBJECT4DV1_PTR obj);

#endif
