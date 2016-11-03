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
			
			//Shader Program
			virtual IShaderProgram *GetShaderProgram() = 0;
			//ȡ�õ�ǰ����Ԫ������
			virtual ITexture *GetTexture(int slot = 0) = 0;

			//ʹ�ù���ģ��
			virtual EIlluminationModel GetIlluminationModel() = 0;

			//��ȡ͸����ϵ��
			virtual float GetAlpha() = 0;
			
			//��ȡ���淴��ϵ��
			virtual float GetSpecularCoefficient() = 0;
			//��ȡ�߹�ָ��
			virtual float GetSpecularIndex() = 0;
			
			//��ȡ�����ⷴ��ϵ��
			virtual float GetAmbientCoefficient() = 0;

			//��ȡ������ϵ��
			virtual float GetDiffuseCoefficient() = 0;
			

		};
	}
}

#endif