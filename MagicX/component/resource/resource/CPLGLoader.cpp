#include "../include/CPLGLoader.h"
#include <string.h>
#include <ctype.h>

namespace mx
{
	namespace resource
	{
		CPLGLoader::CPLGLoader(const char *filename)
		{
			memset(&m_plg, 0, sizeof(m_plg));

			FILE *fp = fopen(filename, "r");
			if (fp)
			{
				const int MAX_BUF = 256;
				char buf[MAX_BUF];

				char *string = GetLinePLG(buf, MAX_BUF, fp);
				if (string)
				{
					sscanf(string, "%s %d %d", m_plg.objectName, &m_plg.verticesNum, &m_plg.polygonsNum);

					m_plg.vertices = new Vertex[m_plg.verticesNum];
					m_plg.polygons = new Polygon[m_plg.polygonsNum];

					//加载顶点数
					for (int i = 0; i < m_plg.verticesNum; ++i)
					{
						string = GetLinePLG(buf, MAX_BUF, fp);
						if (string)
						{
							sscanf(string, "%f %f %f", &m_plg.vertices[i].x, &m_plg.vertices[i].y, &m_plg.vertices[i].z);
						}
					}

					//加载多边形

				}

				fclose(fp);
			}
			else
			{
				printf("Error:open file %s failed.\n", filename);
			}
		}
		CPLGLoader::~CPLGLoader()
		{

		}
		const char * CPLGLoader::GetObjectName()
		{
			return nullptr;
		}
		int CPLGLoader::GetVerticesNum()
		{
			return 0;
		}
		int CPLGLoader::GetPolygonsNum()
		{
			return 0;
		}
		Vertex * CPLGLoader::GetVertices()
		{
			return nullptr;
		}
		Polygon * CPLGLoader::GetPolygons()
		{
			return nullptr;
		}
		char * CPLGLoader::GetLinePLG(char * buffer, int maxlength, FILE * fp)
		{
			if (fp && buffer)
			{
				int index = 0;
				int length = 0;
				
				while (true)
				{
					if (!fgets(buffer, maxlength, fp))
						return NULL;

					length = strlen(buffer);

					//计算空格数
					for (index = 0; isspace(buffer[index]); ++index);

					//检查是否为空行或注释
					if (index >= maxlength || buffer[index] == '#')
						continue;
					return &buffer[index];
				}
			}
			return NULL;
		}
	}
}