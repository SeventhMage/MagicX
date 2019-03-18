#ifndef _EXAMPLE_C_HOUSE_H_
#define _EXAMPLE_C_HOUSE_H_

#include "scene/CEntity.h"

namespace mx
{
	namespace ex
	{
		class CHouse : public scene::CEntity
		{
		public:
			CHouse(float w, float h, float d);
			~CHouse();
			virtual void UpdateImp(int delta);
		private:
			float m_fWidth;
			float m_fHeight;
			float m_fDepth;
		};
	}
}

#endif