/************************************************************************/
/* “ı”∞Ã˘Õº                                                             */
/************************************************************************/

#ifndef _MX_RENDER_I_SHADOW_MAP_H_
#define _MX_RENDER_I_SHADOW_MAP_H_

#include "mxType.h"
#include "IShaderProgram.h"
#include "ITexture.h"

namespace mx
{
	namespace render
	{
		class IShadowMap
		{
		public:
			virtual ~IShadowMap(){}

			virtual void Render() = 0;
			virtual ITexture *GetShadowMap() = 0;
			virtual IShaderProgram *GetShaderProgram() = 0;
		};
	}
}

#endif