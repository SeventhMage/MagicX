#include "COBJResource.h"
#include "base/Log.h"

#include <fstream>


namespace se
{
	namespace resource
	{


		COBJResource::COBJResource(const char *filename)
		{
			std::ifstream in(filename);
			if (in.is_open())
			{
				bool bHaveTexCoord = false;
				char buf[512];
				while (ReadLine(in, buf, 512))
				{
					if ('v' == buf[0] && ' ' == buf[1]) //顶点位置
					{
						CVector3 position;
						char temp[8];
						sscanf_s(buf, "%s %f %f %f", temp, sizeof(temp), &position.x, &position.y, &position.z);
						m_positionList.push_back(position);
					}
					else if ('v' == buf[0] && 'n' == buf[1]) //法线
					{
						CVector3 normal;
						char temp[8];
						sscanf_s(buf, "%s %f %f", temp, sizeof(temp), &normal.x, &normal.y, &normal.z);
						m_normalList.push_back(normal);
					}
					else if ('v' == buf[0] && 't' == buf[1]) //纹理坐标
					{
						bHaveTexCoord = true;
						CVector2 texCoord;
						char temp[8];
						sscanf_s(buf, "%s %f %f", temp, sizeof(temp), &texCoord.x, &texCoord.y);
						m_texCoordList.push_back(texCoord);
					}
					else if ('f' == buf[0]) //面
					{
						SFaceIndex faceIndex;
						memset(&faceIndex, 0, sizeof(SFaceIndex));
						char temp[8];
						if (bHaveTexCoord)
						{
							sscanf_s(buf, "%s %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", temp, sizeof(temp), &faceIndex.position[0], &faceIndex.texCoord[0], &faceIndex.normal[0],
								&faceIndex.position[1], &faceIndex.texCoord[1], &faceIndex.normal[1], &faceIndex.position[2],
								&faceIndex.texCoord[2], &faceIndex.normal[2], &faceIndex.position[3],
								&faceIndex.texCoord[3], &faceIndex.normal[3]);
							for (int i = 0; i < 4; ++i)
							{
								--faceIndex.position[i];
								--faceIndex.texCoord[i];
								--faceIndex.normal[i];							
							}
						}
						else
						{
							sscanf_s(buf, "%s %d//%d %d//%d %d//%d %d//%d", temp, sizeof(temp), &faceIndex.position[0], &faceIndex.normal[0],
								&faceIndex.position[1], &faceIndex.normal[1], &faceIndex.position[2], &faceIndex.normal[2]
								, &faceIndex.position[3], &faceIndex.normal[3]);
							for (int i = 0; i < 4; ++i)
							{
								--faceIndex.position[i];								
								--faceIndex.normal[i];
							}
						}
						m_faceList.push_back(faceIndex);
					}
				}
				in.close();
			}
			else
			{
				LogPrint("Can't open resource:%s\n", filename);
			}
		}

		COBJResource::~COBJResource()
		{

		}

		bool COBJResource::ReadLine(std::ifstream &in, char *out, int size)
		{
			while (!in.eof())
			{
				in.getline(out, size);

				int i = 0;
				for (; i < size; ++i)
				{
					if (out[i] == 0)
						break;
					if (isspace(out[i]))
						continue;
					if (out[i] == '#')
						break;
					break;
				}
				if (isspace(out[i]) || out[i] == '#' || out[i] == 0)
					continue;
				return true;
			}
			return false;
		}
	}
}