/************************************************************************/
/* 材质接口                                                             */
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

			//使用光照模型
			virtual EIlluminationModel GetIlluminationModel() = 0;
			virtual void SetIlluminationModel(EIlluminationModel) = 0;
			
			//获取镜面反射系数
			virtual float GetSpecularCoefficient() = 0;
			virtual void SetSpecularCoefficient(float) = 0;

			//获取高光指数
			virtual float GetSpecularIndex() = 0;
			virtual void SetSpecularIndex(float) = 0;
			
			//获取环境光反射系数
			virtual float GetAmbientCoefficient() = 0;
			virtual void SetAmbientCoefficient(float) = 0;

			//获取漫反射系数
			virtual float GetDiffuseCoefficient() = 0;
			virtual void SetDiffuseCoefficient(float) = 0;

			//对光的反射度
			virtual float GetReflectRed() = 0;
			virtual float GetReflectGreen() = 0;
			virtual float GetReflectBlue() = 0;			
			virtual void SetReflectColor(float r, float g, float b) = 0;

		};
	}
}

#endif