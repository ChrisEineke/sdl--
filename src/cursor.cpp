/* vim: set ts=4 sts=4 sw=4 tw=80: */
#include <SDL++/cursor.hpp>
#include <string>

namespace sdlpp
{
	using std::string;

	Cursor::Cursor(Uint8* data, Uint8* mask, int w, int h, int hot_x, int hot_y) :
		shared_ptr_base<SDL_Cursor>(
				SDL_CreateCursor(data, mask, w, h, hot_x, hot_y),
				SDL_FreeCursor)
	{
		if (p.get() == 0) {
			throw runtime_error(string()
					+ "SDL_CreateCursor returned NULL: "
					+ SDL_GetError());
		}
	}

	Cursor::Cursor(SDL_Cursor* cursor) :
		shared_ptr_base<SDL_Cursor>(cursor, SDL_FreeCursor)
	{
		if (p.get() == 0) {
			throw runtime_error("Attempted to wrap a NULL cursor");
		}
	}

	Cursor::Cursor(const Cursor& that) :
		shared_ptr_base<SDL_Cursor>(that)
	{
		if (p.get() == 0) {
			throw runtime_error("Attempted to copy-construct a NULL cursor");
		}
	}

	void Cursor::warp(Uint16 x, Uint16 y)
	{
		SDL_WarpMouse(x, y);
	}

	void Cursor::set()
	{
		SDL_SetCursor(p.get());
	}

	Cursor Cursor::get()
	{
		return Cursor(SDL_GetCursor());
	}

	bool Cursor::show(int toggle)
	{
		return SDL_ShowCursor(toggle);
	}
}
