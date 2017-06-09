#include "CSceneLoader.h"
#include "base/Log.h"
#include <ctype.h>


namespace se
{
	namespace resource
	{

		CSceneLoader::CSceneLoader(const char *filename)
		{
			std::ifstream in(filename);
			if (in.is_open())
			{
				char buf[512];

				ReadLine(in, buf, 512);
				sscanf_s(buf, "%f %f %f", &m_camPos.x, &m_camPos.y, &m_camPos.z);


				ReadLine(in, buf, 512);
				sscanf_s(buf, "%f %f %f", &m_camDir.x, &m_camDir.y, &m_camDir.z);


				ReadLine(in, buf, 512);
				sscanf_s(buf, "%f %f %f", &m_camUp.x, &m_camUp.y, &m_camUp.z);
				

				ReadLine(in, buf, 512);
				sscanf_s(buf, "%f", &m_camFov);

				ReadLine(in, buf, 512);
				sscanf_s(buf, "%f", &m_camNearClip);

				ReadLine(in, buf, 512);
				sscanf_s(buf,"%f", &m_camFarClip);

				while (ReadLine(in, buf, 512))
				{						
					SEntityInfo entity;
					sscanf_s(buf, "%s %f %f %f", entity.name, sizeof(entity.name), &entity.position.x, &entity.position.y, &entity.position.z);
					m_vecEntity.push_back(entity);
				}
				in.close();
			}
			else
			{
				LogPrint("Can't open resource:%s\n", filename);
			}
		}

		CSceneLoader::~CSceneLoader()
		{

		}

		bool CSceneLoader::ReadLine(std::ifstream &in, char *out, int size)
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