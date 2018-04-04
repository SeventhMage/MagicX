/************************************************************************/
/* 天空盒接口                                                           */
/************************************************************************/

#ifndef _SE_SCENE_I_SKYBOX_H_
#define _SE_SCENE_I_SKYBOX_H_

namespace se
{
	namespace scene
	{
		class ISkyBox
		{
		public:
			virtual ~ISkyBox(){}
			virtual bool Create(const char *filename) = 0;
			virtual bool Create(const char *right, const char *left, const char *top, const char *bottom, const char *front, const char *back) = 0;
			virtual void Update(int delta) = 0;			
		};
	}
}

#endif