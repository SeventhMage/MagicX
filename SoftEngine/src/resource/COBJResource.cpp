#include "COBJResource.h"
#include "base/Log.h"
#include "base/StringHelper.h"

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
					if ('t' == buf[0] && 'p' == buf[1]) //纹理路径
					{
						char *pStart = &buf[2];
						for (; isspace(*pStart); ++pStart);
						m_texturePath = pStart;
					}
					else if ('v' == buf[0] && ' ' == buf[1]) //顶点位置
					{
						CVector3 position;
						char temp[8];
						sscanf(buf, "%s %f %f %f", temp, &position.x, &position.y, &position.z);
						m_positionList.push_back(position);
					}
					else if ('v' == buf[0] && 'n' == buf[1]) //法线
					{
						CVector3 normal;
						char temp[8];
						sscanf(buf, "%s %f %f %f", temp, &normal.x, &normal.y, &normal.z);
						m_normalList.push_back(normal);
					}
					else if ('v' == buf[0] && 't' == buf[1]) //纹理坐标
					{
						bHaveTexCoord = true;
						CVector2 texCoord;
						char temp[8];
						sscanf(buf, "%s %f %f", temp, &texCoord.x, &texCoord.y);
						m_texCoordList.push_back(texCoord);
					}
					else if ('f' == buf[0]) //面
					{
						SFaceIndex faceIndex;
						memset(&faceIndex, 0, sizeof(SFaceIndex));
						char temp[8];
						StringArray split = base::Split(buf, " ");
						//下标0为'f'
						faceIndex.indicesCount = split.size() - 1;
						for (int i = 0, j=1; j < split.size(); ++i, ++j)
						{
							if (bHaveTexCoord)
							{
								sscanf(split[j].c_str(), "%d/%d/%d", &faceIndex.position[i], &faceIndex.texCoord[i], &faceIndex.normal[i]);
							}
							else
							{
								sscanf(split[j].c_str(), "%d//%d", &faceIndex.position[i], &faceIndex.normal[i]);
							}
						}

						for (int k = 0; k < faceIndex.indicesCount; ++k)
						{							
							--faceIndex.position[k];
							if (bHaveTexCoord)
								--faceIndex.texCoord[k];
							--faceIndex.normal[k];
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