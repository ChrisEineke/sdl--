/* vim: set ts=4 sts=4 sw=4 tw=80: */
#include <SDL++/condition.hpp>
#include <string>

namespace sdlpp
{
	using std::string;

	Condition::Condition() :
		shared_ptr_base<SDL_cond>(SDL_CreateCond(), SDL_DestroyCond)
	{
		if (p.get() == 0) {
			throw runtime_error(string()
					+ "SDL_CreateCond returned NULL: "
					+ SDL_GetError());
		}
	}

	Condition::Condition(SDL_cond* condition) :
		shared_ptr_base<SDL_cond>(condition, SDL_DestroyCond)
	{
		if (p.get() == 0) {
			throw runtime_error("Attempted to wrap a NULL condition");
		}
	}

	Condition::Condition(const Condition& that) :
		shared_ptr_base<SDL_cond>(that)
	{
		if (p.get() == 0) {
			throw runtime_error("Attempted to copy-construct a NULL condition");
		}
	}

	bool Condition::wait(Mutex& mutex)
	{
		return SDL_CondWait(p.get(), mutex.raw_ptr()) == 0;
	}

	bool Condition::wait_timeout(Mutex& mutex, Uint32 ms)
	{
		int rc = SDL_CondWaitTimeout(p.get(), mutex.raw_ptr(), ms);
		if (rc == 0) {
			return true;
		}
		else if (rc == SDL_MUTEX_TIMEDOUT) {
			throw runtime_error("Mutex timed out");
			return false;
		} else {
			return false;
		}
	}

	bool Condition::signal()
	{
		return SDL_CondSignal(p.get()) == 0;
	}

	bool Condition::broadcast()
	{
		return SDL_CondBroadcast(p.get()) == 0;
	}
}
