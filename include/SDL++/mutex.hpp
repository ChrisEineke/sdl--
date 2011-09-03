#ifndef SDLPP_MUTEX_HPP_INCLUDED
#define SDLPP_MUTEX_HPP_INCLUDED
/* vim: set ts=4 sts=4 sw=4 tw=80: */

#include "SDL.h"
#include <SDL++/shared_ptr_base.hpp>
#include <stdexcept>

namespace sdlpp
{
	using std::runtime_error;

	/**
	 * The concrete class Mutex.
	 *
	 * Mutex provides a wrapper around an SDL_mutex struct and related
	 * functions.  Internally, the pointer to a SDL_mutex is managed by a
	 * shared_ptr so you don't have to. We provide the helper class Mutex::Lock
	 * for safe locking and unlocking of a Mutex.
	 */
	class Mutex : public shared_ptr_base<SDL_mutex>
	{
	public:
		/**
		 * The default constructor.
		 *
		 * Creates a new, unlocked mutex.
		 *
		 * @throw runtime_error If an error occured while creating a Mutex.
		 */
		Mutex();

		/**
		 * The SDL_mutex constructor.
		 *
		 * Wraps an exisiting mutex.
		 *
		 * @throw runtime_error If mutex is 0.
		 */
		Mutex(SDL_mutex* mutex);

		/**
		 * The copy constructor.
		 *
		 * Constructs a shallow copy of the wrapped mutex.
		 *
		 * @param that the Mutex to copy
		 *
		 * @throw runtime_error If that is an invalid Mutex.
		 */
		Mutex(const Mutex& that);

		/**
		 * The concrete helper class Lock.
		 *
		 * This class will lock a Mutex on construction and unlock a Mutex on
		 * deconstruction. This ensures that a Mutex is unlocked if an exception
		 * is thrown.
		 */
		class Lock
		{
			public:
				/**
				 * Associates a Lock with a Mutex and locks it.
				 */
				Lock(Mutex& mutex) : mutex(mutex)
				{ mutex.lock(); }

				/**
				 * Unlocks the associated Mutex.
				 */
				~Lock()
				{ mutex.unlock(); }

			private:
				/**
				 * The Mutex that this Lock is associated with.
				 */
				Mutex& mutex;

				Lock();
				Lock(const Lock& that);
				Lock& operator= (const Lock& that);
		};

	private:
		friend class Lock;

		/**
		 * Locks the mutex.
		 * @return true on success, false on an error.
		 */
		inline bool lock()
		{ return SDL_mutexP(shared_ptr_base<SDL_mutex>::p.get()) == 0; }
		
		/**
		 * Unlocks the mutex.
		 * @return true on success, false on an error.
		 */
		inline bool unlock()
		{ return SDL_mutexV(shared_ptr_base<SDL_mutex>::p.get()) == 0; }
	};
}

#endif /* SDLPP_MUTEX_HPP_INCLUDED */
