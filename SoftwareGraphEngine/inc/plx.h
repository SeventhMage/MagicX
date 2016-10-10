#ifndef _PLX_H_
#define _PLX_H_

#include <stdio.h>
#include "polygon.h"
#include "math.h"

#define PLX_RGB_MASK				0x8000		//抽取RGB/索引颜色模式的掩码
#define PLX_SHADE_MODE_MASK			0x6000		//抽取着色模式的掩码
#define PLX_2SIDED_MASK				0x1000		//抽取双面状态设置的掩码
#define PLX_COLOR_MASK				0x0fff		//xxxxrrrgggbbb 4位RGB分量；xxxxxxxxiiiiiiii,颜色索引模式下的8位索引

//用于判断颜色模式下的标记
#define PLX_COLOR_MODE_RGB_FLAG			0x8000		//多边形使用RGB颜色
#define PLX_COLOR_MODE_INDEXED_FLAG		0x0000		//多边形使用8位颜色索引

//双面标记
#define PLX_2SIDED_FLAG				0x1000		//双面多边形
#define PLX_1SIDED_FLAG				0x0000		//单面多边形

//着色模式标记
#define PLX_SHADE_MODE_PURE_FLAG		0x0000		//固定着色
#define PLX_SHADE_MODE_FLAT_FLAG		0x2000		//恒定着色
#define PLX_SHADE_MODE_GOURAUD_FLAG		0x4000		//gouraud
#define PLX_SHADE_MODE_PHONG_FLAG		0x6000		//phong

int Load_OBJECT4DV1_PLG(OBJECT4DV1_PTR obj, char *filename, VECTOR4D_PTR scale, VECTOR4D_PTR pos, VECTOR4D_PTR rot);
int Load_OBJECT4DV2_PLG(OBJECT4DV2_PTR obj, char *filename, VECTOR4D_PTR scale, VECTOR4D_PTR pos, VECTOR4D_PTR rot, int vertex_flags = 0);
int Load_OBJECT4DV2_COB(OBJECT4DV2_PTR obj, char *filename, VECTOR4D_PTR scale, VECTOR4D_PTR pos, VECTOR4D_PTR rot, int vertex_flags = 0);
#endif
