/************************************************************************/
/* ���ʽӿ�                                                             */
/************************************************************************/

#ifndef _MX_RENDER_I_MATERIAL_H_
#define _MX_RENDER_I_MATERIAL_H_

#include "ITexture.h"
#include "IShaderProgram.h"

namespace mx
{
	namespace render
	{
		enum EIlluminationModel
		{
			IM_PHONE,
		};

		class IMaterial
		{
		public:
			virtual ~IMaterial(){}

			//ʹ�ù���ģ��
			virtual EIlluminationModel GetIlluminationModel() = 0;
			virtual void SetIlluminationModel(EIlluminationModel) = 0;
			
			//��ȡ���淴��ϵ��
			virtual float GetSpecularCoefficient() = 0;
			virtual void SetSpecularCoefficient(float) = 0;

			//��ȡ�߹�ָ��
			virtual float GetSpecularIndex() = 0;
			virtual void SetSpecularIndex(float) = 0;
			
			//��ȡ�����ⷴ��ϵ��
			virtual float GetAmbientCoefficient() = 0;
			virtual void SetAmbientCoefficient(float) = 0;

			//��ȡ������ϵ��
			virtual float GetDiffuseCoefficient() = 0;
			virtual void SetDiffuseCoefficient(float) = 0;

			//�Թ�ķ����
			virtual float GetReflectRed() = 0;
			virtual float GetReflectGreen() = 0;
			virtual float GetReflectBlue() = 0;			
			virtual void SetReflectColor(float r, float g, float b) = 0;

		};
	}
}

#endif