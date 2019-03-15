/************************************************************************/
/* ²ÄÖÊ                                                                 */
/************************************************************************/

#ifndef _MX_RENDER_C_MATERIAL_H_
#define _MX_RENDER_C_MATERIAL_H_

#include "render/IMaterial.h"
#include "mxDef.h"

#include <map>

namespace mx
{
	namespace render
	{
		class CMaterial : public IMaterial
		{
		public:
			CMaterial(int id);
			virtual ~CMaterial();

			virtual IShaderProgram *GetShaderProgram() const { return m_pShaderProgram; }

			virtual void BindConstantUniform();

			virtual int GetID() const { return m_id; }
		private:
			int m_id;
			IShaderProgram *m_pShaderProgram;
		};
	}
}

#endif