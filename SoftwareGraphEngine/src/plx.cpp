#include "plx.h"
#include "tool.h"
#include <ctype.h>

// 跳过注释和空行，返回一行数据，文件为空反回NULL
char *Get_Line_PLG(char *buffer, int maxlength, FILE *fp)
{
	int index = 0;		//索引
	int length = 0;		//长度

	//分析循环
	while (true)
	{
		if (!fgets(buffer, maxlength, fp))
			return NULL;
		//计算空格
		for (length = strlen(buffer), index = 0; isspace(buffer[index]); ++index);

		//检查是否为空行或注释
		if (index >= length || buffer[index] == '#')
			continue;
		return &buffer[index];
	}
}

//加载plg文件
//obj:指向物体的指针
//filename:文件名
//scale初始绽放因子
//pos初始位置
//rot初始旋转
int Load_OBJECT4DV1_PLG(OBJECT4DV1_PTR obj, char *filename, VECTOR4D_PTR scale, VECTOR4D_PTR pos, VECTOR4D_PTR rot)
{
	FILE *fp;
	char buffer[256];

	char *token_string;

	memset(obj, 0, sizeof(OBJECT4DV1));

	obj->state = OBJECT4DV1_STATE_ACTIVE | OBJECT4DV1_STATE_VISIBLE;
	obj->world_pos.x = pos->x;
	obj->world_pos.y = pos->y;
	obj->world_pos.z = pos->z;
	obj->world_pos.w = pos->w;
	fopen_s(&fp, filename, "r");
	if (!fp)
	{
		printf("Couldn't open PLG file %s.\n", filename);
		return 0;
	}

	if (!(token_string = Get_Line_PLG(buffer, 255, fp)))
	{
		printf("PLG file error with file %s.\n", filename);
		return 0;
	}

	sscanf(token_string, "%s %d %d", obj->name, &obj->num_vertices, &obj->num_polys);

	for (int vertex = 0; vertex < obj->num_vertices; ++vertex)
	{
		if (!(token_string = Get_Line_PLG(buffer, 255, fp)))
		{
			printf("PLG file error with file %s.\n", filename);
			return 0;
		}
		sscanf(token_string, "%f %f %f", &obj->vlist_local[vertex].x, &obj->vlist_local[vertex].y, &obj->vlist_local[vertex].z);
		obj->vlist_local[vertex].w = 1;
		obj->vlist_local[vertex].x *= scale->x;
		obj->vlist_local[vertex].y *= scale->y;
		obj->vlist_local[vertex].z *= scale->z;
	}

	//计算平均半径和最大半径
	Compute_OBJECT4DV1_Radius(obj);

	int poly_surface_desc = 0;
	int poly_num_verts = 0;
	char tmp_string[8];

	//加载多边形列表
	for (int poly = 0; poly < obj->num_polys; ++poly)
	{
		if (!(token_string = Get_Line_PLG(buffer, 255, fp)))
		{
			printf("PLG file error with file %s.\n", filename);
			return 0;
		}
		sscanf(token_string, "%s %d %d %d %d", tmp_string, &poly_num_verts,
			&obj->plist[poly].vert[0], &obj->plist[poly].vert[1],
			&obj->plist[poly].vert[2]);
		if (tmp_string[0] == '0' && toupper(tmp_string[1] == 'X'))
			sscanf(tmp_string, "%x", &poly_surface_desc);
		else
			poly_surface_desc = atoi(tmp_string);

		obj->plist[poly].vlist = obj->vlist_local;

		if ((poly_surface_desc & PLX_2SIDED_FLAG))
		{
			SET_BIT(obj->plist[poly].attr, POLY4DV1_ATTR_2SIDED);
		}
		else
		{

		}

		if ((poly_surface_desc & PLX_COLOR_MODE_RGB_FLAG))
		{
			SET_BIT(obj->plist[poly].attr, POLY4DV1_ATTR_RGB16);
			int red = ((poly_surface_desc & 0x0f00) >> 8);
			int green = ((poly_surface_desc & 0x00f0) >> 4);
			int blue = (poly_surface_desc & 0x000f);
			obj->plist[poly].color = RGB16Bit(red * 16, green * 16, blue * 16);
		}
		else
		{
			SET_BIT(obj->plist[poly].attr, POLY4DV1_ATTR_8BITCOLOR);
			obj->plist[poly].color = (poly_surface_desc & 0x00ff);
		}

		int shade_mode = (poly_surface_desc & PLX_SHADE_MODE_MASK);

		//设置着色模式
		switch (shade_mode)
		{
		case PLX_SHADE_MODE_PURE_FLAG:
		{
										 SET_BIT(obj->plist[poly].attr, POLY4DV1_ATTR_SHADE_MODE_PURE);
		}break;
		case PLX_SHADE_MODE_FLAT_FLAG:
		{
										 SET_BIT(obj->plist[poly].attr, POLY4DV1_ATTR_SHADE_MODE_FLAT);
		}break;
		case PLX_SHADE_MODE_PHONG_FLAG:
		{
										  SET_BIT(obj->plist[poly].attr, POLY4DV1_ATTR_SHADE_MODE_PHONG);
		}break;
		case PLX_SHADE_MODE_GOURAUD_FLAG:
		{
											SET_BIT(obj->plist[poly].attr, POLY4DV1_ATTR_SHADE_MODE_GOURAUD);
		}break;
		default:
			break;
		}
		obj->plist[poly].state = POLY4DV1_STATE_ACTIVE;
	}
	fclose(fp);
	return 1;
}