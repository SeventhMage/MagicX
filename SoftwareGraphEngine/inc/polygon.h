#ifndef _SGE_POLYGON_H_
#define _SGE_POLYGON_H_

#include "sgemath.h"

//////////////////////////////////////////////////////////////////////////
//POLY4DV1																//
//////////////////////////////////////////////////////////////////////////

//����κͶ�����������
#define POLY4DV1_ATTR_2SIDED		0x0001
#define POLY4DV1_ATTR_TRANSPARENT	0x0002
#define POLY4DV1_ATTR_8BITCOLOR     0x0004
#define POLY4DV1_ATTR_RGB16			0x0008
#define POLY4DV1_ATTR_RGB24			0x0010

#define POLY4DV1_ATTR_SHADE_MODE_PURE		0x0020
#define POLY4DV1_ATTR_SHADE_MODE_FLAT		0x0040
#define POLY4DV1_ATTR_SHADE_MODE_GOURAUD	0x0080
#define POLY4DV1_ATTR_SHADE_MODE_PHONG		0x0100

//����κ����״ֵ̬
#define POLY4DV1_STATE_ACTIVE		0x0001
#define POLY4DV1_STATE_CLIPPED		0x0002
#define POLY4DV1_STATE_BACKFACE		0x0004

//��󶥵������������
#define OBJECT4DV1_MAX_VERTICES           1024  // 64
#define OBJECT4DV1_MAX_POLYS              1024 // 128

// ����״̬
#define OBJECT4DV1_STATE_ACTIVE           0x0001
#define OBJECT4DV1_STATE_VISIBLE          0x0002 
#define OBJECT4DV1_STATE_CULLED           0x0004

//��Ⱦ�б��ж������
#define RENDERLIST4DV1_MAX_POLYS          32768

// a 2D vertex
typedef struct VERTEX2DI_TYP
{
	int x, y; // the vertex
} VERTEX2DI, *VERTEX2DI_PTR;

// a 2D vertex
typedef struct VERTEX2DF_TYP
{
	float x, y; // the vertex
} VERTEX2DF, *VERTEX2DF_PTR;


// a 2D polygon
typedef struct POLYGON2D_TYP
{
	int state;        // state of polygon
	int num_verts;    // number of vertices
	int x0, y0;        // position of center of polygon  
	int xv, yv;        // initial velocity
	DWORD color;      // could be index or PALETTENTRY
	VERTEX2DF *vlist; // pointer to vertex list

} POLYGON2D, *POLYGON2D_PTR;

//typedef struct POLY_EX_TYP_1
//{
//	POINT3D v[3];
//}POLY_EX_1, *POLY_EX_1_PTR;
//
//typedef struct POLY_EX_TYP_2
//{
//	POINT3D_PTR vlist;
//	int vertices[3];
//}POLY_EX_2, *POLY_EX_2_PTR;

typedef struct POLY4DV1_TYP
{
	int state;	//״̬��Ϣ
	int attr;	//����ε���������
	int color;	//����ε���ɫ

	POINT4D_PTR vlist;	//�����б�
	int vert[3];		//�����б������
}POLY4DV1, *POLY4DV1_PTR;

typedef struct POLYF4DV1_TYP
{
	int state;	//״̬��Ϣ
	int attr;	//����ε���������
	int color;	//����ε���ɫ

	POINT4D vlist[3];	//�����εĶ���
	POINT4D tvlist[3];	//��ú�Ķ���
	POLYF4DV1_TYP *next;	//ָ���б�����һ������ε�ָ��
	POLYF4DV1_TYP *prev;	//ָ���б���ǰһ������ε�ָ��	
}POLYF4DV1, *POLYF4DV1_PTR;

typedef struct OBJECT4DV1_TYP
{
	int id;		//�������ֵID
	char name[64];	//������ַ�������
	int state;	//�����״̬
	int attr;	//���������
       	float avg_radius;	//�����ƽ���뾶����ײ���
	float max_radius;	//�������뾶

	POINT4D world_pos;	//���������������е�λ��
	VECTOR4D dir;		//�����ھֲ������µ���ת�Ƕ�	
	VECTOR4D ux, uy, uz;	//���峯��ľֲ������ᣬ������תʱ��Ӧ��ת

	int num_vertices;	//���嶥����
	POINT4D vlist_local[OBJECT4DV1_MAX_VERTICES];	//�洢����ֲ����������
	POINT4D vlist_trans[OBJECT4DV1_MAX_VERTICES];	//�洢����仯�����������

	int num_polys;			//����Ķ������	
	POLY4DV1 plist[OBJECT4DV1_MAX_POLYS];		//�洢����ε�����		
}OBJECT4DV1, *OBJECT4DV1_PTR;

typedef struct RENDERLIST4DV1_TYP
{
	int state;	//��Ⱦ�б��״̬
	int attr;	//��Ⱦ�б������

	POLYF4DV1_PTR poly_ptrs[RENDERLIST4DV1_MAX_POLYS];	//��Ⱦ�б�
	POLYF4DV1 poly_data[RENDERLIST4DV1_MAX_POLYS];		//���������
	int num_polys;						//��Ⱦ�б��а����Ķ������Ŀ
}RENDERLIST4DV1, *RENDERLIST4DV1_PTR;
 
void Reset_RENDERLIST4DV1(RENDERLIST4DV1_PTR rend_list);

float Compute_OBJECT4DV1_Radius(OBJECT4DV1_PTR obj);


//////////////////////////////////////////////////////////////////////////
//POLY4DV2																//
//////////////////////////////////////////////////////////////////////////

#define TRI_TYPE_NONE           0
#define TRI_TYPE_FLAT_TOP       1 
#define TRI_TYPE_FLAT_BOTTOM	2
#define TRI_TYPE_FLAT_MASK      3
#define TRI_TYPE_GENERAL        4
#define INTERP_LHS              0
#define INTERP_RHS              1
#define MAX_VERTICES_PER_POLY   6

#define POLY4DV2_ATTR_2SIDED                0x0001
#define POLY4DV2_ATTR_TRANSPARENT           0x0002
#define POLY4DV2_ATTR_8BITCOLOR             0x0004
#define POLY4DV2_ATTR_RGB16                 0x0008
#define POLY4DV2_ATTR_RGB24                 0x0010

#define POLY4DV2_ATTR_SHADE_MODE_PURE       0x0020
#define POLY4DV2_ATTR_SHADE_MODE_CONSTANT   0x0020 // (alias)
#define POLY4DV2_ATTR_SHADE_MODE_EMISSIVE   0x0020 // (alias)

#define POLY4DV2_ATTR_SHADE_MODE_FLAT       0x0040
#define POLY4DV2_ATTR_SHADE_MODE_GOURAUD    0x0080
#define POLY4DV2_ATTR_SHADE_MODE_PHONG      0x0100
#define POLY4DV2_ATTR_SHADE_MODE_FASTPHONG  0x0100 // (alias)
#define POLY4DV2_ATTR_SHADE_MODE_TEXTURE    0x0200 

//����
#define POLY4DV2_ATTR_ENABLE_MATERIAL       0x0800
#define POLY4DV2_ATTR_DISABLE_MATERIAL      0x1000

#define POLY4DV2_STATE_NULL               0x0000
#define POLY4DV2_STATE_ACTIVE             0x0001  
#define POLY4DV2_STATE_CLIPPED            0x0002  
#define POLY4DV2_STATE_BACKFACE           0x0004  
#define POLY4DV2_STATE_LIT                0x0008

#define VERTEX_FLAGS_INVERT_X               0x0001   // inverts the Z-coordinates
#define VERTEX_FLAGS_INVERT_Y               0x0002   // inverts the Z-coordinates
#define VERTEX_FLAGS_INVERT_Z               0x0004   // inverts the Z-coordinates
#define VERTEX_FLAGS_SWAP_YZ                0x0008   // transforms a RHS model to a LHS model
#define VERTEX_FLAGS_SWAP_XZ                0x0010   
#define VERTEX_FLAGS_SWAP_XY                0x0020
#define VERTEX_FLAGS_INVERT_WINDING_ORDER   0x0040   // invert winding order from cw to ccw or ccw to cc


#define VERTEX_FLAGS_TRANSFORM_LOCAL        0x0200   // if file format has local transform then do it!
#define VERTEX_FLAGS_TRANSFORM_LOCAL_WORLD  0x0400  // if file format has local to world then do it!

#define VERTEX_FLAGS_OVERRIDE_MASK          0xf000
#define VERTEX_FLAGS_OVERRIDE_CONSTANT      0x1000
#define VERTEX_FLAGS_OVERRIDE_EMISSIVE      0x1000 //(alias)
#define VERTEX_FLAGS_OVERRIDE_PURE          0x1000
#define VERTEX_FLAGS_OVERRIDE_FLAT          0x2000
#define VERTEX_FLAGS_OVERRIDE_GOURAUD       0x4000
#define VERTEX_FLAGS_OVERRIDE_TEXTURE       0x8000

#define VERTEX_FLAGS_INVERT_TEXTURE_U       0x0080
#define VERTEX_FLAGS_INVERT_TEXTURE_V       0x0100
#define VERTEX_FLAGS_INVERT_SWAP_UV         0x0800

#define OBJECT4DV2_MAX_VERTICES           4096  // 64
#define OBJECT4DV2_MAX_POLYS              8192 // 128

#define OBJECT4DV2_STATE_NULL             0x0000
#define OBJECT4DV2_STATE_ACTIVE           0x0001
#define OBJECT4DV2_STATE_VISIBLE          0x0002 
#define OBJECT4DV2_STATE_CULLED           0x0004

#define OBJECT4DV2_ATTR_SINGLE_FRAME      0x0001 // ��֡����
#define OBJECT4DV2_ATTR_MULTI_FRAME       0x0002 // ��֡����
#define OBJECT4DV2_ATTR_TEXTURES          0x0004

#define RENDERLIST4DV2_MAX_POLYS          32768

#define VERTEX4DTV1_ATTR_NULL             0x0000
#define VERTEX4DTV1_ATTR_POINT            0x0001
#define VERTEX4DTV1_ATTR_NORMAL           0x0002
#define VERTEX4DTV1_ATTR_TEXTURE          0x0004

#define RASTERIZER_ACCURATE    0
#define RASTERIZER_FAST        1
#define RASTERIZER_FASTEST     2

#define RASTERIZER_MODE        RASTERIZER_ACCURATE


//����ṹ
typedef struct VECTOR2DI_TYP
{
	union
	{
		int M[2];
		
		struct
		{
			int x, y;
		};

	};

} VECTOR2DI, POINT2DI, *VECTOR2DI_PTR, *POINT2DI_PTR;

typedef struct VECTOR3DI_TYP
{
	union
	{
		int M[3];

		struct
		{
			int x, y, z;
		};
	};

} VECTOR3DI, POINT3DI, *VECTOR3DI_PTR, *POINT3DI_PTR;

typedef struct VECTOR4DI_TYP
{
	union
	{
		int M[4];

		struct
		{
			int x, y, z, w;
		};
	};

} VECTOR4DI, POINT4DI, *VECTOR4DI_PTR, *POINT4DI_PTR;

typedef struct VERTEX4DTV1_TYP
{
	union
	{
		float M[12];

		struct
		{
			float x, y, z, w;
			float nx, ny, nz, nw;
			float u0, v0;

			float i;
			int   attr;
		};
		
		struct
		{
			POINT4D  v;
			VECTOR4D n;
			POINT2D  t;
		};
	};

} VERTEX4DTV1, *VERTEX4DTV1_PTR;

typedef struct POLYF4DV2_TYP
{
	int      state;
	int      attr;
	int      color;
	int      lit_color[3];

	BITMAP_IMAGE_PTR texture;

	int      mati;

	float    nlength;
	VECTOR4D normal;

	float    avg_z;

	VERTEX4DTV1 vlist[3];
	VERTEX4DTV1 tvlist[3];

	POLYF4DV2_TYP *next;
	POLYF4DV2_TYP *prev;

} POLYF4DV2, *POLYF4DV2_PTR;


typedef struct POLY4DV2_TYP
{
	int state;
	int attr;
	int color;
	int lit_color[3];	

	BITMAP_IMAGE_PTR texture;

	int mati;

	VERTEX4DTV1_PTR vlist;
	POINT2D_PTR     tlist;
	int vert[3];
	int text[3];
	float nlength;

} POLY4DV2, *POLY4DV2_PTR;

typedef struct OBJECT4DV2_TYP
{
	int   id;
	char  name[64];
	int   state;
	int   attr;
	int   mati;
	float *avg_radius;
	float *max_radius;

	POINT4D world_pos;

	VECTOR4D dir;

	VECTOR4D ux, uy, uz;

	int num_vertices;
	int num_frames;
	int total_vertices;
	int curr_frame;

	VERTEX4DTV1_PTR vlist_local;
	VERTEX4DTV1_PTR vlist_trans;

	VERTEX4DTV1_PTR head_vlist_local;
	VERTEX4DTV1_PTR head_vlist_trans;

	POINT2D_PTR tlist;

	BITMAP_IMAGE_PTR texture; 

	int num_polys;
	POLY4DV2_PTR plist;

	int   ivar1, ivar2; 
	float fvar1, fvar2;

	int Set_Frame(int frame);

} OBJECT4DV2, *OBJECT4DV2_PTR;


typedef struct RENDERLIST4DV2_TYP
{
	int state;
	int attr;

	POLYF4DV2_PTR poly_ptrs[RENDERLIST4DV2_MAX_POLYS];

	POLYF4DV2 poly_data[RENDERLIST4DV2_MAX_POLYS];

	int num_polys;

} RENDERLIST4DV2, *RENDERLIST4DV2_PTR;

int Destroy_OBJECT4DV2(OBJECT4DV2_PTR obj);
int Init_OBJECT4DV2(OBJECT4DV2_PTR obj, int _num_vertices, int _num_polys, int _num_frames, int destroy = 0);

inline void VERTEX4DTV1_COPY(VERTEX4DTV1_PTR vdst, VERTEX4DTV1_PTR vsrc)
{
	*vdst = *vsrc;
}

inline void VERTEX4DTV1_INIT(VERTEX4DTV1_PTR vdst, VERTEX4DTV1_PTR vsrc)
{
	*vdst = *vsrc;
}

#endif
