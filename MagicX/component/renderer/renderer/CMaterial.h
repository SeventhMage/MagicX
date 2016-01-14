#ifndef _MX_RENDER_C_MATERIAL_H_
#define _MX_RENDER_C_MATERIAL_H_

#include "../include/IMaterial.h"
#include "../include/ITexture.h"
#include "../include/IShader.h"

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
			ITexture *m_pTexture;			//纹理
			IShader *m_pShader;				//着色器
			float m_fAlpha;					//透明度
			float m_fSmoothness;			//光滑度
			float m_fReflectivity;			//反射率
			float m_fRefractivity;			//折射率
			float m_fLuminosity;			//发光度
		};
	}
}

#endif