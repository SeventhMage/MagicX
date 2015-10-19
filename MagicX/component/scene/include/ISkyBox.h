#ifndef _I_SKY_BOX_INC_
#define _I_SKY_BOX_INC_

namespace mx
{
	namespace scene
	{
		class ISkyBox
		{
		public:
			ISkyBox(){}
			virtual ~ISkyBox(){}
			
			virtual bool Create() = 0;
			virtual void Update() = 0;
		};
	}
}

#endif // !_I_SKY_BOX_INC_
