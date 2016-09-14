#ifndef _SGE_RENDERER_H_
#define _SGE_RENDERER_H_

#include "polygon.h"
#include "camera.h"
#include "typedef.h"

#define TRANSFORM_LOCAL_ONLY       0
#define TRANSFORM_TRANS_ONLY       1
#define TRANSFORM_LOCAL_TO_TRANS   2

#define CULL_OBJECT_X_PLANE			0x0001
#define CULL_OBJECT_Y_PLANE			0x0002
#define CULL_OBJECT_Z_PLANE			0x0004
#define CULL_OBJECT_XYZ_PLANES		(CULL_OBJECT_X_PLANE | CULL_OBJECT_Y_PLANE | CULL_OBJECT_Z_PLANE)

void Rotate_XYZ_OBJECT4DV1(OBJECT4DV1_PTR obj, // object to rotate
	float theta_x,      // euler angles
	float theta_y,
	float theta_z);

//通过矩阵对渲染列表多边形顶点进行变换
void Transform_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, MATRIX4X4_PTR mt, int coord_select);
//通过矩阵对物体进行变换
void Transform_OBJECT4DV1(OBJECT4DV1_PTR obj, MATRIX4X4_PTR mt, int coord_select, int transform_basis);
//通过物体的世界坐标对物体局部坐标转换
void Model_To_World_OBJECT4DV1(OBJECT4DV1_PTR obj, int coord_select = TRANSFORM_LOCAL_TO_TRANS);
//创建局部坐标到世界坐标的变换矩阵
void Build_Model_To_World_MATRIX4X4(VECTOR4D_PTR vpos, MATRIX4X4_PTR m);
//变换渲染列表的局部坐标到世界坐标
void Model_To_World_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, POINT4D_PTR world_pos, int coord_select = TRANSFORM_LOCAL_TO_TRANS);
//通过矩阵将物体从世界坐标转换到摄像机坐标
void World_To_Camera_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam);
//通过矩阵将渲染列表从世界坐标转换到摄像机坐标
void World_To_Camera_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam);
//物体剔除
bool Cull_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam, int cull_flags);
//物体背面剔除
void Remove_Backfaces_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam);
//渲染列表背面剔除
void Remove_Backfaces_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam);
//重置物体裁剪
void Reset_OBJECT4DV1(OBJECT4DV1_PTR obj);
//手动方式将物体转换到透视坐标
void Camera_To_Perspective_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam);
//创建透视矩阵
void Build_Camera_To_Perspective_MATRIX4X4(CAM4DV1_PTR cam, MATRIX4X4_PTR m);
//4D齐次坐标到3D坐标
void Convert_From_Homogeneous4D_OBJECT4DV1(OBJECT4DV1_PTR obj);
//手动方式将渲染列表转换到透视坐标
void Camera_To_Perspective_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam);
//4D齐次坐标到3D坐标
void Convert_From_Homogeneous4D_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list);
//手动对物体执行透视坐标到屏幕坐标
void Perspective_To_Screen_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam);
//4D透视坐标到屏幕坐标矩阵
void Build_Perspective_To_Screen_4D_MATRIX4X4(CAM4DV1_PTR cam, MATRIX4X4_PTR m);
//3D透视坐标到屏幕坐标矩阵
void Build_Camera_To_Screen_MATRIX4X4(CAM4DV1_PTR cam, MATRIX4X4_PTR m);
//渲染列表透视坐标到屏幕坐标的变换
void Perspective_To_Screen_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam);
//物体的相机坐标到屏幕坐标的变换
void Camera_To_Perspective_Screen_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam);
//渲染列表的相机坐标到屏幕坐标的变换
void Camera_To_Perspective_Screen_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam);
//绘制线框物体
void Draw_OBJECT4DV1_Wire(OBJECT4DV1_PTR obj, unsigned char *video_buffer, int lpitch);
//绘制线框渲染列表
void Draw_RENDERLIST4DV1_Wire16(RENDERLIST4DV1_PTR rend_list, unsigned char *video_buffer, int lpitch);
//绘制实心物体
void Draw_OBJECT4DV1_Solid(OBJECT4DV1_PTR obj, UCHAR *video_buffer, int lpitch);
//绘制实心渲染列表
void Draw_RENDERLIST4DV1_Solid(RENDERLIST4DV1_PTR rend_list, UCHAR *video_buffer, int lpitch);
//插入多边形到渲染列表
int Insert_POLY4DV1_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, POLY4DV1_PTR poly);
//插入对象到渲染列表
int Insert_OBJECT4DV1_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, OBJECT4DV1_PTR obj, int insert_local = 0);
#endif
