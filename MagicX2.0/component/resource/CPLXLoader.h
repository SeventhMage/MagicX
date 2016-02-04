#ifndef _MX_RESOURCE__CPLXLOADER_H_
#define _MX_RESOURCE__CPLXLOADER_H_

#include "resource/IResourceLoader.h"
#include "core/CVector3.h"
#include "resource/Polygon.h"

#include <stdio.h>

namespace mx
{
	namespace resource
	{
#define MAX_FILE_NAME 256

#define PLX_RGB_MASK	0x8000	//��ȡRGB/������ɫģʽ������
#define PLX_SHADER_MODE_MASK	0x6000	//��ȡ��ɫģʽ������
#define PLX_2SIDE_MASK	0x1000	//��ȡ˫��ģʽ������
#define PLX_COLOR_MASK	0x0fff	//RGBģʽxxxxrrrrggggbbbb; ��ɫ����ģʽxxxxxxxxxiiiiiiii

//�����ж���ɫģʽ�ı��
#define PLX_COLOR_MODE_RGB_FLAG	0x8000	//ʹ��RGB��ɫ
#define PLX_COLOR_MODE_INDEXED_FLAG	0x0000	//ʹ��8λ��ɫ����

//ҳ����
#define PLX_2SIDED_FLAG	0x1000	//˫���
#define PLX_1SIDED_FLAG	0x0000	//�����

//��ɫģʽ���
#define PLX_SHADER_MODE_PURE_FLAG 0x0000	//�̶���ɫ
#define PLX_SHADER_MODE_FLAT_FLAT	0x2000	//�㶨��ɫ
#define PLX_SHADER_MODE_GOURAUD_FLAG 0x4000	//gouraud��ɫ
#define PLX_SHADER_MODE_PHONE_FLAG	0x6000	//phone��ɫ

		//plx loader
		class CPLXLoader : public IResourceLoader
		{
		public:
			CPLXLoader();
			virtual ~CPLXLoader();		
			virtual bool LoadResource(const char *filename, IResource *pResource);
		private:
			char *GetLinePLG(char *buffer, int maxlength, FILE *fp);
			const char *GetSplitParam(char *outStr, int outSize, const char *inStr, char ch);
			int GetNumber(const char *str);
		};
	}
}

#endif
