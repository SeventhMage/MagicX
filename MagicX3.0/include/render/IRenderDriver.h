/************************************************************************/
/* ��Ⱦ��������ͬ������ʹ�ò�����Ⱦ���棬��OpenGL��DX���������         */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDER_DRIVER_H_
#define _MX_RENDER_I_RENDER_DRIVER_H_

#ifdef WIN32
#include <windows.h>
#endif

namespace mx
{
	namespace render
	{
		//��Ⱦ��������
		enum ERenderDriverType
		{
			RDT_OPENGL,				//ʹ��OpenGL�ӿ�
			RDT_DIRECTX,			//ʹ��DirectX�ӿ�
			RDT_SOFTWARE,			//ʹ���������
		};
		class IRenderDriver
		{
		public:
			virtual ~IRenderDriver(){};
			
#ifdef WIN32
			virtual void InitDriverWin32(HDC hDc) = 0;
#endif
			virtual void Render() = 0;
			virtual void OnSize(int x, int y, int width, int height) = 0;
		};
	}
}

#endif