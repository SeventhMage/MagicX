#include "renderer.h"
#include "tool.h"
#include "draw.h"

#include <math.h>
#include <float.h>

void Rotate_XYZ_OBJECT4DV1(OBJECT4DV1_PTR obj, // object to rotate
	float theta_x,      // euler angles
	float theta_y,
	float theta_z)
{
	// this function rotates and object parallel to the
	// XYZ axes in that order or a subset thereof, without
	// matrices (at least externally sent)
	// modifies the object's local vertex list 
	// additionally it rotates the unit directional vectors
	// that track the objects orientation, also note that each
	// time this function is called it calls the rotation generation
	// function, this is wastefull if a number of object are being rotated
	// by the same matrix, therefore, if that's the case, then generate the
	// rotation matrix, store it, and call the general Transform_OBJECT4DV1()
	// with the matrix

	MATRIX4X4 mrot; // used to store generated rotation matrix

	// generate rotation matrix, no way to avoid rotation with a matrix
	// too much math to do manually!
	Build_XYZ_Rotation_MATRIX4X4(theta_x, theta_y, theta_z, &mrot);

	// now simply rotate each point of the mesh in local/model coordinates
	for (int vertex = 0; vertex < obj->num_vertices; vertex++)
	{
		POINT4D presult; // hold result of each transformation

		// transform point
		Mat_Mul_VECTOR4D_4X4(&obj->vlist_local[vertex], &mrot, &presult);

		// store result back
		VECTOR4D_COPY(&obj->vlist_local[vertex], &presult);

	} // end for index

	// now rotate orientation basis for object
	VECTOR4D vresult; // use to rotate each orientation vector axis

	// rotate ux of basis
	Mat_Mul_VECTOR4D_4X4(&obj->ux, &mrot, &vresult);
	VECTOR4D_COPY(&obj->ux, &vresult);

	// rotate uy of basis
	Mat_Mul_VECTOR4D_4X4(&obj->uy, &mrot, &vresult);
	VECTOR4D_COPY(&obj->uy, &vresult);

	// rotate uz of basis
	Mat_Mul_VECTOR4D_4X4(&obj->uz, &mrot, &vresult);
	VECTOR4D_COPY(&obj->uz, &vresult);

} // end Rotate_XYZ_OBJECT4DV1

void Transform_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, MATRIX4X4_PTR mt, int coord_select)
{
	switch(coord_select)
	{
		case TRANSFORM_LOCAL_ONLY:	//对局部顶点列表变幻
			{
				for (int poly = 0; poly < rend_list->num_polys; ++poly)
				{
					POLYF4DV1_PTR curr_poly = rend_list->poly_ptrs[poly];
					if ((curr_poly == NULL) || !(curr_poly->state & POLY4DV1_STATE_ACTIVE)
							|| (curr_poly->state & POLY4DV1_STATE_CLIPPED) || (curr_poly->state & POLY4DV1_STATE_BACKFACE))
						continue;
					for (int vertex = 0; vertex < 3; ++vertex)
					{
						POINT4D presult;
						Mat_Mul_VECTOR4D_4X4(&curr_poly->vlist[vertex], mt, &presult);
						VECTOR4D_COPY(&curr_poly->vlist[vertex], &presult);
					}
				}
			}break;	
		case TRANSFORM_TRANS_ONLY:	//对变幻后的顶点列表变幻	
			{
				for (int poly = 0; poly < rend_list->num_polys; ++poly)
				{
					POLYF4DV1_PTR curr_poly = rend_list->poly_ptrs[poly];
					if ((curr_poly == NULL) || !(curr_poly->state & POLY4DV1_STATE_ACTIVE)
							|| (curr_poly->state & POLY4DV1_STATE_CLIPPED) || (curr_poly->state & POLY4DV1_STATE_BACKFACE))
						continue;
					for (int vertex = 0; vertex < 3; ++vertex)
					{
						POINT4D presult;
						Mat_Mul_VECTOR4D_4X4(&curr_poly->tvlist[vertex], mt, &presult);
						VECTOR4D_COPY(&curr_poly->tvlist[vertex], &presult);
					}
				}
			}break;
		case TRANSFORM_LOCAL_TO_TRANS:		//局部顶点列表变幻，结果存于变幻后的顶点列表
			{
				for (int poly = 0; poly < rend_list->num_polys; ++poly)
				{
					POLYF4DV1_PTR curr_poly = rend_list->poly_ptrs[poly];
					if ((curr_poly == NULL) || !(curr_poly->state & POLY4DV1_STATE_ACTIVE)
							|| (curr_poly->state & POLY4DV1_STATE_CLIPPED) || (curr_poly->state & POLY4DV1_STATE_BACKFACE))
						continue;
					for (int vertex = 0; vertex < 3; ++vertex)
					{
						Mat_Mul_VECTOR4D_4X4(&curr_poly->vlist[vertex], mt, &curr_poly->tvlist[vertex]);
					}
				}
			}break;
		default:
			break;
	}
}

void Transform_OBJECT4DV1(OBJECT4DV1_PTR obj, MATRIX4X4_PTR mt, int coord_select, int transform_basis)
{
	switch(coord_select)
	{
		case TRANSFORM_LOCAL_ONLY:
			for (int vertex = 0; vertex < obj->num_vertices; ++vertex)
			{
				POINT4D presult;
				Mat_Mul_VECTOR4D_4X4(&obj->vlist_local[vertex], mt, &presult);
				VECTOR4D_COPY(&obj->vlist_local[vertex], &presult);
			}
			break;
		case TRANSFORM_TRANS_ONLY:
			for (int vertex = 0; vertex < obj->num_vertices; ++vertex)
			{
				POINT4D presult;
				Mat_Mul_VECTOR4D_4X4(&obj->vlist_trans[vertex], mt, &presult);
				VECTOR4D_COPY(&obj->vlist_trans[vertex], &presult);
			}
			break;
		case TRANSFORM_LOCAL_TO_TRANS:
			for (int vertex = 0; vertex < obj->num_vertices; ++vertex)
			{
				Mat_Mul_VECTOR4D_4X4(&obj->vlist_local[vertex], mt, &obj->vlist_trans[vertex]);
			}
			break;
		default:
			break;
	}
	//对朝向向量变幻，不变幻朝向向量不再有效
	if (transform_basis)
	{
		VECTOR4D vresult;

		Mat_Mul_VECTOR4D_4X4(&obj->ux, mt, &vresult);
		VECTOR4D_COPY(&obj->ux, &vresult);

		Mat_Mul_VECTOR4D_4X4(&obj->uy, mt, &vresult);
		VECTOR4D_COPY(&obj->uy, &vresult);

		Mat_Mul_VECTOR4D_4X4(&obj->uz, mt, &vresult);
		VECTOR4D_COPY(&obj->uz, &vresult);
	}
}

void Model_To_World_OBJECT4DV1(OBJECT4DV1_PTR obj, int coord_select)
{
	if (coord_select == TRANSFORM_LOCAL_TO_TRANS)
	{
		for (int vertex = 0; vertex < obj->num_vertices; ++vertex)
		{
			VECTOR4D_Add(&obj->vlist_local[vertex], &obj->world_pos, &obj->vlist_trans[vertex]);
		}
	}
	else		//TRANSFORM_TRANS_ONLY
	{
		for (int vertex = 0; vertex < obj->num_vertices; ++vertex)
		{
			VECTOR4D_Add(&obj->vlist_trans[vertex], &obj->world_pos, &obj->vlist_trans[vertex]);
		}
	}
}

void Build_Model_To_World_MATRIX4X4(VECTOR4D_PTR vpos, MATRIX4X4_PTR m)
{
	Mat_Init_4X4(m, 1, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 1, 0,
			vpos->x, vpos->y, vpos->z, 1);
}

void Model_To_World_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, POINT4D_PTR world_pos, int coord_select)
{
	if (coord_select == TRANSFORM_LOCAL_TO_TRANS)
	{
		for (int poly=0; poly < rend_list->num_polys; ++poly)
		{
			POLYF4DV1_PTR curr_poly = rend_list->poly_ptrs[poly];
			if ((curr_poly == NULL) || !(curr_poly->state & POLY4DV1_STATE_ACTIVE) || 
					(curr_poly->state & POLY4DV1_STATE_CLIPPED) || (curr_poly->state & POLY4DV1_STATE_BACKFACE))
				continue;
			for (int vertex = 0; vertex < 3; ++vertex)
			{
				VECTOR4D_Add(&curr_poly->vlist[vertex], world_pos, &curr_poly->tvlist[vertex]);
			}
		}
	}
	else
	{
		for (int poly=0; poly < rend_list->num_polys; ++poly)
		{
			POLYF4DV1_PTR curr_poly = rend_list->poly_ptrs[poly];
			if ((curr_poly == NULL) || !(curr_poly->state & POLY4DV1_STATE_ACTIVE) || 
					(curr_poly->state & POLY4DV1_STATE_CLIPPED) || (curr_poly->state & POLY4DV1_STATE_BACKFACE))
				continue;
			for (int vertex = 0; vertex < 3; ++vertex)
			{
				VECTOR4D_Add(&curr_poly->tvlist[vertex], world_pos, &curr_poly->tvlist[vertex]);
			}
		}

	}
}

void World_To_Camera_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam)
{
	for (int vertex = 0; vertex < obj->num_vertices; ++vertex)
	{
		POINT4D presult;
		Mat_Mul_VECTOR4D_4X4(&obj->vlist_trans[vertex], &cam->mcam, &presult);
		VECTOR4D_COPY(&obj->vlist_trans[vertex], &presult);
	}
}

void World_To_Camera_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam)
{
	for (int poly = 0; poly < rend_list->num_polys; ++poly)
	{
		POLYF4DV1_PTR curr_poly = rend_list->poly_ptrs[poly];
		if (curr_poly)
		{
			if (!(curr_poly->state & POLY4DV1_STATE_ACTIVE) || 
				(curr_poly->state & POLY4DV1_STATE_BACKFACE) || curr_poly->state & POLY4DV1_STATE_CLIPPED)
				continue;
			for (int vertex = 0; vertex < 3; ++vertex)
			{
				POINT4D presult;
				Mat_Mul_VECTOR4D_4X4(&curr_poly->tvlist[vertex], &cam->mcam, &presult);
				VECTOR4D_COPY(&curr_poly->tvlist[vertex], &presult);
			}
		}
	}
}

bool Cull_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam, int cull_flags)
{
	POINT4D sphere_pos;
	Mat_Mul_VECTOR4D_4X4(&obj->world_pos, &cam->mcam, &sphere_pos);

	if (cull_flags & CULL_OBJECT_X_PLANE)
	{
		float posz_view_width = fabs(0.5f * cam->viewplane_width * sphere_pos.z / cam->view_dist);
		float clip_width = fabs(obj->max_radius / Fast_Cos(cam->fov * 0.5f));
		if ((sphere_pos.x - clip_width > posz_view_width) || (sphere_pos.x + clip_width < -posz_view_width))
		{
			SET_BIT(obj->state, OBJECT4DV1_STATE_CULLED);
			return true;
		}
	}

	if (cull_flags & CULL_OBJECT_Y_PLANE)
	{
		float posz_view_height = fabs(0.5f * cam->viewplane_height * sphere_pos.z / cam->view_dist);
		float clip_height = fabs(obj->max_radius / Fast_Cos((cam->fov / cam->aspect_ratio) * 0.5f));
		if ((sphere_pos.y - clip_height > posz_view_height) || (sphere_pos.y + clip_height < -posz_view_height))
		{
			SET_BIT(obj->state, OBJECT4DV1_STATE_CULLED);
			return false;
		}
	}

	if (cull_flags & CULL_OBJECT_Z_PLANE)
	{
		if ((sphere_pos.z - obj->max_radius) > -cam->near_clip_z || (sphere_pos.z + obj->max_radius < -cam->far_clip_z))
		{
			SET_BIT(obj->state, OBJECT4DV1_STATE_CULLED);
			return true;
		}
	}

	return false;
}

void Reset_OBJECT4DV1(OBJECT4DV1_PTR obj)
{
	RESET_BIT(obj->state, OBJECT4DV1_STATE_CULLED);
	for (int poly = 0; poly < obj->num_polys; ++poly)
	{
		POLY4DV1 &curr_poly = obj->plist[poly];
		if (!(curr_poly.state & OBJECT4DV1_STATE_ACTIVE))
			continue;
		RESET_BIT(curr_poly.state, POLY4DV1_STATE_CLIPPED);
		RESET_BIT(curr_poly.state, POLY4DV1_STATE_BACKFACE);
	}
}

void Remove_Backfaces_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam)
{
	if (obj->state & OBJECT4DV1_STATE_CULLED)
		return;
	for (int poly = 0; poly < obj->num_polys; ++poly)
	{
		POLY4DV1_PTR curr_poly = &obj->plist[poly];
		if (!(curr_poly->state & POLY4DV1_STATE_ACTIVE) || (curr_poly->state & POLY4DV1_STATE_BACKFACE)
			|| (curr_poly->state & POLY4DV1_STATE_CLIPPED) || (curr_poly->attr & POLY4DV1_ATTR_2SIDED))
			continue;
		int vindex_0 = curr_poly->vert[0];
		int vindex_1 = curr_poly->vert[1];
		int vindex_2 = curr_poly->vert[2];
		VECTOR4D u, v, n;
		
		VECTOR4D_Build(&obj->vlist_trans[vindex_0], &obj->vlist_trans[vindex_1], &u);
		VECTOR4D_Build(&obj->vlist_trans[vindex_0], &obj->vlist_trans[vindex_2], &v);

		VECTOR4D_Cross(&u, &v, &n);

		VECTOR4D view;
		VECTOR4D_Build(&obj->vlist_trans[vindex_0], &cam->pos, &view);

		float dot = VECTOR4D_Dot(&view, &n);
		if (dot <= 0)
			SET_BIT(curr_poly->state, POLY4DV1_STATE_BACKFACE);
	}
}

void Remove_Backfaces_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam)
{
	for (int poly = 0; poly < rend_list->num_polys; ++poly)
	{
		POLYF4DV1_PTR curr_poly = rend_list->poly_ptrs[poly];
		if (curr_poly)
		{
			if (!(curr_poly->state & POLY4DV1_STATE_ACTIVE) || (curr_poly->state & POLY4DV1_STATE_BACKFACE)
				|| (curr_poly->state & POLY4DV1_STATE_CLIPPED) || (curr_poly->attr & POLY4DV1_ATTR_2SIDED))
				continue;

			VECTOR4D u, v, n;

			VECTOR4D_Build(&curr_poly->tvlist[0], &curr_poly->tvlist[1], &u);
			VECTOR4D_Build(&curr_poly->tvlist[0], &curr_poly->tvlist[2], &v);

			VECTOR4D_Cross(&u, &v, &n);

			VECTOR4D view;
			VECTOR4D_Build(&curr_poly->tvlist[0], &cam->pos, &view);
			VECTOR4D_Normalize(&view);
			VECTOR4D_Normalize(&n);
			float dot = VECTOR4D_Dot(&view, &n);
			if (dot <= 0)
				SET_BIT(curr_poly->state, POLY4DV1_STATE_BACKFACE);
		}
	}
}

void Camera_To_Perspective_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam)
{
	for (int vertex = 0; vertex < obj->num_polys; ++vertex)
	{
		float z = obj->vlist_trans[vertex].z;
		obj->vlist_trans[vertex].x = cam->view_dist * obj->vlist_trans[vertex].x / z;
		obj->vlist_trans[vertex].y = cam->view_dist * obj->vlist_trans[vertex].y * cam->aspect_ratio / z;
	}
}

void Build_Camera_To_Perspective_MATRIX4X4(CAM4DV1_PTR cam, MATRIX4X4_PTR m)
{
	Mat_Init_4X4(m, cam->view_dist, 0, 0, 0,
		0, cam->view_dist * cam->aspect_ratio, 0, 0,
		0, 0, 1, 1,
		0, 0, 0, 0);
}

void Convert_From_Homogeneous4D_OBJECT4DV1(OBJECT4DV1_PTR obj)
{
	for (int vertex = 0; vertex < obj->num_polys; ++vertex)
	{
		VECTOR4D_DIV_BY_W(&obj->vlist_trans[vertex]);
	}
}

void Camera_To_Perspective_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam)
{
	for (int poly = 0; poly < rend_list->num_polys; ++poly)
	{
		POLYF4DV1_PTR curr_poly = rend_list->poly_ptrs[poly];
		if (curr_poly)
		{
			if (!(curr_poly->state & POLY4DV1_STATE_ACTIVE) || (curr_poly->state & POLY4DV1_STATE_CLIPPED)
				||(curr_poly->state & POLY4DV1_STATE_BACKFACE))
				continue;
			for (int vertex = 0; vertex < 3; ++vertex)
			{
				float z = curr_poly->tvlist[vertex].z;
				curr_poly->tvlist[vertex].x = cam->view_dist * curr_poly->tvlist[vertex].x / z;
				curr_poly->tvlist[vertex].y = cam->view_dist * cam->aspect_ratio * curr_poly->tvlist[vertex].y / z;
			}
		}
	}
}

void Convert_From_Homogeneous4D_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list)
{
	for (int poly = 0; poly < rend_list->num_polys; ++poly)
	{
		POLYF4DV1_PTR curr_poly = rend_list->poly_ptrs[poly];
		if (curr_poly)
		{
			if (!(curr_poly->state & POLY4DV1_STATE_ACTIVE) || (curr_poly->state & POLY4DV1_STATE_CLIPPED)
				|| (curr_poly->state & POLY4DV1_STATE_BACKFACE))
				continue;
			for (int vertex = 0; vertex < 3; ++vertex)
			{
				VECTOR4D_DIV_BY_W(&curr_poly->tvlist[vertex]);
			}
		}
	}
}

void Perspective_To_Screen_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam)
{
	float alpha = 0.5f * (cam->viewport_width - 0.5f);
	float beta = 0.5f * (cam->viewport_height - 0.5f);

	for (int vertex = 0; vertex < obj->num_vertices; ++vertex)
	{
		obj->vlist_trans[vertex].x = alpha + alpha * obj->vlist_trans[vertex].x;
		obj->vlist_trans[vertex].y = beta - beta * obj->vlist_trans[vertex].y;
	}
}

void Build_Perspective_To_Screen_4D_MATRIX4X4(CAM4DV1_PTR cam, MATRIX4X4_PTR m)
{
	float alpha = 0.5f * cam->viewport_width - 0.5f;
	float beta = 0.5f * cam->viewport_height - 0.5f;

	Mat_Init_4X4(m, alpha, 0, 0, 0,
		0, -beta, 0, 0,
		alpha, beta, 1, 0,
		0, 0, 0, 1
		);
}

void Build_Camera_To_Screen_MATRIX4X4(CAM4DV1_PTR cam, MATRIX4X4_PTR m)
{
	float alpha = 0.5f * cam->viewport_width - 0.5f;
	float beta = 0.5f * cam->viewport_height - 0.5f;

	Mat_Init_4X4(m, alpha, 0, 0, 0,
					0, -beta, 0, 0,
					alpha, beta, 1, 1,
					0, 0, 0, 0);
}

void Perspective_To_Screen_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam)
{
	for (int poly = 0; poly < rend_list->num_polys; ++poly)
	{
		POLYF4DV1_PTR curr_poly = rend_list->poly_ptrs[poly];
		if (curr_poly)
		{
			if (!(curr_poly->state & POLY4DV1_STATE_ACTIVE) || (curr_poly->state & POLY4DV1_STATE_CLIPPED) 
				|| (curr_poly->state & POLY4DV1_STATE_BACKFACE))
				continue;
			float alpha = (0.5 * cam->viewport_width - 0.5f);
			float beta = (0.5 * cam->viewport_height - 0.5f);

			for (int vertex = 0; vertex < 3; ++vertex)
			{
				curr_poly->tvlist[vertex].x = alpha + alpha * curr_poly->tvlist[vertex].x;
				curr_poly->tvlist[vertex].y = beta - beta * curr_poly->tvlist[vertex].y;
			}
		}
	}
}

void Camera_To_Perspective_Screen_OBJECT4DV1(OBJECT4DV1_PTR obj, CAM4DV1_PTR cam)
{
	float alpha = 0.5f * cam->viewport_width - 0.5f;
	float beta = 0.5f* cam->viewport_height - 0.5f;

	for (int vertex = 0; vertex < obj->num_vertices; ++vertex)
	{
		float z = fabs(obj->vlist_trans[vertex].z);
		obj->vlist_trans[vertex].x = cam->viewport_dist * obj->vlist_trans[vertex].x / z;
		obj->vlist_trans[vertex].y = cam->viewport_dist * cam->aspect_ratio * obj->vlist_trans[vertex].y / z;
		obj->vlist_trans[vertex].z = .0f;

		obj->vlist_trans[vertex].x = obj->vlist_trans[vertex].x + alpha;
		obj->vlist_trans[vertex].y = obj->vlist_trans[vertex].y + beta; //glDrawPixels()屏幕左下角为0， 0
		//obj->vlist_trans[vertex].y = -obj->vlist_trans[vertex].y + beta;
	}
}

void Camera_To_Perspective_Screen_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam)
{
	float alpha = 0.5f * cam->viewport_width - 0.5f;
	float beta = 0.5f * cam->viewport_height - 0.5f;

	for (int poly = 0; poly < rend_list->num_polys; ++poly)
	{
		POLYF4DV1_PTR curr_poly = rend_list->poly_ptrs[poly];
		if (curr_poly)
		{
			if (!(curr_poly->state & POLY4DV1_STATE_ACTIVE) || (curr_poly->state & POLY4DV1_STATE_CLIPPED)
				|| (curr_poly->state & POLY4DV1_STATE_BACKFACE))
				continue;
			for (int vertex = 0; vertex < 3; ++vertex)
			{
				float z = fabs(curr_poly->tvlist[vertex].z);
				curr_poly->tvlist[vertex].x = cam->viewport_dist * curr_poly->tvlist[vertex].x / z;
				curr_poly->tvlist[vertex].y = cam->viewport_dist * cam->aspect_ratio * curr_poly->tvlist[vertex].y / z;

				curr_poly->tvlist[vertex].x = curr_poly->tvlist[vertex].x + alpha;
				//curr_poly->tvlist[vertex].y = curr_poly->tvlist[vertex].y + beta;//glDrawPixels()屏幕左下角为0， 0
				curr_poly->tvlist[vertex].y = -curr_poly->tvlist[vertex].y + beta;
			}
		}
	}
}

void Draw_OBJECT4DV1_Wire(OBJECT4DV1_PTR obj, unsigned char *video_buffer, int lpitch)
{
	for (int poly = 0; poly < obj->num_polys; ++poly)
	{
		if (!(obj->plist[poly].state & POLY4DV1_STATE_ACTIVE) || (obj->plist[poly].state & POLY4DV1_STATE_BACKFACE)
			|| (obj->plist[poly].state & POLY4DV1_STATE_CLIPPED))
			continue;
		int vindex_0 = obj->plist[poly].vert[0];
		int vindex_1 = obj->plist[poly].vert[1];
		int vindex_2 = obj->plist[poly].vert[2];

		Draw_Clip_Line(obj->vlist_trans[vindex_0].x, obj->vlist_trans[vindex_0].y, obj->vlist_trans[vindex_1].x,
			obj->vlist_trans[vindex_1].y, obj->plist[poly].color, video_buffer, lpitch);
		Draw_Clip_Line(obj->vlist_trans[vindex_1].x, obj->vlist_trans[vindex_1].y, obj->vlist_trans[vindex_2].x,
			obj->vlist_trans[vindex_2].y, obj->plist[poly].color, video_buffer, lpitch);
		Draw_Clip_Line(obj->vlist_trans[vindex_2].x, obj->vlist_trans[vindex_2].y, obj->vlist_trans[vindex_0].x,
			obj->vlist_trans[vindex_0].y, obj->plist[poly].color, video_buffer, lpitch);
	}
}

void Draw_RENDERLIST4DV1_Wire(RENDERLIST4DV1_PTR rend_list, unsigned char *video_buffer, int lpitch)
{
	for (int poly = 0; poly < rend_list->num_polys; ++poly)
	{
		if (!(rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_ACTIVE) || (rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_BACKFACE)
			|| (rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_CLIPPED))
			continue;
		Draw_Clip_Line(rend_list->poly_ptrs[poly]->tvlist[0].x, rend_list->poly_ptrs[poly]->tvlist[0].y, rend_list->poly_ptrs[poly]->tvlist[1].x,
			rend_list->poly_ptrs[poly]->tvlist[1].y, rend_list->poly_ptrs[poly]->color, video_buffer, lpitch);
		Draw_Clip_Line(rend_list->poly_ptrs[poly]->tvlist[1].x, rend_list->poly_ptrs[poly]->tvlist[1].y, rend_list->poly_ptrs[poly]->tvlist[2].x,
			rend_list->poly_ptrs[poly]->tvlist[2].y, rend_list->poly_ptrs[poly]->color, video_buffer, lpitch);
		Draw_Clip_Line(rend_list->poly_ptrs[poly]->tvlist[2].x, rend_list->poly_ptrs[poly]->tvlist[2].y, rend_list->poly_ptrs[poly]->tvlist[0].x,
			rend_list->poly_ptrs[poly]->tvlist[0].y, rend_list->poly_ptrs[poly]->color, video_buffer, lpitch);
	}
}

void Draw_OBJECT4DV1_Solid(OBJECT4DV1_PTR obj, UCHAR *video_buffer, int lpitch)
{	
	for (int poly = 0; poly < obj->num_polys; poly++)
	{
		if (!(obj->plist[poly].state & POLY4DV1_STATE_ACTIVE) ||
			(obj->plist[poly].state & POLY4DV1_STATE_CLIPPED) ||
			(obj->plist[poly].state & POLY4DV1_STATE_BACKFACE))
			continue; 

		int vindex_0 = obj->plist[poly].vert[0];
		int vindex_1 = obj->plist[poly].vert[1];
		int vindex_2 = obj->plist[poly].vert[2];
		
		Draw_Triangle_2D(obj->vlist_trans[vindex_0].x, obj->vlist_trans[vindex_0].y,
			obj->vlist_trans[vindex_1].x, obj->vlist_trans[vindex_1].y,
			obj->vlist_trans[vindex_2].x, obj->vlist_trans[vindex_2].y,
			obj->plist[poly].color, video_buffer, lpitch);

	}
}

void Draw_RENDERLIST4DV1_Solid(RENDERLIST4DV1_PTR rend_list, UCHAR *video_buffer, int lpitch)
{	
	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		if (!(rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_ACTIVE) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_CLIPPED) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_BACKFACE))
			continue;
		
		Draw_Triangle_2D(rend_list->poly_ptrs[poly]->tvlist[0].x, rend_list->poly_ptrs[poly]->tvlist[0].y,
			rend_list->poly_ptrs[poly]->tvlist[1].x, rend_list->poly_ptrs[poly]->tvlist[1].y,
			rend_list->poly_ptrs[poly]->tvlist[2].x, rend_list->poly_ptrs[poly]->tvlist[2].y,
			rend_list->poly_ptrs[poly]->color, video_buffer, lpitch);

	}
}

int Insert_POLY4DV1_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, POLY4DV1_PTR poly)
{
	if (rend_list->num_polys >= RENDERLIST4DV1_MAX_POLYS)
		return(0);

	rend_list->poly_ptrs[rend_list->num_polys] = &rend_list->poly_data[rend_list->num_polys];
	
	rend_list->poly_data[rend_list->num_polys].state = poly->state;
	rend_list->poly_data[rend_list->num_polys].attr = poly->attr;
	rend_list->poly_data[rend_list->num_polys].color = poly->color;

	VECTOR4D_COPY(&rend_list->poly_data[rend_list->num_polys].tvlist[0],
		&poly->vlist[poly->vert[0]]);

	VECTOR4D_COPY(&rend_list->poly_data[rend_list->num_polys].tvlist[1],
		&poly->vlist[poly->vert[1]]);

	VECTOR4D_COPY(&rend_list->poly_data[rend_list->num_polys].tvlist[2],
		&poly->vlist[poly->vert[2]]);
	
	VECTOR4D_COPY(&rend_list->poly_data[rend_list->num_polys].vlist[0],
		&poly->vlist[poly->vert[0]]);

	VECTOR4D_COPY(&rend_list->poly_data[rend_list->num_polys].vlist[1],
		&poly->vlist[poly->vert[1]]);

	VECTOR4D_COPY(&rend_list->poly_data[rend_list->num_polys].vlist[2],
		&poly->vlist[poly->vert[2]]);

	if (rend_list->num_polys == 0)
	{		
		rend_list->poly_data[0].next = NULL;
		rend_list->poly_data[0].prev = NULL;
	}
	else
	{		
		rend_list->poly_data[rend_list->num_polys].next = NULL;
		rend_list->poly_data[rend_list->num_polys].prev =
			&rend_list->poly_data[rend_list->num_polys - 1];
		
		rend_list->poly_data[rend_list->num_polys - 1].next =
			&rend_list->poly_data[rend_list->num_polys];
	}
	
	rend_list->num_polys++;

	return(1);

}

int Insert_OBJECT4DV1_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, OBJECT4DV1_PTR obj, int insert_local)
{
	if (!(obj->state & OBJECT4DV1_STATE_ACTIVE) ||
		(obj->state & OBJECT4DV1_STATE_CULLED) ||
		!(obj->state & OBJECT4DV1_STATE_VISIBLE))
		return(0);
	
	for (int poly = 0; poly < obj->num_polys; poly++)
	{		
		POLY4DV1_PTR curr_poly = &obj->plist[poly];
		
		if (!(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV1_STATE_CLIPPED) ||
			(curr_poly->state & POLY4DV1_STATE_BACKFACE))
			continue; 

		POINT4D_PTR vlist_old = curr_poly->vlist;

		if (insert_local)
			curr_poly->vlist = obj->vlist_local;
		else
			curr_poly->vlist = obj->vlist_trans;
		
		if (!Insert_POLY4DV1_RENDERLIST4DV1(rend_list, curr_poly))
		{			
			curr_poly->vlist = vlist_old;
			
			return(0);
		}
		
		curr_poly->vlist = vlist_old;

	}	
	return(1);

}

static int Compare_AvgZ_POLY4DV1(const void *arg1, const void *arg2)
{	
	POLYF4DV1_PTR poly_1 = *((POLYF4DV1_PTR *)(arg1));
	POLYF4DV1_PTR poly_2 = *((POLYF4DV1_PTR *)(arg2));

	float z1 = 0.3333f * (poly_1->tvlist[0].z + poly_1->tvlist[1].z + poly_1->tvlist[2].z);
	float z2 = 0.3333f * (poly_2->tvlist[0].z + poly_2->tvlist[1].z + poly_2->tvlist[2].z);
	if (z1 > z2)
		return 1;
	else if (z1 < z2)
		return -1;
	else
		return 0;
}

static int Compare_FarZ_POLY4DV1(const void *arg1, const void *arg2)
{
	POLYF4DV1_PTR poly_1 = *((POLYF4DV1_PTR *)(arg1));
	POLYF4DV1_PTR poly_2 = *((POLYF4DV1_PTR *)(arg2));

	float z1 =  MIN(MIN(poly_1->tvlist[0].z, poly_1->tvlist[1].z), poly_1->tvlist[2].z);
	float z2 = MIN(MIN(poly_2->tvlist[0].z, poly_2->tvlist[1].z), poly_2->tvlist[2].z);
	if (z1 > z2)
		return 1;
	else if (z1 < z2)
		return -1;
	else
		return 0;
}

static int Compare_NearZ_POLY4DV1(const void *arg1, const void *arg2)
{
	POLYF4DV1_PTR poly_1 = *((POLYF4DV1_PTR *)(arg1));
	POLYF4DV1_PTR poly_2 = *((POLYF4DV1_PTR *)(arg2));

	float z1 = MAX(MAX(poly_1->tvlist[0].z, poly_1->tvlist[1].z), poly_1->tvlist[2].z);
	float z2 = MAX(MAX(poly_2->tvlist[0].z, poly_2->tvlist[1].z), poly_2->tvlist[2].z);
	if (z1 > z2)
		return 1;
	else if (z1 < z2)
		return -1;
	else
		return 0;
}

void Sort_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list, int sort_method)
{
	switch (sort_method)
	{
	case SORT_POLYLIST_AVGZ:
		qsort(rend_list->poly_ptrs, rend_list->num_polys, sizeof(POLY4DV1_PTR), Compare_AvgZ_POLY4DV1);
		break;
	case SORT_POLYLIST_NEARZ:
		qsort(rend_list->poly_ptrs, rend_list->num_polys, sizeof(POLY4DV1_PTR), Compare_NearZ_POLY4DV1);
		break;
	case SORT_POLYLIST_FARZ:
		qsort(rend_list->poly_ptrs, rend_list->num_polys, sizeof(POLY4DV1_PTR), Compare_FarZ_POLY4DV1);
		break;
	default:
		break;
	}
}

void Light_RENDERLIST4DV1_World(RENDERLIST4DV1_PTR rend_list, CAM4DV1_PTR cam, LIGHTV1_PTR lights, int max_lights)
{
	unsigned int r_base, g_base, b_base,  // base color being lit
		r_sum, g_sum, b_sum,   // sum of lighting process over all lights
		shaded_color;            // final color

	float dp,     // dot product 
		dist,   // distance from light to surface
		i,      // general intensities
		nl,     // length of normal
		atten;  // attenuation computations


	// for each valid poly, light it...
	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		// acquire polygon
		POLYF4DV1_PTR curr_poly = rend_list->poly_ptrs[poly];

		// light this polygon if and only if it's not clipped, not culled,
		// active, and visible
		if (!(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV1_STATE_CLIPPED) ||
			(curr_poly->state & POLY4DV1_STATE_BACKFACE))
			continue; // move onto next poly


		// we will use the transformed polygon vertex list since the backface removal
		// only makes sense at the world coord stage further of the pipeline 

		// test the lighting mode of the polygon (use flat for flat, gouraud))
		if (curr_poly->attr & POLY4DV1_ATTR_SHADE_MODE_FLAT || curr_poly->attr & POLY4DV1_ATTR_SHADE_MODE_GOURAUD)
		{
			// step 1: extract the base color out in RGB mode
			ARGBV1 rgba;
			rgba.argb = curr_poly->color;
			r_base = rgba.r;
			g_base = rgba.g;
			b_base = rgba.b;

			// initialize color sum
			r_sum = 0;
			g_sum = 0;
			b_sum = 0;

			// loop thru lights
			for (int curr_light = 0; curr_light < max_lights; curr_light++)
			{
				// is this light active
				if (lights[curr_light].state == LIGHTV1_STATE_OFF)
					continue;

				// what kind of light are we dealing with
				if (lights[curr_light].attr & LIGHTV1_ATTR_AMBIENT)
				{
					// simply multiply each channel against the color of the 
					// polygon then divide by 256 to scale back to 0..255
					// use a shift in real life!!! >> 8
					r_sum += ((lights[curr_light].c_ambient.r * r_base) / 256);
					g_sum += ((lights[curr_light].c_ambient.g * g_base) / 256);
					b_sum += ((lights[curr_light].c_ambient.b * b_base) / 256);

					// there better only be one ambient light!

				} // end if
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_INFINITE)
				{
					// infinite lighting, we need the surface normal, and the direction
					// of the light source

					// we need to compute the normal of this polygon face, and recall
					// that the vertices are in cw order, u=p0->p1, v=p0->p2, n=uxv
					VECTOR4D u, v, n;

					// build u, v
					VECTOR4D_Build(&curr_poly->tvlist[0], &curr_poly->tvlist[1], &u);
					VECTOR4D_Build(&curr_poly->tvlist[0], &curr_poly->tvlist[2], &v);

					// compute cross product
					VECTOR4D_Cross(&u, &v, &n);

					// at this point, we are almost ready, but we have to normalize the normal vector!
					// this is a key optimization we can make later, we can pre-compute the length of all polygon
					// normals, so this step can be optimized
					// compute length of normal
					nl = VECTOR4D_Length_Fast(&n);

					// ok, recalling the lighting model for infinite lights
					// I(d)dir = I0dir * Cldir
					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles

					dp = VECTOR4D_Dot(&n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						i = 256 * dp / nl;
						r_sum += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 256);
						g_sum += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 256);
						b_sum += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 256);
					} // end if

				} // end if infinite light
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_POINT)
				{
					// perform point light computations
					// light model for point light is once again:
					//              I0point * Clpoint
					//  I(d)point = ___________________
					//              kc +  kl*d + kq*d2              
					//
					//  Where d = |p - s|
					// thus it's almost identical to the infinite light, but attenuates as a function
					// of distance from the point source to the surface point being lit

					// we need to compute the normal of this polygon face, and recall
					// that the vertices are in cw order, u=p0->p1, v=p0->p2, n=uxv
					VECTOR4D u, v, n, l;

					// build u, v
					VECTOR4D_Build(&curr_poly->tvlist[0], &curr_poly->tvlist[1], &u);
					VECTOR4D_Build(&curr_poly->tvlist[0], &curr_poly->tvlist[2], &v);

					// compute cross product
					VECTOR4D_Cross(&u, &v, &n);

					// at this point, we are almost ready, but we have to normalize the normal vector!
					// this is a key optimization we can make later, we can pre-compute the length of all polygon
					// normals, so this step can be optimized
					// compute length of normal
					nl = VECTOR4D_Length_Fast(&n);

					// compute vector from surface to light
					VECTOR4D_Build(&curr_poly->tvlist[0], &lights[curr_light].pos, &l);

					// compute distance and attenuation
					dist = VECTOR4D_Length_Fast(&l);

					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles
					dp = VECTOR4D_Dot(&n, &l);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 256 * dp / (nl * dist * atten);
						//i = 256 * dp / (nl * atten);

						r_sum += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 256);
						g_sum += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 256);
						b_sum += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 256);
					} // end if

				} // end if point
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_SPOTLIGHT1)
				{
					// perform spotlight/point computations simplified model that uses
					// point light WITH a direction to simulate a spotlight
					// light model for point light is once again:
					//              I0point * Clpoint
					//  I(d)point = ___________________
					//              kc +  kl*d + kq*d2              
					//
					//  Where d = |p - s|
					// thus it's almost identical to the infinite light, but attenuates as a function
					// of distance from the point source to the surface point being lit

					// we need to compute the normal of this polygon face, and recall
					// that the vertices are in cw order, u=p0->p1, v=p0->p2, n=uxv
					VECTOR4D u, v, n, l;

					// build u, v
					VECTOR4D_Build(&curr_poly->tvlist[0], &curr_poly->tvlist[1], &u);
					VECTOR4D_Build(&curr_poly->tvlist[0], &curr_poly->tvlist[2], &v);

					// compute cross product (we need -n, so do vxu)
					VECTOR4D_Cross(&u, &v, &n);

					// at this point, we are almost ready, but we have to normalize the normal vector!
					// this is a key optimization we can make later, we can pre-compute the length of all polygon
					// normals, so this step can be optimized
					// compute length of normal
					nl = VECTOR4D_Length_Fast(&n);

					// compute vector from surface to light
					VECTOR4D_Build(&curr_poly->tvlist[0], &lights[curr_light].pos, &l);

					// compute distance and attenuation
					dist = VECTOR4D_Length_Fast(&l);

					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles

					// note that I use the direction of the light here rather than a the vector to the light
					// thus we are taking orientation into account which is similar to the spotlight model
					dp = VECTOR4D_Dot(&n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 256 * dp / (nl * atten);

						r_sum += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 256);
						g_sum += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 256);
						b_sum += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 256);
					} // end if

				} // end if spotlight1
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_SPOTLIGHT2) // simple version
				{
					// perform spot light computations
					// light model for spot light simple version is once again:
					//         	     I0spotlight * Clspotlight * MAX( (l . s), 0)^pf                     
					// I(d)spotlight = __________________________________________      
					//               		 kc + kl*d + kq*d2        
					// Where d = |p - s|, and pf = power factor

					// thus it's almost identical to the point, but has the extra term in the numerator
					// relating the angle between the light source and the point on the surface

					// we need to compute the normal of this polygon face, and recall
					// that the vertices are in cw order, u=p0->p1, v=p0->p2, n=uxv
					VECTOR4D u, v, n, d, s;

					// build u, v
					VECTOR4D_Build(&curr_poly->tvlist[0], &curr_poly->tvlist[1], &u);
					VECTOR4D_Build(&curr_poly->tvlist[0], &curr_poly->tvlist[2], &v);

					// compute cross product (v x u, to invert n)
					VECTOR4D_Cross(&u, &v, &n);

					// at this point, we are almost ready, but we have to normalize the normal vector!
					// this is a key optimization we can make later, we can pre-compute the length of all polygon
					// normals, so this step can be optimized
					// compute length of normal
					nl = VECTOR4D_Length_Fast(&n);

					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles
					dp = VECTOR4D_Dot(&n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						// compute vector from light to surface (different from l which IS the light dir)
						VECTOR4D_Build(&curr_poly->tvlist[0], &lights[curr_light].pos, &s);

						// compute length of s (distance to light source) to normalize s for lighting calc
						dist = VECTOR4D_Length_Fast(&s);

						// compute spot light term (s . l)
						float dpsl = VECTOR4D_Dot(&s, &lights[curr_light].dir) / dist;

						// proceed only if term is positive
						if (dpsl > 0)
						{
							// compute attenuation
							atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

							// for speed reasons, pf exponents that are less that 1.0 are out of the question, and exponents
							// must be integral
							float dpsl_exp = dpsl;

							// exponentiate for positive integral powers
							for (int e_index = 1; e_index < (int)lights[curr_light].pf; e_index++)
								dpsl_exp *= dpsl;

							// now dpsl_exp holds (dpsl)^pf power which is of course (s . l)^pf 

							i = 256 * dp * dpsl_exp / (nl * atten);

							r_sum += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 256);
							g_sum += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 256);
							b_sum += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 256);

						} // end if

					} // end if

				} // end if spot light

			} // end for light

			// make sure colors aren't out of range
			if (r_sum > 255) r_sum = 255;
			if (g_sum > 255) g_sum = 255;
			if (b_sum > 255) b_sum = 255;

			// write the color over current color
			curr_poly->color = _ARGB32BIT(255, r_sum, g_sum, b_sum);

		} // end if
		else // assume POLY4DV1_ATTR_SHADE_MODE_CONSTANT
		{
			// emmisive shading only, do nothing
			// ...
		} // end if

	} // end for poly
}


//////////////////////////////////////////////////////////////////////////
//V2																	//
//////////////////////////////////////////////////////////////////////////
int Set_OBJECT4DV2_Frame(OBJECT4DV2_PTR obj, int frame)
{
	if (!obj)
		return(0);

	if (!(obj->attr & OBJECT4DV2_ATTR_MULTI_FRAME))
		return(0);	
	
	if (frame < 0)
		frame = 0;
	else
	if (frame >= obj->num_frames)
		frame = obj->num_frames - 1;

	obj->curr_frame = frame;

	obj->vlist_local = &(obj->head_vlist_local[frame*obj->num_vertices]);
	obj->vlist_trans = &(obj->head_vlist_trans[frame*obj->num_vertices]);
	
	return(1);
}

void Translate_OBJECT4DV2(OBJECT4DV2_PTR obj, VECTOR4D_PTR vt)
{
	VECTOR4D_Add(&obj->world_pos, vt, &obj->world_pos);
}

void Scale_OBJECT4DV2(OBJECT4DV2_PTR obj, VECTOR4D_PTR vs, int all_frames /*= 0*/)
{
	if (!all_frames)
	{		
		for (int vertex = 0; vertex < obj->num_vertices; vertex++)
		{
			obj->vlist_local[vertex].x *= vs->x;
			obj->vlist_local[vertex].y *= vs->y;
			obj->vlist_local[vertex].z *= vs->z;	
		}


		float scale = MAX(vs->x, vs->y);
		scale = MAX(scale, vs->z);
		
		obj->max_radius[obj->curr_frame] *= scale;
		obj->avg_radius[obj->curr_frame] *= scale;

	}
	else
	{		
		for (int vertex = 0; vertex < obj->total_vertices; vertex++)
		{
			obj->head_vlist_local[vertex].x *= vs->x;
			obj->head_vlist_local[vertex].y *= vs->y;
			obj->head_vlist_local[vertex].z *= vs->z;
		}

		for (int curr_frame = 0; curr_frame < obj->num_frames; curr_frame++)
		{
			float scale = MAX(vs->x, vs->y);
			scale = MAX(scale, vs->z);
		
			obj->max_radius[curr_frame] *= scale;
			obj->avg_radius[curr_frame] *= scale;
		}
	}

	for (int poly = 0; poly < obj->num_polys; poly++)
	{
		obj->plist[poly].nlength *= (vs->x * vs->y * vs->z);
	}
}

void Transform_OBJECT4DV2(OBJECT4DV2_PTR obj, MATRIX4X4_PTR mt, int coord_select, int transform_basis, int all_frames /*= 0*/)
{
	if (!all_frames)
	{		
		switch (coord_select)
		{
		case TRANSFORM_LOCAL_ONLY:
		{									
									 for (int vertex = 0; vertex < obj->num_vertices; vertex++)
									 {
										 POINT4D presult;

										 // transform point
										 Mat_Mul_VECTOR4D_4X4(&obj->vlist_local[vertex].v, mt, &presult);

										 // store result back
										 VECTOR4D_COPY(&obj->vlist_local[vertex].v, &presult);

										 // transform vertex normal if needed
										 if (obj->vlist_local[vertex].attr & VERTEX4DTV1_ATTR_NORMAL)
										 {
											 // transform normal
											 Mat_Mul_VECTOR4D_4X4(&obj->vlist_local[vertex].n, mt, &presult);

											 // store result back
											 VECTOR4D_COPY(&obj->vlist_local[vertex].n, &presult);
										 } // end if

									 } // end for index
		} break;

		case TRANSFORM_TRANS_ONLY:
		{
									 // transform each "transformed" vertex of the object mesh in place
									 // remember, the idea of the vlist_trans[] array is to accumulate
									 // transformations
									 for (int vertex = 0; vertex < obj->num_vertices; vertex++)
									 {
										 POINT4D presult; // hold result of each transformation

										 // transform point
										 Mat_Mul_VECTOR4D_4X4(&obj->vlist_trans[vertex].v, mt, &presult);

										 // store result back
										 VECTOR4D_COPY(&obj->vlist_trans[vertex].v, &presult);

										 // transform vertex normal if needed
										 if (obj->vlist_trans[vertex].attr & VERTEX4DTV1_ATTR_NORMAL)
										 {
											 // transform normal
											 Mat_Mul_VECTOR4D_4X4(&obj->vlist_trans[vertex].n, mt, &presult);

											 // store result back
											 VECTOR4D_COPY(&obj->vlist_trans[vertex].n, &presult);
										 } // end if

									 } // end for index

		} break;

		case TRANSFORM_LOCAL_TO_TRANS:
		{
										 // transform each local/model vertex of the object mesh and store result
										 // in "transformed" vertex list
										 for (int vertex = 0; vertex < obj->num_vertices; vertex++)
										 {
											 POINT4D presult; // hold result of each transformation

											 // transform point
											 Mat_Mul_VECTOR4D_4X4(&obj->vlist_local[vertex].v, mt, &obj->vlist_trans[vertex].v);

											 // transform vertex normal if needed
											 if (obj->vlist_local[vertex].attr & VERTEX4DTV1_ATTR_NORMAL)
											 {
												 // transform point
												 Mat_Mul_VECTOR4D_4X4(&obj->vlist_local[vertex].n, mt, &obj->vlist_trans[vertex].n);
											 } // end if

										 } // end for index
		} break;

		default: break;

		} // end switch

	} // end if single frame
	else // transform all frames
	{
		// what coordinates should be transformed?
		switch (coord_select)
		{
		case TRANSFORM_LOCAL_ONLY:
		{
									 // transform each local/model vertex of the object mesh in place
									 for (int vertex = 0; vertex < obj->total_vertices; vertex++)
									 {
										 POINT4D presult; // hold result of each transformation

										 // transform point
										 Mat_Mul_VECTOR4D_4X4(&obj->head_vlist_local[vertex].v, mt, &presult);

										 // store result back
										 VECTOR4D_COPY(&obj->head_vlist_local[vertex].v, &presult);

										 // transform vertex normal if needed
										 if (obj->head_vlist_local[vertex].attr & VERTEX4DTV1_ATTR_NORMAL)
										 {
											 // transform normal
											 Mat_Mul_VECTOR4D_4X4(&obj->head_vlist_local[vertex].n, mt, &presult);

											 // store result back
											 VECTOR4D_COPY(&obj->head_vlist_local[vertex].n, &presult);
										 } // end if


									 } // end for index
		} break;

		case TRANSFORM_TRANS_ONLY:
		{
									 // transform each "transformed" vertex of the object mesh in place
									 // remember, the idea of the vlist_trans[] array is to accumulate
									 // transformations
									 for (int vertex = 0; vertex < obj->total_vertices; vertex++)
									 {
										 POINT4D presult; // hold result of each transformation

										 // transform point
										 Mat_Mul_VECTOR4D_4X4(&obj->head_vlist_trans[vertex].v, mt, &presult);

										 // store result back
										 VECTOR4D_COPY(&obj->head_vlist_trans[vertex].v, &presult);

										 // transform vertex normal if needed
										 if (obj->head_vlist_trans[vertex].attr & VERTEX4DTV1_ATTR_NORMAL)
										 {
											 // transform normal
											 Mat_Mul_VECTOR4D_4X4(&obj->head_vlist_trans[vertex].n, mt, &presult);

											 // store result back
											 VECTOR4D_COPY(&obj->head_vlist_trans[vertex].n, &presult);
										 } // end if

									 } // end for index

		} break;

		case TRANSFORM_LOCAL_TO_TRANS:
		{
										 // transform each local/model vertex of the object mesh and store result
										 // in "transformed" vertex list
										 for (int vertex = 0; vertex < obj->total_vertices; vertex++)
										 {
											 POINT4D presult; // hold result of each transformation

											 // transform point
											 Mat_Mul_VECTOR4D_4X4(&obj->head_vlist_local[vertex].v, mt, &obj->head_vlist_trans[vertex].v);

											 // transform vertex normal if needed
											 if (obj->head_vlist_local[vertex].attr & VERTEX4DTV1_ATTR_NORMAL)
											 {
												 // transform point
												 Mat_Mul_VECTOR4D_4X4(&obj->head_vlist_local[vertex].n, mt, &obj->head_vlist_trans[vertex].n);
											 } // end if

										 } // end for index
		} break;

		default: break;

		} // end switch

	} // end else multiple frames

	// finally, test if transform should be applied to orientation basis
	// hopefully this is a rotation, otherwise the basis will get corrupted
	if (transform_basis)
	{
		// now rotate orientation basis for object
		VECTOR4D vresult; // use to rotate each orientation vector axis

		// rotate ux of basis
		Mat_Mul_VECTOR4D_4X4(&obj->ux, mt, &vresult);
		VECTOR4D_COPY(&obj->ux, &vresult);

		// rotate uy of basis
		Mat_Mul_VECTOR4D_4X4(&obj->uy, mt, &vresult);
		VECTOR4D_COPY(&obj->uy, &vresult);

		// rotate uz of basis
		Mat_Mul_VECTOR4D_4X4(&obj->uz, mt, &vresult);
		VECTOR4D_COPY(&obj->uz, &vresult);
	} // end if
}

void Rotate_XYZ_OBJECT4DV2(OBJECT4DV2_PTR obj, // object to rotate
	float theta_x,       // euler angles
	float theta_y,
	float theta_z,
	int all_frames) // process all frames
{
	// this function rotates and object parallel to the
	// XYZ axes in that order or a subset thereof, without
	// matrices (at least externally sent)
	// modifies the object's local vertex list 
	// additionally it rotates the unit directional vectors
	// that track the objects orientation, also note that each
	// time this function is called it calls the rotation generation
	// function, this is wastefull if a number of object are being rotated
	// by the same matrix, therefore, if that's the case, then generate the
	// rotation matrix, store it, and call the general Transform_OBJECT4DV2()
	// with the matrix
	// also vertex normals are rotated by the matrix

	// future optimization: set flag in object attributes, and objects without 
	// vertex normals can be rotated without the test in line

	MATRIX4X4 mrot; // used to store generated rotation matrix

	// generate rotation matrix, no way to avoid rotation with a matrix
	// too much math to do manually!
	Build_XYZ_Rotation_MATRIX4X4(theta_x, theta_y, theta_z, &mrot);

	// single or multi frames
	if (!all_frames)
	{
		// now simply rotate each point of the mesh in local/model coordinates
		for (int vertex = 0; vertex < obj->num_vertices; vertex++)
		{
			POINT4D presult; // hold result of each transformation

			// transform point
			Mat_Mul_VECTOR4D_4X4(&obj->vlist_local[vertex].v, &mrot, &presult);

			// store result back
			VECTOR4D_COPY(&obj->vlist_local[vertex].v, &presult);

			// test for vertex normal
			if (obj->vlist_local[vertex].attr & VERTEX4DTV1_ATTR_NORMAL)
			{
				// transform point
				Mat_Mul_VECTOR4D_4X4(&obj->vlist_local[vertex].n, &mrot, &presult);

				// store result back
				VECTOR4D_COPY(&obj->vlist_local[vertex].n, &presult);
			} // end if

		} // end for index

	} // end if single frame
	else
	{ // process all frames
		// now simply rotate each point of the mesh in local/model coordinates
		for (int vertex = 0; vertex < obj->total_vertices; vertex++)
		{
			POINT4D presult; // hold result of each transformation

			// transform point
			Mat_Mul_VECTOR4D_4X4(&obj->head_vlist_local[vertex].v, &mrot, &presult);

			// store result back
			VECTOR4D_COPY(&obj->head_vlist_local[vertex].v, &presult);

			// test for vertex normal
			if (obj->head_vlist_local[vertex].attr & VERTEX4DTV1_ATTR_NORMAL)
			{
				// transform point
				Mat_Mul_VECTOR4D_4X4(&obj->head_vlist_local[vertex].n, &mrot, &presult);

				// store result back
				VECTOR4D_COPY(&obj->head_vlist_local[vertex].n, &presult);
			} // end if

		} // end for index

	} // end else all frames

	// now rotate orientation basis for object
	VECTOR4D vresult; // use to rotate each orientation vector axis

	// rotate ux of basis
	Mat_Mul_VECTOR4D_4X4(&obj->ux, &mrot, &vresult);
	VECTOR4D_COPY(&obj->ux, &vresult);

	// rotate uy of basis
	Mat_Mul_VECTOR4D_4X4(&obj->uy, &mrot, &vresult);
	VECTOR4D_COPY(&obj->uy, &vresult);

	// rotate uz of basis
	Mat_Mul_VECTOR4D_4X4(&obj->uz, &mrot, &vresult);
	VECTOR4D_COPY(&obj->uz, &vresult);

} // end Rotate_XYZ_OBJECT4DV2

////////////////////////////////////////////////////////////

void Model_To_World_OBJECT4DV2(OBJECT4DV2_PTR obj,
	int coord_select,
	int all_frames)
{
	// NOTE: Not matrix based
	// this function converts the local model coordinates of the
	// sent object into world coordinates, the results are stored
	// in the transformed vertex list (vlist_trans) within the object

	// interate thru vertex list and transform all the model/local 
	// coords to world coords by translating the vertex list by
	// the amount world_pos and storing the results in vlist_trans[]
	// no need to transform vertex normals, they are invariant of position

	if (!all_frames)
	{
		if (coord_select == TRANSFORM_LOCAL_TO_TRANS)
		{
			for (int vertex = 0; vertex < obj->num_vertices; vertex++)
			{
				// translate vertex
				VECTOR4D_Add(&obj->vlist_local[vertex].v, &obj->world_pos, &obj->vlist_trans[vertex].v);
				// copy normal
				VECTOR4D_COPY(&obj->vlist_trans[vertex].n, &obj->vlist_local[vertex].n);

			} // end for vertex
		} // end if local
		else
		{ // TRANSFORM_TRANS_ONLY
			for (int vertex = 0; vertex < obj->num_vertices; vertex++)
			{
				// translate vertex
				VECTOR4D_Add(&obj->vlist_trans[vertex].v, &obj->world_pos, &obj->vlist_trans[vertex].v);
			} // end for vertex
		} // end else trans

	} // end if single frame
	else // all frames
	{
		if (coord_select == TRANSFORM_LOCAL_TO_TRANS)
		{
			for (int vertex = 0; vertex < obj->total_vertices; vertex++)
			{
				// translate vertex
				VECTOR4D_Add(&obj->head_vlist_local[vertex].v, &obj->world_pos, &obj->head_vlist_trans[vertex].v);
				// copy normal
				VECTOR4D_COPY(&obj->head_vlist_trans[vertex].n, &obj->head_vlist_local[vertex].n);
			} // end for vertex
		} // end if local
		else
		{ // TRANSFORM_TRANS_ONLY
			for (int vertex = 0; vertex < obj->total_vertices; vertex++)
			{
				// translate vertex
				VECTOR4D_Add(&obj->head_vlist_trans[vertex].v, &obj->world_pos, &obj->head_vlist_trans[vertex].v);
			} // end for vertex
		} // end else trans

	} // end if all frames

} // end Model_To_World_OBJECT4DV2

//////////////////////////////////////////////////////////////////////

bool Cull_OBJECT4DV2(OBJECT4DV2_PTR obj,  // object to cull
	CAM4DV1_PTR cam,     // camera to cull relative to
	int cull_flags)     // clipping planes to consider
{
	// NOTE: is matrix based
	// this function culls an entire object from the viewing
	// frustrum by using the sent camera information and object
	// the cull_flags determine what axes culling should take place
	// x, y, z or all which is controlled by ORing the flags
	// together
	// if the object is culled its state is modified thats all
	// this function assumes that both the camera and the object
	// are valid!
	// also for OBJECT4DV2, only the current frame matters for culling


	// step 1: transform the center of the object's bounding
	// sphere into camera space

	POINT4D sphere_pos; // hold result of transforming center of bounding sphere

	// transform point
	Mat_Mul_VECTOR4D_4X4(&obj->world_pos, &cam->mcam, &sphere_pos);

	// step 2:  based on culling flags remove the object
	if (cull_flags & CULL_OBJECT_Z_PLANE)
	{
		// cull only based on z clipping planes

		if ((sphere_pos.z - obj->max_radius[obj->curr_frame]) > -cam->near_clip_z || (sphere_pos.z + obj->max_radius[obj->curr_frame] < -cam->far_clip_z))
		{
			SET_BIT(obj->state, OBJECT4DV1_STATE_CULLED);
			return true;
		}

	} // end if

	if (cull_flags & CULL_OBJECT_X_PLANE)
	{
		float posz_view_width = fabs(0.5f * cam->viewplane_width * sphere_pos.z / cam->view_dist);
		float clip_width = fabs(obj->max_radius[obj->curr_frame] / Fast_Cos(cam->fov * 0.5f));
		if ((sphere_pos.x - clip_width > posz_view_width) || (sphere_pos.x + clip_width < -posz_view_width))
		{
			SET_BIT(obj->state, OBJECT4DV1_STATE_CULLED);
			return true;
		}
	} // end if

	if (cull_flags & CULL_OBJECT_Y_PLANE)
	{
		float posz_view_height = fabs(0.5f * cam->viewplane_height * sphere_pos.z / cam->view_dist);
		float clip_height = fabs(obj->max_radius[obj->curr_frame] / Fast_Cos((cam->fov / cam->aspect_ratio) * 0.5f));
		if ((sphere_pos.y - clip_height > posz_view_height) || (sphere_pos.y + clip_height < -posz_view_height))
		{
			SET_BIT(obj->state, OBJECT4DV1_STATE_CULLED);
			return false;
		}

	} // end if

	// return failure to cull
	return false;

} // end Cull_OBJECT4DV2

/////////////////////////////////////////////////////////////////////////////

void Remove_Backfaces_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list, CAM4DV1_PTR cam)
{
	// NOTE: this is not a matrix based function
	// this function removes the backfaces from polygon list
	// the function does this based on the polygon list data
	// tvlist along with the camera position (only)
	// note that only the backface state is set in each polygon

	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		// acquire current polygon
		POLYF4DV2_PTR curr_poly = rend_list->poly_ptrs[poly];

		// is this polygon valid?
		// test this polygon if and only if it's not clipped, not culled,
		// active, and visible and not 2 sided. Note we test for backface in the event that
		// a previous call might have already determined this, so why work
		// harder!
		if ((curr_poly == NULL) || !(curr_poly->state & POLY4DV2_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV2_STATE_CLIPPED) ||
			(curr_poly->attr  & POLY4DV2_ATTR_2SIDED) ||
			(curr_poly->state & POLY4DV2_STATE_BACKFACE))
			continue; // move onto next poly

		// we need to compute the normal of this polygon face, and recall
		// that the vertices are in cw order, u = p0->p1, v=p0->p2, n=uxv
		VECTOR4D u, v, n;

		// build u, v
		VECTOR4D_Build(&curr_poly->tvlist[0].v, &curr_poly->tvlist[1].v, &u);
		VECTOR4D_Build(&curr_poly->tvlist[0].v, &curr_poly->tvlist[2].v, &v);

		// compute cross product
		VECTOR4D_Cross(&u, &v, &n);

		// now create eye vector to viewpoint
		VECTOR4D view;
		VECTOR4D_Build(&curr_poly->tvlist[0].v, &cam->pos, &view);

		// and finally, compute the dot product
		float dp = VECTOR4D_Dot(&n, &view);

		// if the sign is > 0 then visible, 0 = scathing, < 0 invisible
		if (dp <= 0.0)
			SET_BIT(curr_poly->state, POLY4DV2_STATE_BACKFACE);

	} // end for poly

} // end Remove_Backfaces_RENDERLIST4DV2

////////////////////////////////////////////////////////////

void Remove_Backfaces_OBJECT4DV2(OBJECT4DV2_PTR obj, CAM4DV1_PTR cam)
{
	// NOTE: this is not a matrix based function
	// this function removes the backfaces from an object's
	// polygon mesh, the function does this based on the vertex
	// data in vlist_trans along with the camera position (only)
	// note that only the backface state is set in each polygon
	// also since this works on polygons the current frame is the frame
	// that's vertices are used by the backface cull
	// note: only operates on the current frame

	// test if the object is culled
	if (obj->state & OBJECT4DV2_STATE_CULLED)
		return;

	// process each poly in mesh
	for (int poly = 0; poly < obj->num_polys; poly++)
	{
		// acquire polygon
		POLY4DV2_PTR curr_poly = &obj->plist[poly];

		// is this polygon valid?
		// test this polygon if and only if it's not clipped, not culled,
		// active, and visible and not 2 sided. Note we test for backface in the event that
		// a previous call might have already determined this, so why work
		// harder!
		if (!(curr_poly->state & POLY4DV2_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV2_STATE_CLIPPED) ||
			(curr_poly->attr  & POLY4DV2_ATTR_2SIDED) ||
			(curr_poly->state & POLY4DV2_STATE_BACKFACE))
			continue; // move onto next poly

		// extract vertex indices into master list, rember the polygons are 
		// NOT self contained, but based on the vertex list stored in the object
		// itself
		int vindex_0 = curr_poly->vert[0];
		int vindex_1 = curr_poly->vert[1];
		int vindex_2 = curr_poly->vert[2];

		// we will use the transformed polygon vertex list since the backface removal
		// only makes sense at the world coord stage further of the pipeline 

		// we need to compute the normal of this polygon face, and recall
		// that the vertices are in cw order, u = p0->p1, v=p0->p2, n=uxv
		VECTOR4D u, v, n;

		// build u, v
		VECTOR4D_Build(&obj->vlist_trans[vindex_0].v, &obj->vlist_trans[vindex_1].v, &u);
		VECTOR4D_Build(&obj->vlist_trans[vindex_0].v, &obj->vlist_trans[vindex_2].v, &v);

		// compute cross product
		VECTOR4D_Cross(&u, &v, &n);

		// now create eye vector to viewpoint
		VECTOR4D view;
		VECTOR4D_Build(&obj->vlist_trans[vindex_0].v, &cam->pos, &view);

		// and finally, compute the dot product
		float dp = VECTOR4D_Dot(&n, &view);

		// if the sign is > 0 then visible, 0 = scathing, < 0 invisible
		if (dp <= 0.0)
			SET_BIT(curr_poly->state, POLY4DV2_STATE_BACKFACE);

	} // end for poly

} // end Remove_Backfaces_OBJECT4DV2

////////////////////////////////////////////////////////////

void World_To_Camera_OBJECT4DV2(OBJECT4DV2_PTR obj, CAM4DV1_PTR cam)
{
	// NOTE: this is a matrix based function
	// this function transforms the world coordinates of an object
	// into camera coordinates, based on the sent camera matrix
	// but it totally disregards the polygons themselves,
	// it only works on the vertices in the vlist_trans[] list
	// this is one way to do it, you might instead transform
	// the global list of polygons in the render list since you 
	// are guaranteed that those polys represent geometry that 
	// has passed thru backfaces culling (if any)
	// note: only operates on the current frame

	// transform each vertex in the object to camera coordinates
	// assumes the object has already been transformed to world
	// coordinates and the result is in vlist_trans[]
	for (int vertex = 0; vertex < obj->num_vertices; vertex++)
	{
		// transform the vertex by the mcam matrix within the camera
		// it better be valid!
		POINT4D presult; // hold result of each transformation

		// transform point
		Mat_Mul_VECTOR4D_4X4(&obj->vlist_trans[vertex].v, &cam->mcam, &presult);

		// store result back
		VECTOR4D_COPY(&obj->vlist_trans[vertex].v, &presult);
	} // end for vertex

} // end World_To_Camera_OBJECT4DV2

////////////////////////////////////////////////////////


void Camera_To_Perspective_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list,
	CAM4DV1_PTR cam)
{
	// NOTE: this is not a matrix based function
	// this function transforms each polygon in the global render list
	// into perspective coordinates, based on the 
	// sent camera object, 
	// you would use this function instead of the object based function
	// if you decided earlier in the pipeline to turn each object into 
	// a list of polygons and then add them to the global render list

	// transform each polygon in the render list into camera coordinates
	// assumes the render list has already been transformed to world
	// coordinates and the result is in tvlist[] of each polygon object

	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		// acquire current polygon
		POLYF4DV2_PTR curr_poly = rend_list->poly_ptrs[poly];

		// is this polygon valid?
		// transform this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concept of "backface" is 
		// irrelevant in a wire frame engine though
		if ((curr_poly == NULL) || !(curr_poly->state & POLY4DV2_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV2_STATE_CLIPPED) ||
			(curr_poly->state & POLY4DV2_STATE_BACKFACE))
			continue; // move onto next poly

		// all good, let's transform 
		for (int vertex = 0; vertex < 3; vertex++)
		{
			float z = curr_poly->tvlist[vertex].z;

			// transform the vertex by the view parameters in the camera
			curr_poly->tvlist[vertex].x = cam->view_dist*curr_poly->tvlist[vertex].x / z;
			curr_poly->tvlist[vertex].y = cam->view_dist*curr_poly->tvlist[vertex].y*cam->aspect_ratio / z;
			// z = z, so no change

			// not that we are NOT dividing by the homogenous w coordinate since
			// we are not using a matrix operation for this version of the function 

		} // end for vertex

	} // end for poly

} // end Camera_To_Perspective_RENDERLIST4DV2

////////////////////////////////////////////////////////////////

void Camera_To_Perspective_Screen_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list,
	CAM4DV1_PTR cam)
{
	// NOTE: this is not a matrix based function
	// this function transforms the camera coordinates of an object
	// into Screen scaled perspective coordinates, based on the 
	// sent camera object, that is, view_dist_h and view_dist_v 
	// should be set to cause the desired (viewport_width X viewport_height)
	// it only works on the vertices in the tvlist[] list
	// finally, the function also inverts the y axis, so the coordinates
	// generated from this function ARE screen coordinates and ready for
	// rendering

	// transform each polygon in the render list to perspective screen 
	// coordinates assumes the render list has already been transformed 
	// to camera coordinates and the result is in tvlist[]
	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		// acquire current polygon
		POLYF4DV2_PTR curr_poly = rend_list->poly_ptrs[poly];

		// is this polygon valid?
		// transform this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concept of "backface" is 
		// irrelevant in a wire frame engine though
		if ((curr_poly == NULL) || !(curr_poly->state & POLY4DV2_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV2_STATE_CLIPPED) ||
			(curr_poly->state & POLY4DV2_STATE_BACKFACE))
			continue; // move onto next poly

		float alpha = (0.5*cam->viewport_width - 0.5);
		float beta = (0.5*cam->viewport_height - 0.5);

		// all good, let's transform 
		for (int vertex = 0; vertex < 3; vertex++)
		{
			float z = curr_poly->tvlist[vertex].z;
			if (z == 0)
				break;
			// transform the vertex by the view parameters in the camera
			curr_poly->tvlist[vertex].x = cam->viewport_dist*curr_poly->tvlist[vertex].x / z;
			curr_poly->tvlist[vertex].y = cam->viewport_dist*curr_poly->tvlist[vertex].y / z;
			// z = z, so no change

			// not that we are NOT dividing by the homogenous w coordinate since
			// we are not using a matrix operation for this version of the function 

			// now the coordinates are in the range x:(-viewport_width/2 to viewport_width/2)
			// and y:(-viewport_height/2 to viewport_height/2), thus we need a translation and
			// since the y-axis is inverted, we need to invert y to complete the screen 
			// transform:
			curr_poly->tvlist[vertex].x = curr_poly->tvlist[vertex].x + alpha;
			curr_poly->tvlist[vertex].y = -curr_poly->tvlist[vertex].y + beta;

		} // end for vertex

	} // end for poly

} // end Camera_To_Perspective_Screen_RENDERLIST4DV2

//////////////////////////////////////////////////////////////

void Perspective_To_Screen_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list,
	CAM4DV1_PTR cam)
{
	// NOTE: this is not a matrix based function
	// this function transforms the perspective coordinates of the render
	// list into screen coordinates, based on the sent viewport in the camera
	// assuming that the viewplane coordinates were normalized
	// you would use this function instead of the object based function
	// if you decided earlier in the pipeline to turn each object into 
	// a list of polygons and then add them to the global render list
	// you would only call this function if you previously performed
	// a normalized perspective transform

	// transform each polygon in the render list from perspective to screen 
	// coordinates assumes the render list has already been transformed 
	// to normalized perspective coordinates and the result is in tvlist[]
	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		// acquire current polygon
		POLYF4DV2_PTR curr_poly = rend_list->poly_ptrs[poly];

		// is this polygon valid?
		// transform this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concept of "backface" is 
		// irrelevant in a wire frame engine though
		if ((curr_poly == NULL) || !(curr_poly->state & POLY4DV2_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV2_STATE_CLIPPED) ||
			(curr_poly->state & POLY4DV2_STATE_BACKFACE))
			continue; // move onto next poly

		float alpha = (0.5*cam->viewport_width - 0.5);
		float beta = (0.5*cam->viewport_height - 0.5);

		// all good, let's transform 
		for (int vertex = 0; vertex < 3; vertex++)
		{
			// the vertex is in perspective normalized coords from -1 to 1
			// on each axis, simple scale them and invert y axis and project
			// to screen

			// transform the vertex by the view parameters in the camera
			curr_poly->tvlist[vertex].x = alpha + alpha*curr_poly->tvlist[vertex].x;
			curr_poly->tvlist[vertex].y = beta - beta *curr_poly->tvlist[vertex].y;
		} // end for vertex

	} // end for poly

} // end Perspective_To_Screen_RENDERLIST4DV2

///////////////////////////////////////////////////////////////

void World_To_Camera_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list,
	CAM4DV1_PTR cam)
{
	// NOTE: this is a matrix based function
	// this function transforms each polygon in the global render list
	// to camera coordinates based on the sent camera transform matrix
	// you would use this function instead of the object based function
	// if you decided earlier in the pipeline to turn each object into 
	// a list of polygons and then add them to the global render list
	// the conversion of an object into polygons probably would have
	// happened after object culling, local transforms, local to world
	// and backface culling, so the minimum number of polygons from
	// each object are in the list, note that the function assumes
	// that at LEAST the local to world transform has been called
	// and the polygon data is in the transformed list tvlist of
	// the POLYF4DV1 object

	// transform each polygon in the render list into camera coordinates
	// assumes the render list has already been transformed to world
	// coordinates and the result is in tvlist[] of each polygon object

	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		// acquire current polygon
		POLYF4DV2_PTR curr_poly = rend_list->poly_ptrs[poly];

		// is this polygon valid?
		// transform this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concept of "backface" is 
		// irrelevant in a wire frame engine though
		if ((curr_poly == NULL) || !(curr_poly->state & POLY4DV2_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV2_STATE_CLIPPED) ||
			(curr_poly->state & POLY4DV2_STATE_BACKFACE))
			continue; // move onto next poly

		// all good, let's transform 
		for (int vertex = 0; vertex < 3; vertex++)
		{
			// transform the vertex by the mcam matrix within the camera
			// it better be valid!
			POINT4D presult; // hold result of each transformation

			// transform point
			Mat_Mul_VECTOR4D_4X4(&curr_poly->tvlist[vertex].v, &cam->mcam, &presult);

			// store result back
			VECTOR4D_COPY(&curr_poly->tvlist[vertex].v, &presult);
		} // end for vertex

	} // end for poly

} // end World_To_Camera_RENDERLIST4DV2


////////////////////////////////////////////////////////////

void Camera_To_Perspective_OBJECT4DV2(OBJECT4DV2_PTR obj, CAM4DV1_PTR cam)
{
	// NOTE: this is not a matrix based function
	// this function transforms the camera coordinates of an object
	// into perspective coordinates, based on the 
	// sent camera object, but it totally disregards the polygons themselves,
	// it only works on the vertices in the vlist_trans[] list
	// this is one way to do it, you might instead transform
	// the global list of polygons in the render list since you 
	// are guaranteed that those polys represent geometry that 
	// has passed thru backfaces culling (if any)
	// finally this function is really for experimental reasons only
	// you would probably never let an object stay intact this far down
	// the pipeline, since it's probably that there's only a single polygon
	// that is visible! But this function has to transform the whole mesh!
	// note: only operates on the current frame

	// transform each vertex in the object to perspective coordinates
	// assumes the object has already been transformed to camera
	// coordinates and the result is in vlist_trans[]
	for (int vertex = 0; vertex < obj->num_vertices; vertex++)
	{
		float z = obj->vlist_trans[vertex].z;

		// transform the vertex by the view parameters in the camera
		obj->vlist_trans[vertex].x = cam->view_dist*obj->vlist_trans[vertex].x / z;
		obj->vlist_trans[vertex].y = cam->view_dist*obj->vlist_trans[vertex].y*cam->aspect_ratio / z;
		// z = z, so no change

		// not that we are NOT dividing by the homogenous w coordinate since
		// we are not using a matrix operation for this version of the function 

	} // end for vertex

} // end Camera_To_Perspective_OBJECT4DV2

//////////////////////////////////////////////////////////////

void Camera_To_Perspective_Screen_OBJECT4DV2(OBJECT4DV2_PTR obj, CAM4DV1_PTR cam)
{
	// NOTE: this is not a matrix based function
	// this function transforms the camera coordinates of an object
	// into Screen scaled perspective coordinates, based on the 
	// sent camera object, that is, view_dist_h and view_dist_v 
	// should be set to cause the desired (width X height)
	// projection of the vertices, but the function totally 
	// disregards the polygons themselves,
	// it only works on the vertices in the vlist_trans[] list
	// this is one way to do it, you might instead transform
	// the global list of polygons in the render list since you 
	// are guaranteed that those polys represent geometry that 
	// has passed thru backfaces culling (if any)
	// finally this function is really for experimental reasons only
	// you would probably never let an object stay intact this far down
	// the pipeline, since it's probably that there's only a single polygon
	// that is visible! But this function has to transform the whole mesh!
	// finally, the function also inverts the y axis, so the coordinates
	// generated from this function ARE screen coordinates and ready for
	// rendering
	// note: only operates on the current frame

	float alpha = (0.5*cam->viewport_width - 0.5);
	float beta = (0.5*cam->viewport_height - 0.5);

	// transform each vertex in the object to perspective screen coordinates
	// assumes the object has already been transformed to camera
	// coordinates and the result is in vlist_trans[]
	for (int vertex = 0; vertex < obj->num_vertices; vertex++)
	{
		float z = obj->vlist_trans[vertex].z;

		// transform the vertex by the view parameters in the camera
		obj->vlist_trans[vertex].x = cam->view_dist*obj->vlist_trans[vertex].x / z;
		obj->vlist_trans[vertex].y = cam->view_dist*obj->vlist_trans[vertex].y / z;
		// z = z, so no change

		// not that we are NOT dividing by the homogenous w coordinate since
		// we are not using a matrix operation for this version of the function 

		// now the coordinates are in the range x:(-viewport_width/2 to viewport_width/2)
		// and y:(-viewport_height/2 to viewport_height/2), thus we need a translation and
		// since the y-axis is inverted, we need to invert y to complete the screen 
		// transform:
		obj->vlist_trans[vertex].x = obj->vlist_trans[vertex].x + alpha;
		obj->vlist_trans[vertex].y = -obj->vlist_trans[vertex].y + beta;

	} // end for vertex

} // end Camera_To_Perspective_Screen_OBJECT4DV2

//////////////////////////////////////////////////////////////

void Perspective_To_Screen_OBJECT4DV2(OBJECT4DV2_PTR obj, CAM4DV1_PTR cam)
{
	// NOTE: this is not a matrix based function
	// this function transforms the perspective coordinates of an object
	// into screen coordinates, based on the sent viewport info
	// but it totally disregards the polygons themselves,
	// it only works on the vertices in the vlist_trans[] list
	// this is one way to do it, you might instead transform
	// the global list of polygons in the render list since you 
	// are guaranteed that those polys represent geometry that 
	// has passed thru backfaces culling (if any)
	// finally this function is really for experimental reasons only
	// you would probably never let an object stay intact this far down
	// the pipeline, since it's probably that there's only a single polygon
	// that is visible! But this function has to transform the whole mesh!
	// this function would be called after a perspective
	// projection was performed on the object

	// transform each vertex in the object to screen coordinates
	// assumes the object has already been transformed to perspective
	// coordinates and the result is in vlist_trans[]
	// note: only operates on the current frame

	float alpha = (0.5*cam->viewport_width - 0.5);
	float beta = (0.5*cam->viewport_height - 0.5);

	for (int vertex = 0; vertex < obj->num_vertices; vertex++)
	{
		// assumes the vertex is in perspective normalized coords from -1 to 1
		// on each axis, simple scale them to viewport and invert y axis and project
		// to screen

		// transform the vertex by the view parameters in the camera
		obj->vlist_trans[vertex].x = alpha + alpha*obj->vlist_trans[vertex].x;
		obj->vlist_trans[vertex].y = beta - beta *obj->vlist_trans[vertex].y;

	} // end for vertex

} // end Perspective_To_Screen_OBJECT4DV2

/////////////////////////////////////////////////////////////

void Convert_From_Homogeneous4D_OBJECT4DV2(OBJECT4DV2_PTR obj)
{
	// this function convertes all vertices in the transformed
	// vertex list from 4D homogeneous coordinates to normal 3D coordinates
	// by dividing each x,y,z component by w
	// note: only operates on the current frame

	for (int vertex = 0; vertex < obj->num_vertices; vertex++)
	{
		// convert to non-homogenous coords
		VECTOR4D_DIV_BY_W(&obj->vlist_trans[vertex].v);
	} // end for vertex

} // end Convert_From_Homogeneous4D_OBJECT4DV2

//////////////////////////////////////////////////////////////////

int Insert_POLY4DV2_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list,
	POLY4DV2_PTR poly)
{
	// converts the sent POLY4DV2 into a POLYF4DV2 and inserts it
	// into the render list, this function needs optmizing

	// step 0: are we full?
	if (rend_list->num_polys >= RENDERLIST4DV2_MAX_POLYS)
		return(0);

	// step 1: copy polygon into next opening in polygon render list

	// point pointer to polygon structure
	rend_list->poly_ptrs[rend_list->num_polys] = &rend_list->poly_data[rend_list->num_polys];

	// copy fields { ??????????? make sure ALL fields are copied, normals, textures, etc!!!  }
	rend_list->poly_data[rend_list->num_polys].state = poly->state;
	rend_list->poly_data[rend_list->num_polys].attr = poly->attr;
	rend_list->poly_data[rend_list->num_polys].color = poly->color;
	rend_list->poly_data[rend_list->num_polys].nlength = poly->nlength;
	rend_list->poly_data[rend_list->num_polys].texture = poly->texture;

	// poly could be lit, so copy these too...
	rend_list->poly_data[rend_list->num_polys].lit_color[0] = poly->lit_color[0];
	rend_list->poly_data[rend_list->num_polys].lit_color[1] = poly->lit_color[1];
	rend_list->poly_data[rend_list->num_polys].lit_color[2] = poly->lit_color[2];

	// now copy vertices, be careful! later put a loop, but for now
	// know there are 3 vertices always!
	VERTEX4DTV1_COPY(&rend_list->poly_data[rend_list->num_polys].tvlist[0],
		&poly->vlist[poly->vert[0]]);

	VERTEX4DTV1_COPY(&rend_list->poly_data[rend_list->num_polys].tvlist[1],
		&poly->vlist[poly->vert[1]]);

	VERTEX4DTV1_COPY(&rend_list->poly_data[rend_list->num_polys].tvlist[2],
		&poly->vlist[poly->vert[2]]);

	// and copy into local vertices too
	VERTEX4DTV1_COPY(&rend_list->poly_data[rend_list->num_polys].vlist[0],
		&poly->vlist[poly->vert[0]]);

	VERTEX4DTV1_COPY(&rend_list->poly_data[rend_list->num_polys].vlist[1],
		&poly->vlist[poly->vert[1]]);

	VERTEX4DTV1_COPY(&rend_list->poly_data[rend_list->num_polys].vlist[2],
		&poly->vlist[poly->vert[2]]);

	// finally the texture coordinates, this has to be performed manually
	// since at this point in the pipeline the vertices do NOT have texture
	// coordinate, the polygons DO, however, now, there are 3 vertices for 
	// EVERY polygon, rather than vertex sharing, so we can copy the texture
	// coordinates out of the indexed arrays into the VERTEX4DTV1 structures
	rend_list->poly_data[rend_list->num_polys].tvlist[0].t = poly->tlist[poly->text[0]];
	rend_list->poly_data[rend_list->num_polys].tvlist[1].t = poly->tlist[poly->text[1]];
	rend_list->poly_data[rend_list->num_polys].tvlist[2].t = poly->tlist[poly->text[2]];

	rend_list->poly_data[rend_list->num_polys].vlist[0].t = poly->tlist[poly->text[0]];
	rend_list->poly_data[rend_list->num_polys].vlist[1].t = poly->tlist[poly->text[1]];
	rend_list->poly_data[rend_list->num_polys].vlist[2].t = poly->tlist[poly->text[2]];

	// now the polygon is loaded into the next free array position, but
	// we need to fix up the links

	// test if this is the first entry
	if (rend_list->num_polys == 0)
	{
		// set pointers to null, could loop them around though to self
		rend_list->poly_data[0].next = NULL;
		rend_list->poly_data[0].prev = NULL;
	} // end if
	else
	{
		// first set this node to point to previous node and next node (null)
		rend_list->poly_data[rend_list->num_polys].next = NULL;
		rend_list->poly_data[rend_list->num_polys].prev =
			&rend_list->poly_data[rend_list->num_polys - 1];

		// now set previous node to point to this node
		rend_list->poly_data[rend_list->num_polys - 1].next =
			&rend_list->poly_data[rend_list->num_polys];
	} // end else

	// increment number of polys in list
	rend_list->num_polys++;

	// return successful insertion
	return(1);

} // end Insert_POLY4DV2_RENDERLIST4DV2

//////////////////////////////////////////////////////////////

int Insert_POLYF4DV2_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list,
	POLYF4DV2_PTR poly)
{
	// inserts the sent polyface POLYF4DV1 into the render list

	// step 0: are we full?
	if (rend_list->num_polys >= RENDERLIST4DV2_MAX_POLYS)
		return(0);

	// step 1: copy polygon into next opening in polygon render list

	// point pointer to polygon structure
	rend_list->poly_ptrs[rend_list->num_polys] = &rend_list->poly_data[rend_list->num_polys];

	// copy face right into array, thats it!
	memcpy((void *)&rend_list->poly_data[rend_list->num_polys], (void *)poly, sizeof(POLYF4DV2));

	// now the polygon is loaded into the next free array position, but
	// we need to fix up the links
	// test if this is the first entry
	if (rend_list->num_polys == 0)
	{
		// set pointers to null, could loop them around though to self
		rend_list->poly_data[0].next = NULL;
		rend_list->poly_data[0].prev = NULL;
	} // end if
	else
	{
		// first set this node to point to previous node and next node (null)
		rend_list->poly_data[rend_list->num_polys].next = NULL;
		rend_list->poly_data[rend_list->num_polys].prev =
			&rend_list->poly_data[rend_list->num_polys - 1];

		// now set previous node to point to this node
		rend_list->poly_data[rend_list->num_polys - 1].next =
			&rend_list->poly_data[rend_list->num_polys];
	} // end else

	// increment number of polys in list
	rend_list->num_polys++;

	// return successful insertion
	return(1);

} // end Insert_POLYF4DV2_RENDERLIST4DV2

//////////////////////////////////////////////////////////////

int Insert_OBJECT4DV2_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list,
	OBJECT4DV2_PTR obj,
	int insert_local)

{
	// { andre work in progress, rewrite with materials...}

	// converts the entire object into a face list and then inserts
	// the visible, active, non-clipped, non-culled polygons into
	// the render list, also note the flag insert_local control 
	// whether or not the vlist_local or vlist_trans vertex list
	// is used, thus you can insert an object "raw" totally untranformed
	// if you set insert_local to 1, default is 0, that is you would
	// only insert an object after at least the local to world transform
	// the last parameter is used to control if their has been
	// a lighting step that has generated a light value stored
	// in the upper 16-bits of color, if lighting_on = 1 then
	// this value is used to overwrite the base color of the 
	// polygon when its sent to the rendering list

	unsigned int base_color; // save base color of polygon

	// is this objective inactive or culled or invisible?
	if (!(obj->state & OBJECT4DV2_STATE_ACTIVE) ||
		(obj->state & OBJECT4DV2_STATE_CULLED) ||
		!(obj->state & OBJECT4DV2_STATE_VISIBLE))
		return(0);

	// the object is valid, let's rip it apart polygon by polygon
	for (int poly = 0; poly < obj->num_polys; poly++)
	{
		// acquire polygon
		POLY4DV2_PTR curr_poly = &obj->plist[poly];

		// first is this polygon even visible?
		if (!(curr_poly->state & POLY4DV2_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV2_STATE_CLIPPED) ||
			(curr_poly->state & POLY4DV2_STATE_BACKFACE))
			continue; // move onto next poly

		// override vertex list polygon refers to
		// the case that you want the local coords used
		// first save old pointer
		VERTEX4DTV1_PTR vlist_old = curr_poly->vlist;

		if (insert_local)
			curr_poly->vlist = obj->vlist_local;
		else
			curr_poly->vlist = obj->vlist_trans;

		// now insert this polygon
		if (!Insert_POLY4DV2_RENDERLIST4DV2(rend_list, curr_poly))
		{
			// fix vertex list pointer
			curr_poly->vlist = vlist_old;

			// the whole object didn't fit!
			return(0);
		} // end if

		// fix vertex list pointer
		curr_poly->vlist = vlist_old;

	} // end for

	// return success
	return(1);

} // end Insert_OBJECT4DV2_RENDERLIST4DV2

/////////////////////////////////////////////////////////////////////

void Reset_OBJECT4DV2(OBJECT4DV2_PTR obj)
{
	// this function resets the sent object and redies it for 
	// transformations, basically just resets the culled, clipped and
	// backface flags, but here's where you would add stuff
	// to ready any object for the pipeline
	// the object is valid, let's rip it apart polygon by polygon
	// note: works on the entire object, all frames

	// reset object's culled flag
	RESET_BIT(obj->state, OBJECT4DV2_STATE_CULLED);

	// now the clipped and backface flags for the polygons 
	for (int poly = 0; poly < obj->num_polys; poly++)
	{
		// acquire polygon
		POLY4DV2_PTR curr_poly = &obj->plist[poly];

		// first is this polygon even visible?
		if (!(curr_poly->state & POLY4DV2_STATE_ACTIVE))
			continue; // move onto next poly

		// reset clipped and backface flags
		RESET_BIT(curr_poly->state, POLY4DV2_STATE_CLIPPED);
		RESET_BIT(curr_poly->state, POLY4DV2_STATE_BACKFACE);
		RESET_BIT(curr_poly->state, POLY4DV2_STATE_LIT);

	} // end for poly

} // end Reset_OBJECT4DV2

//////////////////////////////////////////////////////////////

void Draw_OBJECT4DV2_Wire(OBJECT4DV2_PTR obj,
	UCHAR *video_buffer, int lpitch)

{
	// this function renders an object to the screen in wireframe, 
	// 8 bit mode, it has no regard at all about hidden surface removal, 
	// etc. the function only exists as an easy way to render an object 
	// without converting it into polygons, the function assumes all 
	// coordinates are screen coordinates, but will perform 2D clipping
	// note: only operates on the current frame

	// iterate thru the poly list of the object and simply draw
	// each polygon
	for (int poly = 0; poly < obj->num_polys; poly++)
	{
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(obj->plist[poly].state & POLY4DV2_STATE_ACTIVE) ||
			(obj->plist[poly].state & POLY4DV2_STATE_CLIPPED) ||
			(obj->plist[poly].state & POLY4DV2_STATE_BACKFACE))
			continue; // move onto next poly

		// extract vertex indices into master list, rember the polygons are 
		// NOT self contained, but based on the vertex list stored in the object
		// itself
		int vindex_0 = obj->plist[poly].vert[0];
		int vindex_1 = obj->plist[poly].vert[1];
		int vindex_2 = obj->plist[poly].vert[2];

		// {andre need material stuff here!!!! }
		// draw the lines now
		Draw_Clip_Line(obj->vlist_trans[vindex_0].x, obj->vlist_trans[vindex_0].y,
			obj->vlist_trans[vindex_1].x, obj->vlist_trans[vindex_1].y,
			obj->plist[poly].lit_color[0],
			video_buffer, lpitch);

		Draw_Clip_Line(obj->vlist_trans[vindex_1].x, obj->vlist_trans[vindex_1].y,
			obj->vlist_trans[vindex_2].x, obj->vlist_trans[vindex_2].y,
			obj->plist[poly].lit_color[0],
			video_buffer, lpitch);

		Draw_Clip_Line(obj->vlist_trans[vindex_2].x, obj->vlist_trans[vindex_2].y,
			obj->vlist_trans[vindex_0].x, obj->vlist_trans[vindex_0].y,
			obj->plist[poly].lit_color[0],
			video_buffer, lpitch);

		// track rendering stats
#ifdef DEBUG_ON
		debug_polys_rendered_per_frame++;
#endif

	} // end for poly

} // end Draw_OBJECT4DV2_Wire

///////////////////////////////////////////////////////////////

void Draw_OBJECT4DV2_Wire16(OBJECT4DV2_PTR obj,
	UCHAR *video_buffer, int lpitch)

{
	// this function renders an object to the screen in wireframe, 
	// 16 bit mode, it has no regard at all about hidden surface removal, 
	// etc. the function only exists as an easy way to render an object 
	// without converting it into polygons, the function assumes all 
	// coordinates are screen coordinates, but will perform 2D clipping
	// note: only operates on the current frame

	// iterate thru the poly list of the object and simply draw
	// each polygon
	for (int poly = 0; poly < obj->num_polys; poly++)
	{
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(obj->plist[poly].state & POLY4DV2_STATE_ACTIVE) ||
			(obj->plist[poly].state & POLY4DV2_STATE_CLIPPED) ||
			(obj->plist[poly].state & POLY4DV2_STATE_BACKFACE))
			continue; // move onto next poly

		// extract vertex indices into master list, rember the polygons are 
		// NOT self contained, but based on the vertex list stored in the object
		// itself
		int vindex_0 = obj->plist[poly].vert[0];
		int vindex_1 = obj->plist[poly].vert[1];
		int vindex_2 = obj->plist[poly].vert[2];

		// {andre need material stuff here!!!! }

		// draw the lines now
		Draw_Clip_Line16(obj->vlist_trans[vindex_0].x, obj->vlist_trans[vindex_0].y,
			obj->vlist_trans[vindex_1].x, obj->vlist_trans[vindex_1].y,
			obj->plist[poly].lit_color[0],
			video_buffer, lpitch);

		Draw_Clip_Line16(obj->vlist_trans[vindex_1].x, obj->vlist_trans[vindex_1].y,
			obj->vlist_trans[vindex_2].x, obj->vlist_trans[vindex_2].y,
			obj->plist[poly].lit_color[0],
			video_buffer, lpitch);

		Draw_Clip_Line16(obj->vlist_trans[vindex_2].x, obj->vlist_trans[vindex_2].y,
			obj->vlist_trans[vindex_0].x, obj->vlist_trans[vindex_0].y,
			obj->plist[poly].lit_color[0],
			video_buffer, lpitch);

		// track rendering stats
#ifdef DEBUG_ON
		debug_polys_rendered_per_frame++;
#endif

	} // end for poly

} // end Draw_OBJECT4DV2_Wire16

///////////////////////////////////////////////////////////////////////////////

int Compare_AvgZ_POLYF4DV2(const void *arg1, const void *arg2)
{
	// this function comapares the average z's of two polygons and is used by the
	// depth sort surface ordering algorithm

	float z1, z2;

	POLYF4DV2_PTR poly_1, poly_2;

	// dereference the poly pointers
	poly_1 = *((POLYF4DV2_PTR *)(arg1));
	poly_2 = *((POLYF4DV2_PTR *)(arg2));

	// compute z average of each polygon
	z1 = (float)0.33333*(poly_1->tvlist[0].z + poly_1->tvlist[1].z + poly_1->tvlist[2].z);

	// now polygon 2
	z2 = (float)0.33333*(poly_2->tvlist[0].z + poly_2->tvlist[1].z + poly_2->tvlist[2].z);

	// compare z1 and z2, such that polys' will be sorted in descending Z order
	if (z1 > z2)
		return(1);
	else
	if (z1 < z2)
		return(-1);
	else
		return(0);

} // end Compare_AvgZ_POLYF4DV2

////////////////////////////////////////////////////////////////////////////////

int Compare_NearZ_POLYF4DV2(const void *arg1, const void *arg2)
{
	// this function comapares the closest z's of two polygons and is used by the
	// depth sort surface ordering algorithm

	float z1, z2;

	POLYF4DV2_PTR poly_1, poly_2;

	// dereference the poly pointers
	poly_1 = *((POLYF4DV2_PTR *)(arg1));
	poly_2 = *((POLYF4DV2_PTR *)(arg2));

	// compute the near z of each polygon
	z1 = MIN(poly_1->tvlist[0].z, poly_1->tvlist[1].z);
	z1 = MIN(z1, poly_1->tvlist[2].z);

	z2 = MIN(poly_2->tvlist[0].z, poly_2->tvlist[1].z);
	z2 = MIN(z2, poly_2->tvlist[2].z);

	// compare z1 and z2, such that polys' will be sorted in descending Z order
	if (z1 > z2)
		return(1);
	else
	if (z1 < z2)
		return(-1);
	else
		return(0);

} // end Compare_NearZ_POLYF4DV2

////////////////////////////////////////////////////////////////////////////////

int Compare_FarZ_POLYF4DV2(const void *arg1, const void *arg2)
{
	// this function comapares the farthest z's of two polygons and is used by the
	// depth sort surface ordering algorithm

	float z1, z2;

	POLYF4DV2_PTR poly_1, poly_2;

	// dereference the poly pointers
	poly_1 = *((POLYF4DV2_PTR *)(arg1));
	poly_2 = *((POLYF4DV2_PTR *)(arg2));

	// compute the near z of each polygon
	z1 = MAX(poly_1->tvlist[0].z, poly_1->tvlist[1].z);
	z1 = MAX(z1, poly_1->tvlist[2].z);

	z2 = MAX(poly_2->tvlist[0].z, poly_2->tvlist[1].z);
	z2 = MAX(z2, poly_2->tvlist[2].z);

	// compare z1 and z2, such that polys' will be sorted in descending Z order
	if (z1 > z2)
		return(1);
	else
	if (z1 < z2)
		return(-1);
	else
		return(0);

} // end Compare_FarZ_POLYF4DV2

///////////////////////////////////////////////////////////////////////////////

void Sort_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list, int sort_method = SORT_POLYLIST_AVGZ)
{
	// this function sorts the rendering list based on the polygon z-values 
	// the specific sorting method is controlled by sending in control flags
	// #define SORT_POLYLIST_AVGZ  0 - sorts on average of all vertices
	// #define SORT_POLYLIST_NEARZ 1 - sorts on closest z vertex of each poly
	// #define SORT_POLYLIST_FARZ  2 - sorts on farthest z vertex of each poly

	switch (sort_method)
	{
	case SORT_POLYLIST_AVGZ:  //  - sorts on average of all vertices
	{
								  qsort((void *)rend_list->poly_ptrs, rend_list->num_polys, sizeof(POLYF4DV2_PTR), Compare_AvgZ_POLYF4DV2);
	} break;

	case SORT_POLYLIST_NEARZ: // - sorts on closest z vertex of each poly
	{
								  qsort((void *)rend_list->poly_ptrs, rend_list->num_polys, sizeof(POLYF4DV2_PTR), Compare_NearZ_POLYF4DV2);
	} break;

	case SORT_POLYLIST_FARZ:  //  - sorts on farthest z vertex of each poly
	{
								  qsort((void *)rend_list->poly_ptrs, rend_list->num_polys, sizeof(POLYF4DV2_PTR), Compare_FarZ_POLYF4DV2);
	} break;

	default: break;
	} // end switch

} // end Sort_RENDERLIST4DV2

////////////////////////////////////////////////////////////////////////////////

int Light_OBJECT4DV2_World16(OBJECT4DV2_PTR obj,  // object to process
	CAM4DV1_PTR cam,     // camera position
	LIGHTV1_PTR lights,  // light list (might have more than one)
	int max_lights)      // maximum lights in list
{
	// {andre work in progress }

	// 16-bit version of function
	// function lights an object based on the sent lights and camera. the function supports
	// constant/pure shading (emmisive), flat shading with ambient, infinite, point lights, and spot lights
	// note that this lighting function is rather brute force and simply follows the math, however
	// there are some clever integer operations that are used in scale 256 rather than going to floating
	// point, but why? floating point and ints are the same speed, HOWEVER, the conversion to and from floating
	// point can be cycle intensive, so if you can keep your calcs in ints then you can gain some speed
	// also note, type 1 spot lights are simply point lights with direction, the "cone" is more of a function
	// of the falloff due to attenuation, but they still look like spot lights
	// type 2 spot lights are implemented with the intensity having a dot product relationship with the
	// angle from the surface point to the light direction just like in the optimized model, but the pf term
	// that is used for a concentration control must be 1,2,3,.... integral and non-fractional


	unsigned int r_base, g_base, b_base,  // base color being lit
		r_sum, g_sum, b_sum,   // sum of lighting process over all lights
		r_sum0, g_sum0, b_sum0,
		r_sum1, g_sum1, b_sum1,
		r_sum2, g_sum2, b_sum2,
		ri, gi, bi,
		shaded_color;            // final color

	float dp,     // dot product 
		dist,   // distance from light to surface
		dists,
		i,      // general intensities
		nl,     // length of normal
		atten;  // attenuation computations

	VECTOR4D u, v, n, l, d, s; // used for cross product and light vector calculations

	//Write_Error("\nEntering lighting function");


	// test if the object is culled
	if (!(obj->state & OBJECT4DV2_STATE_ACTIVE) ||
		(obj->state & OBJECT4DV2_STATE_CULLED) ||
		!(obj->state & OBJECT4DV2_STATE_VISIBLE))
		return(0);

	// for each valid poly, light it...
	for (int poly = 0; poly < obj->num_polys; poly++)
	{
		// acquire polygon
		POLY4DV2_PTR curr_poly = &obj->plist[poly];

		// light this polygon if and only if it's not clipped, not culled,
		// active, and visible
		if (!(curr_poly->state & POLY4DV2_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV2_STATE_CLIPPED) ||
			(curr_poly->state & POLY4DV2_STATE_BACKFACE))
			continue; // move onto next poly

		// set state of polygon to lit, so we don't light again in renderlist
		// lighting system if it happens to get called
		SET_BIT(curr_poly->state, POLY4DV2_STATE_LIT);

		// extract vertex indices into master list, rember the polygons are 
		// NOT self contained, but based on the vertex list stored in the object
		// itself
		int vindex_0 = curr_poly->vert[0];
		int vindex_1 = curr_poly->vert[1];
		int vindex_2 = curr_poly->vert[2];

		// we will use the transformed polygon vertex list since the backface removal
		// only makes sense at the world coord stage further of the pipeline 

		//Write_Error("\npoly %d",poly);

		// we will use the transformed polygon vertex list since the backface removal
		// only makes sense at the world coord stage further of the pipeline 

		// test the lighting mode of the polygon (use flat for flat, gouraud))
		if (curr_poly->attr & POLY4DV2_ATTR_SHADE_MODE_FLAT)
		{
			//Write_Error("\nEntering Flat Shader");

			// step 1: extract the base color out in RGB mode, assume RGB 565
			_RGB565FROM16BIT(curr_poly->color, &r_base, &g_base, &b_base);

			// scale to 8 bit 
			r_base <<= 3;
			g_base <<= 2;
			b_base <<= 3;

			//Write_Error("\nBase color=%d,%d,%d", r_base, g_base, b_base);

			// initialize color sum
			r_sum = 0;
			g_sum = 0;
			b_sum = 0;

			//Write_Error("\nsum color=%d,%d,%d", r_sum, g_sum, b_sum);

			// new optimization:
			// when there are multiple lights in the system we will end up performing numerous
			// redundant calculations to minimize this my strategy is to set key variables to 
			// to MAX values on each loop, then during the lighting calcs to test the vars for
			// the max value, if they are the max value then the first light that needs the math
			// will do it, and then save the information into the variable (causing it to change state
			// from an invalid number) then any other lights that need the math can use the previously
			// computed value

			// set surface normal.z to FLT_MAX to flag it as non-computed
			n.z = FLT_MAX;

			// loop thru lights
			for (int curr_light = 0; curr_light < max_lights; curr_light++)
			{
				// is this light active
				if (lights[curr_light].state == LIGHTV1_STATE_OFF)
					continue;

				//Write_Error("\nprocessing light %d",curr_light);

				// what kind of light are we dealing with
				if (lights[curr_light].attr & LIGHTV1_ATTR_AMBIENT)
				{
					//Write_Error("\nEntering ambient light...");

					// simply multiply each channel against the color of the 
					// polygon then divide by 256 to scale back to 0..255
					// use a shift in real life!!! >> 8
					r_sum += ((lights[curr_light].c_ambient.r * r_base) / 256);
					g_sum += ((lights[curr_light].c_ambient.g * g_base) / 256);
					b_sum += ((lights[curr_light].c_ambient.b * b_base) / 256);

					//Write_Error("\nambient sum=%d,%d,%d", r_sum, g_sum, b_sum);

					// there better only be one ambient light!

				} // end if
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_INFINITE) ///////////////////////////////////////////
				{
					//Write_Error("\nEntering infinite light...");

					// infinite lighting, we need the surface normal, and the direction
					// of the light source

					// test if we already computed poly normal in previous calculation
					if (n.z == FLT_MAX)
					{
						// we need to compute the normal of this polygon face, and recall
						// that the vertices are in cw order, u=p0->p1, v=p0->p2, n=uxv

						// build u, v
						VECTOR4D_Build(&obj->vlist_trans[vindex_0].v, &obj->vlist_trans[vindex_1].v, &u);
						VECTOR4D_Build(&obj->vlist_trans[vindex_0].v, &obj->vlist_trans[vindex_2].v, &v);

						// compute cross product
						VECTOR4D_Cross(&u, &v, &n);
					} // end if

					// at this point, we are almost ready, but we have to normalize the normal vector!
					// this is a key optimization we can make later, we can pre-compute the length of all polygon
					// normals, so this step can be optimized
					// compute length of normal
					//nl = VECTOR4D_Length_Fast2(&n);
					nl = curr_poly->nlength;

					// ok, recalling the lighting model for infinite lights
					// I(d)dir = I0dir * Cldir
					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles

					dp = VECTOR4D_Dot(&n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						i = 128 * dp / nl;
						r_sum += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if

					//Write_Error("\ninfinite sum=%d,%d,%d", r_sum, g_sum, b_sum);

				} // end if infinite light
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_POINT) ///////////////////////////////////////
				{
					//Write_Error("\nEntering point light...");

					// perform point light computations
					// light model for point light is once again:
					//              I0point * Clpoint
					//  I(d)point = ___________________
					//              kc +  kl*d + kq*d2              
					//
					//  Where d = |p - s|
					// thus it's almost identical to the infinite light, but attenuates as a function
					// of distance from the point source to the surface point being lit

					// test if we already computed poly normal in previous calculation
					if (n.z == FLT_MAX)
					{
						// we need to compute the normal of this polygon face, and recall
						// that the vertices are in cw order, u=p0->p1, v=p0->p2, n=uxv

						// build u, v
						VECTOR4D_Build(&obj->vlist_trans[vindex_0].v, &obj->vlist_trans[vindex_1].v, &u);
						VECTOR4D_Build(&obj->vlist_trans[vindex_0].v, &obj->vlist_trans[vindex_2].v, &v);

						// compute cross product
						VECTOR4D_Cross(&u, &v, &n);
					} // end if

					// at this point, we are almost ready, but we have to normalize the normal vector!
					// this is a key optimization we can make later, we can pre-compute the length of all polygon
					// normals, so this step can be optimized
					// compute length of normal
					//nl = VECTOR4D_Length_Fast2(&n);
					nl = curr_poly->nlength;

					// compute vector from surface to light
					VECTOR4D_Build(&obj->vlist_trans[vindex_0].v, &lights[curr_light].pos, &l);

					// compute distance and attenuation
					dist = VECTOR4D_Length_Fast2(&l);

					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles
					dp = VECTOR4D_Dot(&n, &l);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 128 * dp / (nl * dist * atten);

						r_sum += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if


					//Write_Error("\npoint sum=%d,%d,%d",r_sum,g_sum,b_sum);

				} // end if point
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_SPOTLIGHT1) ////////////////////////////////////
				{
					//Write_Error("\nentering spot light1...");

					// perform spotlight/point computations simplified model that uses
					// point light WITH a direction to simulate a spotlight
					// light model for point light is once again:
					//              I0point * Clpoint
					//  I(d)point = ___________________
					//              kc +  kl*d + kq*d2              
					//
					//  Where d = |p - s|
					// thus it's almost identical to the infinite light, but attenuates as a function
					// of distance from the point source to the surface point being lit

					// test if we already computed poly normal in previous calculation
					if (n.z == FLT_MAX)
					{
						// we need to compute the normal of this polygon face, and recall
						// that the vertices are in cw order, u=p0->p1, v=p0->p2, n=uxv

						// build u, v
						VECTOR4D_Build(&obj->vlist_trans[vindex_0].v, &obj->vlist_trans[vindex_1].v, &u);
						VECTOR4D_Build(&obj->vlist_trans[vindex_0].v, &obj->vlist_trans[vindex_2].v, &v);

						// compute cross product
						VECTOR4D_Cross(&u, &v, &n);
					} // end if

					// at this point, we are almost ready, but we have to normalize the normal vector!
					// this is a key optimization we can make later, we can pre-compute the length of all polygon
					// normals, so this step can be optimized
					// compute length of normal
					//nl = VECTOR4D_Length_Fast2(&n);
					nl = curr_poly->nlength;

					// compute vector from surface to light
					VECTOR4D_Build(&obj->vlist_trans[vindex_0].v, &lights[curr_light].pos, &l);

					// compute distance and attenuation
					dist = VECTOR4D_Length_Fast2(&l);

					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles

					// note that I use the direction of the light here rather than a the vector to the light
					// thus we are taking orientation into account which is similar to the spotlight model
					dp = VECTOR4D_Dot(&n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 128 * dp / (nl * atten);

						r_sum += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if

					//Write_Error("\nspotlight sum=%d,%d,%d",r_sum, g_sum, b_sum);

				} // end if spotlight1
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_SPOTLIGHT2) // simple version ////////////////////
				{
					//Write_Error("\nEntering spotlight2 ...");

					// perform spot light computations
					// light model for spot light simple version is once again:
					//         	     I0spotlight * Clspotlight * MAX( (l . s), 0)^pf                     
					// I(d)spotlight = __________________________________________      
					//               		 kc + kl*d + kq*d2        
					// Where d = |p - s|, and pf = power factor

					// thus it's almost identical to the point, but has the extra term in the numerator
					// relating the angle between the light source and the point on the surface

					// test if we already computed poly normal in previous calculation
					if (n.z == FLT_MAX)
					{
						// we need to compute the normal of this polygon face, and recall
						// that the vertices are in cw order, u=p0->p1, v=p0->p2, n=uxv

						// build u, v
						VECTOR4D_Build(&obj->vlist_trans[vindex_0].v, &obj->vlist_trans[vindex_1].v, &u);
						VECTOR4D_Build(&obj->vlist_trans[vindex_0].v, &obj->vlist_trans[vindex_2].v, &v);

						// compute cross product
						VECTOR4D_Cross(&u, &v, &n);
					} // end if

					// at this point, we are almost ready, but we have to normalize the normal vector!
					// this is a key optimization we can make later, we can pre-compute the length of all polygon
					// normals, so this step can be optimized
					// compute length of normal
					//nl = VECTOR4D_Length_Fast2(&n);
					nl = curr_poly->nlength;

					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles
					dp = VECTOR4D_Dot(&n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						// compute vector from light to surface (different from l which IS the light dir)
						VECTOR4D_Build(&lights[curr_light].pos, &obj->vlist_trans[vindex_0].v, &s);

						// compute length of s (distance to light source) to normalize s for lighting calc
						dists = VECTOR4D_Length_Fast2(&s);

						// compute spot light term (s . l)
						float dpsl = VECTOR4D_Dot(&s, &lights[curr_light].dir) / dists;

						// proceed only if term is positive
						if (dpsl > 0)
						{
							// compute attenuation
							atten = (lights[curr_light].kc + lights[curr_light].kl*dists + lights[curr_light].kq*dists*dists);

							// for speed reasons, pf exponents that are less that 1.0 are out of the question, and exponents
							// must be integral
							float dpsl_exp = dpsl;

							// exponentiate for positive integral powers
							for (int e_index = 1; e_index < (int)lights[curr_light].pf; e_index++)
								dpsl_exp *= dpsl;

							// now dpsl_exp holds (dpsl)^pf power which is of course (s . l)^pf 

							i = 128 * dp * dpsl_exp / (nl * atten);

							r_sum += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
							g_sum += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
							b_sum += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);

						} // end if

					} // end if

					//Write_Error("\nSpotlight sum=%d,%d,%d",r_sum, g_sum, b_sum);

				} // end if spot light

			} // end for light

			// make sure colors aren't out of range
			if (r_sum > 255) r_sum = 255;
			if (g_sum > 255) g_sum = 255;
			if (b_sum > 255) b_sum = 255;

			//Write_Error("\nWriting final values to polygon %d = %d,%d,%d", poly, r_sum, g_sum, b_sum);

			// write the color over current color
			curr_poly->lit_color[0] = _ARGB32BIT(255, r_sum, g_sum, b_sum);

		} // end if
		else
		if (curr_poly->attr & POLY4DV2_ATTR_SHADE_MODE_GOURAUD) /////////////////////////////////
		{
			// gouraud shade, unfortunetly at this point in the pipeline, we have lost the original
			// mesh, and only have triangles, thus, many triangles will share the same vertices and
			// they will get lit 2x since we don't have any way to tell this, alas, performing lighting
			// at the object level is a better idea when gouraud shading is performed since the 
			// commonality of vertices is still intact, in any case, lighting here is similar to polygon
			// flat shaded, but we do it 3 times, once for each vertex, additionally there are lots
			// of opportunities for optimization, but I am going to lay off them for now, so the code
			// is intelligible, later we will optimize

			//Write_Error("\nEntering gouraud shader...");

			// step 1: extract the base color out in RGB mode
			// assume 565 format
			_RGB565FROM16BIT(curr_poly->color, &r_base, &g_base, &b_base);

			// scale to 8 bit 
			r_base <<= 3;
			g_base <<= 2;
			b_base <<= 3;

			//Write_Error("\nBase color=%d, %d, %d", r_base, g_base, b_base);

			// initialize color sum(s) for vertices
			r_sum0 = 0;
			g_sum0 = 0;
			b_sum0 = 0;

			r_sum1 = 0;
			g_sum1 = 0;
			b_sum1 = 0;

			r_sum2 = 0;
			g_sum2 = 0;
			b_sum2 = 0;

			//Write_Error("\nColor sums rgb0[%d, %d, %d], rgb1[%d,%d,%d], rgb2[%d,%d,%d]", r_sum0, g_sum0, b_sum0,   r_sum1, g_sum1, b_sum1, r_sum2, g_sum2, b_sum2);

			// new optimization:
			// when there are multiple lights in the system we will end up performing numerous
			// redundant calculations to minimize this my strategy is to set key variables to 
			// to MAX values on each loop, then during the lighting calcs to test the vars for
			// the max value, if they are the max value then the first light that needs the math
			// will do it, and then save the information into the variable (causing it to change state
			// from an invalid number) then any other lights that need the math can use the previously
			// computed value

			// loop thru lights
			for (int curr_light = 0; curr_light < max_lights; curr_light++)
			{
				// is this light active
				if (lights[curr_light].state == LIGHTV1_STATE_OFF)
					continue;

				//Write_Error("\nprocessing light %d", curr_light);

				// what kind of light are we dealing with
				if (lights[curr_light].attr & LIGHTV1_ATTR_AMBIENT) ///////////////////////////////
				{
					//Write_Error("\nEntering ambient light....");

					// simply multiply each channel against the color of the 
					// polygon then divide by 256 to scale back to 0..255
					// use a shift in real life!!! >> 8
					ri = ((lights[curr_light].c_ambient.r * r_base) / 256);
					gi = ((lights[curr_light].c_ambient.g * g_base) / 256);
					bi = ((lights[curr_light].c_ambient.b * b_base) / 256);

					// ambient light has the same affect on each vertex
					r_sum0 += ri;
					g_sum0 += gi;
					b_sum0 += bi;

					r_sum1 += ri;
					g_sum1 += gi;
					b_sum1 += bi;

					r_sum2 += ri;
					g_sum2 += gi;
					b_sum2 += bi;

					// there better only be one ambient light!
					//Write_Error("\nexiting ambient ,sums rgb0[%d, %d, %d], rgb1[%d,%d,%d], rgb2[%d,%d,%d]", r_sum0, g_sum0, b_sum0,  r_sum1, g_sum1, b_sum1,  r_sum2, g_sum2, b_sum2);

				} // end if
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_INFINITE) /////////////////////////////////
				{
					//Write_Error("\nentering infinite light...");

					// infinite lighting, we need the surface normal, and the direction
					// of the light source

					// no longer need to compute normal or length, we already have the vertex normal
					// and it's length is 1.0  
					// ....

					// ok, recalling the lighting model for infinite lights
					// I(d)dir = I0dir * Cldir
					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles

					// need to perform lighting for each vertex (lots of redundant math, optimize later!)

					//Write_Error("\nv0=[%f, %f, %f]=%f, v1=[%f, %f, %f]=%f, v2=[%f, %f, %f]=%f",
					// curr_poly->tvlist[0].n.x, curr_poly->tvlist[0].n.y,curr_poly->tvlist[0].n.z, VECTOR4D_Length(&curr_poly->tvlist[0].n),
					// curr_poly->tvlist[1].n.x, curr_poly->tvlist[1].n.y,curr_poly->tvlist[1].n.z, VECTOR4D_Length(&curr_poly->tvlist[1].n),
					// curr_poly->tvlist[2].n.x, curr_poly->tvlist[2].n.y,curr_poly->tvlist[2].n.z, VECTOR4D_Length(&curr_poly->tvlist[2].n) );

					// vertex 0
					dp = VECTOR4D_Dot(&obj->vlist_trans[vindex_0].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						i = 128 * dp;
						r_sum0 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum0 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum0 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if

					// vertex 1
					dp = VECTOR4D_Dot(&obj->vlist_trans[vindex_1].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						i = 128 * dp;
						r_sum1 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum1 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum1 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if

					// vertex 2
					dp = VECTOR4D_Dot(&obj->vlist_trans[vindex_2].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						i = 128 * dp;
						r_sum2 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum2 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum2 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if

					//Write_Error("\nexiting infinite, color sums rgb0[%d, %d, %d], rgb1[%d,%d,%d], rgb2[%d,%d,%d]", r_sum0, g_sum0, b_sum0,  r_sum1, g_sum1, b_sum1,  r_sum2, g_sum2, b_sum2);

				} // end if infinite light
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_POINT) //////////////////////////////////////
				{
					// perform point light computations
					// light model for point light is once again:
					//              I0point * Clpoint
					//  I(d)point = ___________________
					//              kc +  kl*d + kq*d2              
					//
					//  Where d = |p - s|
					// thus it's almost identical to the infinite light, but attenuates as a function
					// of distance from the point source to the surface point being lit

					// .. normal already in vertex

					//Write_Error("\nEntering point light....");

					// compute vector from surface to light
					VECTOR4D_Build(&obj->vlist_trans[vindex_0].v, &lights[curr_light].pos, &l);

					// compute distance and attenuation
					dist = VECTOR4D_Length_Fast2(&l);

					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles

					// perform the calculation for all 3 vertices

					// vertex 0
					dp = VECTOR4D_Dot(&obj->vlist_trans[vindex_0].n, &l);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 128 * dp / (dist * atten);

						r_sum0 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum0 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum0 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if


					// vertex 1
					dp = VECTOR4D_Dot(&obj->vlist_trans[vindex_1].n, &l);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 128 * dp / (dist * atten);

						r_sum1 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum1 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum1 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if

					// vertex 2
					dp = VECTOR4D_Dot(&obj->vlist_trans[vindex_2].n, &l);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 128 * dp / (dist * atten);

						r_sum2 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum2 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum2 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if

					//Write_Error("\nexiting point light, rgb0[%d, %d, %d], rgb1[%d,%d,%d], rgb2[%d,%d,%d]", r_sum0, g_sum0, b_sum0,  r_sum1, g_sum1, b_sum1, r_sum2, g_sum2, b_sum2);

				} // end if point
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_SPOTLIGHT1) ///////////////////////////////////////
				{
					// perform spotlight/point computations simplified model that uses
					// point light WITH a direction to simulate a spotlight
					// light model for point light is once again:
					//              I0point * Clpoint
					//  I(d)point = ___________________
					//              kc +  kl*d + kq*d2              
					//
					//  Where d = |p - s|
					// thus it's almost identical to the infinite light, but attenuates as a function
					// of distance from the point source to the surface point being lit

					//Write_Error("\nentering spotlight1....");

					// .. normal is already computed

					// compute vector from surface to light
					VECTOR4D_Build(&obj->vlist_trans[vindex_0].v, &lights[curr_light].pos, &l);

					// compute distance and attenuation
					dist = VECTOR4D_Length_Fast2(&l);

					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles

					// note that I use the direction of the light here rather than a the vector to the light
					// thus we are taking orientation into account which is similar to the spotlight model

					// vertex 0
					dp = VECTOR4D_Dot(&obj->vlist_trans[vindex_0].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 128 * dp / (atten);

						r_sum0 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum0 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum0 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if

					// vertex 1
					dp = VECTOR4D_Dot(&obj->vlist_trans[vindex_1].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 128 * dp / (atten);

						r_sum1 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum1 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum1 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end i

					// vertex 2
					dp = VECTOR4D_Dot(&obj->vlist_trans[vindex_2].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 128 * dp / (atten);

						r_sum2 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum2 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum2 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end i

					//Write_Error("\nexiting spotlight1, sums rgb0[%d, %d, %d], rgb1[%d,%d,%d], rgb2[%d,%d,%d]", r_sum0, g_sum0, b_sum0,  r_sum1, g_sum1, b_sum1,  r_sum2, g_sum2, b_sum2);

				} // end if spotlight1
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_SPOTLIGHT2) // simple version //////////////////////////
				{
					// perform spot light computations
					// light model for spot light simple version is once again:
					//         	     I0spotlight * Clspotlight * MAX( (l . s), 0)^pf                     
					// I(d)spotlight = __________________________________________      
					//               		 kc + kl*d + kq*d2        
					// Where d = |p - s|, and pf = power factor

					// thus it's almost identical to the point, but has the extra term in the numerator
					// relating the angle between the light source and the point on the surface

					// .. already have normals and length are 1.0

					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles

					//Write_Error("\nEntering spotlight2...");

					// tons of redundant math here! lots to optimize later!

					// vertex 0
					dp = VECTOR4D_Dot(&obj->vlist_trans[vindex_0].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						// compute vector from light to surface (different from l which IS the light dir)
						VECTOR4D_Build(&lights[curr_light].pos, &obj->vlist_trans[vindex_0].v, &s);

						// compute length of s (distance to light source) to normalize s for lighting calc
						dists = VECTOR4D_Length_Fast2(&s);

						// compute spot light term (s . l)
						float dpsl = VECTOR4D_Dot(&s, &lights[curr_light].dir) / dists;

						// proceed only if term is positive
						if (dpsl > 0)
						{
							// compute attenuation
							atten = (lights[curr_light].kc + lights[curr_light].kl*dists + lights[curr_light].kq*dists*dists);

							// for speed reasons, pf exponents that are less that 1.0 are out of the question, and exponents
							// must be integral
							float dpsl_exp = dpsl;

							// exponentiate for positive integral powers
							for (int e_index = 1; e_index < (int)lights[curr_light].pf; e_index++)
								dpsl_exp *= dpsl;

							// now dpsl_exp holds (dpsl)^pf power which is of course (s . l)^pf 

							i = 128 * dp * dpsl_exp / (atten);

							r_sum0 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
							g_sum0 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
							b_sum0 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);

						} // end if

					} // end if

					// vertex 1
					dp = VECTOR4D_Dot(&obj->vlist_trans[vindex_1].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						// compute vector from light to surface (different from l which IS the light dir)
						VECTOR4D_Build(&lights[curr_light].pos, &obj->vlist_trans[vindex_1].v, &s);

						// compute length of s (distance to light source) to normalize s for lighting calc
						dists = VECTOR4D_Length_Fast2(&s);

						// compute spot light term (s . l)
						float dpsl = VECTOR4D_Dot(&s, &lights[curr_light].dir) / dists;

						// proceed only if term is positive
						if (dpsl > 0)
						{
							// compute attenuation
							atten = (lights[curr_light].kc + lights[curr_light].kl*dists + lights[curr_light].kq*dists*dists);

							// for speed reasons, pf exponents that are less that 1.0 are out of the question, and exponents
							// must be integral
							float dpsl_exp = dpsl;

							// exponentiate for positive integral powers
							for (int e_index = 1; e_index < (int)lights[curr_light].pf; e_index++)
								dpsl_exp *= dpsl;

							// now dpsl_exp holds (dpsl)^pf power which is of course (s . l)^pf 

							i = 128 * dp * dpsl_exp / (atten);

							r_sum1 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
							g_sum1 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
							b_sum1 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);

						} // end if

					} // end if

					// vertex 2
					dp = VECTOR4D_Dot(&obj->vlist_trans[vindex_2].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						// compute vector from light to surface (different from l which IS the light dir)
						VECTOR4D_Build(&lights[curr_light].pos, &obj->vlist_trans[vindex_2].v, &s);

						// compute length of s (distance to light source) to normalize s for lighting calc
						dists = VECTOR4D_Length_Fast2(&s);

						// compute spot light term (s . l)
						float dpsl = VECTOR4D_Dot(&s, &lights[curr_light].dir) / dists;

						// proceed only if term is positive
						if (dpsl > 0)
						{
							// compute attenuation
							atten = (lights[curr_light].kc + lights[curr_light].kl*dists + lights[curr_light].kq*dists*dists);

							// for speed reasons, pf exponents that are less that 1.0 are out of the question, and exponents
							// must be integral
							float dpsl_exp = dpsl;

							// exponentiate for positive integral powers
							for (int e_index = 1; e_index < (int)lights[curr_light].pf; e_index++)
								dpsl_exp *= dpsl;

							// now dpsl_exp holds (dpsl)^pf power which is of course (s . l)^pf 

							i = 128 * dp * dpsl_exp / (atten);

							r_sum2 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
							g_sum2 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
							b_sum2 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
						} // end if

					} // end if

					//Write_Error("\nexiting spotlight2, sums rgb0[%d, %d, %d], rgb1[%d,%d,%d], rgb2[%d,%d,%d]", r_sum0, g_sum0, b_sum0,   r_sum1, g_sum1, b_sum1,  r_sum2, g_sum2, b_sum2);

				} // end if spot light

			} // end for light

			// make sure colors aren't out of range
			if (r_sum0 > 255) r_sum0 = 255;
			if (g_sum0 > 255) g_sum0 = 255;
			if (b_sum0 > 255) b_sum0 = 255;

			if (r_sum1 > 255) r_sum1 = 255;
			if (g_sum1 > 255) g_sum1 = 255;
			if (b_sum1 > 255) b_sum1 = 255;

			if (r_sum2 > 255) r_sum2 = 255;
			if (g_sum2 > 255) g_sum2 = 255;
			if (b_sum2 > 255) b_sum2 = 255;

			//Write_Error("\nwriting color for poly %d", poly);

			//Write_Error("\n******** final sums rgb0[%d, %d, %d], rgb1[%d,%d,%d], rgb2[%d,%d,%d]", r_sum0, g_sum0, b_sum0,  r_sum1, g_sum1, b_sum1, r_sum2, g_sum2, b_sum2);

			// write the colors
			curr_poly->lit_color[0] = _ARGB32BIT(255, r_sum0, g_sum0, b_sum0);
			curr_poly->lit_color[1] = _ARGB32BIT(255, r_sum1, g_sum1, b_sum1);
			curr_poly->lit_color[2] = _ARGB32BIT(255, r_sum2, g_sum2, b_sum2);

		} // end if
		else // assume POLY4DV2_ATTR_SHADE_MODE_CONSTANT
		{
			// emmisive shading only, do nothing
			// ...
			curr_poly->lit_color[0] = curr_poly->color;

			//Write_Error("\nentering constant shader, and exiting...");

		} // end if

	} // end for poly

	// return success
	return(1);

} // end Light_OBJECT4DV2_World16

//////////////////////////////////////////////////////////////////////////////

int Light_RENDERLIST4DV2_World16(RENDERLIST4DV2_PTR rend_list,  // list to process
	CAM4DV1_PTR cam,     // camera position
	LIGHTV1_PTR lights,  // light list (might have more than one)
	int max_lights)      // maximum lights in list
{

	// 16-bit version of function
	// function lights the entire rendering list based on the sent lights and camera. the function supports
	// constant/pure shading (emmisive), flat shading with ambient, infinite, point lights, and spot lights
	// note that this lighting function is rather brute force and simply follows the math, however
	// there are some clever integer operations that are used in scale 256 rather than going to floating
	// point, but why? floating point and ints are the same speed, HOWEVER, the conversion to and from floating
	// point can be cycle intensive, so if you can keep your calcs in ints then you can gain some speed
	// also note, type 1 spot lights are simply point lights with direction, the "cone" is more of a function
	// of the falloff due to attenuation, but they still look like spot lights
	// type 2 spot lights are implemented with the intensity having a dot product relationship with the
	// angle from the surface point to the light direction just like in the optimized model, but the pf term
	// that is used for a concentration control must be 1,2,3,.... integral and non-fractional
	// this function now performs emissive, flat, and gouraud lighting, results are stored in the 
	// lit_color[] array of each polygon

	unsigned int r_base, g_base, b_base,  // base color being lit
		r_sum, g_sum, b_sum,   // sum of lighting process over all lights
		r_sum0, g_sum0, b_sum0,
		r_sum1, g_sum1, b_sum1,
		r_sum2, g_sum2, b_sum2,
		ri, gi, bi,
		shaded_color;            // final color

	float dp,     // dot product 
		dist,   // distance from light to surface
		dists,
		i,      // general intensities
		nl,     // length of normal
		atten;  // attenuation computations

	VECTOR4D u, v, n, l, d, s; // used for cross product and light vector calculations

	//Write_Error("\nEntering lighting function");

	// for each valid poly, light it...
	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		// acquire polygon
		POLYF4DV2_PTR curr_poly = rend_list->poly_ptrs[poly];

		// light this polygon if and only if it's not clipped, not culled,
		// active, and visible
		if (!(curr_poly->state & POLY4DV2_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV2_STATE_CLIPPED) ||
			(curr_poly->state & POLY4DV2_STATE_BACKFACE) ||
			(curr_poly->state & POLY4DV2_STATE_LIT))
			continue; // move onto next poly

		//Write_Error("\npoly %d",poly);

#ifdef DEBUG_ON
		// track rendering stats
		debug_polys_lit_per_frame++;
#endif



		// set state of polygon to lit
		SET_BIT(curr_poly->state, POLY4DV2_STATE_LIT);

		// we will use the transformed polygon vertex list since the backface removal
		// only makes sense at the world coord stage further of the pipeline 

		// test the lighting mode of the polygon (use flat for flat, gouraud))
		if (curr_poly->attr & POLY4DV2_ATTR_SHADE_MODE_FLAT)
		{
			//Write_Error("\nEntering Flat Shader");

			// step 1: extract the base color out in RGB mode
			// assume 565 format
			//_RGB565FROM16BIT(curr_poly->color, &r_base, &g_base, &b_base);

			//// scale to 8 bit 
			//r_base <<= 3;
			//g_base <<= 2;
			//b_base <<= 3;

			ARGBV1 rgba;
			rgba.argb = curr_poly->color;

			r_base = rgba.r;
			g_base = rgba.g;
			b_base = rgba.b;

			//Write_Error("\nBase color=%d,%d,%d", r_base, g_base, b_base);

			// initialize color sum
			r_sum = 0;
			g_sum = 0;
			b_sum = 0;

			//Write_Error("\nsum color=%d,%d,%d", r_sum, g_sum, b_sum);

			// new optimization:
			// when there are multiple lights in the system we will end up performing numerous
			// redundant calculations to minimize this my strategy is to set key variables to 
			// to MAX values on each loop, then during the lighting calcs to test the vars for
			// the max value, if they are the max value then the first light that needs the math
			// will do it, and then save the information into the variable (causing it to change state
			// from an invalid number) then any other lights that need the math can use the previously
			// computed value

			// set surface normal.z to FLT_MAX to flag it as non-computed
			n.z = FLT_MAX;

			// loop thru lights
			for (int curr_light = 0; curr_light < max_lights; curr_light++)
			{
				// is this light active
				if (lights[curr_light].state == LIGHTV1_STATE_OFF)
					continue;

				//Write_Error("\nprocessing light %d",curr_light);

				// what kind of light are we dealing with
				if (lights[curr_light].attr & LIGHTV1_ATTR_AMBIENT)
				{
					//Write_Error("\nEntering ambient light...");

					// simply multiply each channel against the color of the 
					// polygon then divide by 256 to scale back to 0..255
					// use a shift in real life!!! >> 8
					r_sum += ((lights[curr_light].c_ambient.r * r_base) / 256);
					g_sum += ((lights[curr_light].c_ambient.g * g_base) / 256);
					b_sum += ((lights[curr_light].c_ambient.b * b_base) / 256);

					//Write_Error("\nambient sum=%d,%d,%d", r_sum, g_sum, b_sum);

					// there better only be one ambient light!

				} // end if
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_INFINITE) ///////////////////////////////////////////
				{
					//Write_Error("\nEntering infinite light...");

					// infinite lighting, we need the surface normal, and the direction
					// of the light source

					// test if we already computed poly normal in previous calculation
					if (n.z == FLT_MAX)
					{
						// we need to compute the normal of this polygon face, and recall
						// that the vertices are in cw order, u=p0->p1, v=p0->p2, n=uxv

						// build u, v
						VECTOR4D_Build(&curr_poly->tvlist[0].v, &curr_poly->tvlist[1].v, &u);
						VECTOR4D_Build(&curr_poly->tvlist[0].v, &curr_poly->tvlist[2].v, &v);

						// compute cross product
						VECTOR4D_Cross(&u, &v, &n);
					} // end if

					// at this point, we are almost ready, but we have to normalize the normal vector!
					// this is a key optimization we can make later, we can pre-compute the length of all polygon
					// normals, so this step can be optimized
					// compute length of normal
					//nl = VECTOR4D_Length_Fast2(&n);
					nl = curr_poly->nlength;

					// ok, recalling the lighting model for infinite lights
					// I(d)dir = I0dir * Cldir
					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles

					dp = VECTOR4D_Dot(&n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						i = 128 * dp / nl;
						r_sum += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if

					//Write_Error("\ninfinite sum=%d,%d,%d", r_sum, g_sum, b_sum);

				} // end if infinite light
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_POINT) ///////////////////////////////////////
				{
					//Write_Error("\nEntering point light...");

					// perform point light computations
					// light model for point light is once again:
					//              I0point * Clpoint
					//  I(d)point = ___________________
					//              kc +  kl*d + kq*d2              
					//
					//  Where d = |p - s|
					// thus it's almost identical to the infinite light, but attenuates as a function
					// of distance from the point source to the surface point being lit

					// test if we already computed poly normal in previous calculation
					if (n.z == FLT_MAX)
					{
						// we need to compute the normal of this polygon face, and recall
						// that the vertices are in cw order, u=p0->p1, v=p0->p2, n=uxv

						// build u, v
						VECTOR4D_Build(&curr_poly->tvlist[0].v, &curr_poly->tvlist[1].v, &u);
						VECTOR4D_Build(&curr_poly->tvlist[0].v, &curr_poly->tvlist[2].v, &v);

						// compute cross product
						VECTOR4D_Cross(&u, &v, &n);
					} // end if

					// at this point, we are almost ready, but we have to normalize the normal vector!
					// this is a key optimization we can make later, we can pre-compute the length of all polygon
					// normals, so this step can be optimized
					// compute length of normal
					//nl = VECTOR4D_Length_Fast2(&n);
					nl = curr_poly->nlength;

					// compute vector from surface to light
					VECTOR4D_Build(&curr_poly->tvlist[0].v, &lights[curr_light].pos, &l);

					// compute distance and attenuation
					dist = VECTOR4D_Length_Fast2(&l);

					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles
					dp = VECTOR4D_Dot(&n, &l);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 128 * dp / (nl * dist * atten);

						r_sum += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if


					//Write_Error("\npoint sum=%d,%d,%d",r_sum,g_sum,b_sum);

				} // end if point
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_SPOTLIGHT1) ////////////////////////////////////
				{
					//Write_Error("\nentering spot light1...");

					// perform spotlight/point computations simplified model that uses
					// point light WITH a direction to simulate a spotlight
					// light model for point light is once again:
					//              I0point * Clpoint
					//  I(d)point = ___________________
					//              kc +  kl*d + kq*d2              
					//
					//  Where d = |p - s|
					// thus it's almost identical to the infinite light, but attenuates as a function
					// of distance from the point source to the surface point being lit

					// test if we already computed poly normal in previous calculation
					if (n.z == FLT_MAX)
					{
						// we need to compute the normal of this polygon face, and recall
						// that the vertices are in cw order, u=p0->p1, v=p0->p2, n=uxv

						// build u, v
						VECTOR4D_Build(&curr_poly->tvlist[0].v, &curr_poly->tvlist[1].v, &u);
						VECTOR4D_Build(&curr_poly->tvlist[0].v, &curr_poly->tvlist[2].v, &v);

						// compute cross product
						VECTOR4D_Cross(&u, &v, &n);
					} // end if

					// at this point, we are almost ready, but we have to normalize the normal vector!
					// this is a key optimization we can make later, we can pre-compute the length of all polygon
					// normals, so this step can be optimized
					// compute length of normal
					//nl = VECTOR4D_Length_Fast2(&n);
					nl = curr_poly->nlength;

					// compute vector from surface to light
					VECTOR4D_Build(&curr_poly->tvlist[0].v, &lights[curr_light].pos, &l);

					// compute distance and attenuation
					dist = VECTOR4D_Length_Fast2(&l);

					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles

					// note that I use the direction of the light here rather than a the vector to the light
					// thus we are taking orientation into account which is similar to the spotlight model
					dp = VECTOR4D_Dot(&n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 128 * dp / (nl * atten);

						r_sum += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if

					//Write_Error("\nspotlight sum=%d,%d,%d",r_sum, g_sum, b_sum);

				} // end if spotlight1
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_SPOTLIGHT2) // simple version ////////////////////
				{
					//Write_Error("\nEntering spotlight2 ...");

					// perform spot light computations
					// light model for spot light simple version is once again:
					//         	     I0spotlight * Clspotlight * MAX( (l . s), 0)^pf                     
					// I(d)spotlight = __________________________________________      
					//               		 kc + kl*d + kq*d2        
					// Where d = |p - s|, and pf = power factor

					// thus it's almost identical to the point, but has the extra term in the numerator
					// relating the angle between the light source and the point on the surface

					// test if we already computed poly normal in previous calculation
					if (n.z == FLT_MAX)
					{
						// we need to compute the normal of this polygon face, and recall
						// that the vertices are in cw order, u=p0->p1, v=p0->p2, n=uxv

						// build u, v
						VECTOR4D_Build(&curr_poly->tvlist[0].v, &curr_poly->tvlist[1].v, &u);
						VECTOR4D_Build(&curr_poly->tvlist[0].v, &curr_poly->tvlist[2].v, &v);

						// compute cross product
						VECTOR4D_Cross(&u, &v, &n);
					} // end if

					// at this point, we are almost ready, but we have to normalize the normal vector!
					// this is a key optimization we can make later, we can pre-compute the length of all polygon
					// normals, so this step can be optimized
					// compute length of normal
					//nl = VECTOR4D_Length_Fast2(&n);
					nl = curr_poly->nlength;

					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles
					dp = VECTOR4D_Dot(&n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						// compute vector from light to surface (different from l which IS the light dir)
						VECTOR4D_Build(&lights[curr_light].pos, &curr_poly->tvlist[0].v, &s);

						// compute length of s (distance to light source) to normalize s for lighting calc
						dists = VECTOR4D_Length_Fast2(&s);

						// compute spot light term (s . l)
						float dpsl = VECTOR4D_Dot(&s, &lights[curr_light].dir) / dists;

						// proceed only if term is positive
						if (dpsl > 0)
						{
							// compute attenuation
							atten = (lights[curr_light].kc + lights[curr_light].kl*dists + lights[curr_light].kq*dists*dists);

							// for speed reasons, pf exponents that are less that 1.0 are out of the question, and exponents
							// must be integral
							float dpsl_exp = dpsl;

							// exponentiate for positive integral powers
							for (int e_index = 1; e_index < (int)lights[curr_light].pf; e_index++)
								dpsl_exp *= dpsl;

							// now dpsl_exp holds (dpsl)^pf power which is of course (s . l)^pf 

							i = 128 * dp * dpsl_exp / (nl * atten);

							r_sum += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
							g_sum += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
							b_sum += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);

						} // end if

					} // end if

					//Write_Error("\nSpotlight sum=%d,%d,%d",r_sum, g_sum, b_sum);

				} // end if spot light

			} // end for light

			// make sure colors aren't out of range
			if (r_sum > 255) r_sum = 255;
			if (g_sum > 255) g_sum = 255;
			if (b_sum > 255) b_sum = 255;

			//Write_Error("\nWriting final values to polygon %d = %d,%d,%d", poly, r_sum, g_sum, b_sum);

			// write the color over current color
			curr_poly->lit_color[0] = _ARGB32BIT(255, r_sum, g_sum, b_sum);

		} // end if
		else
		if (curr_poly->attr & POLY4DV2_ATTR_SHADE_MODE_GOURAUD) /////////////////////////////////
		{
			// gouraud shade, unfortunetly at this point in the pipeline, we have lost the original
			// mesh, and only have triangles, thus, many triangles will share the same vertices and
			// they will get lit 2x since we don't have any way to tell this, alas, performing lighting
			// at the object level is a better idea when gouraud shading is performed since the 
			// commonality of vertices is still intact, in any case, lighting here is similar to polygon
			// flat shaded, but we do it 3 times, once for each vertex, additionally there are lots
			// of opportunities for optimization, but I am going to lay off them for now, so the code
			// is intelligible, later we will optimize

			//Write_Error("\nEntering gouraud shader...");

			// step 1: extract the base color out in RGB mode
			// assume 565 format
			//_RGB565FROM16BIT(curr_poly->color, &r_base, &g_base, &b_base);

			//// scale to 8 bit 
			//r_base <<= 3;
			//g_base <<= 2;
			//b_base <<= 3;

			ARGBV1 rgba;
			rgba.argb = curr_poly->color;

			r_base = rgba.r;
			g_base = rgba.g;
			b_base = rgba.b;

			//Write_Error("\nBase color=%d, %d, %d", r_base, g_base, b_base);

			// initialize color sum(s) for vertices
			r_sum0 = 0;
			g_sum0 = 0;
			b_sum0 = 0;

			r_sum1 = 0;
			g_sum1 = 0;
			b_sum1 = 0;

			r_sum2 = 0;
			g_sum2 = 0;
			b_sum2 = 0;

			//Write_Error("\nColor sums rgb0[%d, %d, %d], rgb1[%d,%d,%d], rgb2[%d,%d,%d]", r_sum0, g_sum0, b_sum0,   r_sum1, g_sum1, b_sum1, r_sum2, g_sum2, b_sum2);

			// new optimization:
			// when there are multiple lights in the system we will end up performing numerous
			// redundant calculations to minimize this my strategy is to set key variables to 
			// to MAX values on each loop, then during the lighting calcs to test the vars for
			// the max value, if they are the max value then the first light that needs the math
			// will do it, and then save the information into the variable (causing it to change state
			// from an invalid number) then any other lights that need the math can use the previously
			// computed value, however, since we already have the normals, not much here to cache on
			// a large scale, but small scale stuff is there, however, we will optimize those later

			// loop thru lights
			for (int curr_light = 0; curr_light < max_lights; curr_light++)
			{
				// is this light active
				if (lights[curr_light].state == LIGHTV1_STATE_OFF)
					continue;

				//Write_Error("\nprocessing light %d", curr_light);

				// what kind of light are we dealing with
				if (lights[curr_light].attr & LIGHTV1_ATTR_AMBIENT) ///////////////////////////////
				{
					//Write_Error("\nEntering ambient light....");

					// simply multiply each channel against the color of the 
					// polygon then divide by 256 to scale back to 0..255
					// use a shift in real life!!! >> 8
					ri = ((lights[curr_light].c_ambient.r * r_base) / 256);
					gi = ((lights[curr_light].c_ambient.g * g_base) / 256);
					bi = ((lights[curr_light].c_ambient.b * b_base) / 256);

					// ambient light has the same affect on each vertex
					r_sum0 += ri;
					g_sum0 += gi;
					b_sum0 += bi;

					r_sum1 += ri;
					g_sum1 += gi;
					b_sum1 += bi;

					r_sum2 += ri;
					g_sum2 += gi;
					b_sum2 += bi;

					// there better only be one ambient light!
					//Write_Error("\nexiting ambient ,sums rgb0[%d, %d, %d], rgb1[%d,%d,%d], rgb2[%d,%d,%d]", r_sum0, g_sum0, b_sum0,  r_sum1, g_sum1, b_sum1,  r_sum2, g_sum2, b_sum2);

				} // end if
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_INFINITE) /////////////////////////////////
				{
					//Write_Error("\nentering infinite light...");

					// infinite lighting, we need the surface normal, and the direction
					// of the light source

					// no longer need to compute normal or length, we already have the vertex normal
					// and it's length is 1.0  
					// ....

					// ok, recalling the lighting model for infinite lights
					// I(d)dir = I0dir * Cldir
					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles

					// need to perform lighting for each vertex (lots of redundant math, optimize later!)

					//Write_Error("\nv0=[%f, %f, %f]=%f, v1=[%f, %f, %f]=%f, v2=[%f, %f, %f]=%f",
					// curr_poly->tvlist[0].n.x, curr_poly->tvlist[0].n.y,curr_poly->tvlist[0].n.z, VECTOR4D_Length(&curr_poly->tvlist[0].n),
					// curr_poly->tvlist[1].n.x, curr_poly->tvlist[1].n.y,curr_poly->tvlist[1].n.z, VECTOR4D_Length(&curr_poly->tvlist[1].n),
					// curr_poly->tvlist[2].n.x, curr_poly->tvlist[2].n.y,curr_poly->tvlist[2].n.z, VECTOR4D_Length(&curr_poly->tvlist[2].n) );

					// vertex 0
					dp = VECTOR4D_Dot(&curr_poly->tvlist[0].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						i = 128 * dp;
						r_sum0 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum0 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum0 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if

					// vertex 1
					dp = VECTOR4D_Dot(&curr_poly->tvlist[1].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						i = 128 * dp;
						r_sum1 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum1 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum1 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if

					// vertex 2
					dp = VECTOR4D_Dot(&curr_poly->tvlist[2].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						i = 128 * dp;
						r_sum2 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum2 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum2 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if

					//Write_Error("\nexiting infinite, color sums rgb0[%d, %d, %d], rgb1[%d,%d,%d], rgb2[%d,%d,%d]", r_sum0, g_sum0, b_sum0,  r_sum1, g_sum1, b_sum1,  r_sum2, g_sum2, b_sum2);

				} // end if infinite light
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_POINT) //////////////////////////////////////
				{
					// perform point light computations
					// light model for point light is once again:
					//              I0point * Clpoint
					//  I(d)point = ___________________
					//              kc +  kl*d + kq*d2              
					//
					//  Where d = |p - s|
					// thus it's almost identical to the infinite light, but attenuates as a function
					// of distance from the point source to the surface point being lit

					// .. normal already in vertex

					//Write_Error("\nEntering point light....");

					// compute vector from surface to light
					VECTOR4D_Build(&curr_poly->tvlist[0].v, &lights[curr_light].pos, &l);

					// compute distance and attenuation
					dist = VECTOR4D_Length_Fast2(&l);

					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles

					// perform the calculation for all 3 vertices

					// vertex 0
					dp = VECTOR4D_Dot(&curr_poly->tvlist[0].n, &l);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 128 * dp / (dist * atten);

						r_sum0 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum0 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum0 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if


					// vertex 1
					dp = VECTOR4D_Dot(&curr_poly->tvlist[1].n, &l);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 128 * dp / (dist * atten);

						r_sum1 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum1 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum1 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if

					// vertex 2
					dp = VECTOR4D_Dot(&curr_poly->tvlist[2].n, &l);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 128 * dp / (dist * atten);

						r_sum2 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum2 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum2 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if

					//Write_Error("\nexiting point light, rgb0[%d, %d, %d], rgb1[%d,%d,%d], rgb2[%d,%d,%d]", r_sum0, g_sum0, b_sum0,  r_sum1, g_sum1, b_sum1, r_sum2, g_sum2, b_sum2);

				} // end if point
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_SPOTLIGHT1) ///////////////////////////////////////
				{
					// perform spotlight/point computations simplified model that uses
					// point light WITH a direction to simulate a spotlight
					// light model for point light is once again:
					//              I0point * Clpoint
					//  I(d)point = ___________________
					//              kc +  kl*d + kq*d2              
					//
					//  Where d = |p - s|
					// thus it's almost identical to the infinite light, but attenuates as a function
					// of distance from the point source to the surface point being lit

					//Write_Error("\nentering spotlight1....");

					// .. normal is already computed

					// compute vector from surface to light
					VECTOR4D_Build(&curr_poly->tvlist[0].v, &lights[curr_light].pos, &l);

					// compute distance and attenuation
					dist = VECTOR4D_Length_Fast2(&l);

					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles

					// note that I use the direction of the light here rather than a the vector to the light
					// thus we are taking orientation into account which is similar to the spotlight model

					// vertex 0
					dp = VECTOR4D_Dot(&curr_poly->tvlist[0].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 128 * dp / (atten);

						r_sum0 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum0 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum0 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end if

					// vertex 1
					dp = VECTOR4D_Dot(&curr_poly->tvlist[1].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 128 * dp / (atten);

						r_sum1 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum1 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum1 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end i

					// vertex 2
					dp = VECTOR4D_Dot(&curr_poly->tvlist[2].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						atten = (lights[curr_light].kc + lights[curr_light].kl*dist + lights[curr_light].kq*dist*dist);

						i = 128 * dp / (atten);

						r_sum2 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
						g_sum2 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
						b_sum2 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
					} // end i

					//Write_Error("\nexiting spotlight1, sums rgb0[%d, %d, %d], rgb1[%d,%d,%d], rgb2[%d,%d,%d]", r_sum0, g_sum0, b_sum0,  r_sum1, g_sum1, b_sum1,  r_sum2, g_sum2, b_sum2);

				} // end if spotlight1
				else
				if (lights[curr_light].attr & LIGHTV1_ATTR_SPOTLIGHT2) // simple version //////////////////////////
				{
					// perform spot light computations
					// light model for spot light simple version is once again:
					//         	     I0spotlight * Clspotlight * MAX( (l . s), 0)^pf                     
					// I(d)spotlight = __________________________________________      
					//               		 kc + kl*d + kq*d2        
					// Where d = |p - s|, and pf = power factor

					// thus it's almost identical to the point, but has the extra term in the numerator
					// relating the angle between the light source and the point on the surface

					// .. already have normals and length are 1.0

					// and for the diffuse model
					// Itotald =   Rsdiffuse*Idiffuse * (n . l)
					// so we basically need to multiple it all together
					// notice the scaling by 128, I want to avoid floating point calculations, not because they 
					// are slower, but the conversion to and from cost cycles

					//Write_Error("\nEntering spotlight2...");

					// tons of redundant math here! lots to optimize later!

					// vertex 0
					dp = VECTOR4D_Dot(&curr_poly->tvlist[0].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						// compute vector from light to surface (different from l which IS the light dir)
						VECTOR4D_Build(&lights[curr_light].pos, &curr_poly->tvlist[0].v, &s);

						// compute length of s (distance to light source) to normalize s for lighting calc
						dists = VECTOR4D_Length_Fast2(&s);

						// compute spot light term (s . l)
						float dpsl = VECTOR4D_Dot(&s, &lights[curr_light].dir) / dists;

						// proceed only if term is positive
						if (dpsl > 0)
						{
							// compute attenuation
							atten = (lights[curr_light].kc + lights[curr_light].kl*dists + lights[curr_light].kq*dists*dists);

							// for speed reasons, pf exponents that are less that 1.0 are out of the question, and exponents
							// must be integral
							float dpsl_exp = dpsl;

							// exponentiate for positive integral powers
							for (int e_index = 1; e_index < (int)lights[curr_light].pf; e_index++)
								dpsl_exp *= dpsl;

							// now dpsl_exp holds (dpsl)^pf power which is of course (s . l)^pf 

							i = 128 * dp * dpsl_exp / (atten);

							r_sum0 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
							g_sum0 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
							b_sum0 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);

						} // end if

					} // end if

					// vertex 1
					dp = VECTOR4D_Dot(&curr_poly->tvlist[1].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						// compute vector from light to surface (different from l which IS the light dir)
						VECTOR4D_Build(&lights[curr_light].pos, &curr_poly->tvlist[1].v, &s);

						// compute length of s (distance to light source) to normalize s for lighting calc
						dists = VECTOR4D_Length_Fast2(&s);

						// compute spot light term (s . l)
						float dpsl = VECTOR4D_Dot(&s, &lights[curr_light].dir) / dists;

						// proceed only if term is positive
						if (dpsl > 0)
						{
							// compute attenuation
							atten = (lights[curr_light].kc + lights[curr_light].kl*dists + lights[curr_light].kq*dists*dists);

							// for speed reasons, pf exponents that are less that 1.0 are out of the question, and exponents
							// must be integral
							float dpsl_exp = dpsl;

							// exponentiate for positive integral powers
							for (int e_index = 1; e_index < (int)lights[curr_light].pf; e_index++)
								dpsl_exp *= dpsl;

							// now dpsl_exp holds (dpsl)^pf power which is of course (s . l)^pf 

							i = 128 * dp * dpsl_exp / (atten);

							r_sum1 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
							g_sum1 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
							b_sum1 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);

						} // end if

					} // end if

					// vertex 2
					dp = VECTOR4D_Dot(&curr_poly->tvlist[2].n, &lights[curr_light].dir);

					// only add light if dp > 0
					if (dp > 0)
					{
						// compute vector from light to surface (different from l which IS the light dir)
						VECTOR4D_Build(&lights[curr_light].pos, &curr_poly->tvlist[2].v, &s);

						// compute length of s (distance to light source) to normalize s for lighting calc
						dists = VECTOR4D_Length_Fast2(&s);

						// compute spot light term (s . l)
						float dpsl = VECTOR4D_Dot(&s, &lights[curr_light].dir) / dists;

						// proceed only if term is positive
						if (dpsl > 0)
						{
							// compute attenuation
							atten = (lights[curr_light].kc + lights[curr_light].kl*dists + lights[curr_light].kq*dists*dists);

							// for speed reasons, pf exponents that are less that 1.0 are out of the question, and exponents
							// must be integral
							float dpsl_exp = dpsl;

							// exponentiate for positive integral powers
							for (int e_index = 1; e_index < (int)lights[curr_light].pf; e_index++)
								dpsl_exp *= dpsl;

							// now dpsl_exp holds (dpsl)^pf power which is of course (s . l)^pf 

							i = 128 * dp * dpsl_exp / (atten);

							r_sum2 += (lights[curr_light].c_diffuse.r * r_base * i) / (256 * 128);
							g_sum2 += (lights[curr_light].c_diffuse.g * g_base * i) / (256 * 128);
							b_sum2 += (lights[curr_light].c_diffuse.b * b_base * i) / (256 * 128);
						} // end if

					} // end if

					//Write_Error("\nexiting spotlight2, sums rgb0[%d, %d, %d], rgb1[%d,%d,%d], rgb2[%d,%d,%d]", r_sum0, g_sum0, b_sum0,   r_sum1, g_sum1, b_sum1,  r_sum2, g_sum2, b_sum2);

				} // end if spot light

			} // end for light

			// make sure colors aren't out of range
			if (r_sum0 > 255) r_sum0 = 255;
			if (g_sum0 > 255) g_sum0 = 255;
			if (b_sum0 > 255) b_sum0 = 255;

			if (r_sum1 > 255) r_sum1 = 255;
			if (g_sum1 > 255) g_sum1 = 255;
			if (b_sum1 > 255) b_sum1 = 255;

			if (r_sum2 > 255) r_sum2 = 255;
			if (g_sum2 > 255) g_sum2 = 255;
			if (b_sum2 > 255) b_sum2 = 255;

			//Write_Error("\nwriting color for poly %d", poly);

			//Write_Error("\n******** final sums rgb0[%d, %d, %d], rgb1[%d,%d,%d], rgb2[%d,%d,%d]", r_sum0, g_sum0, b_sum0,  r_sum1, g_sum1, b_sum1, r_sum2, g_sum2, b_sum2);

			// write the colors
			curr_poly->lit_color[0] = _ARGB32BIT(255, r_sum0, g_sum0, b_sum0);
			curr_poly->lit_color[1] = _ARGB32BIT(255, r_sum1, g_sum1, b_sum1);
			curr_poly->lit_color[2] = _ARGB32BIT(255, r_sum2, g_sum2, b_sum2);

		} // end if
		else // assume POLY4DV2_ATTR_SHADE_MODE_CONSTANT
		{
			// emmisive shading only, do nothing
			// ...
			curr_poly->lit_color[0] = curr_poly->color;

			//Write_Error("\nentering constant shader, and exiting...");

		} // end if

	} // end for poly

	// return success
	return(1);

} // end Light_RENDERLIST4DV2_World16

/////////////////////////////////////////////////////////////////////////

float Compute_OBJECT4DV2_Radius(OBJECT4DV2_PTR obj)
{
	// this function computes the average and maximum radius for 
	// sent object and opdates the object data for the "current frame"
	// it's up to the caller to make sure Set_Frame() for this object
	// has been called to set the object up properly

	// reset incase there's any residue
	obj->avg_radius[obj->curr_frame] = 0;
	obj->max_radius[obj->curr_frame] = 0;

	// loop thru and compute radius
	for (int vertex = 0; vertex < obj->num_vertices; vertex++)
	{
		// update the average and maximum radius
		float dist_to_vertex =
			sqrt(obj->vlist_local[vertex].x*obj->vlist_local[vertex].x +
			obj->vlist_local[vertex].y*obj->vlist_local[vertex].y +
			obj->vlist_local[vertex].z*obj->vlist_local[vertex].z);

		// accumulate total radius
		obj->avg_radius[obj->curr_frame] += dist_to_vertex;

		// update maximum radius   
		if (dist_to_vertex > obj->max_radius[obj->curr_frame])
			obj->max_radius[obj->curr_frame] = dist_to_vertex;

	} // end for vertex

	// finallize average radius computation
	obj->avg_radius[obj->curr_frame] /= obj->num_vertices;

	// return max radius of frame 0
	return(obj->max_radius[0]);

} // end Compute_OBJECT4DV2_Radius

//////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////

void Reset_RENDERLIST4DV2(RENDERLIST4DV2_PTR rend_list)
{
	// this function intializes and resets the sent render list and
	// redies it for polygons/faces to be inserted into it
	// note that the render list in this version is composed
	// of an array FACE4DV1 pointer objects, you call this
	// function each frame

	// since we are tracking the number of polys in the
	// list via num_polys we can set it to 0
	// but later we will want a more robust scheme if
	// we generalize the linked list more and disconnect
	// it from the polygon pointer list
	rend_list->num_polys = 0; // that was hard!

}  // end Reset_RENDERLIST4DV2

////////////////////////////////////////////////////////////////

void Draw_RENDERLIST4DV2_Wire16(RENDERLIST4DV2_PTR rend_list,
	UCHAR *video_buffer, int lpitch)
{
	// this function "executes" the render list or in other words
	// draws all the faces in the list in wire frame 16bit mode
	// note there is no need to sort wire frame polygons

	// at this point, all we have is a list of polygons and it's time
	// to draw them
	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(rend_list->poly_ptrs[poly]->state & POLY4DV2_STATE_ACTIVE) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV2_STATE_CLIPPED) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV2_STATE_BACKFACE))
			continue; // move onto next poly

		// draw the triangle edge one, note that clipping was already set up
		// by 2D initialization, so line clipper will clip all polys out
		// of the 2D screen/window boundary
		Draw_Clip_Line16(rend_list->poly_ptrs[poly]->tvlist[0].x,
			rend_list->poly_ptrs[poly]->tvlist[0].y,
			rend_list->poly_ptrs[poly]->tvlist[1].x,
			rend_list->poly_ptrs[poly]->tvlist[1].y,
			rend_list->poly_ptrs[poly]->lit_color[0],
			video_buffer, lpitch);

		Draw_Clip_Line16(rend_list->poly_ptrs[poly]->tvlist[1].x,
			rend_list->poly_ptrs[poly]->tvlist[1].y,
			rend_list->poly_ptrs[poly]->tvlist[2].x,
			rend_list->poly_ptrs[poly]->tvlist[2].y,
			rend_list->poly_ptrs[poly]->lit_color[0],
			video_buffer, lpitch);

		Draw_Clip_Line16(rend_list->poly_ptrs[poly]->tvlist[2].x,
			rend_list->poly_ptrs[poly]->tvlist[2].y,
			rend_list->poly_ptrs[poly]->tvlist[0].x,
			rend_list->poly_ptrs[poly]->tvlist[0].y,
			rend_list->poly_ptrs[poly]->lit_color[0],
			video_buffer, lpitch);

		// track rendering stats
#ifdef DEBUG_ON
		debug_polys_rendered_per_frame++;
#endif
	} // end for poly

} // end Draw_RENDERLIST4DV2_Wire16

/////////////////////////////////////////////////////////////

void Draw_RENDERLIST4DV2_Wire(RENDERLIST4DV2_PTR rend_list,
	UCHAR *video_buffer, int lpitch)
{
	// this function "executes" the render list or in other words
	// draws all the faces in the list in wire frame 8bit mode
	// note there is no need to sort wire frame polygons

	// at this point, all we have is a list of polygons and it's time
	// to draw them
	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(rend_list->poly_ptrs[poly]->state & POLY4DV2_STATE_ACTIVE) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV2_STATE_CLIPPED) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV2_STATE_BACKFACE))
			continue; // move onto next poly

		// draw the triangle edge one, note that clipping was already set up
		// by 2D initialization, so line clipper will clip all polys out
		// of the 2D screen/window boundary
		Draw_Clip_Line(rend_list->poly_ptrs[poly]->tvlist[0].x,
			rend_list->poly_ptrs[poly]->tvlist[0].y,
			rend_list->poly_ptrs[poly]->tvlist[1].x,
			rend_list->poly_ptrs[poly]->tvlist[1].y,
			rend_list->poly_ptrs[poly]->lit_color[0],
			video_buffer, lpitch);

		Draw_Clip_Line(rend_list->poly_ptrs[poly]->tvlist[1].x,
			rend_list->poly_ptrs[poly]->tvlist[1].y,
			rend_list->poly_ptrs[poly]->tvlist[2].x,
			rend_list->poly_ptrs[poly]->tvlist[2].y,
			rend_list->poly_ptrs[poly]->lit_color[0],
			video_buffer, lpitch);

		Draw_Clip_Line(rend_list->poly_ptrs[poly]->tvlist[2].x,
			rend_list->poly_ptrs[poly]->tvlist[2].y,
			rend_list->poly_ptrs[poly]->tvlist[0].x,
			rend_list->poly_ptrs[poly]->tvlist[0].y,
			rend_list->poly_ptrs[poly]->lit_color[0],
			video_buffer, lpitch);
		// track rendering stats
#ifdef DEBUG_ON
		debug_polys_rendered_per_frame++;
#endif

	} // end for poly

} // end Draw_RENDERLIST4DV2_Wire

///////////////////////////////////////////////////////////////

void Draw_RENDERLIST4DV2_Solid16(RENDERLIST4DV2_PTR rend_list,
	UCHAR *video_buffer,
	int lpitch)
{
	// 16-bit version
	// this function "executes" the render list or in other words
	// draws all the faces in the list, the function will call the 
	// proper rasterizer based on the lighting model of the polygons


	POLYF4DV2 face; // temp face used to render polygon

	// at this point, all we have is a list of polygons and it's time
	// to draw them
	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(rend_list->poly_ptrs[poly]->state & POLY4DV2_STATE_ACTIVE) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV2_STATE_CLIPPED) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV2_STATE_BACKFACE))
			continue; // move onto next poly

		// need to test for textured first, since a textured poly can either
		// be emissive, or flat shaded, hence we need to call different
		// rasterizers    
		if (rend_list->poly_ptrs[poly]->attr & POLY4DV2_ATTR_SHADE_MODE_TEXTURE)
		{

			// set the vertices
			face.tvlist[0].x = (int)rend_list->poly_ptrs[poly]->tvlist[0].x;
			face.tvlist[0].y = (int)rend_list->poly_ptrs[poly]->tvlist[0].y;
			face.tvlist[0].u0 = (int)rend_list->poly_ptrs[poly]->tvlist[0].u0;
			face.tvlist[0].v0 = (int)rend_list->poly_ptrs[poly]->tvlist[0].v0;

			face.tvlist[1].x = (int)rend_list->poly_ptrs[poly]->tvlist[1].x;
			face.tvlist[1].y = (int)rend_list->poly_ptrs[poly]->tvlist[1].y;
			face.tvlist[1].u0 = (int)rend_list->poly_ptrs[poly]->tvlist[1].u0;
			face.tvlist[1].v0 = (int)rend_list->poly_ptrs[poly]->tvlist[1].v0;

			face.tvlist[2].x = (int)rend_list->poly_ptrs[poly]->tvlist[2].x;
			face.tvlist[2].y = (int)rend_list->poly_ptrs[poly]->tvlist[2].y;
			face.tvlist[2].u0 = (int)rend_list->poly_ptrs[poly]->tvlist[2].u0;
			face.tvlist[2].v0 = (int)rend_list->poly_ptrs[poly]->tvlist[2].v0;


			// assign the texture
			face.texture = rend_list->poly_ptrs[poly]->texture;

			// is this a plain emissive texture?
			if (rend_list->poly_ptrs[poly]->attr & POLY4DV2_ATTR_SHADE_MODE_CONSTANT)
			{
				// draw the textured triangle as emissive
				Draw_Textured_Triangle16(&face, video_buffer, lpitch);
			} // end if
			else
			{
				// draw as flat shaded
				face.lit_color[0] = rend_list->poly_ptrs[poly]->lit_color[0];
				Draw_Textured_TriangleFS16(&face, video_buffer, lpitch);
			} // end else

		} // end if      
		else
		if ((rend_list->poly_ptrs[poly]->attr & POLY4DV2_ATTR_SHADE_MODE_FLAT) ||
			(rend_list->poly_ptrs[poly]->attr & POLY4DV2_ATTR_SHADE_MODE_CONSTANT))
		{
			// draw the triangle with basic flat rasterizer
			Draw_Triangle_2D2_16(rend_list->poly_ptrs[poly]->tvlist[0].x, rend_list->poly_ptrs[poly]->tvlist[0].y,
				rend_list->poly_ptrs[poly]->tvlist[1].x, rend_list->poly_ptrs[poly]->tvlist[1].y,
				rend_list->poly_ptrs[poly]->tvlist[2].x, rend_list->poly_ptrs[poly]->tvlist[2].y,
				rend_list->poly_ptrs[poly]->lit_color[0], video_buffer, lpitch);

		} // end if
		else
		if (rend_list->poly_ptrs[poly]->attr & POLY4DV2_ATTR_SHADE_MODE_GOURAUD)
		{
			// {andre take advantage of the data structures later..}
			// set the vertices
			face.tvlist[0].x = (int)rend_list->poly_ptrs[poly]->tvlist[0].x;
			face.tvlist[0].y = (int)rend_list->poly_ptrs[poly]->tvlist[0].y;
			face.lit_color[0] = rend_list->poly_ptrs[poly]->lit_color[0];

			face.tvlist[1].x = (int)rend_list->poly_ptrs[poly]->tvlist[1].x;
			face.tvlist[1].y = (int)rend_list->poly_ptrs[poly]->tvlist[1].y;
			face.lit_color[1] = rend_list->poly_ptrs[poly]->lit_color[1];

			face.tvlist[2].x = (int)rend_list->poly_ptrs[poly]->tvlist[2].x;
			face.tvlist[2].y = (int)rend_list->poly_ptrs[poly]->tvlist[2].y;
			face.lit_color[2] = rend_list->poly_ptrs[poly]->lit_color[2];

			// draw the gouraud shaded triangle
			Draw_Gouraud_Triangle16(&face, video_buffer, lpitch);
		} // end if gouraud

	} // end for poly

} // end Draw_RENDERLIST4DV2_Solid16

///////////////////////////////////////////////////////////////

void Draw_OBJECT4DV2_Solid16(OBJECT4DV2_PTR obj,
	UCHAR *video_buffer, int lpitch)

{
	// this function renders an object to the screen  in
	// 16 bit mode, it has no regard at all about hidden surface removal, 
	// etc. the function only exists as an easy way to render an object 
	// without converting it into polygons, the function assumes all 
	// coordinates are screen coordinates, but will perform 2D clipping

	POLYF4DV2 face; // temp face used to render polygon

	// at this point, all we have is a list of polygons and it's time
	// to draw them
	for (int poly = 0; poly < obj->num_polys; poly++)
	{
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(obj->plist[poly].state & POLY4DV2_STATE_ACTIVE) ||
			(obj->plist[poly].state & POLY4DV2_STATE_CLIPPED) ||
			(obj->plist[poly].state & POLY4DV2_STATE_BACKFACE))
			continue; // move onto next poly

		// extract vertex indices into master list, rember the polygons are 
		// NOT self contained, but based on the vertex list stored in the object
		// itself
		int vindex_0 = obj->plist[poly].vert[0];
		int vindex_1 = obj->plist[poly].vert[1];
		int vindex_2 = obj->plist[poly].vert[2];


		// need to test for textured first, since a textured poly can either
		// be emissive, or flat shaded, hence we need to call different
		// rasterizers    
		if (obj->plist[poly].attr  & POLY4DV2_ATTR_SHADE_MODE_TEXTURE)
		{

			// set the vertices
			face.tvlist[0].x = (int)obj->vlist_trans[vindex_0].x;
			face.tvlist[0].y = (int)obj->vlist_trans[vindex_0].y;
			face.tvlist[0].u0 = (int)obj->vlist_trans[vindex_0].u0;
			face.tvlist[0].v0 = (int)obj->vlist_trans[vindex_0].v0;

			face.tvlist[1].x = (int)obj->vlist_trans[vindex_1].x;
			face.tvlist[1].y = (int)obj->vlist_trans[vindex_1].y;
			face.tvlist[1].u0 = (int)obj->vlist_trans[vindex_1].u0;
			face.tvlist[1].v0 = (int)obj->vlist_trans[vindex_1].v0;

			face.tvlist[2].x = (int)obj->vlist_trans[vindex_2].x;
			face.tvlist[2].y = (int)obj->vlist_trans[vindex_2].y;
			face.tvlist[2].u0 = (int)obj->vlist_trans[vindex_2].u0;
			face.tvlist[2].v0 = (int)obj->vlist_trans[vindex_2].v0;


			// assign the texture
			face.texture = obj->plist[poly].texture;

			// is this a plain emissive texture?
			if (obj->plist[poly].attr & POLY4DV2_ATTR_SHADE_MODE_CONSTANT)
			{
				// draw the textured triangle as emissive
				Draw_Textured_Triangle16(&face, video_buffer, lpitch);
			} // end if
			else
			{
				// draw as flat shaded
				face.lit_color[0] = obj->plist[poly].lit_color[0];
				Draw_Textured_TriangleFS16(&face, video_buffer, lpitch);
			} // end else

		} // end if      
		else
		if ((obj->plist[poly].attr  & POLY4DV2_ATTR_SHADE_MODE_FLAT) ||
			(obj->plist[poly].attr  & POLY4DV2_ATTR_SHADE_MODE_CONSTANT))
		{
			// draw the triangle with basic flat rasterizer
			Draw_Triangle_2D2_16(obj->vlist_trans[vindex_0].x, obj->vlist_trans[vindex_0].y,
				obj->vlist_trans[vindex_1].x, obj->vlist_trans[vindex_1].y,
				obj->vlist_trans[vindex_2].x, obj->vlist_trans[vindex_2].y,
				obj->plist[poly].lit_color[0], video_buffer, lpitch);

		} // end if
		else
		if (obj->plist[poly].attr & POLY4DV2_ATTR_SHADE_MODE_GOURAUD)
		{
			// {andre take advantage of the data structures later..}
			// set the vertices
			face.tvlist[0].x = (int)obj->vlist_trans[vindex_0].x;
			face.tvlist[0].y = (int)obj->vlist_trans[vindex_0].y;
			face.lit_color[0] = obj->plist[poly].lit_color[0];

			face.tvlist[1].x = (int)obj->vlist_trans[vindex_1].x;
			face.tvlist[1].y = (int)obj->vlist_trans[vindex_1].y;
			face.lit_color[1] = obj->plist[poly].lit_color[1];

			face.tvlist[2].x = (int)obj->vlist_trans[vindex_2].x;
			face.tvlist[2].y = (int)obj->vlist_trans[vindex_2].y;
			face.lit_color[2] = obj->plist[poly].lit_color[2];

			// draw the gouraud shaded triangle
			Draw_Gouraud_Triangle16(&face, video_buffer, lpitch);
		} // end if gouraud

	} // end for poly

} // end Draw_OBJECT4DV2_Solid16

/////////////////////////////////////////////////////////////

int Compute_OBJECT4DV2_Poly_Normals(OBJECT4DV2_PTR obj)
{
	// the normal of a polygon is commonly needed in a number 
	// of functions, however, to store a normal turns out to
	// be counterproductive in most cases since the transformation
	// to rotate the normal ends up taking as long as computing the
	// normal -- HOWEVER, if the normal must have unit length, then
	// pre-computing the length of the normal, and then in real-time
	// dividing by this save a length computation, so we get the 
	// best of both worlds... thus, this function computes the length
	// of a polygon's normal, but care must be taken, so that we compute
	// the length based on the EXACT same two vectors that all other 
	// functions will use when computing the normal
	// in most cases the functions of interest are the lighting functions
	// if we can pre-compute the normal length
	// for all these functions then that will save at least:
	// num_polys_per_frame * (time to compute length of vector)

	// the way we have written the engine, in all cases the normals 
	// during lighting are computed as u = v0->v1, and v = v1->v2
	// so as long as we follow that convention we are fine.
	// also, since the new OBJECT4DV2 format supports multiple frames
	// we must perform these calculations for EACH frame of the animation
	// since although the poly indices don't change, the vertice positions
	// do and thus, so do the normals!!!

	// is this object valid
	if (!obj)
		return(0);

	// iterate thru the poly list of the object and compute normals
	// each polygon
	for (int poly = 0; poly < obj->num_polys; poly++)
	{

		// extract vertex indices into master list, rember the polygons are 
		// NOT self contained, but based on the vertex list stored in the object
		// itself
		int vindex_0 = obj->plist[poly].vert[0];
		int vindex_1 = obj->plist[poly].vert[1];
		int vindex_2 = obj->plist[poly].vert[2];

		// we need to compute the normal of this polygon face, and recall
		// that the vertices are in cw order, u=p0->p1, v=p0->p2, n=uxv
		VECTOR4D u, v, n;

		// build u, v
		VECTOR4D_Build(&obj->vlist_local[vindex_0].v, &obj->vlist_local[vindex_1].v, &u);
		VECTOR4D_Build(&obj->vlist_local[vindex_0].v, &obj->vlist_local[vindex_2].v, &v);

		// compute cross product
		VECTOR4D_Cross(&u, &v, &n);

		// compute length of normal accurately and store in poly nlength
		// +- epsilon later to fix over/underflows
		obj->plist[poly].nlength = VECTOR4D_Length(&n);
	} // end for poly

	// return success
	return(1);

} // end Compute_OBJECT4DV2_Poly_Normals

///////////////////////////////////////////////////////////////////////////////

int Compute_OBJECT4DV2_Vertex_Normals(OBJECT4DV2_PTR obj)
{
	// the vertex normals of each polygon are commonly needed in a number 
	// functions, most importantly lighting calculations for gouraud shading
	// however, we only need to compute the vertex normals for polygons that are
	// gouraud shader, so for every vertex we must determine the polygons that
	// share the vertex then compute the average normal, to determine if a polygon
	// contributes we look at the shading flags for the polygon

	// is this object valid
	if (!obj)
		return(0);

	// algorithm: we are going to scan the polygon list and for every polygon
	// that needs normals we are going to "accumulate" the surface normal into all
	// vertices that the polygon touches, and increment a counter to track how many
	// polys contribute to vertex, then when the scan is done the counts will be used
	// to average the accumulated values, so instead of an O(n^2) algorithm, we get a O(c*n)

	// this tracks the polygon indices that touch a particular vertex
	// the array is used to count the number of contributors to the vertex
	// so at the end of the process we can divide each "accumulated" normal
	// and average
	int polys_touch_vertex[OBJECT4DV2_MAX_VERTICES];
	memset((void *)polys_touch_vertex, 0, sizeof(int)*OBJECT4DV2_MAX_VERTICES);

	// iterate thru the poly list of the object, compute its normal, then add
	// each vertice that composes it to the "touching" vertex array
	// while accumulating the normal in the vertex normal array

	for (int poly = 0; poly < obj->num_polys; poly++)
	{
		Write_Error("\nprocessing poly %d", poly);

		// test if this polygon needs vertex normals
		if (obj->plist[poly].attr & POLY4DV2_ATTR_SHADE_MODE_GOURAUD)
		{
			// extract vertex indices into master list, rember the polygons are 
			// NOT self contained, but based on the vertex list stored in the object
			// itself
			int vindex_0 = obj->plist[poly].vert[0];
			int vindex_1 = obj->plist[poly].vert[1];
			int vindex_2 = obj->plist[poly].vert[2];

			Write_Error("\nTouches vertices: %d, %d, %d", vindex_0, vindex_1, vindex_2);

			// we need to compute the normal of this polygon face, and recall
			// that the vertices are in cw order, u=p0->p1, v=p0->p2, n=uxv
			VECTOR4D u, v, n;

			// build u, v
			VECTOR4D_Build(&obj->vlist_local[vindex_0].v, &obj->vlist_local[vindex_1].v, &u);
			VECTOR4D_Build(&obj->vlist_local[vindex_0].v, &obj->vlist_local[vindex_2].v, &v);

			// compute cross product
			VECTOR4D_Cross(&u, &v, &n);

			// update vertex array to flag this polygon as a contributor
			polys_touch_vertex[vindex_0]++;
			polys_touch_vertex[vindex_1]++;
			polys_touch_vertex[vindex_2]++;

			Write_Error("\nPoly touch array v[%d] = %d,  v[%d] = %d,  v[%d] = %d", vindex_0, polys_touch_vertex[vindex_0],
				vindex_1, polys_touch_vertex[vindex_1],
				vindex_2, polys_touch_vertex[vindex_2]);

			// now accumulate the normal into the vertex normal itself
			// note, we do NOT normalize at this point since we want the length of the normal
			// to weight on the average, and since the length is in fact the area of the parallelogram
			// constructed by uxv, so we are taking the "influence" of the area into consideration
			VECTOR4D_Add(&obj->vlist_local[vindex_0].n, &n, &obj->vlist_local[vindex_0].n);
			VECTOR4D_Add(&obj->vlist_local[vindex_1].n, &n, &obj->vlist_local[vindex_1].n);
			VECTOR4D_Add(&obj->vlist_local[vindex_2].n, &n, &obj->vlist_local[vindex_2].n);
		} // end for poly

	} // end if needs vertex normals

	// now we are almost done, we have accumulated all the vertex normals, but need to average them
	for (int vertex = 0; vertex < obj->num_vertices; vertex++)
	{
		// if this vertex has any contributors then it must need averaging, OR we could check
		// the shading hints flags, they should be one to one
		Write_Error("\nProcessing vertex: %d, attr: %d, contributors: %d", vertex,
			obj->vlist_local[vertex].attr,
			polys_touch_vertex[vertex]);

		// test if this vertex has a normal and needs averaging
		if (polys_touch_vertex[vertex] >= 1)
		{
			obj->vlist_local[vertex].nx /= polys_touch_vertex[vertex];
			obj->vlist_local[vertex].ny /= polys_touch_vertex[vertex];
			obj->vlist_local[vertex].nz /= polys_touch_vertex[vertex];

			// now normalize the normal
			VECTOR4D_Normalize(&obj->vlist_local[vertex].n);

			Write_Error("\nAvg Vertex normal: [%f, %f, %f]", obj->vlist_local[vertex].nx,
				obj->vlist_local[vertex].ny,
				obj->vlist_local[vertex].nz);

		} // end if

	} // end for

	// return success
	return(1);

} // end Compute_OBJECT4DV2_Vertex_Normals

///////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// OBSOLETE and TEST FUNCTIONS ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void Draw_RENDERLIST4DV1_Solid2_16(RENDERLIST4DV1_PTR rend_list,
	UCHAR *video_buffer, int lpitch)
{
	// this function "executes" the render list or in other words
	// draws all the faces in the list in wire frame 16bit mode
	// note there is no need to sort wire frame polygons, but 
	// later we will need to, so hidden surfaces stay hidden
	// also, we leave it to the function to determine the bitdepth
	// and call the correct rasterizer

	// at this point, all we have is a list of polygons and it's time
	// to draw them
	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_ACTIVE) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_CLIPPED) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_BACKFACE))
			continue; // move onto next poly

		// draw the triangle
		Draw_Triangle_2D2_16(rend_list->poly_ptrs[poly]->tvlist[0].x, rend_list->poly_ptrs[poly]->tvlist[0].y,
			rend_list->poly_ptrs[poly]->tvlist[1].x, rend_list->poly_ptrs[poly]->tvlist[1].y,
			rend_list->poly_ptrs[poly]->tvlist[2].x, rend_list->poly_ptrs[poly]->tvlist[2].y,
			rend_list->poly_ptrs[poly]->color, video_buffer, lpitch);

	} // end for poly

} // end Draw_RENDERLIST4DV1_Solid2_16

//////////////////////////////////////////////////////////////////////////////////////

void Draw_OBJECT4DV1_Solid2(OBJECT4DV1_PTR obj,
	UCHAR *video_buffer, int lpitch)

{
	// this function renders an object to the screen in solid, 
	// 8 bit mode, it has no regard at all about hidden surface removal, 
	// etc. the function only exists as an easy way to render an object 
	// without converting it into polygons, the function assumes all 
	// coordinates are screen coordinates, but will perform 2D clipping

	// iterate thru the poly list of the object and simply draw
	// each polygon
	for (int poly = 0; poly < obj->num_polys; poly++)
	{
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(obj->plist[poly].state & POLY4DV1_STATE_ACTIVE) ||
			(obj->plist[poly].state & POLY4DV1_STATE_CLIPPED) ||
			(obj->plist[poly].state & POLY4DV1_STATE_BACKFACE))
			continue; // move onto next poly

		// extract vertex indices into master list, rember the polygons are 
		// NOT self contained, but based on the vertex list stored in the object
		// itself
		int vindex_0 = obj->plist[poly].vert[0];
		int vindex_1 = obj->plist[poly].vert[1];
		int vindex_2 = obj->plist[poly].vert[2];

		// draw the triangle
		Draw_Triangle_2D2(obj->vlist_trans[vindex_0].x, obj->vlist_trans[vindex_0].y,
			obj->vlist_trans[vindex_1].x, obj->vlist_trans[vindex_1].y,
			obj->vlist_trans[vindex_2].x, obj->vlist_trans[vindex_2].y,
			obj->plist[poly].color, video_buffer, lpitch);

	} // end for poly

} // end Draw_OBJECT4DV1_Solid2

///////////////////////////////////////////////////////////////

void Draw_RENDERLIST4DV1_Solid2(RENDERLIST4DV1_PTR rend_list,
	UCHAR *video_buffer, int lpitch)
{
	// this function "executes" the render list or in other words
	// draws all the faces in the list in wire frame 8bit mode
	// note there is no need to sort wire frame polygons, but 
	// later we will need to, so hidden surfaces stay hidden
	// also, we leave it to the function to determine the bitdepth
	// and call the correct rasterizer

	// at this point, all we have is a list of polygons and it's time
	// to draw them
	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_ACTIVE) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_CLIPPED) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_BACKFACE))
			continue; // move onto next poly

		// draw the triangle
		Draw_Triangle_2D2(rend_list->poly_ptrs[poly]->tvlist[0].x, rend_list->poly_ptrs[poly]->tvlist[0].y,
			rend_list->poly_ptrs[poly]->tvlist[1].x, rend_list->poly_ptrs[poly]->tvlist[1].y,
			rend_list->poly_ptrs[poly]->tvlist[2].x, rend_list->poly_ptrs[poly]->tvlist[2].y,
			rend_list->poly_ptrs[poly]->color, video_buffer, lpitch);

	} // end for poly

} // end Draw_RENDERLIST4DV1_Solid2

/////////////////////////////////////////////////////////////

void Draw_OBJECT4DV1_Solid2_16(OBJECT4DV1_PTR obj,
	UCHAR *video_buffer, int lpitch)

{
	// this function renders an object to the screen in wireframe, 
	// 16 bit mode, it has no regard at all about hidden surface removal, 
	// etc. the function only exists as an easy way to render an object 
	// without converting it into polygons, the function assumes all 
	// coordinates are screen coordinates, but will perform 2D clipping

	// iterate thru the poly list of the object and simply draw
	// each polygon
	for (int poly = 0; poly < obj->num_polys; poly++)
	{
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(obj->plist[poly].state & POLY4DV1_STATE_ACTIVE) ||
			(obj->plist[poly].state & POLY4DV1_STATE_CLIPPED) ||
			(obj->plist[poly].state & POLY4DV1_STATE_BACKFACE))
			continue; // move onto next poly

		// extract vertex indices into master list, rember the polygons are 
		// NOT self contained, but based on the vertex list stored in the object
		// itself
		int vindex_0 = obj->plist[poly].vert[0];
		int vindex_1 = obj->plist[poly].vert[1];
		int vindex_2 = obj->plist[poly].vert[2];

		// draw the triangle
		Draw_Triangle_2D2_16(obj->vlist_trans[vindex_0].x, obj->vlist_trans[vindex_0].y,
			obj->vlist_trans[vindex_1].x, obj->vlist_trans[vindex_1].y,
			obj->vlist_trans[vindex_2].x, obj->vlist_trans[vindex_2].y,
			obj->plist[poly].color, video_buffer, lpitch);

	} // end for poly

} // end Draw_OBJECT4DV1_Solid2_16

///////////////////////////////////////////////////////////////////////////

void Draw_RENDERLIST4DV2_Textured(RENDERLIST4DV2_PTR rend_list,
	UCHAR *video_buffer,
	int lpitch,
	BITMAP_IMAGE_PTR texture)
{
	// TEST FUNCTION ONLY!!!

	POLYF4DV2 face; // temp face used to render polygon

	// at this point, all we have is a list of polygons and it's time
	// to draw them
	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(rend_list->poly_ptrs[poly]->state & POLY4DV2_STATE_ACTIVE) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV2_STATE_CLIPPED) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV2_STATE_BACKFACE))
			continue; // move onto next poly

		// set the vertices
		face.tvlist[0].x = (int)rend_list->poly_ptrs[poly]->tvlist[0].x;
		face.tvlist[0].y = (int)rend_list->poly_ptrs[poly]->tvlist[0].y;
		face.tvlist[0].u0 = 0;
		face.tvlist[0].v0 = 0;

		face.tvlist[1].x = (int)rend_list->poly_ptrs[poly]->tvlist[1].x;
		face.tvlist[1].y = (int)rend_list->poly_ptrs[poly]->tvlist[1].y;
		face.tvlist[1].u0 = 0;
		face.tvlist[1].v0 = 63;

		face.tvlist[2].x = (int)rend_list->poly_ptrs[poly]->tvlist[2].x;
		face.tvlist[2].y = (int)rend_list->poly_ptrs[poly]->tvlist[2].y;
		face.tvlist[2].u0 = 63;
		face.tvlist[2].v0 = 63;

		// assign the texture
		face.texture = texture;

		// draw the textured triangle
		Draw_Textured_Triangle(&face, video_buffer, lpitch);

	} // end for poly

} // end Draw_RENDERLIST4DV2_Textured

///////////////////////////////////////////////////////////////////////////

void Draw_RENDERLIST4DV2_Textured16(RENDERLIST4DV2_PTR rend_list,
	UCHAR *video_buffer,
	int lpitch,
	BITMAP_IMAGE_PTR texture)
{
	// TEST FUNCTION ONLY!!!!

	POLYF4DV2 face; // temp face used to render polygon

	// at this point, all we have is a list of polygons and it's time
	// to draw them
	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(rend_list->poly_ptrs[poly]->state & POLY4DV2_STATE_ACTIVE) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV2_STATE_CLIPPED) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV2_STATE_BACKFACE))
			continue; // move onto next poly

		// set the vertices
		face.tvlist[0].x = (int)rend_list->poly_ptrs[poly]->tvlist[0].x;
		face.tvlist[0].y = (int)rend_list->poly_ptrs[poly]->tvlist[0].y;
		face.tvlist[0].u0 = 0;
		face.tvlist[0].v0 = 0;

		face.tvlist[1].x = (int)rend_list->poly_ptrs[poly]->tvlist[1].x;
		face.tvlist[1].y = (int)rend_list->poly_ptrs[poly]->tvlist[1].y;
		face.tvlist[1].u0 = 0;
		face.tvlist[1].v0 = 63;

		face.tvlist[2].x = (int)rend_list->poly_ptrs[poly]->tvlist[2].x;
		face.tvlist[2].y = (int)rend_list->poly_ptrs[poly]->tvlist[2].y;
		face.tvlist[2].u0 = 63;
		face.tvlist[2].v0 = 63;

		// assign the texture
		face.texture = texture;

		// draw the textured triangle
		Draw_Textured_Triangle16(&face, video_buffer, lpitch);

	} // end for poly

} // end Draw_RENDERLIST4DV2_Textured16


/////////////////////////////////////////////////////////////////////////

void Draw_OBJECT4DV1_Textured(OBJECT4DV1_PTR obj,
	UCHAR *video_buffer, int lpitch)

{
	// TEST FUNCTION ONLY!!!

	// iterate thru the poly list of the object and simply draw
	// each polygon
	for (int poly = 0; poly < obj->num_polys; poly++)
	{
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(obj->plist[poly].state & POLY4DV1_STATE_ACTIVE) ||
			(obj->plist[poly].state & POLY4DV1_STATE_CLIPPED) ||
			(obj->plist[poly].state & POLY4DV1_STATE_BACKFACE))
			continue; // move onto next poly

		// extract vertex indices into master list, rember the polygons are 
		// NOT self contained, but based on the vertex list stored in the object
		// itself
		int vindex_0 = obj->plist[poly].vert[0];
		int vindex_1 = obj->plist[poly].vert[1];
		int vindex_2 = obj->plist[poly].vert[2];

		// draw the triangle
		Draw_Triangle_2D(obj->vlist_trans[vindex_0].x, obj->vlist_trans[vindex_0].y,
			obj->vlist_trans[vindex_1].x, obj->vlist_trans[vindex_1].y,
			obj->vlist_trans[vindex_2].x, obj->vlist_trans[vindex_2].y,
			obj->plist[poly].color, video_buffer, lpitch);

	} // end for poly

} // end Draw_OBJECT4DV1_Textured

///////////////////////////////////////////////////////////////

void Draw_RENDERLIST4DV1_Textured(RENDERLIST4DV1_PTR rend_list,
	UCHAR *video_buffer,
	int lpitch,
	BITMAP_IMAGE_PTR texture)
{
	// TEST FUNCTION

	POLYF4DV2 face; // temp face used to render polygon

	// at this point, all we have is a list of polygons and it's time
	// to draw them
	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_ACTIVE) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_CLIPPED) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_BACKFACE))
			continue; // move onto next poly

		// set the vertices
		face.tvlist[0].x = (int)rend_list->poly_ptrs[poly]->tvlist[0].x;
		face.tvlist[0].y = (int)rend_list->poly_ptrs[poly]->tvlist[0].y;
		face.tvlist[0].u0 = 0;
		face.tvlist[0].v0 = 0;

		face.tvlist[1].x = (int)rend_list->poly_ptrs[poly]->tvlist[1].x;
		face.tvlist[1].y = (int)rend_list->poly_ptrs[poly]->tvlist[1].y;
		face.tvlist[1].u0 = 0;
		face.tvlist[1].v0 = 63;

		face.tvlist[2].x = (int)rend_list->poly_ptrs[poly]->tvlist[2].x;
		face.tvlist[2].y = (int)rend_list->poly_ptrs[poly]->tvlist[2].y;
		face.tvlist[2].u0 = 63;
		face.tvlist[2].v0 = 63;

		// assign the texture
		face.texture = texture;

		// draw the textured triangle
		Draw_Textured_Triangle(&face, video_buffer, lpitch);

	} // end for poly

} // end Draw_RENDERLIST4DV1_Textured

///////////////////////////////////////////////////////////////

void Draw_RENDERLIST4DV1_Textured16(RENDERLIST4DV1_PTR rend_list,
	UCHAR *video_buffer,
	int lpitch,
	BITMAP_IMAGE_PTR texture)
{
	// TEST FUNCTION

	POLYF4DV2 face; // temp face used to render polygon

	// at this point, all we have is a list of polygons and it's time
	// to draw them
	for (int poly = 0; poly < rend_list->num_polys; poly++)
	{
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_ACTIVE) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_CLIPPED) ||
			(rend_list->poly_ptrs[poly]->state & POLY4DV1_STATE_BACKFACE))
			continue; // move onto next poly

		// set the vertices
		face.tvlist[0].x = (int)rend_list->poly_ptrs[poly]->tvlist[0].x;
		face.tvlist[0].y = (int)rend_list->poly_ptrs[poly]->tvlist[0].y;
		face.tvlist[0].u0 = 0;
		face.tvlist[0].v0 = 0;

		face.tvlist[1].x = (int)rend_list->poly_ptrs[poly]->tvlist[1].x;
		face.tvlist[1].y = (int)rend_list->poly_ptrs[poly]->tvlist[1].y;
		face.tvlist[1].u0 = 0;
		face.tvlist[1].v0 = 63;

		face.tvlist[2].x = (int)rend_list->poly_ptrs[poly]->tvlist[2].x;
		face.tvlist[2].y = (int)rend_list->poly_ptrs[poly]->tvlist[2].y;
		face.tvlist[2].u0 = 63;
		face.tvlist[2].v0 = 63;

		// assign the texture
		face.texture = texture;

		// draw the textured triangle
		Draw_Textured_Triangle16(&face, video_buffer, lpitch);

	} // end for poly

} // end Draw_RENDERLIST4DV1_Textured16