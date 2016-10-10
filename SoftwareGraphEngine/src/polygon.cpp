#include "polygon.h"
#include <math.h>

void Reset_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list)
{
	rend_list->num_polys = 0;
}


float Compute_OBJECT4DV1_Radius(OBJECT4DV1_PTR obj)
{
	// this function computes the average and maximum radius for 
	// sent object and opdates the object data

	// reset incase there's any residue
	obj->avg_radius = 0;
	obj->max_radius = 0;

	// loop thru and compute radius
	for (int vertex = 0; vertex < obj->num_vertices; vertex++)
	{
		// update the average and maximum radius
		float dist_to_vertex =
			sqrt(obj->vlist_local[vertex].x*obj->vlist_local[vertex].x +
			obj->vlist_local[vertex].y*obj->vlist_local[vertex].y +
			obj->vlist_local[vertex].z*obj->vlist_local[vertex].z);

		// accumulate total radius
		obj->avg_radius += dist_to_vertex;

		// update maximum radius   
		if (dist_to_vertex > obj->max_radius)
			obj->max_radius = dist_to_vertex;

	} // end for vertex

	// finallize average radius computation
	obj->avg_radius /= obj->num_vertices;

	// return max radius
	return(obj->max_radius);

} // end Compute_OBJECT4DV1_Radius

//////////////////////////////////////////////////////////////////////////
//V2																	//
//////////////////////////////////////////////////////////////////////////
int OBJECT4DV2::Set_Frame(int frame)
{
	if (!this)
		return(0);
	
	if (!(this->attr & OBJECT4DV2_ATTR_MULTI_FRAME))
		return(0);
	
	if (frame < 0)
		frame = 0;
	else
	if (frame >= this->num_frames)
		frame = this->num_frames - 1;
	
	this->curr_frame = frame;


	this->vlist_local = &(this->head_vlist_local[frame*this->num_vertices]);
	this->vlist_trans = &(this->head_vlist_trans[frame*this->num_vertices]);

	return(1);
}

int Destroy_OBJECT4DV2(OBJECT4DV2_PTR obj)
{
	if (obj->head_vlist_local)
		free(obj->head_vlist_local);
	
	if (obj->head_vlist_trans)
		free(obj->head_vlist_trans);

	if (obj->tlist)
		free(obj->tlist);
	
	if (obj->plist)
		free(obj->plist);
	
	if (obj->avg_radius)
		free(obj->avg_radius);

	if (obj->max_radius)
		free(obj->max_radius);
	
	memset((void *)obj, 0, sizeof(OBJECT4DV2));

	return(1);
}

int Init_OBJECT4DV2(OBJECT4DV2_PTR obj, int _num_vertices, int _num_polys, int _num_frames, int destroy)
{
	if (destroy)
		Destroy_OBJECT4DV2(obj);
	
	if (!(obj->vlist_local = (VERTEX4DTV1_PTR)malloc(sizeof(VERTEX4DTV1)*_num_vertices*_num_frames)))
		return(0);
	
	memset((void *)obj->vlist_local, 0, sizeof(VERTEX4DTV1)*_num_vertices*_num_frames);

	if (!(obj->vlist_trans = (VERTEX4DTV1_PTR)malloc(sizeof(VERTEX4DTV1)*_num_vertices*_num_frames)))
		return(0);

	memset((void *)obj->vlist_trans, 0, sizeof(VERTEX4DTV1)*_num_vertices*_num_frames);
	
	if (!(obj->tlist = (POINT2D_PTR)malloc(sizeof(POINT2D)*_num_polys * 3)))
		return(0);

	memset((void *)obj->tlist, 0, sizeof(POINT2D)*_num_polys * 3);

	if (!(obj->avg_radius = (float *)malloc(sizeof(float)*_num_frames)))
		return(0);
	
	memset((void *)obj->avg_radius, 0, sizeof(float)*_num_frames);


	if (!(obj->max_radius = (float *)malloc(sizeof(float)*_num_frames)))
		return(0);

	memset((void *)obj->max_radius, 0, sizeof(float)*_num_frames);

	if (!(obj->plist = (POLY4DV2_PTR)malloc(sizeof(POLY4DV2)*_num_polys)))
		return(0);
	
	memset((void *)obj->plist, 0, sizeof(POLY4DV2)*_num_polys);

	obj->head_vlist_local = obj->vlist_local;
	obj->head_vlist_trans = obj->vlist_trans;

	obj->num_frames = _num_frames;
	obj->num_polys = _num_polys;
	obj->num_vertices = _num_vertices;
	obj->total_vertices = _num_vertices*_num_frames;
	
	return(1);
}