/************************************************************************/
/* “ı”∞Ã˘Õº                                                             */
/************************************************************************/

#ifndef _MX_RENDER_I_SHADOW_MAP_H_
#define _MX_RENDER_I_SHADOW_MAP_H_

#include "mxType.h"

namespace mx
{
	namespace render
	{
		class IShadowMap
		{
		public:
			virtual ~IShadowMap(){}

			virtual void Render() = 0;
			virtual uint GetShadowMap() = 0;
		};
	}
}

#endif