#include <SDL++/semaphore.hpp>

namespace sdlpp
{
	Semaphore::Semaphore(Uint32 initial_value) :
		shared_ptr_base<SDL_sem>(SDL_CreateSemaphore(initial_value), SDL_DestroySemaphore)
	{
		if (p.get() == 0) {
			throw runtime_error("SDL_CreateSemaphore returned NULL");
		}
	}

	Semaphore::Semaphore(SDL_sem* semaphore) :
		shared_ptr_base<SDL_sem>(semaphore, SDL_DestroySemaphore)
	{
		if (p.get() == 0) {
			throw runtime_error("NULL is not a valid semaphore");
		}
	}

	Semaphore::Semaphore(const Semaphore& that) :
		shared_ptr_base<SDL_sem>(that)
	{
		if (p.get() == 0) {
			throw runtime_error("Attempted to copy-construct a NULL semaphore");
		}
	}

	bool Semaphore::wait()
	{
		return SDL_SemWait(p.get()) == 0;
	}

	bool Semaphore::try_wait()
	{
		int ret = SDL_SemTryWait(p.get());
		switch (ret) {
		case -2: /* SDL_MUTEX_TIMEOUT */
			throw runtime_error("Attempt to lock semaphore timed out");
		case -1:
			return false;
		case 0:
			return true;
		default:
			return false;
		}
	}

	bool Semaphore::wait_timeout(Uint32 timeout)
	{
		int ret = SDL_SemWaitTimeout(p.get(), timeout);
		switch (ret) {
		case -2: /* SDL_MUTEX_TIMEOUT */
			throw runtime_error("Attempt to lock semaphore timed out");
		case -1:
			return false;
		case 0:
			return true;
		default:
			return false;
		}
	}

	bool Semaphore::post()
	{
		return SDL_SemPost(p.get()) == 0;
	}

	Uint32 Semaphore::value()
	{
		return SDL_SemValue(p.get());
	}
}
