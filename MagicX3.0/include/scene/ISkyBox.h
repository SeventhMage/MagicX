/************************************************************************/
/* ��պнӿ�                                                           */
/************************************************************************/

#ifndef _MX_SCENE_I_SKYBOX_H_
#define _MX_SCENE_I_SKYBOX_H_

namespace mx
{
	namespace scene
	{
		class ISkyBox
		{
		public:
			virtual ~ISkyBox(){}
			virtual bool Create(const char *filename) = 0;
			virtual bool Create(const char *front, const char *back, const char * left, 
				const char *right, const char *top, const char *bottom) = 0;
			virtual void Update(int delta) = 0;
			virtual void Render() = 0;
		};
	}
}

#endif