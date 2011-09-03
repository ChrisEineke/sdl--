#ifndef SDLPP_EVENT_HPP_INCLUDED
#define SDLPP_EVENT_HPP_INCLUDED
/* vim:set cindent:set sw=4:set ts=4:set sts=4 */

#include "SDL.h"
#include <SDL++/source.hpp>
#include <SDL++/callback.hpp>
#include <assert.h>
#include <vector>
#include <list>

namespace sdlpp
{
	/**
	 * The base class Event.
	 */
	class Event
	{
	public:
		/**
		 * The default constructor.
		 */
		Event()
			: m_timestamp(SDL_GetTicks())
		{ }

		/**
		 * The destructor.
		 */
		virtual ~Event() { } = 0;

	private:
		/**
		 * The copy constructor -- made private to block copies.
		 */
		Event(const Event&) { }

		Uint32 m_timestamp;
	};
}

#endif /* SDLPP_EVENT_HPP_INCLUDED */
