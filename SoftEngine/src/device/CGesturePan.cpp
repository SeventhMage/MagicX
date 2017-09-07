#include "CGesturePan.h"
#include "base/seDef.h"

namespace se
{
	namespace device
	{

		CGesturePan::CGesturePan()
		{
            m_panArgs = new SGesturePanArgs();
		}

		CGesturePan::~CGesturePan()
		{
            SAFE_DEL(m_panArgs);
		}

		void CGesturePan::OnTouchBegin(int pointID, int x, int y, uint classID, uint touchNum)
		{
            m_panArgs->startTouchX = x;
            m_panArgs->startTouchY = y;
		}

		void CGesturePan::OnTouchEnd(int pointID, int x, int y, uint classID, uint touchNum)
		{

		}

		void CGesturePan::OnTouchMove(int pointID, int x, int y, uint classID, uint touchNum)
		{
            m_panArgs->curTouchX = x;
            m_panArgs->curTouchY = y;
            
            for (auto it = m_GestureCallback.begin(); it!=m_GestureCallback.end(); ++it)
            {
                (*it)(m_panArgs);
            }
		}

	}
}
