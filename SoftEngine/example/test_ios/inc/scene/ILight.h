/************************************************************************/
/* 光源接口                                                             */
/************************************************************************/

#ifndef _SE_SCENE_I_LIGHT_H_
#define _SE_SCENE_I_LIGHT_H_

namespace se
{
	namespace scene
	{
		//光照类型
		enum ELightType
		{
			LT_DIRECTIONAL,
			LT_POINT,
			LT_SPOT,
		};

		class ILight
		{
		public:
			virtual ~ILight(){}

			virtual ELightType GetLightType() = 0;

			//光的颜色
			virtual void SetColor(float fColor[4]) = 0;
			virtual float *GetColor() = 0;

		};
	}
}

#endif