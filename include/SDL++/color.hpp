#ifndef SDLPP_COLOR_HPP_INCLUDED
#define SDLPP_COLOR_HPP_INCLUDED
/* vim: set ts=4 sts=4 sw=4 tw=80: */

#include "SDL.h"

namespace sdlpp
{
	/**
	 * The concrete class Color.
	 *
	 * Color provides a wrapper around the SDL_Color struct. It doesn't add
	 * any members at all to keep backwards compatibility with SDL function that
	 * expect arrays of ColorS.
	 */
	class Color : public SDL_Color
	{
	public:
		/**
		 * The default constructor.
		 *
		 * Format independent color description.
		 */
		inline
		Color(Uint8 red = 0, Uint8 green = 0, Uint8 blue = 0);

		/**
		 * The wrapper constructor.
		 */
		inline
		Color(const SDL_Color& that);

		/**
		 * The copy constructor.
		 */
		inline
		Color(const Color& that);
	};

	inline
	Color::Color(Uint8 red, Uint8 green, Uint8 blue) :
		SDL_Color()
	{
		r = red;
		g = green;
		b = blue;
	}

	inline
	Color::Color(const SDL_Color& color) :
		SDL_Color(color)
	{
	}

	inline
	Color::Color(const Color& that) :
		SDL_Color(that)
	{
	}

	typedef Color Colour;
}

#endif /* SDLPP_COLOR_HPP_INCLUDED */
