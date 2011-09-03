#ifndef SDLPP_TIMER_HPP_INCLUDED
#define SDLPP_TIMER_HPP_INCLUDED

#include "SDL.h"
#include <SDL++/source.hpp>
#include <SDL++/callback.hpp>
#include <utility>

using std::pair;
using std::make_pair;

namespace sdlpp
{
	template <typename U = void*>
	class Timer : public Source
	{
	public:
		typedef U data_type;
		typedef Timer<U> timer_type;
		typedef Timer_callback<U> callback_type;
		typedef pair<timer_type*, U> box_type;

		Timer(callback_type& callback) :
			Source(),
			callback(callback), box(), id(0)
		{
		}
		
		~Timer()
		{
			removeTimer();
		}

		bool addTimer(Uint32 interval, U param = 0)
		{
			removeTimer();
			box = make_pair(this, param);
			id = SDL_AddTimer(interval, &trampoline, static_cast<void*>(&box));
			if (id == 0) {
				emptyBox();
				return false;
			}
			else {
				return true;
			}
		}

		bool removeTimer()
		{
			bool result = SDL_RemoveTimer(id);
			id = 0;
			emptyBox();
			return result;
		}

		void emptyBox()
		{
			box.first = 0;
			box.second = 0;
		}

	private:	
		callback_type& callback;
		box_type box;
		SDL_TimerID id;
		
		static Uint32 trampoline(Uint32 interval, void* param)
		{
			box_type* box = static_cast<box_type*>(param);
			timer_type* timer = box->first;
			U real_param = box->second;
			Uint32 invoke_rc = timer->callback.invoke(*timer, interval, real_param);
			if (invoke_rc == 0) {
				timer->removeTimer();
			}
			return invoke_rc;
		}
	};
}

#endif /* SDLPP_TIMER_HPP_INCLUDED */
