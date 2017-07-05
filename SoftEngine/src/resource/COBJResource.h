#ifndef _RESOURCE_C_OBJ_RESOURCE_H_
#define _RESOURCE_C_OBJ_RESOURCE_H_

#include "resource/IOBJResource.h"


namespace se
{
	namespace resource
	{		
		class COBJResource : public IOBJResource
		{
		public:
			COBJResource(const char *filename);
			virtual ~COBJResource();
			const std::vector<CVector3> &GetPositionList(){ return m_positionList; }
			const std::vector<CVector3> &GetNormalList(){ return m_normalList; }
			const std::vector<CVector2> &GetTexCoordList(){ return m_texCoordList; }
			const std::vector<SFaceIndex> &GetFaceIndexList(){ return m_faceList; }
		private:
			bool ReadLine(std::ifstream &in, char *out, int size);
		private:
			std::vector<CVector3> m_positionList;
			std::vector<CVector3> m_normalList;
			std::vector<CVector2> m_texCoordList;
			std::vector<SFaceIndex> m_faceList;
		};
	}
}

#endif