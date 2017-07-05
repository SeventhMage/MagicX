#ifndef _RENDER_C_RENDER_CELL_H_
#define _RENDER_C_RENDER_CELL_H_

#include "render/IRenderCell.h"
#include "base/seType.h"
#include "math/CMatrix4.h"

namespace se
{
	namespace render
	{
		class CRenderCell : public IRenderCell
		{
		public:
			CRenderCell(uint bufferId, uint materialId, uint textureId);
			virtual ~CRenderCell();
			virtual uint GetMaterialID()const{ return m_materialId; }
			virtual uint GetTextureID()const { return m_textureId; }
			virtual uint GetBufferID()const{ return m_bufferId; }
			virtual IShaderProgram *GetShaderProgram()const{ return m_pShaderProgram; }

		private:			
			uint m_materialId;
			uint m_bufferId;
			uint m_textureId;
			IShaderProgram *m_pShaderProgram;
		};
	}
}

#endif