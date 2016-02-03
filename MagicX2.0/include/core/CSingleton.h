#ifndef _C_SINGLETON_H_INC_
#define _C_SINGLETON_H_INC_

namespace mx
{
	template <typename T>
	class CSingleton
	{
	public:
		static T *NewInstance()
		{
			if (!_instance)
				_instance = new T;
			return _instance;
		}

		static void DeleteInstance()
		{
			if (_instance)
			{
				delete _instance;
				_instance = 0;
			}
		}

		static T *Instance()
		{
			if (_instance)
				return _instance;
			else
				return NewInstance();
		}

	protected:
		CSingleton<T>() {}
		CSingleton<T>(const CSingleton<T> &){}
		CSingleton<T> &operator = (const CSingleton<T> &) { return *this; }
		~CSingleton<T>(){}

		static T *_instance;
	};

	template <typename T>
	T *CSingleton<T>::_instance = 0;
}

#endif // !_C_SINGLETON_H_INC_
