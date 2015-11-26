#ifndef _MX_SCENE_C_MESH_H_
#define _MX_SCENE_C_MESH_H_

#include "../include/IMesh.h"
namespace mx
{
	namespace scene
	{
		class CMesh : public IMesh
		{
		public:
			CMesh(uint vertNum, uint idsNum);
			virtual ~CMesh();

			SVertex *GetVertices() { return m_pVertices; }
			uint *GetIndices() { return m_pIndices; }
			uint GetVerticesNum() { return m_uVertNum; }
			uint GetIndicesNum() { return m_uIdsNum; }
		private:
			SVertex *m_pVertices;
			uint *m_pIndices;
			uint m_uVertNum;
			uint m_uIdsNum;
		};
	}
}

#endif
