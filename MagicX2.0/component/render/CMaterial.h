#ifndef _MX_RENDER_C_MATERIAL_H_
#define _MX_RENDER_C_MATERIAL_H_

#include "render/IMaterial.h"
#include "render/ITexture.h"
#include "render/IShader.h"

namespace mx
{
	namespace render
	{
		class CMaterial : public IMaterial
		{
		public:
			CMaterial();
			virtual ~CMaterial();
		protected:
			float m_fAlpha;					//透明度
			float m_fSmoothness;			//光滑度
			float m_fReflectivity;			//反射率
			float m_fRefractivity;			//折射率
			float m_fLuminosity;			//发光度
		};
	}
}

#endif