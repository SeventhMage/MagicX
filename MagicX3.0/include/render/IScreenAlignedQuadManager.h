#ifndef _MX_RENDER_I_SCREEN_ALIGNED_QUAD_MANAGER_H_
#define _MX_RENDER_I_SCREEN_ALIGNED_QUAD_MANAGER_H_


namespace mx
{
	namespace render
	{
		class IScreenAlignedQuadManager
		{
		public:
			virtual ~IScreenAlignedQuadManager(){}
			virtual void CreateScreenAlignedQuad(const char *name, IRenderQueue *pRenderQuque) = 0;
			virtual void Render() = 0;
		};
	}
}

#endif