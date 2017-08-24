#ifndef _RENDER_I_LIGHT_MODEL_H_
#define _RENDER_I_LIGHT_MODEL_H_

namespace se
{
	namespace render
	{
		class ILightModel
		{
		public:
			virtual ~ILightModel(){}
			virtual void Render();
		};
	}
}

#endif