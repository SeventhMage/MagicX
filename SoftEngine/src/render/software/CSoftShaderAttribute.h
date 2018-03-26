#ifndef _SE_RENDER_SOFT_SHADER_ATTRIBUTE_
#define _SE_RENDER_SOFT_SHADER_ATTRIBUTE_

#include "render/IShaderAttribute.h"
#include "math/CVector3.h"

namespace se
{
	namespace render
	{
		class CSoftShaderAttribute : public IShaderAttribute
		{
		public:
			virtual const ShaderAttrData &GetAttribute(base::EVertexAttribute vertType);
			virtual void SetAttribute(base::EVertexAttribute vertType, void *source, uint size);
		private:
			std::vector<ShaderAttrData> m_vecAttrData;
		};
	}
}

#endif