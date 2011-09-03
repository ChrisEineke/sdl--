#ifndef SDLPP_SDLLIBRARY_HPP_INCLUDED
#define SDLPP_SDLLIBRARY_HPP_INCLUDED
/* vim: set ts=2 sts=2 sw=2 tw=80: */

#include "SDL.h"

namespace sdlpp
{
	class SDLLibrary
		: public EventDispatcher<SDL_ActiveEvent*>
		, public EventDispatcher<SDL_KeyboardEvent*>
		, public EventDispatcher<SDL_MouseMotionEvent*>
		, public EventDispatcher<SDL_MouseButtonEvent*>
		, public EventDispatcher<SDL_JoyAxisEvent*>
		, public EventDispatcher<SDL_JoyBallEvent*>
		, public EventDispatcher<SDL_JoyHatEvent*>
		, public EventDispatcher<SDL_JoyButtonEvent*>
		, public EventDispatcher<SDL_QuitEvent*>
		, public EventDispatcher<SDL_SysWMmsg*>
		, public EventDispatcher<SDL_ResizeEvent*>
		, public EventDispatcher<SDL_ExposeEvent*>
	{
		public:
			int WaitEvent();
			int PollEvent();

		private:
			void dispatchEvent(SDL_Event&);
	};
}

#endif /* SDLPP_SDLLIBRARY_HPP_INCLUDED */
