#include "CPLXLoader.h"
#include "resource/Attribute.h"
#include "CMesh.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>

namespace mx
{
	namespace resource
	{		
		CPLXLoader::CPLXLoader()
		{

		}
		CPLXLoader::~CPLXLoader()
		{
		}

		char * CPLXLoader::GetLinePLG(char * buffer, int maxlength, FILE * fp)
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

					//����ո���
					for (index = 0; isspace(buffer[index]); ++index);

					//����Ƿ�Ϊ���л�ע��
					if (index >= length || buffer[index] == '#')
						continue;
					return &buffer[index];
				}
			}
			return NULL;
		}
		const char * CPLXLoader::GetSplitParam(char *outStr, int outSize, const char * inStr, char ch)
		{
			if (!outStr || !inStr) return NULL;
			const char *pos = strchr(inStr, ch);
			if (pos)
			{
				int size = pos - inStr;
				strncpy(outStr, inStr, size < outSize ? size : outSize - 1);
			}
			else
			{
				strncpy(outStr, inStr, outSize - 1);
			}

			return pos + 1;
		}
		int CPLXLoader::GetNumber(const char * str)
		{
			if (!str) return 0;

			int num = 0;
			if (str[0] == '0' && tolower(str[1]) == 'x')
			{
				sscanf(str, "%x", &num);
			}
			else
			{
				num = atoi(str);
			}
			return num;
		}

		IMesh *CPLXLoader::LoadResource(const char *filename)
		{
			CMesh *pMesh = new CMesh();
			
			pMesh->m_uState = OBJECT_STATE_ACTIVE | OBJECT_STATE_VISIBLE;

			pMesh->m_vWorldPos.x = pMesh->m_vWorldPos.y = pMesh->m_vWorldPos.z = 0;

			FILE *fp = fopen(filename, "r");
			if (fp)
			{
				static const int MAX_BUF = 256;
				char buf[MAX_BUF];

				char *string = GetLinePLG(buf, MAX_BUF, fp);
				if (string)
				{
					sscanf(string, "%s %d %d", pMesh->m_szName, &pMesh->m_uVerticesNum, &pMesh->m_uTriangleNum);

					pMesh->m_pvLocalList = new CVector3[pMesh->m_uVerticesNum];
					pMesh->m_pTriangleList = new Triangle[pMesh->m_uTriangleNum];

					//���ض�����
					for (int i = 0; i < pMesh->m_uVerticesNum; ++i)
					{
						string = GetLinePLG(buf, MAX_BUF, fp);
						if (string)
						{
							sscanf(string, "%f %f %f", &pMesh->m_pvLocalList[i].x, &pMesh->m_pvLocalList[i].y, &pMesh->m_pvLocalList[i].z);
						}
					}

					pMesh->CalculateRadius();

					char tempBuf[MAX_BUF] = { 0 };
					//���ض����
					for (int i = 0; i < pMesh->m_uTriangleNum; ++i)
					{
						string = GetLinePLG(buf, MAX_BUF, fp);
						int indecesNum = 0;
						sscanf(string, "%d %d %d %d %d", &pMesh->m_pTriangleList[i].attr, &indecesNum, &pMesh->m_pTriangleList[i].indices[1], &pMesh->m_pTriangleList[i].indices[2], &pMesh->m_pTriangleList[i].indices[3]);
						pMesh->m_pTriangleList[i].state = POLY_STATE_ACTIVE;
					}
				}

				fclose(fp);
			}
			else
			{
				printf("Error:open file %s failed.\n", filename);
			}
			return pMesh;
		}

	}
}