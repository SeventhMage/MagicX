#ifndef _MX_IREFERENCE_COUNT_H_
#define _MX_IREFERENCE_COUNT_H_

namespace mx
{
	class IReferenceCount
	{
	public:
		IReferenceCount():m_refCount(1){}
		virtual ~IReferenceCount(){}
		
		void Increase() { ++m_refCount; }
		void Decrease() 
		{
			if (m_refCount > 0)
				--m_refCount;
			if (m_refCount == 0)
				delete this;
		}
		int ReferenceCount() { return m_refCount; }
	private:
		int m_refCount;
	};
}

#endif