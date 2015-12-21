#include "../include/CEntity.h"

namespace mx
{
	namespace scene
	{
		CEntity::CEntity()
			:m_pMeshData(NULL)
			,m_pTexture(NULL)
		{
		}
		CEntity::~CEntity()
		{
		}
		bool CEntity::LoadEntity(const char * filename)
		{
			bool bRet = false;
			const char *extPos = strrchr(filename, '.');
			if (extPos)
			{
				if (extPos == ".xml")
				{
					bRet = true;
				}
			}
			else
			{
				printf("Invalid filename\n");
			}
			return bRet;
		}		
	}
}