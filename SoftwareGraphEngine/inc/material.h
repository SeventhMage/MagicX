#ifndef _SGE_MATERIAL_H_
#define _SGE_MATERIAL_H_

#include "tool.h"

//��������
#define MATV1_ATTR_2SIDED				0x0001
#define MATV1_ATTR_TRANSPARENT			0x0002
#define MATV1_ATTR_8BITCOLOR			0x0004
#define MATV1_ATTR_RGB16				0x0008
#define MATV1_ATTR_RGB24				0x0010

#define MATV1_ATTR_SHADE_MODE_CONSTANT	0x0020
#define MATV1_ATTR_SHADE_MODE_EMMISIVE	0x0020
#define MATV1_ATTR_SHADE_MODE_FLAG		0x0040
#define MATV1_ATTR_SHADE_MODE_GOURAUD	0x0080
#define MATV1_ATTR_SHADE_MODE_FASTPHONG	0x0100
#define MATV1_ATTR_SHADE_MODE_TEXTURE	0x0200

//����״̬
#define MATV1_STATE_ACTIVE				0x0001

//�������
#define MAX_MATERIALS					256


typedef struct MATV1_TYPE
{
	int state;						//����״̬
	int id;							//����id
	char name[64];					//��������
	int attr;						//��������

	RGBAV1 color;					//������ɫ
	
	float ka;						//��������ϵ��
	float kd;						//ɢ��ⷴ��ϵ��
	float ks;						//����ⷴ��ϵ��
	float power;					//���淴��ָ��

	//Ԥ�ȼ�����ɫ�뷴��ϵ���Ļ�
	RGBAV1 ra;
	RGBAV1 rd;
	RGBAV1 rs;

	char texture_file[128];			//�����ļ�λ��
	BITMAP_IMAGE texture;			//����ͼ
}MATV1, *MATV1_PTR;

extern MATV1 materials[MAX_MATERIALS];		//ȫ��ϵͳ�еĲ���
extern int num_materials;					//��ǰ������

void Reset_Materials_MATV1();

#endif