#ifndef _SGE_LIGHT_H_
#define _SGE_LIGHT_H_

#include "tool.h"
#include "sgemath.h"

#define LIGHTV1_ATTR_AMBIENT      0x0001    // 环境光
#define LIGHTV1_ATTR_INFINITE     0x0002    // 无穷远光源
#define LIGHTV1_ATTR_DIRECTIONAL  0x0002    // 方向光（无穷远光）
#define LIGHTV1_ATTR_POINT        0x0004    // 点光源
#define LIGHTV1_ATTR_SPOTLIGHT1   0x0008    // 聚光灯（简单）
#define LIGHTV1_ATTR_SPOTLIGHT2   0x0010    // 聚光灯（复杂）

#define LIGHTV1_STATE_ON          1         // 光源打开
#define LIGHTV1_STATE_OFF         0         // 光源关闭

#define MAX_LIGHTS                8         // 最多支持光源数

typedef struct LIGHTV1_TYP
{
	int state;								// 光源状态
	int id;									// 光源id
	int attr;								// 光源属性
		
	RGBAV1 c_ambient;						// 环境光强度
	RGBAV1 c_diffuse;						// 散射光强度
	RGBAV1 c_specular;						// 镜面反射光强度

	POINT4D  pos;							// 光源位置
	VECTOR4D dir;							// 光照方向

	float kc, kl, kq;						// 衰减因子
	float spot_inner;						// 聚光灯内锥角
	float spot_outer;						// 聚光灯外锥角
	float pf;								// 聚光灯指数因子

}LIGHTV1, *LIGHTV1_PTR;

extern LIGHTV1 lights[MAX_LIGHTS];					//全局光源数组
extern int num_lights;								//当前光源数

void Reset_Lights_LIGHTV1();
int Init_Light_LIGHTV1(int index, int _state, int _attr, RGBAV1 _c_ambient, RGBAV1 _c_diffuse,
	RGBAV1 _c_specular, POINT4D_PTR _pos, VECTOR4D_PTR _dir, float _kc, float _kl, float _kq, 
	float _spot_inner, float _spot_outer, float _pf);

#endif