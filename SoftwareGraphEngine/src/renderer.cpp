#include "renderer.h"
#include "tool.h"
#include "draw.h"

#include <math.h>

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

void Draw_RENDERLIST4DV1_Wire16(RENDERLIST4DV1_PTR rend_list, unsigned char *video_buffer, int lpitch)
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
