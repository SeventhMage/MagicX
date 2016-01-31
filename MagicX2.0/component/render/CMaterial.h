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
			float m_fAlpha;					//͸����
			float m_fSmoothness;			//�⻬��
			float m_fReflectivity;			//������
			float m_fRefractivity;			//������
			float m_fLuminosity;			//�����
		};
	}
}

#endif