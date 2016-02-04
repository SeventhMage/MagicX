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

#define PLX_RGB_MASK	0x8000	//抽取RGB/索引颜色模式的掩码
#define PLX_SHADER_MODE_MASK	0x6000	//抽取着色模式的掩码
#define PLX_2SIDE_MASK	0x1000	//抽取双面模式的掩码
#define PLX_COLOR_MASK	0x0fff	//RGB模式xxxxrrrrggggbbbb; 颜色索引模式xxxxxxxxxiiiiiiii

//用于判断颜色模式的标记
#define PLX_COLOR_MODE_RGB_FLAG	0x8000	//使用RGB颜色
#define PLX_COLOR_MODE_INDEXED_FLAG	0x0000	//使用8位颜色索引

//页面标记
#define PLX_2SIDED_FLAG	0x1000	//双面的
#define PLX_1SIDED_FLAG	0x0000	//单面的

//着色模式标记
#define PLX_SHADER_MODE_PURE_FLAG 0x0000	//固定着色
#define PLX_SHADER_MODE_FLAT_FLAT	0x2000	//恒定着色
#define PLX_SHADER_MODE_GOURAUD_FLAG 0x4000	//gouraud着色
#define PLX_SHADER_MODE_PHONE_FLAG	0x6000	//phone着色

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
