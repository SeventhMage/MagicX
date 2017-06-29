/************************************************************************/
/* ������IRenderQueue�д������Ϣ                                       */
/************************************************************************/

#ifndef _RENDER_I_RENDER_CELL_H_
#define _RENDER_I_RENDER_CELL_H_

#include "base/seType.h"

namespace se
{
	namespace render
	{
		class IRenderCell
		{
		public:
			virtual ~IRenderCell(){}		
			virtual uint GetMaterialID()const = 0;
			virtual uint GetTextureID()const = 0;
			virtual uint GetBufferID()const = 0;
		};
	}
}

#endif