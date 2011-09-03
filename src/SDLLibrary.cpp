/* vim: set ts=2 sts=2 sw=2 tw=80: */
#include <SDL++/SDLLibrary.hpp>

int SDLLibrary::WaitEvent()
{
	SDL_Event event;
	int rc = SDL_WaitEvent(&event);
	if (rc != -1) {
		dispatchEvent(event);
	}
	return rc;
}

int SDLLibrary::PollEvent()
{
	SDL_Event event;
	int rc = SDL_PollEvent(&event);
	if (rc != 0) {
		dispatchEvent(event);
	}
	return rc;
}

void SDLLibrary::dispatchEvent(SDL_Event& event)
{
	switch (event.type) {
		case SDL_ACTIVEEVENT:
			EventDispatcher<SDL_ActiveEvent*>::distributeLibraryEvent(&event);
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			EventDispatcher<SDL_KeyboardEvent*>::distributeLibraryEvent(&event);
			break;
		case SDL_MOUSEMOTION:
			EventDispatcher<SDL_MouseMotionEvent*>::distributeLibraryEvent(&event);
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			EventDispatcher<SDL_MouseButtonEvent*>::distributeLibraryEvent(&event);
			break;
		case SDL_JOYAXISMOTION:
			EventDispatcher<SDL_JoyAxisEvent*>::distributeLibraryEvent(&event);
			break;
		case SDL_JOYBALLMOTION:
			EventDispatcher<SDL_JoyBallEvent*>::distributeLibraryEvent(&event);
			break;
		case SDL_JOYHATMOTION:
			EventDispatcher<SDL_JoyHatEvent*>::distributeLibraryEvent(&event);
			break;
		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
			EventDispatcher<SDL_JoyButtonEvent*>::distributeLibraryEvent(&event);
			break;
		case SDL_QUIT:
			EventDispatcher<SDL_QuitEvent*>::distributeLibraryEvent(&event);
			break;
		case SDL_SYSWMEVENT:
			EventDispatcher<SDL_SysWMmsg*>::distributeLibraryEvent(&event);
			break;
		case SDL_VIDEORESIZE:
			EventDispatcher<SDL_ResizeEvent*>::distributeLibraryEvent(&event);
			break;
		case SDL_VIDEOEXPOSE:
			EventDispatcher<SDL_ExposeEvent*>::distributeLibraryEvent(&event);
			break;
		case SDL_USEREVENT:
			static_cast<EventDispatcher*>(event.user.data1)->distributeUserEvent(&event);
			break;
		default:
			break;
	}
}
