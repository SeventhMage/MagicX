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