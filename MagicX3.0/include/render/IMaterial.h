/************************************************************************/
/* ²ÄÖÊ½Ó¿Ú                                                             */
/************************************************************************/

#ifndef _MX_RENDER_I_MATERIAL_H_
#define _MX_RENDER_I_MATERIAL_H_

#include "ITexture.h"
#include "IShaderProgram.h"

namespace mx
{
	namespace render
	{
		class IMaterial
		{
		public:
			virtual ~IMaterial(){}

			virtual IShaderProgram *GetShaderProgram() const = 0;

			virtual int GetID() const = 0;
		};
	}
}

#endif