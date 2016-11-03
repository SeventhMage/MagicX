/************************************************************************/
/* Ä£ÐÍ                                                                 */
/************************************************************************/

#ifndef _MX_SCENE_C_MESH_H_
#define _MX_SCENE_C_MESH_H_

#include "resource/IMesh.h"

namespace mx
{
	namespace resource
	{
		class CMesh : public IMesh
		{
		public:
			CMesh(int triNum);
			virtual ~CMesh();
			virtual bool HaveIndex();
			virtual PTriangle GetMesh();
			virtual int GetStride();

			void AddTriangle(const Triangle &tri);
			void Clear();
		private:
			Triangle *m_triangles;
			int m_totalTris;
			int m_curTriNum;
		};
	}
}

#endif