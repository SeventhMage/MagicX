#ifndef _MX_RENDER_I_RENDER_PHASE_H_
#define _MX_RENDER_I_RENDER_PHASE_H_

#include "render/IRenderTarget.h"
#include "render/IRenderer.h"

namespace mx
{
	namespace render
	{
		enum ERenderPhaseID
		{
			ERPI_SHADOWMAP,
			ERPI_SCENEGRAPH,
			ERPI_POSTPROCESS,
			ERPI_SCENEOUTCOME,
		};

		class IRenderPhase
		{
		public:
			virtual void Initialize(IRenderer *pRenderer, int width, int height) = 0;
			virtual void Destroy() = 0;
			virtual void Render() = 0;
			virtual int GetPhaseID() const = 0;

			virtual void SetEnable(bool bEnable) = 0;
			virtual bool IsEnable() const = 0;
			virtual IRenderTarget *GetRenderTarget() const = 0;
		};
	}
}

#endif