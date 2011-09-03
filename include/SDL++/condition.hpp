#ifndef SDLPP_CONDITION_HPP_INCLUDED
#define SDLPP_CONDITION_HPP_INCLUDED
/* vim: set ts=4 sts=4 sw=4 tw=80: */

#include "SDL.h"
#include <SDL++/mutex.hpp>
#include <SDL++/shared_ptr_base.hpp>
#include <stdexcept>

namespace sdlpp
{
	using std::runtime_error;

	/**
	 * The concrete class Condition.
	 *
	 * Condition provides a wrapper around an SDL_cond struct and related
	 * functions. Internally, the pointer to a SDL_cond is managed by a
	 * shared_ptr so you don't have to.
	 *
	 * @todo Are there speed concerns? Should the function definitions be
	 * available in the header file so that they become inlinable?
	 */
	class Condition : public shared_ptr_base<SDL_cond>
	{
	public:
		/**
		 * The default constructor.
		 *
		 * Creates a condition variable.
		 *
		 * @throw runtime_error If an error occured while creating a condition
		 * variable.
		 */
		Condition();

		/**
		 * The wrapper constructor.
		 *
		 * Wraps an existing condition.
		 *
		 * @throw runtime_error If condition is 0.
		 */
		Condition(SDL_cond* condition);

		/**
		 * The copy constructor.
		 *
		 * @throw runtime_error If that is an invalid instance of Condition.
		 */
		Condition(const Condition& that);

		/**
		 * Waits on the condition variable.
		 */
		bool wait(Mutex& mutex);

		/**
		 * Waits on a condition variable, with timeout.
		 *
		 * @throw runtime_error If a timeout occured while waiting.
		 */
		bool wait_timeout(Mutex& mutex, Uint32 ms);

		/**
		 * Restarts a thread wait on a condition variable.
		 */
		bool signal();

		/**
		 * Restart all threads waiting on a condition variable.
		 */
		bool broadcast();
	};
}

#endif /* SDLPP_CONDITION_HPP_INCLUDED */
