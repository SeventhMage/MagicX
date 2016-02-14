#ifndef _MX_SCENE_CSPHEREMESHNODE_H_
#define _MX_SCENE_CSPHEREMESHNODE_H_

#include "ISceneNode.h"
#include "core/CVector2.h"

namespace mx
{
	namespace scene
	{
		using core::CVector2;

		typedef struct SVertex
		{
			CVector3 vPosition;
			CVector3 vNormal;
			CVector2 vTexture;
		}Vertex;

		typedef struct STriangle
		{
			SVertex vertices[3];
		}Triangle;

		class CShpereMeshNode : public ISceneNode
		{
		public:
			CShpereMeshNode(float radius, uint uSlices, uint uStacks);
			virtual ~CShpereMeshNode();

		private:
			void AddTriangle(CVector3 verts[3], CVector3 vNorms[3], CVector2 vTexCoords[3]);
		private:
			float m_fRadius;
			uint m_uSlices;
			uint m_uStacks;
			uint m_uVertNum;			
		};
	}
}

#endif