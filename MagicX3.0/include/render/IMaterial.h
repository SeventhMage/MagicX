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
			
			//Shader Program
			virtual IShaderProgram *GetShaderProgram() = 0;
			//取得当前纹理单元的纹理
			virtual ITexture *GetTexture(int slot = 0) = 0;

			//使用光照模型
			virtual EIlluminationModel GetIlluminationModel() = 0;

			//获取透明度系数
			virtual float GetAlpha() = 0;
			
			//获取镜面反射系数
			virtual float GetSpecularCoefficient() = 0;
			//获取高光指数
			virtual float GetSpecularIndex() = 0;
			
			//获取环境光反射系数
			virtual float GetAmbientCoefficient() = 0;

			//获取漫反射系数
			virtual float GetDiffuseCoefficient() = 0;
			

		};
	}
}

#endif