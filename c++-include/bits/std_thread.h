#pragma once

#include <utility>
#include <tuple>
#include <cassert>
#include <circle/sched/task.h>
#include <circle/sched/scheduler.h>

namespace
{

template<typename Func, typename... Args>
class CStdTask : public CTask
{
public:
	CStdTask (Func &&rrFunc, Args &&... rrArgs)
	:	m_Func (std::forward<Func> (rrFunc)),
		m_Args (std::forward<Args> (rrArgs)...)
	{
	}

	void Run (void)
	{
		CallFunc (std::make_index_sequence<sizeof...(Args)> ());
	}

private:
	template<std::size_t... Is>
	void CallFunc (std::index_sequence<Is...>)
	{
		m_Func (std::get<Is> (m_Args)...);
	}

private:
	Func m_Func;
	std::tuple<Args...> m_Args;
};

}

namespace std
{

class thread
{
public:
	thread (void)
	:	m_pTask (nullptr)
	{
	}

	template<typename Func, typename... Args>
	thread (Func &&rrFunc, Args &&... rrArgs)
	:	m_pTask (new CStdTask<Func, Args...> (std::forward<Func> (rrFunc),
						      std::forward<Args> (rrArgs)...))
	{
		assert (m_pTask);
	}

	void join (void)
	{
		if (m_pTask)
		{
			m_pTask->WaitForTermination ();
			m_pTask = nullptr;
		}
	}

private:
	CTask *m_pTask;
};

}
