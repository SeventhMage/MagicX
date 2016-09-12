#include "camera.h"
#include "tool.h"

#include <math.h>

void Init_CAM4DV1(CAM4DV1_PTR cam, int cam_attr, POINT4D_PTR cam_pos, VECTOR4D_PTR cam_dir
	, POINT4D_PTR cam_target, float near_clip_z, float far_clip_z, float fov, float viewport_width, float viewport_height)
{
	cam->attr = cam_attr;
	VECTOR4D_COPY(&cam->pos, cam_pos);
	VECTOR4D_COPY(&cam->dir, cam_dir);

	VECTOR4D_INITXYZ(&cam->u, 1.f, .0f, .0f);
	VECTOR4D_INITXYZ(&cam->v, 0.f, 1.f, .0f);
	VECTOR4D_INITXYZ(&cam->n, .0f, .0f, 1.f);

	if (cam_pos != NULL)
		VECTOR4D_COPY(&cam->target, cam_target);
	else
		VECTOR4D_ZERO(&cam->target);

	cam->near_clip_z = near_clip_z;
	cam->far_clip_z = far_clip_z;

	cam->viewport_width = viewport_width;
	cam->viewplane_height = viewport_height;

	cam->viewport_center_x = (viewport_width - 1) / 2;
	cam->viewport_center_y = (viewport_height - 1) / 2;

	cam->aspect_ratio = (float)viewport_width / (float)viewport_height;

	MAT_IDENTITY_4X4(&cam->mcam);
	MAT_IDENTITY_4X4(&cam->mper);
	MAT_IDENTITY_4X4(&cam->mscr);

	cam->fov = fov;

	cam->viewplane_width = 2;
	cam->viewplane_height = 2 / cam->aspect_ratio;

	float tan_fov_div2 = tan(DEG_TO_RAD(fov / 2));
	//cam->view_dist = 0.5f * cam->viewplane_width * tan_fov_div2;
	cam->view_dist = 0.5f * cam->viewplane_width / tan_fov_div2;
	cam->viewport_dist = 0.5f * cam->viewport_width / tan_fov_div2;

	if (fov == 90.0)
	{
		POINT3D pt_origin;
		VECTOR3D_INITXYZ(&pt_origin, 0, 0, 0);
		VECTOR3D vn;
		//右裁剪面
		VECTOR3D_INITXYZ(&vn, 1, 0, 11);
		PLANE3D_Init(&cam->rt_clip_plane, &pt_origin, &vn, 1);
		//左裁剪面
		VECTOR3D_INITXYZ(&vn, -1, 0, 1);
		PLANE3D_Init(&cam->lt_clip_plane, &pt_origin, &vn, 1);
		//上裁剪面
		VECTOR3D_INITXYZ(&vn, 0, 1, 1);
		PLANE3D_Init(&cam->tp_clip_plane, &pt_origin, &vn, 1);
		//下裁剪面
		VECTOR3D_INITXYZ(&vn, 0, -1, 1);
		PLANE3D_Init(&cam->bt_clip_plane, &pt_origin, &vn, 1);
	}
	else
	{
		POINT3D pt_origin;
		VECTOR3D_INITXYZ(&pt_origin, 0, 0, 0);
		VECTOR3D vn;

		VECTOR3D_INITXYZ(&vn, cam->view_dist, 0, cam->viewplane_width / 2.0f);
		PLANE3D_Init(&cam->rt_clip_plane, &pt_origin, &vn, 1);

		VECTOR3D_INITXYZ(&vn, -cam->view_dist, 0, cam->viewplane_width / 2.0f);
		PLANE3D_Init(&cam->lt_clip_plane, &pt_origin, &vn, 1);

		VECTOR3D_INITXYZ(&vn, 0, cam->view_dist, cam->viewplane_width / 2.0f);
		PLANE3D_Init(&cam->rt_clip_plane, &pt_origin, &vn, 1);

		VECTOR3D_INITXYZ(&vn, 0, -cam->view_dist, cam->viewplane_width / 2.0f);
		PLANE3D_Init(&cam->rt_clip_plane, &pt_origin, &vn, 1);
	}
}

void Build_CAM4DV1_Matrix_Euler(CAM4DV1_PTR cam, int cam_rot_seq)
{
	MATRIX4X4 mt_inv;
	MATRIX4X4 mx_inv;
	MATRIX4X4 my_inv;
	MATRIX4X4 mz_inv;
	MATRIX4X4 mrot;
	MATRIX4X4 mtmp;

	//相机平移矩阵的逆矩阵
	Mat_Init_4X4(&mt_inv, 1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 0, 1,
		-cam->pos.x, -cam->pos.y, -cam->pos.z, 1);

	//旋转矩阵
	//提取欧拉角
	float theta_x = cam->dir.x;
	float theta_y = cam->dir.y;
	float theta_z = cam->dir.z;

	float cos_theta = Fast_Cos(theta_x); //cos(-x) = cos(x)
	float sin_theta = -Fast_Sin(theta_x);	//sin(-x) = -sin(x)

	Mat_Init_4X4(&mx_inv, 1, 0, 0, 0,
		0, cos_theta, sin_theta, 0,
		0, -sin_theta, cos_theta, 0,
		0, 0, 0, 1);

	Mat_Init_4X4(&mx_inv, cos_theta, 0, -sin_theta, 0,
		0, 1, 0, 0,
		sin_theta, 0, cos_theta, 0,
		0, 0, 0, 1);

	Mat_Init_4X4(&mz_inv, 
		cos_theta, sin_theta, 0, 0,
		-sin_theta, cos_theta, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	switch (cam_rot_seq)
	{
	case CAM_ROT_SEQ_XYZ:
		Mat_Mul_4X4(&mx_inv, &my_inv, &mtmp);
		Mat_Mul_4X4(&mtmp, &mz_inv, &mrot);
		break;
	case CAM_ROT_SEQ_YXZ:
		Mat_Mul_4X4(&my_inv, &mx_inv, &mtmp);
		Mat_Mul_4X4(&mtmp, &mz_inv, &mrot);
		break;
	case CAM_ROT_SEQ_XZY:
		Mat_Mul_4X4(&mx_inv, &mz_inv, &mtmp);
		Mat_Mul_4X4(&mtmp, &my_inv, &mrot);
		break;
	case CAM_ROT_SEQ_YZX:
		Mat_Mul_4X4(&my_inv, &mz_inv, &mtmp);
		Mat_Mul_4X4(&mtmp, &mx_inv, &mrot);
		break;
	case CAM_ROT_SEQ_ZYX:
		Mat_Mul_4X4(&mz_inv, &my_inv, &mtmp);
		Mat_Mul_4X4(&mtmp, &mx_inv, &mrot);
		break;
	case CAM_ROT_SEQ_ZXY:
		Mat_Mul_4X4(&mz_inv, &mx_inv, &mtmp);
		Mat_Mul_4X4(&mtmp, &my_inv, &mrot);
		break;
	default:
		break;
	}

	Mat_Mul_4X4(&mt_inv, &mrot, &cam->mcam);
}

void Build_CAM4DV1_Matrix_UVN(CAM4DV1_PTR cam, int mode)
{
	MATRIX4X4 mt_inv;
	MATRIX4X4 mt_uvn;
	MATRIX4X4 mtmp;

	//相机平移矩阵的逆矩阵
	Mat_Init_4X4(&mt_inv, 1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 0, 1,
		-cam->pos.x, -cam->pos.y, -cam->pos.z, 1);

	if (UVN_MODE_SPHERICAL == mode)
	{
		float phi = cam->dir.x;
		float theta = cam->dir.y;

		float sin_phi = Fast_Sin(phi);
		float cos_phi = Fast_Cos(theta);

		float sin_theta = Fast_Sin(theta);
		float cos_theta = Fast_Cos(theta);

		cam->target.x = -1 * sin_phi * sin_theta;
		cam->target.y = 1 * cos_phi;
		cam->target.z = 1 * sin_phi * cos_theta;
	}

	VECTOR4D_Build(&cam->pos, &cam->target, &cam->n);
	
	VECTOR4D_INITXYZ(&cam->v, 0, 1, 0);

	VECTOR4D_Cross(&cam->v, &cam->n, &cam->u);
	
	VECTOR4D_Cross(&cam->n, &cam->u, &cam->v);
	
	VECTOR4D_Normalize(&cam->u);
	VECTOR4D_Normalize(&cam->v);
	VECTOR4D_Normalize(&cam->n);

	Mat_Init_4X4(&mt_uvn, cam->u.x, cam->v.x, cam->n.x, 0,
		cam->u.y, cam->v.y, cam->n.y, 0,
		cam->u.z, cam->v.z, cam->n.z, 0,
		0, 0, 0, 1);

	Mat_Mul_4X4(&mt_inv, &mt_uvn, &cam->mcam);
}
