#ifndef _PLX_H_
#define _PLX_H_

#include <stdio.h>
#include "polygon.h"
#include "math.h"

#define PLX_RGB_MASK				0x8000		//��ȡRGB/������ɫģʽ������
#define PLX_SHADE_MODE_MASK			0x6000		//��ȡ��ɫģʽ������
#define PLX_2SIDED_MASK				0x1000		//��ȡ˫��״̬���õ�����
#define PLX_COLOR_MASK				0x0fff		//xxxxrrrgggbbb 4λRGB������xxxxxxxxiiiiiiii,��ɫ����ģʽ�µ�8λ����

//�����ж���ɫģʽ�µı��
#define PLX_COLOR_MODE_RGB_FLAG			0x8000		//�����ʹ��RGB��ɫ
#define PLX_COLOR_MODE_INDEXED_FLAG		0x0000		//�����ʹ��8λ��ɫ����

//˫����
#define PLX_2SIDED_FLAG				0x1000		//˫������
#define PLX_1SIDED_FLAG				0x0000		//��������

//��ɫģʽ���
#define PLX_SHADE_MODE_PURE_FLAG		0x0000		//�̶���ɫ
#define PLX_SHADE_MODE_FLAT_FLAG		0x2000		//�㶨��ɫ
#define PLX_SHADE_MODE_GOURAUD_FLAG		0x4000		//gouraud
#define PLX_SHADE_MODE_PHONG_FLAG		0x6000		//phong

int Load_OBJECT4DV1_PLG(OBJECT4DV1_PTR obj, char *filename, VECTOR4D_PTR scale, VECTOR4D_PTR pos, VECTOR4D_PTR rot);
int Load_OBJECT4DV2_PLG(OBJECT4DV2_PTR obj, char *filename, VECTOR4D_PTR scale, VECTOR4D_PTR pos, VECTOR4D_PTR rot, int vertex_flags = 0);
int Load_OBJECT4DV2_COB(OBJECT4DV2_PTR obj, char *filename, VECTOR4D_PTR scale, VECTOR4D_PTR pos, VECTOR4D_PTR rot, int vertex_flags = 0);
#endif
