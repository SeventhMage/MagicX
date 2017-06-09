#ifndef _RESOURCE_C_OBJ_LOADER_H_
#define _RESOURCE_C_OBJ_LOADER_H_

#include "resource/IResourceLoader.h"
#include "math/CVector3.h"
#include "math/CVector2.h"

#include <vector>
#include <fstream>

namespace se
{
	namespace resource
	{
		using namespace math;
		struct SFaceIndex
		{
			int position[4];
			int texCoord[4];
			int normal[4];
		};
		class COBJLoader : public IResourceLoader
		{
		public:
			COBJLoader(const char *filename);
			virtual ~COBJLoader();
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