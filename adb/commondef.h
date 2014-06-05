#pragma once


#define STRING(s)  #s

#define SINGLE_INSTANCE(C)		\
	static C& getInstance()		\
	{							\
		static C _a;			\
		return _a;				\
	}						

template <typename T>
struct FastBuffer
{
    FastBuffer(int len) : _buf(buf), m_len(sizeof(buf))
    {
        _buf = len > sizeof(buf) / sizeof(buf[0]) ? new T [len] : buf;
        m_len = len > sizeof(buf) ? len : sizeof(buf);
        memset(_buf, 0, m_len);
    }
    ~FastBuffer()
    {
        if (_buf != buf && _buf)
            delete [] _buf;
    }

    int  m_len;
    T    buf[10 * 1024];
    T*   _buf;
};

//#define SAFE_THREAD		std::recursive_mutex _mtx;
//#define LOCKIT	\
//	std::lock_guard<std::recursive_mutex> lc(_mtx);	

#define SAFE_THREAD	std::mutex _mtx2;
#define LOCKIT	\
	std::lock_guard<std::mutex> lc2(_mtx2);