#ifndef _RENDER_C_RENDER_CELL_H_
#define _RENDER_C_RENDER_CELL_H_

#include <map>

#include "render/IRenderCell.h"
#include "render/UniformDef.h"
#include "base/seType.h"
#include "math/CMatrix4.h"

namespace se
{
	namespace render
	{
		class CRenderCell : public IRenderCell
		{
		public:
			struct ShaderParam
			{
				EUniformName name;
				byte *data;
				EDataType type;
				uint size;
			};
			CRenderCell(uint bufferId, uint materialId, uint textureId);
			virtual ~CRenderCell();			
			virtual uint GetTextureID()const { return m_textureId; }
			virtual uint GetBufferID()const{ return m_bufferId; }
			virtual uint GetMaterialID()const { return m_materialId; }
			virtual void SetRenderQueue(IRenderQueue *parent);
			virtual void SetShaderParam(EUniformName name, void *data, EDataType type, uint size);
			virtual void BindShaderParams(IShaderProgram *pShaderParam);
		private:
			IRenderQueue *m_pParentQueue;			
			uint m_bufferId;
			uint m_textureId;
			uint m_materialId;

			std::map<EUniformName, ShaderParam>m_mapShaderParam;
		};
	}
}

#endif