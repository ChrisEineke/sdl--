/* vim: set ts=4 sts=4 sw=4 tw=80: */
#include <SDL++/overlay.hpp>
#include <string>

namespace
{
	using std::runtime_error;
	using std::string;

	/**
	 * Creates a YUV video overlay
	 */
	SDL_Overlay* CreateYUVOverlay(int width, int height, Uint32 format,
			SDL_Surface* display)
	{
		SDL_Overlay* overlay = SDL_CreateYUVOverlay(width, height, format, display);
		if (overlay == 0) {
			throw runtime_error(string()
					+ "SDL_CreateYUVOverlay returned NULL: "
					+ SDL_GetError());
		}
		return overlay;
	}
}

namespace sdlpp
{
	Overlay::Overlay(int width, int height, Uint32 format, Video_surface& display) :
		shared_ptr_base<SDL_Overlay>(CreateYUVOverlay(width, height, format,
					display.raw_ptr()), SDL_FreeYUVOverlay)
	{
		/*
		 * If SDL_CreateYUVOverlay returns a NULL pointer,
		 * CreateYUVOverlay will throw the exception.
		 */
	}

	Overlay::Overlay(SDL_Overlay* overlay) :
		shared_ptr_base<SDL_Overlay>(overlay, SDL_FreeYUVOverlay)
	{
		if (p.get() == 0) {
			throw runtime_error("Attempted to wrap a NULL overlay");
		}
	}

	Overlay::Overlay(const Overlay& that) :
		shared_ptr_base<SDL_Overlay>(that)
	{
		if (p.get() == 0) {
			throw runtime_error("Attempted to copy-construct a NULL overlay");
		}
	}
}
