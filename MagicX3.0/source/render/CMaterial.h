/************************************************************************/
/* ����                                                                 */
/************************************************************************/

#ifndef _MX_RENDER_C_MATERIAL_H_
#define _MX_RENDER_C_MATERIAL_H_

#include "render/IMaterial.h"

namespace mx
{
	namespace render
	{
		class CMaterial : public IMaterial
		{
		public:
			CMaterial();
			virtual ~CMaterial();

			//ʹ�ù���ģ��
			virtual EIlluminationModel GetIlluminationModel() { return m_eIllumination; }
			virtual void SetIlluminationModel(EIlluminationModel model) { m_eIllumination = model; }

			//��ȡ���淴��ϵ��
			virtual float GetSpecularCoefficient() { return m_fSpecularCoefficient; }
			virtual void SetSpecularCoefficient(float coe) { m_fSpecularCoefficient = coe; }

			//��ȡ�߹�ָ��
			virtual float GetSpecularIndex() { return m_fSpecularIndex; }
			virtual void SetSpecularIndex(float index) { m_fSpecularIndex = index; }

			//��ȡ�����ⷴ��ϵ��
			virtual float GetAmbientCoefficient() { return m_fAmbientCoefficient; }
			virtual void SetAmbientCoefficient(float coe) { m_fAmbientCoefficient = coe; }

			//��ȡ������ϵ��
			virtual float GetDiffuseCoefficient() { return m_fDiffuseCoefficient; }
			virtual void SetDiffuseCoefficient(float coe) { m_fDiffuseCoefficient = coe; }

			//�Թ�ķ����
			virtual float GetReflectRed() { return m_fReflectR; }
			virtual float GetReflectGreen() { return m_fReflectG; }
			virtual float GetReflectBlue() { return m_fReflectB; }
			virtual void SetReflectColor(float r, float g, float b);

		private:
			EIlluminationModel m_eIllumination;								//����ģ��
			float m_fSpecularCoefficient;									//���淴��ϵ��
			float m_fSpecularIndex;											//�߹�ָ��
			float m_fAmbientCoefficient;									//�����ⷴ��ϵ��
			float m_fDiffuseCoefficient;									//������ϵ��
			float m_fReflectR, m_fReflectG, m_fReflectB;					//��ķ���

		};
	}
}

#endif