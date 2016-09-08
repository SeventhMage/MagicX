#include "renderer.h"

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

void World_To_Camera_OBJECT4DV1(CAM4DV1_PTR cam, OBJECT4DV1_PTR obj)
{
	for (int vertex = 0; vertex < obj->num_vertices; ++vertex)
	{
		POINT4D presult;
		//Mat_Mul_VECTOR4D_4X4(&obj->vlist_trans)
	}
}
