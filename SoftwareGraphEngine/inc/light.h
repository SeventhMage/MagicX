#ifndef _SGE_LIGHT_H_
#define _SGE_LIGHT_H_

#include "tool.h"
#include "sgemath.h"

#define LIGHTV1_ATTR_AMBIENT      0x0001    // ������
#define LIGHTV1_ATTR_INFINITE     0x0002    // ����Զ��Դ
#define LIGHTV1_ATTR_DIRECTIONAL  0x0002    // ����⣨����Զ�⣩
#define LIGHTV1_ATTR_POINT        0x0004    // ���Դ
#define LIGHTV1_ATTR_SPOTLIGHT1   0x0008    // �۹�ƣ��򵥣�
#define LIGHTV1_ATTR_SPOTLIGHT2   0x0010    // �۹�ƣ����ӣ�

#define LIGHTV1_STATE_ON          1         // ��Դ��
#define LIGHTV1_STATE_OFF         0         // ��Դ�ر�

#define MAX_LIGHTS                8         // ���֧�ֹ�Դ��

typedef struct LIGHTV1_TYP
{
	int state;								// ��Դ״̬
	int id;									// ��Դid
	int attr;								// ��Դ����
		
	RGBAV1 c_ambient;						// ������ǿ��
	RGBAV1 c_diffuse;						// ɢ���ǿ��
	RGBAV1 c_specular;						// ���淴���ǿ��

	POINT4D  pos;							// ��Դλ��
	VECTOR4D dir;							// ���շ���

	float kc, kl, kq;						// ˥������
	float spot_inner;						// �۹����׶��
	float spot_outer;						// �۹����׶��
	float pf;								// �۹��ָ������

}LIGHTV1, *LIGHTV1_PTR;

extern LIGHTV1 lights[MAX_LIGHTS];					//ȫ�ֹ�Դ����
extern int num_lights;								//��ǰ��Դ��

void Reset_Lights_LIGHTV1();
int Init_Light_LIGHTV1(int index, int _state, int _attr, RGBAV1 _c_ambient, RGBAV1 _c_diffuse,
	RGBAV1 _c_specular, POINT4D_PTR _pos, VECTOR4D_PTR _dir, float _kc, float _kl, float _kq, 
	float _spot_inner, float _spot_outer, float _pf);

#endif