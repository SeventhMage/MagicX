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
			ITexture *m_pTexture;			//����
			IShader *m_pShader;				//��ɫ��
			float m_fAlpha;					//͸����
			float m_fSmoothness;			//�⻬��
			float m_fReflectivity;			//������
			float m_fRefractivity;			//������
			float m_fLuminosity;			//�����
		};
	}
}

#endif