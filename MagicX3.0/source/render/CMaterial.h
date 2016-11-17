/************************************************************************/
/* 材质                                                                 */
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

			//使用光照模型
			virtual EIlluminationModel GetIlluminationModel() { return m_eIllumination; }
			virtual void SetIlluminationModel(EIlluminationModel model) { m_eIllumination = model; }

			//获取镜面反射系数
			virtual float GetSpecularCoefficient() { return m_fSpecularCoefficient; }
			virtual void SetSpecularCoefficient(float coe) { m_fSpecularCoefficient = coe; }

			//获取高光指数
			virtual float GetSpecularIndex() { return m_fSpecularIndex; }
			virtual void SetSpecularIndex(float index) { m_fSpecularIndex = index; }

			//获取环境光反射系数
			virtual float GetAmbientCoefficient() { return m_fAmbientCoefficient; }
			virtual void SetAmbientCoefficient(float coe) { m_fAmbientCoefficient = coe; }

			//获取漫反射系数
			virtual float GetDiffuseCoefficient() { return m_fDiffuseCoefficient; }
			virtual void SetDiffuseCoefficient(float coe) { m_fDiffuseCoefficient = coe; }

			//对光的反射度
			virtual float GetReflectRed() { return m_fReflectR; }
			virtual float GetReflectGreen() { return m_fReflectG; }
			virtual float GetReflectBlue() { return m_fReflectB; }
			virtual void SetReflectColor(float r, float g, float b);

		private:
			EIlluminationModel m_eIllumination;								//光照模型
			float m_fSpecularCoefficient;									//镜面反射系数
			float m_fSpecularIndex;											//高光指数
			float m_fAmbientCoefficient;									//环境光反射系数
			float m_fDiffuseCoefficient;									//漫反射系数
			float m_fReflectR, m_fReflectG, m_fReflectB;					//光的反射

		};
	}
}

#endif