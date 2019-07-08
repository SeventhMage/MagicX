#ifndef _MX_UI_I_WINDOW_H_
#define _MX_UI_I_WINDOW_H_

#include "math/CVector2.h"

namespace mx
{
	namespace ui
	{
		using math::CVector2;
		class IWindow
		{
		public:
			virtual ~IWindow() {};
			virtual const CVector2 &GetPosition() const = 0;
			virtual void SetPosition(const CVector2 &position) = 0;
			virtual void SetScale() = 0;
		};
	}
}

#endif