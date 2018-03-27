#ifndef _SE_RENDER_I_SHADER_ATTRIBUTE_H_
#define _SE_RENDER_I_SHADER_ATTRIBUTE_H_

#include "base/seType.h"
#include "base/VertexAttribute.h"

namespace se
{
	namespace render
	{
		typedef struct SShaderAttrData
		{
		public:
			SShaderAttrData(base::EVertexAttribute vertType, void *source, uint size)
			{
				data = new byte[size];
				memcpy(data, source, size);
			}
			SShaderAttrData(const SShaderAttrData &attrData)
			{
				size = attrData.size;
				data = new byte[size];
				memcpy(data, attrData.data, size);
			}
			
			SShaderAttrData &operator=(const SShaderAttrData &attrData)
			{
				if (&attrData != this)
				{					
					delete[]data;
					size = attrData.size;
					data = new byte[size];
					memcpy(data, attrData.data, size);
				}
				return *this;
			}

			~SShaderAttrData()
			{
				delete[]data;
			}

			base::EVertexAttribute vertType;
			uint size;
			void *data;		
			
		}ShaderAttrData;

		class IShaderAttribute
		{
		public:
			virtual const ShaderAttrData &GetAttribute(base::EVertexAttribute vertType) const = 0;
			virtual void SetAttribute(base::EVertexAttribute vertType, void *source, uint size) = 0;
		};
	}
}

#endif