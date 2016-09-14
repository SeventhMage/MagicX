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
	int state;			//���״̬
	int attr;			//�������
	POINT4D pos;		//��������������е�λ��
	VECTOR4D dir;		//ŷ���ǶȻ�UVN���ģ���е�ע�ӷ���
	
	VECTOR4D u, v, n;	//UVNģ���еĳ�������
	POINT4D target;		//UVNģ�͵�Ŀ��λ��
		
	float view_dist;	//�Ӿ�
	float viewport_dist;

	float fov;			//��Ұ

	float near_clip_z;	//���ü���
	float far_clip_z;	//Զ�ü���

	PLANE3D rt_clip_plane;	//�Ҳü���
	PLANE3D lt_clip_plane;	//��ü���
	PLANE3D tp_clip_plane;	//�ϲü���
	PLANE3D bt_clip_plane;	//�²ü���

	float viewplane_width;	//��ƽ��Ŀ��
	float viewplane_height;	//��ƽ��ĸ߶�

	float viewport_width;		//�ӿڿ��
	float viewport_height;		//�ӿڸ߶�
	float viewport_center_x;	//�ӿ�����
	float viewport_center_y;

	float aspect_ratio;			//��߱�

	MATRIX4X4 mcam;				//�������
	MATRIX4X4 mper;				//͸�Ӿ���
	MATRIX4X4 mscr;				//ͶӰ����
}CAM4DV1, *CAM4DV1_PTR;

void Init_CAM4DV1(CAM4DV1_PTR cam, int cam_attr, POINT4D_PTR cam_pos, VECTOR4D_PTR cam_dir
	, POINT4D_PTR cam_target, float near_clip_z, float far_clip_z, float fov, float viewport_width, float viewport_height);
void Build_CAM4DV1_Matrix_Euler(CAM4DV1_PTR cam, int cam_rot_seq);
void Build_CAM4DV1_Matrix_UVN(CAM4DV1_PTR cam, int mode);

#endif