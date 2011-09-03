/* vim: set ts=4 sts=4 sw=4 tw=80: */
#include <SDL++/mutex.hpp>

/*
 * We need to write shared_ptr_base<SDL_mutex>::p here, because SDL_mutex is a
 * declared, but not defined struct type.
 */

namespace sdlpp
{
	Mutex::Mutex() :
		shared_ptr_base<SDL_mutex>(SDL_CreateMutex(), SDL_DestroyMutex)
	{
		if (shared_ptr_base<SDL_mutex>::p.get() == 0) {
			throw runtime_error("SDL_CreateMutex returned NULL");
		}
	}

	Mutex::Mutex(SDL_mutex* mutex) :
		shared_ptr_base<SDL_mutex>(mutex, SDL_DestroyMutex)
	{
		if (shared_ptr_base<SDL_mutex>::p.get() == 0) {
			throw runtime_error("Attempted to wrap a NULL mutex");
		}
	}

	Mutex::Mutex(const Mutex& that) :
		shared_ptr_base<SDL_mutex>(that)
	{
		if (shared_ptr_base<SDL_mutex>::p.get() == 0) {
			throw runtime_error("Attempted to copy-construct a NULL mutex");
		}
	}
}
