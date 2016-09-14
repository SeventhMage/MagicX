#ifndef _SGE_MATERIAL_H_
#define _SGE_MATERIAL_H_

#include "tool.h"

//材质属性
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

//材质状态
#define MATV1_STATE_ACTIVE				0x0001

//最大数量
#define MAX_MATERIALS					256


typedef struct MATV1_TYPE
{
	int state;						//材质状态
	int id;							//材质id
	char name[64];					//材质名称
	int attr;						//材质属性

	RGBAV1 color;					//材质颜色
	
	float ka;						//环境反射系数
	float kd;						//散射光反射系数
	float ks;						//镜面光反射系数
	float power;					//镜面反射指数

	//预先计算颜色与反射系数的积
	RGBAV1 ra;
	RGBAV1 rd;
	RGBAV1 rs;

	char texture_file[128];			//纹理文件位置
	BITMAP_IMAGE texture;			//纹理图
}MATV1, *MATV1_PTR;

extern MATV1 materials[MAX_MATERIALS];		//全局系统中的材质
extern int num_materials;					//当前材质数

void Reset_Materials_MATV1();

#endif