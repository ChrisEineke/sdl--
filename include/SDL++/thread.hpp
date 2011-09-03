#ifndef SDLPP_THREAD_HPP_INCLUDED
#define SDLPP_THREAD_HPP_INCLUDED
/* vim: set ts=4 sts=4 sw=4 tw=80: */

#include "SDL.h"
#include <SDL++/shared_ptr_base.hpp>
#include <stdexcept>
#include <utility> // for pair<A, B>

namespace sdlpp
{
	using std::runtime_error;
	using std::pair;

	template <typename T = void*>
	class Thread : public shared_ptr_base<SDL_Thread>
	{
	public:
		/**
		  The default constructor.
		  @throw runtime_error
		 */
		Thread(T data) :
			shared_ptr_base<SDL_Thread>(static_cast<SDL_Thread*>(0), SDL_KillThread),
			user_data(data),
			box(this, user_data)
		{
			/*
			 * There are a couple of important steps we can't do in the Thread
			 * constructors:
			 *
			 * First, we need to defer initialization of the shared ptr to until
			 * we have the box constructed.
			 *
			 * Second, we cannot call SDL_CreateThread from the constructor. SDL
			 * will _immediately_ spawn the new thread, invoke the trampoline
			 * function, and redirect to the virtual function func(). But func()
			 * is yet to be initialized by a client class and so the program
			 * will crash and burn with a "pure virtual function called" error
			 * message.  Additionally, that's called undefined behaviour and the
			 * compiler is free to do its own thing and not even required to
			 * print that error message. Thank GNU gcc does though.
			 */
		}

		/**
		 * The wrapper constructor.
		 *
		 * Wraps an existing thread.
		 *
		 * @throw runtime_error
		 */
		Thread(SDL_Thread* thread) :
			shared_ptr_base<SDL_Thread>(static_cast<SDL_Thread*>(0), SDL_KillThread),
			user_data(static_cast<user_t>(0)), // XXX: What can we do to make this work?
			box(this, user_data)
		{
			p.reset(thread, SDL_KillThread);
			if (p.get() == 0) {
				throw runtime_error("Attempted to wrap a NULL thread");
			}
		}

		/**
		 * The copy constructor.
		 *
		 * @throw runtime_error
		 */
		Thread(const Thread& that) :
			shared_ptr_base<SDL_Thread>(that),
			user_data(that.user_data),
			box(that.box)
		{
			if (p.get() == 0) {
				throw runtime_error("Attempted to copy-construct a NULL thread");
			}
		}

		/**
		 * Creates a new thread of execution that shares its parent's properties.
		 */
		void run()
		{
			p.reset(SDL_CreateThread(trampoline, &box), SDL_KillThread);
			if (p.get() == 0) {
				throw runtime_error("SDL_CreateThread returned NULL");
			}
		}

		/**
		 * The function that will be implemented by clients and run when the thread starts.
		 * @param data pointer to user data.
		 * @return the result code.
		 */
		virtual int func(T data) = 0;

		/**
		 * @return the SDL thread ID of this Thread.
		 */
		Uint32 id()
		{
			return SDL_GetThreadID(p.get());
		}

		/**
		 * Waits for a thread to finish.
		 *
		 * @return the return code for the thread function.
		 */
		int wait()
		{
			int status;
			SDL_WaitThread(p.get(), &status);
			return status;
		}

		/**
		 * Gracelessly terminates the thread.
		 */
		void kill()
		{
			SDL_KillThread(p.get());
		}

	private:
		typedef pair<Thread<T>*, T> box_t;
		typedef Thread<T> thread_t;
		typedef T user_t;

		/**
		 * The actual user data.
		 */
		user_t user_data;

		/**
		 * The boxed pair that we pass to the SDL_CreateThread
		 * function as the user pointer, which is later unboxed into a
		 * pointer to a Thread<T> and a pointer to user data T.
		 */
		box_t box;

		/**
		 * SDL_CreateThread expects a "non-member" function, which a
		 * static member function can be turned into.  This function
		 * then invokes the real function as implemented by our clients.
		 *
		 * @param data the pointer to the boxed Thread instance and user data.
		 * @return the real function's return code.
		 */
		static int trampoline(void* data)
		{
			box_t* box = static_cast<box_t*>(data);
			thread_t* thread = box->first;
			user_t user = box->second;
			return thread->func(user);
		}
	};

	inline
	Uint32 ThreadID()
	{
		return SDL_ThreadID();
	}
}

#endif /* SDLPP_THREAD_HPP_INCLUDED */
