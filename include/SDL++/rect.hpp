#ifndef SDLPP_RECT_HPP_INCLUDED
#define SDLPP_RECT_HPP_INCLUDED
/* vim: set ts=4 sts=4 sw=4 tw=80: */

#include "SDL.h"

namespace sdlpp
{
	struct Rect : public SDL_Rect
	{
		/**
		 * The default constructor.
		 *
		 * Defines a rectangular area.
		 */
		inline
		Rect(Sint16 x_coord = 0, Sint16 y_coord = 0, Uint16 width = 0, Uint16 height = 0);

		/**
		 * The wrapper constructor.
		 */
		inline
		Rect(const SDL_Rect& rect);

		/**
		 * The copy constructor.
		 */
		inline
		Rect(const Rect& that);
	};

	inline
	Rect::Rect(Sint16 x_coord, Sint16 y_coord, Uint16 width, Uint16 height) :
		SDL_Rect()
	{
		x = x_coord;
		y = y_coord;
		w = width;
		h = height;
	}

	inline
	Rect::Rect(const SDL_Rect& rect) :
		SDL_Rect(rect)
	{
	}

	inline
	Rect::Rect(const Rect& that) :
		SDL_Rect(that)
	{
	}
}

#endif /* SDLPP_RECT_HPP_INCLUDED */
