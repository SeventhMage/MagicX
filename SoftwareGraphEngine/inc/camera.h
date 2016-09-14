#ifndef _SGE_CAMERA_H_
#define _SGE_CAMERA_H_

#include "sgemath.h"

#define CAM_ROT_SEQ_XYZ 0
#define CAM_ROT_SEQ_YXZ 1
#define CAM_ROT_SEQ_XZY 2
#define CAM_ROT_SEQ_YZX 3
#define CAM_ROT_SEQ_ZYX 4
#define CAM_ROT_SEQ_ZXY 5

#define CAM_MODEL_EULER            0x0008
#define CAM_MODEL_UVN              0x0010

#define UVN_MODE_SIMPLE 0
#define UVN_MODE_SPHERICAL 1

typedef struct CAM4DV1_TYPE
{
	int state;			//相机状态
	int attr;			//相机属性
	POINT4D pos;		//相机在世界坐标中的位置
	VECTOR4D dir;		//欧拉角度或UVN相机模型中的注视方向
	
	VECTOR4D u, v, n;	//UVN模型中的朝向向量
	POINT4D target;		//UVN模型的目标位置
		
	float view_dist;	//视距
	float viewport_dist;

	float fov;			//视野

	float near_clip_z;	//近裁剪面
	float far_clip_z;	//远裁剪面

	PLANE3D rt_clip_plane;	//右裁剪面
	PLANE3D lt_clip_plane;	//左裁剪面
	PLANE3D tp_clip_plane;	//上裁剪面
	PLANE3D bt_clip_plane;	//下裁剪面

	float viewplane_width;	//视平面的宽度
	float viewplane_height;	//视平面的高度

	float viewport_width;		//视口宽度
	float viewport_height;		//视口高度
	float viewport_center_x;	//视口中心
	float viewport_center_y;

	float aspect_ratio;			//宽高比

	MATRIX4X4 mcam;				//相机矩阵
	MATRIX4X4 mper;				//透视矩阵
	MATRIX4X4 mscr;				//投影矩阵
}CAM4DV1, *CAM4DV1_PTR;

void Init_CAM4DV1(CAM4DV1_PTR cam, int cam_attr, POINT4D_PTR cam_pos, VECTOR4D_PTR cam_dir
	, POINT4D_PTR cam_target, float near_clip_z, float far_clip_z, float fov, float viewport_width, float viewport_height);
void Build_CAM4DV1_Matrix_Euler(CAM4DV1_PTR cam, int cam_rot_seq);
void Build_CAM4DV1_Matrix_UVN(CAM4DV1_PTR cam, int mode);

#endif