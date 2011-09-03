#ifndef SDLPP_SEMAPHORE_HPP_INCLUDED
#define SDLPP_SEMAPHORE_HPP_INCLUDED

#include "SDL.h"
#include <SDL++/shared_ptr_base.hpp>
#include <stdexcept>

namespace sdlpp
{
	using std::runtime_error;

	class Semaphore : public shared_ptr_base<SDL_sem>
	{
	public:
		/**
		 * The default constructor.
		 *
		 * Creates a new semaphore and assigns an initial value to it.
		 *
		 * @throw runtime_error
		 */
		Semaphore(Uint32 initial_value = 0);

		/**
		 * The SDL_sem constructor.
		 *
		 * Wraps an SDL_sem.
		 *
		 * @throw runtime_error
		 */
		Semaphore(SDL_sem* semaphore);

		/**
		 * The copy constructor.
		 *
		 * Constructs a shallow copy of the wrapped semaphore.
		 * @param that the Semaphore to copy
		 *
		 * @throw runtime_error
		 */
		Semaphore(const Semaphore& that);

		/**
		 * Locks a semaphore and suspends the thread if the semaphore value is
		 * zero.
		 */
		bool wait();

		/**
		 * Attempts to lock a semaphore but doesn’t suspend the thread.
		 *
		 * @throw runtime_error
		 */
		bool try_wait();

		/**
		 * Locks a semaphore, but only wait up to a specified maximum time.
		 *
		 * @throw runtime_error
		 */
		bool wait_timeout(Uint32 timeout);

		/**
		 * Unlocks a semaphore.
		 */
		bool post();

		/**
		 * Return the current value of a semaphore.
		 */
		Uint32 value();
	};
}

#endif /* SDLPP_SEMAPHORE_HPP_INCLUDED */
