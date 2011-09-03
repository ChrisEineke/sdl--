#ifndef SDLPP_TASK_INCLUDED
#define SDLPP_TASK_INCLUDED
/* vim:set cindent sw=4 ts=4 sts=4 */

#include <SDL++/callback.hpp>
#include <SDL++/user_event.hpp>
#include <SDL++/timer.hpp>

namespace sdlpp
{
	template <typename T>
	class Task :
		public User_event<T>,
		public Timer_callback<T>
	{
	public:
		Task(Uint32 interval, unsigned times = 1) :
			User_event<T>(),
			Timer_callback<T>(),
			task_timer(*this),
			interval(interval),
			times(times)
		{
		}

		void start(T param = 0)
		{
			task_timer.addTimer(interval, param);
		}

		void stop()
		{
			task_timer.removeTimer();
		}

	private:
		Timer<T> task_timer;
		Uint32 interval;
		unsigned times;

		/* implement timer_callback<T> */
		virtual Uint32 invoke(Source&, Uint32 interval = 0, T param = 0)
		{
			push(param);
			return (--times == 0 ? 0 : interval);
		}
	};
}

#endif /* SDLPP_TASK_INCLUDED */
