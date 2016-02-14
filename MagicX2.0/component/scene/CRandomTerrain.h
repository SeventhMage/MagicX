#ifndef _MX_SCENE_C_TERRAIN_ENTITY_H_
#define _MX_SCENE_C_TERRAIN_ENTITY_H_

#include "scene/ITerrain.h"
#include "render/ITexture.h"
#include "render/IRenderer.h"
#include "core/CVector3.h"
#include "core/CMatrix4.h"

namespace mx
{
	namespace scene
	{
		typedef struct
		{
			core::CVector3 vPosition;
			core::CVector3 vNormal;
			float u, v;
		}SVertex;

		typedef struct
		{
			SVertex *pVertices;
			uint *pIndices;
			uint uVertNum;
			uint uIdsNum;
		}SMesh;

		class CRandomTerrain : public ITerrain
		{
		public:
			CRandomTerrain(render::IRenderer *renderer, uint width);
			virtual ~CRandomTerrain();

			void RandGenerateMesh();

			void RandHeightMap();
			void RandHeightMapSD(int lefttop, int righttop, int rightbottom, int leftbottom, float zoom);
			short GetHeight(uint x, uint y);
			void GenerateMesh();	
			virtual void Update(int elapsedTime, const core::CMatrix4 &mat4MVP, const core::CMatrix4 &mat4MV);
		private:
			short GetLeftHeight(uint high, uint low);
			short GetTopHeight(uint high, uint low);
			short GetRightHeight(uint high, uint low);
			short GetBottomHeight(uint high, uint low);
			float GetRandomHeight(float zoom);
			float GetRandomHeight(short base, short range);
			short GetMaxAndmin(short &maxValue, short &minValue, short value1, short value2, short value3, short value4);
		private:
			uint m_uWidth;			//大小：m_uWidth * m_uWidth
			int m_maxHeight;
			short *m_pHeightMap;		//高度图			
			SMesh *m_pMeshData;

			render::ITerrainTextureGenerator *m_pTextureGenerator;
			render::ITexture *m_pTexture;
			render::IRenderer *m_pRenderer;
			render::IGPUBuffer *m_pGPUBuffer;
			render::IRenderableObject *m_pRenderableObject;
			
		};
	}
}

#endif
