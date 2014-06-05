#pragma once

class synchronize
{
private:
	CRITICAL_SECTION* plock;

public:
	synchronize(CRITICAL_SECTION* lock)
	{
		plock = lock;
		if ( plock == NULL ) return;

		EnterCriticalSection(plock);
	}

	~synchronize()
	{
		if ( plock != NULL )
			LeaveCriticalSection(plock);
	} 
};

#define LOG(fmt, ...) printf(fmt"\n", __VA_ARGS__);

#define LOG_DEBUG LOG
#define LOG_INFO  LOG
#define LOG_WARN  LOG
#define LOG_ERROR LOG

class __log_bound
{
	const char* __p;
public:
	__log_bound(const char* s)
	{
		__p = s;
		LOG_DEBUG("Enter %s", __p);
	}
	~__log_bound()
	{
		LOG_DEBUG("Leave %s", __p);
	}
};

#define LOG_BOUND(s) __log_bound __log_bound_instance(#s)