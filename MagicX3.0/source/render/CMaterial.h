/************************************************************************/
/* ²ÄÖÊ                                                                 */
/************************************************************************/

#ifndef _MX_RENDER_C_MATERIAL_H_
#define _MX_RENDER_C_MATERIAL_H_

#include "render/IMaterial.h"
#include "mxDef.h"

#include <map>

namespace mx
{
	namespace render
	{
		class CMaterial : public IMaterial
		{
		public:
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
					, m_value(nullptr)
					, m_bDirty(false)
				{
					memset(m_name, 0, sizeof(m_name));
				}
				~Uniform()
				{
					SAFE_DEL(m_value);
				}

				void SetValue(const void *value, uint size)
				{
					if (value && size > 0)
					{
						if (!m_value || size != m_size)
						{
							m_size = size;
							SAFE_DEL(m_value);
							m_value = new byte[m_size];
						}
						memcpy(m_value, value, m_size);
						Dirty(true);
					}
				}
				inline void Dirty(bool bDirty) { m_bDirty = bDirty; }
				inline bool IsDirty() const { return m_bDirty; }
			private:
				Uniform(const Uniform&);
				Uniform &operator=(const Uniform &);
			};
			typedef std::map<int, Uniform> UniformArray;

			CMaterial(int id);
			virtual ~CMaterial();

			virtual IShaderProgram *GetShaderProgram() const { return m_pShaderProgram; }

			virtual int GetID() const { return m_id; }
		private:
			int m_id;
			IShaderProgram *m_pShaderProgram;
			UniformArray m_uniforms;
		};
	}
}

#endif