#ifndef _MX_RENDER_S_VERTEX_ATTRIBUTE_H_
#define _MX_RENDER_S_VERTEX_ATTRIBUTE_H_

namespace mx
{
	namespace render
	{
		enum VertexAttributeLocation
		{
			VAL_POSITION = 0,
			VAL_COLOR,
			VAL_NORMAL,
			VAL_TEXTURE0,
			VAL_TEXTURE1,
			VAL_TEXTURE2,
			VAL_TEXTURE3,
			VAL_TEXTURE4,
			VAL_TEXTURE5,
			VAL_TEXTURE6,
			VAL_TEXTURE7,
			VAL_TEXTURE8,		

			VAL_NUM
		};

		typedef struct
		{
			int attrId;
			const char *attrName;
		}SVertexAttribute;

		static SVertexAttribute g_sVertexAttributeArray[VAL_NUM]
		{
			{ VAL_POSITION, "vVertex" },
			{ VAL_COLOR, "vColor" },
			{ VAL_NORMAL, "vNormal" },
			{ VAL_TEXTURE0, "vTexCoord0" },
			{ VAL_TEXTURE1, "vTexCoord1" },
			{ VAL_TEXTURE2, "vTexCoord2" },
			{ VAL_TEXTURE3, "vTexCoord3" },
			{ VAL_TEXTURE4, "vTexCoord4" },
			{ VAL_TEXTURE5, "vTexCoord5" },
			{ VAL_TEXTURE6, "vTexCoord6" },
			{ VAL_TEXTURE7, "vTexCoord7" },
			{ VAL_TEXTURE8, "vTexCoord8" },
		};
	}
}

#endif
