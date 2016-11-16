/************************************************************************/
/* ��Դ�ӿ�                                                             */
/************************************************************************/

#ifndef _MX_SCENE_I_LIGHT_H_
#define _MX_SCENE_I_LIGHT_H_

namespace mx
{
	namespace scene
	{
		//��������
		enum ELightType
		{
			LT_AMBGIENT,
			LT_DIRECTIONAL,
			LT_POINT,
			LT_SPOT,
		};

		class ILight
		{
		public:
			virtual ~ILight(){}

			virtual ELightType GetLightType() = 0;
			virtual void SetPosition();
			virtual void GetPosition();
		};
	}
}

#endif