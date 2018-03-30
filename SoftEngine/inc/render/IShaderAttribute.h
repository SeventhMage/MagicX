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
			SShaderAttrData()
				:vertType(base::VA_NONE), size(0), data(nullptr)
			{

			}
			SShaderAttrData(base::EVertexAttribute vertType, const void *source, uint size)
				:size(size)
				, vertType(vertType)
			{
				data = new ubyte[size];
				memcpy(data, source, size);
			}
			SShaderAttrData(const SShaderAttrData &attrData)
				:size(attrData.size)
				, vertType(attrData.vertType)
			{				
				data = new ubyte[size];
				memcpy(data, attrData.data, size);
			}
			
			SShaderAttrData &operator=(const SShaderAttrData &attrData)
			{
				if (&attrData != this)
				{					
					delete[]data;
					size = attrData.size;
					vertType = attrData.vertType;
					data = new ubyte[size];
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
			ubyte *data;		
			
		}ShaderAttrData;

		class IShaderAttribute
		{
		public:
			virtual ~IShaderAttribute(){}
			virtual ShaderAttrData GetAttribute(base::EVertexAttribute vertType) const = 0;
			virtual void SetAttribute(base::EVertexAttribute vertType, const void *source, uint size) = 0;
		};
	}
}

#endif