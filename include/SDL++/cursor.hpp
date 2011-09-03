#ifndef SDLPP_CURSOR_HPP_INCLUDED
#define SDLPP_CURSOR_HPP_INCLUDED
/* vim: set ts=4 sts=4 sw=4 tw=80: */

#include "SDL.h"
#include <SDL++/shared_ptr_base.hpp>
#include <SDL++/rect.hpp>
#include <stdexcept>

namespace sdlpp
{
	using std::runtime_error;

	/**
	 * The concrete class Cursor.
	 *
	 * Cursor provides a wrapper around an SDL_Cursor struct and related
	 * functions. Internally, the pointer to a SDL_Cursor is managed by a
	 * shared_ptr so you don't have to.
	 */
	class Cursor : public shared_ptr_base<SDL_Cursor>
	{
	public:
		/**
		 * The default constructor.
		 *
		 * Creates a new mouse cursor.
		 *
		 * @throw runtime_error If an error occured while creating a cursor.
		 */
		Cursor(Uint8* data, Uint8* mask, int w, int h, int hot_x, int hot_y);

		/**
		 * The wrapper constructor.
		 *
		 * Wraps an exisiting cursor.
		 *
		 * @throw runtime_error If cursor is 0.
		 */
		Cursor(SDL_Cursor* cursor);

		/**
		 * The copy constructor.
		 *
		 * @throw runtime_error If that is an invalid instance of Condition.
		 */
		Cursor(const Cursor& that);

		/**
		 * @return The area of the mouse cursor.
		 */
		inline Rect area() const
		{ return p->area; }

		/**
		 * @return The "tip" of the cursor -- X coordinate.
		 */
		inline Sint16 hot_x() const
		{ return p->hot_x; }

		/**
		 * @return The "tip" of the cursor -- Y coordinate.
		 */
        inline Sint16 hot_y() const
		{ return p->hot_y; }

		/**
		 * @return B/W cursor data.
		 */
        inline Uint8* data() const
		{ return p->data; }
        
		/**
		 * @return B/W cursor mask.
		 */
		inline Uint8* mask() const
		{ return p->mask; }

		/**
		 * @return Place to save cursor area.
		 */
		inline Uint8** save() const
		{ return p->save; }

		/**
		 * @return Window-manager cursor.
		 */
		inline WMcursor*& wm_cursor() const
		{ return p->wm_cursor; }

		/**
		 * Sets the position of the mouse cursor (and generates a
		 * mouse motion event).
		 *
		 * @note This is equivalent to calling SDL_WarpMouse.
		 */
		void warp(Uint16 x, Uint16 y);

		/**
		 * Sets the currently active mouse cursor to this one.
		 *
		 * @note This is equivalent to calling SDL_SetCursor.
		 */
		void set();

		/**
		 * Gets the currently active mouse cursor. 
		 *
		 * @note This is equivalent to calling SDL_GetCursor.
		 */
		static Cursor get();

		/**
		 * Toggles whether or not a cursor is shown on the screen.
		 *
		 * @note This is equivalent to calling SDL_ShowCursor.
		 */
		static bool show(int toggle);
	};
}

#endif /* SDLPP_CURSOR_HPP_INCLUDED */
