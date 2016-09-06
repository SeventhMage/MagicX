#ifndef _SGE_POLYGON_H_
#define _SGE_POLYGON_H_

#include "sgemath.h"

//多边形和多边形面的属性
#define POLY4DV1_ATTR_2SIDED		0x0001
#define POLY4DV1_ATTR_TRANSPARENT	0x0002
#define POLY4DV1_ATTR_8BITCOLOR     0x0004
#define POLY4DV1_ATTR_RGB16			0x0008
#define POLY4DV1_ATTR_RGB24			0x0010

#define POLY4DV1_ATTR_SHADE_MODE_PURE		0x0020
#define POLY4DV1_ATTR_SHADE_MODE_FLAT		0x0040
#define POLY4DV1_ATTR_SHADE_MODE_GOURAUD	0x0080
#define POLY4DV1_ATTR_SHADE_MODE_PHONG		0x0100

//多边形和面的状态值
#define POLY4DV1_STATE_ACTIVE		0x0001
#define POLY4DV1_STATE_CLIPPED		0x0002
#define POLY4DV1_STATE_BACKFACE		0x0004

//最大顶点数，多边形数
#define OBJECT4DV1_MAX_VERTICES           1024  // 64
#define OBJECT4DV1_MAX_POLYS              1024 // 128

// 物体状态
#define OBJECT4DV1_STATE_ACTIVE           0x0001
#define OBJECT4DV1_STATE_VISIBLE          0x0002 
#define OBJECT4DV1_STATE_CULLED           0x0004

//渲染列表中多边形数
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
	int state;	//状态信息
	int attr;	//多边形的物理属性
	int color;	//多边形的颜色

	POINT4D_PTR vlist;	//顶点列表
	int vert[3];		//顶点列表的索引
}POLY4DV1, *POLY4DV1_PTR;

typedef struct POLYF4DV1_TYP
{
	int state;	//状态信息
	int attr;	//多边形的物理属性
	int color;	//多边形的颜色

	POINT4D vlist[3];	//三角形的顶点
	POINT4D tvlist[3];	//变幻后的顶点
	POLYF4DV1_TYP *next;	//指向列表中下一个多边形的指针
	POLYF4DV1_TYP *prev;	//指向列表中前一个多边形的指针	
}POLYF4DV1, *POLYF4DV1_PTR;

typedef struct OBJECT4DV1_TYP
{
	int id;		//物体的数值ID
	char name[64];	//物体的字符串名字
	int state;	//物体的状态
	int attr;	//物体的属性
       	float avg_radius;	//物体的平均半径，碰撞检测
	float max_radius;	//物体最大半径

	POINT4D world_pos;	//物体在世界坐标中的位置
	VECTOR4D dir;		//物体在局部坐标下的旋转角度	
	VECTOR4D ux, uy, uz;	//物体朝向的局部坐标轴，物体旋转时相应旋转

	int num_vertices;	//物体顶点数
	POINT4D vlist_local[OBJECT4DV1_MAX_VERTICES];	//存储顶点局部坐标的数组
	POINT4D vlist_trans[OBJECT4DV1_MAX_VERTICES];	//存储顶点变化后坐标的数组

	int num_polys;			//物体的多边形数	
	POLY4DV1 plist[OBJECT4DV1_MAX_POLYS];		//存储多边形的数组		
}OBJECT4DV1, *OBJECT4DV1_PTR;

typedef struct RENDERLIST4DV1_TYP
{
	int state;	//渲染列表的状态
	int attr;	//渲染列表的属性

	POLYF4DV1_PTR poly_ptrs[RENDERLIST4DV1_MAX_POLYS];	//渲染列表
	POLYF4DV1 poly_data;					//多边形数据
	int num_polys;						//渲染列表中包含的多边形数目
}RENDERLIST4DV1, *RENDERLIST4DV1_PTR;
 
void Reset_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list);

float Compute_OBJECT4DV1_Radius(OBJECT4DV1_PTR obj);

#endif
