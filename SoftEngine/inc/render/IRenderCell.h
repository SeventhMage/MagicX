/************************************************************************/
/* 用于在IRenderQueue中处理的信息                                       */
/************************************************************************/

#ifndef _RENDER_I_RENDER_CELL_H_
#define _RENDER_I_RENDER_CELL_H_

#include "base/seType.h"
#include "IShaderProgram.h"

namespace se
{
	namespace render
	{
		class IRenderQueue;
		class IRenderCell
		{
		public:
			virtual ~IRenderCell(){}			
			virtual uint GetTextureID()const = 0;
			virtual uint GetBufferID()const = 0;
			virtual uint GetMaterialID()const = 0;
			virtual void SetRenderQueue(IRenderQueue *parent) = 0;
			virtual void SetShaderParam(EUniformName name, void *data, EDataType type, uint size) = 0;
			virtual void BindShaderParams(IShaderProgram *) = 0;			
		};
	}
}

#endif