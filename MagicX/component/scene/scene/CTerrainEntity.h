#ifndef _MX_SCENE_C_TERRAIN_ENTITY_H_
#define _MX_SCENE_C_TERRAIN_ENTITY_H_

#include "../include/ITerrainSceneNode.h"
#include "ITexture.h"
#include "IRenderer.h"

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
			float RandHeightMap(int left, int top, int right, int bottom, float zoom);
			void RandHeightMapSD(int lefttop, int righttop, int rightbottom, int leftbottom, float zoom);
			short GetHeight(uint x, uint y);
			void GenerateMesh();
			virtual void UpdateImp(int elapsedTime, const CMatrix4 &mat4ViewProj);
		private:
			int GetLeftHeight(int high, int low);
			int GetTopHeight(int high, int low);
			int GetRightHeight(int high, int low);
			int GetBottomHeight(int high, int low);
		private:
			uint m_uWidth;			//大小：m_uWidth * m_uWidth
			short *m_pHeightMap;		//高度图
			float *m_pMeshData;
			render::ITexture *m_pTextureArray;
			render::IRenderer *m_pRenderer;
			render::IGPUBuffer *m_pGPUBuffer;
			render::IRenderableObject *m_pRenderableObject;
			static const int MAX_HEIGHT = 256;
		};
	}
}

#endif
