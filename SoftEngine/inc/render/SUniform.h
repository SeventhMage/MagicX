#ifndef _RENDER_E_UNIFORM_H_
#define _RENDER_E_UNIFORM_H_

#include "base/seType.h"

namespace se
{
	namespace render
	{
		enum EUniformName
		{
			UN_MODEL_MAT = 0,
			UN_WORLD_MAT,
			UN_VIEW_MAT,
			UN_PROJ_MAT,
			UN_CAM_POS,

			UN_COUNT,
		};

		struct
		{
			EUniformName identifer;
			char *name;
		}UniformName[UN_COUNT] = {
			UN_MODEL_MAT, "modelMatrix",
			UN_WORLD_MAT, "worldMatrix",
			UN_VIEW_MAT, "viewMatrix",
			UN_PROJ_MAT, "projMatrix",
		};


		enum UniformFormat
		{
			UF_UNKNOWN,
			UF_INT,
			UF_FLOAT,
			UF_VEC2,
			UF_VEC3,
			UF_VEC4,
			UF_MAT3,
			UF_MAT4,
			UF_TEXTURE,
		};


		struct Uniform
		{
			char m_name[MAX_FILE_NAME];
			int m_location;
			UniformFormat m_format;
			int m_count;
			int m_size;
			byte *m_value;
			bool m_bDirty;
			Uniform()
				: m_location(0)
				, m_format(UF_UNKNOWN)
				, m_count(0)
				, m_size(0)
				, m_value(NULL)
				, m_bDirty(false)
			{
				memset(m_name, 0, sizeof(m_name));
			}
			~Uniform()
			{
				SAFE_DEL(m_value);
			}

			void SetValue(const void *value)
			{
				if (value && m_size > 0)
				{
					if (!m_value)
					{
						m_value = new byte[m_size];
					}
					memcpy(m_value, value, m_size);
					Dirty(true);
				}
			}
			inline void Dirty(bool bDirty) { m_bDirty = bDirty; }
			inline bool IsDirty() const { return m_bDirty; }
		};


	}
}

#endif