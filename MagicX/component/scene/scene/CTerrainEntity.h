#ifndef _MX_SCENE_C_TERRAIN_ENTITY_H_
#define _MX_SCENE_C_TERRAIN_ENTITY_H_

#include "../include/ITerrainSceneNode.h"
#include "ITexture.h"
#include "IRenderer.h"
#include "CMesh.h"

namespace mx
{
	namespace scene
	{
		class CTerrainEntity : public ITerrainSceneNode
		{
		public:
			CTerrainEntity(render::IRenderer *renderer, uint width);
			virtual ~CTerrainEntity();

			void RandGenerateMesh();

			void RandHeightMap();
			void RandHeightMapSD(int lefttop, int righttop, int rightbottom, int leftbottom, float zoom);
			short GetHeight(uint x, uint y);
			void GenerateMesh();	
			virtual void UpdateImp(int elapsedTime, const CMatrix4 &mat4MVP, const CMatrix4 &mat4MV);
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
			short *m_pHeightMap;		//高度图
			CMesh *m_pMeshData;
			render::ITerrainTextureGenerator *m_pTextureGenerator;
			render::ITexture *m_pTexture;
			render::IRenderer *m_pRenderer;
			render::IGPUBuffer *m_pGPUBuffer;
			render::IRenderableObject *m_pRenderableObject;
			static const int MAX_HEIGHT = 128;
		};
	}
}

#endif
