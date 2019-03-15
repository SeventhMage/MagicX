#ifndef _MX_RENDER_C_UNIFOM_H_
#define _MX_RENDER_C_UNIFOM_H_

#include "mxDef.h"
#include "render/ERender.h"
#include "mxType.h"


namespace mx
{
	namespace render
	{
		class SUniform
		{
		public:
			SUniform(const char *name);
			~SUniform();

			void SetValue(const void *value, uint size);
			
			char m_name[MAX_FILE_NAME];
			UniformFormat m_format;
			int m_count;
			int m_size;
			byte *m_value;

		private:
			SUniform(const SUniform&);
			SUniform &operator=(const SUniform &);


		};
	}
}

#endif