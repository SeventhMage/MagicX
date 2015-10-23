#ifndef _MX_RENDER_C_SHADERPROGRAM_H_
#define _MX_RENDER_C_SHADERPROGRAM_H_

#include "../include/IShaderProgram.h"
#include <map>

namespace mx
{
	namespace render
	{
		class CShaderProgram : public IShaderProgram
		{
		public:
			struct Uniform
			{
				CString m_name;
				int m_location;
				UniformFormat m_format;
				int m_count;
				int m_size;
				Byte *m_value;
				bool m_bDirty;
				Uniform()
					:m_name("UnKnown")
					, m_location(0)
					, m_format(UF_UNKNOWN)
					, m_count(0)
					, m_size(0)
					, m_value(NULL)
					, m_bDirty(false)
				{

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
							m_value = new Byte[m_size];
						}
						memcpy(m_value, value, m_size);
						Dirty(true);
					}
				}
				inline void Dirty(bool bDirty) { m_bDirty = bDirty; }
				inline bool IsDirty() const { return m_bDirty; }
			};
			typedef std::map<int, Uniform> UniformArray;
			CShaderProgram();
			virtual ~CShaderProgram();

			virtual void SetUniform(const char *name, void *value);
			virtual void SetUniform(int location, void *value);
			virtual void BindUniform(){};
			virtual void BindAttributeLocation(int argc, ...){};
		private:
			int GetUniformLocation(const char *name) const;
		protected:
			UniformArray m_uniforms;
		};
	}
}

#endif