#ifndef SDLPP_PIXEL_FORMAT_HPP_INCLUDED
#define SDLPP_PIXEL_FORMAT_HPP_INCLUDED
/* vim: set ts=4 sts=4 sw=4 tw=80: */

#include "SDL.h"
#include <SDL++/shared_ptr_base.hpp>
#include <SDL++/rect.hpp>
#include <stdexcept>
#include <vector>

namespace sdlpp
{
	using std::runtime_error;
	using std::auto_ptr;
	using std::vector;
	using std::string;

	/**
	 * Stores surface format information.
	 */
	struct Pixel_format : public SDL_PixelFormat
	{
		/**
		 * The wrapper constructor.
		 *
		 * @note This should be regarded as the primary constructor.
		 */
		Pixel_format(const SDL_PixelFormat& pixel_format) :
			SDL_PixelFormat(pixel_format)
		{
		}

		/**
		 * The copy constructor.
		 */
		Pixel_format(const Pixel_format& that) :
			SDL_PixelFormat(that)
		{
		}

		/**
		 * Lists the available modes.
		 *
		 * @note This is equivalent to calling SDL_ListModes and interpreting
		 * the return value.
		 * @note Due to SDL_ListModes's unusual way of returning integer values
		 * through pointers, we split its functionality into two.
		 *
		 * @return A pointer to an array of available screen dimensions for the
		 * given format and video flags.
		 */
		vector<Rect> modes(Uint32 flags)
		{
			SDL_Rect** rects = SDL_ListModes(this, flags);
			vector<Rect> modes;
			if (rects == 0) {
				return modes;
			}
			for (SDL_Rect* it = rects[0]; it != 0; it++) {
				modes.push_back(*it);
			}
			return modes;
		}

		/**
		 * Checks for restrictedness.
		 *
		 * @note This is equivalent to calling SDL_ListModes and interpreting
		 * the return value.
		 * @note Due to SDL_ListModes's unusual way of returning integer values
		 * through pointers, we split its functionality into two.
		 *
		 * @return True if the current screen dimensions are unrestricted
		 * (meaning, any dimension is okay). False otherwise.
		 */
		bool unrestricted(Uint32 flags)
		{
			SDL_Rect** rects = SDL_ListModes(this, flags);
			return (long)(rects) == -1;
		}

		/**
		 * Maps a RGB color value to a pixel format.
		 *
		 * @note This is equivalent to calling SDL_MapRGB.
		 *
		 * @return A pixel value best approximating the given RGB color value
		 * for a given pixel format. If the pixel format bpp (color depth) is
		 * less than 32-bpp then the unused upper bits of the return value can
		 * safely be ignored (e.g., with a 16-bpp format the return value can be
		 * assigned to a Uint16, and similarly a Uint8 for an 8-bpp format).
		 */
		Uint32 map(Uint8 r, Uint8 g, Uint8 b)
		{
			return SDL_MapRGB(this, r, g, b);
		}

		/**
		 * Maps a RGBA color value to a pixel format.
		 *
		 * @note This is equivalent to calling SDL_MapRGBA.
		 *
		 * @return A pixel value best approximating the given RGB color value
		 * for a given pixel format. If the pixel format bpp (color depth) is
		 * less than 32-bpp then the unused upper bits of the return value can
		 * safely be ignored (e.g., with a 16-bpp format the return value can be
		 * assigned to a Uint16, and similarly a Uint8 for an 8-bpp format).
		 */
		Uint32 map(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
		{
			return SDL_MapRGBA(this, r, g, b, a);
		}

		/**
		 * Gets RGB values from a pixel in the specified pixel format.
		 *
		 * @note This is equivalent to calling SDL_GetRGB.
		 * @note The order of arguments has been slightly altered. Pointers have
		 * been turned into references where possible.
		 */
		void get(Uint32 pixel, Uint8& r, Uint8& g, Uint8& b)
		{
			return SDL_GetRGB(pixel, this, &r, &g, &b);
		}

		/**
		 * Gets RGBA values from a pixel in the specified pixel format.
		 *
		 * @note This is equivalent to calling SDL_GetRGBA.
		 * @note The order of arguments has been slightly altered. Pointers have
		 * been turned into references where possible.
		 */
		void GetRGBA(Uint32 pixel, Uint8& r, Uint8& g, Uint8& b, Uint8& a)
		{
			return SDL_GetRGBA(pixel, this, &r, &g, &b, &a);
		}

	private:
		/**
		 * The default constructor.
		 *
		 * Stores surface format information.
		 *
		 * @note SDL_PixelFormatS are created with a surface.
		 */
		inline
		Pixel_format();
	};
}

#endif /* SDLPP_PIXEL_FORMAT_HPP_INCLUDED */
