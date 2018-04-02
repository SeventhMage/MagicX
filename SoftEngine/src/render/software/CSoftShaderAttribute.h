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
			virtual ~CSoftShaderAttribute();
			virtual inline ShaderAttrData GetAttribute(base::EVertexAttribute vertType) const;
			virtual inline void SetAttribute(base::EVertexAttribute vertType, const void *source, uint size);
			virtual void Clear();

		private:
			std::vector<ShaderAttrData> m_vecAttrData;
		};
	}
}

#endif