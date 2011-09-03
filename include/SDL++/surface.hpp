#ifndef SDLPP_SURFACE_HPP_INCLUDED
#define SDLPP_SURFACE_HPP_INCLUDED
/* vim: set ts=4 sts=4 sw=4 tw=80: */

#include "SDL.h"
#ifdef SDLPP_NEED_SDL_IMAGE
#include "SDL_image.h"
#endif /* SDLPP_NEED_SDL_IMAGE */
#include <SDL++/shared_ptr_base.hpp>
#include <SDL++/rect.hpp>
#include <SDL++/color.hpp>
#include <SDL++/pixel_format.hpp>
#ifdef SDLPP_NEED_SDL_IMAGE
#include <SDL++/rw_ops.hpp>
#endif /* SDLPP_NEED_SDL_IMAGE */
#include <stdexcept>
#include <vector>
#include <string>

/*
TODO:
Implement:
SDL_GetGammaRamp - Gets the color gamma lookup tables for the display
SDL_SetGammaRamp - Sets the color gamma lookup tables for the display 
 */

namespace sdlpp
{
	using std::runtime_error;
	using std::auto_ptr;
	using std::vector;
	using std::string;

	/**
	  A Surface represents an area of graphical memory that can be drawn to.
	 
	  @note According to the comments in the SDL header files, all fields except
	  pixels and refcount are read-only.
	 */
	class Surface : public shared_ptr_base<SDL_Surface>
	{
	public:
		/**
		  The empty Surface constructor.
		 
		  Creates an empty Surface using SDL_CreateRGBSurface.
		 
		  @throw runtime_error
		 */
		Surface(Uint32 flags, int width, int height, int depth,
				Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);
		
		/**
		  The copy Surface constructor.
		 
		  Creates a Surface from pixel data using SDL_CreateRGBSurfaceFrom.
		 
		  @throw runtime_error
		 */
		Surface(void* pixels, int width, int height, int depth, int pitch,
				Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);
	
		/**
		  The wrapper constructor.
		 
		  Wraps a Surface around the given SDL_Surface object. The
		  wrapper becomes the new owner of the object.
		 
		  @param surface the SDL_Surface to wrap
		 
		  @throw runtime_error
		 */
		Surface(SDL_Surface* surface);

		/**
		  The copy constructor.
		 
		  Constructs a shallow copy of the wrapped surface.
		  @param that the Surface to copy
		 */
		Surface(const Surface& that);

		/**
		  The deconstructor.
		 */
		virtual ~Surface();

		/**
		  @return The flags for this Surface.
		 */
		inline Uint32 flags()
		{ return p->flags; }

		/**
		  @return The format of the pixels stored in this Surface.
		  @see SDL_PixelFormat
		 */
		inline const SDL_PixelFormat* format()
		{ return p->format; }

		/**
		  @return The width in pixels of this Surface.
		 */
		inline int w()
		{ return p->w; }
		
		/**
		  @return The height in pixels of this Surface.
		 */
		inline int h()
		{ return p->h; }

		/**
		  @return The length of a Surface scanline in bytes.
		 */
		inline Uint16 pitch()
		{ return p->pitch; }

		/**
		  @return The surface clip rectangle of this Surface.
		  @note This can be set with set_clip().
		 */
		inline SDL_Rect clip_rect()
		{ return p->clip_rect; }

		/**
		  Performs a fast blit from the source surface to the destination
		  surface. Blits the whole surface to the other surface.
		 
		  @note This is equivalent to calling SDL_BlitSurface with NULL source
		  and destination rectangles.
		 */
		bool blit(Surface& dst);

		/**
		  Performs a fast blit from the source surface to the destination
		  surface. Blits parts of the surface to the other surface.
		 
		  @note This is equivalent to calling SDL_BlitSurface with a NULL
		  destination rectangle.
		 */
		bool blit(Rect& src_rect, Surface& dst);

		/**
		  Performs a fast blit from the source surface to the destination
		  surface. Blits parts of the surface to parts of the other surface.
		 
		  @note This is equivalent to calling SDL_BlitSurface.
		 */
		bool blit(Rect& src_rect, Surface& dst, Rect& dst_rect);
		
		/**
		  Performs a fast blit from the source surface to the destination
		  surface. Blits the whole surface to parts of the other surface.
		 
		  @note This is equivalent to calling SDL_BlitSurface with a NULL
		  source rectangle.
		 */
		bool blit(Surface& dst, Rect& dst_rect);

		/**
		  Fast fill the area described by the rectangle with some color.
		 */
		bool fill(Rect* rect, Uint32 color);
		
		/**
		  Converts a surface to the same format as another surface.
		 */
		bool convert(SDL_PixelFormat* fmt, Uint32 flags);

		/**
		  Converts the surface to the display format.
		 */
		bool display_format();

		/**
		  Converts the surface to the display format, including the alpha
		  channel.
		 */
		bool display_format_alpha();

		/**
		  Adjusts the alpha properties of the surface.
		 */
		bool set_alpha(Uint32 flag, Uint8 alpha);

		/**
		  Sets the clipping rectangle for a surface.
		 */
		bool set_clip(Rect* rect = 0);
		Rect get_clip();

		/**
		  Sets a portion of the colormap for an 8-bit surface.
		 */
		bool set_colors(SDL_Color* colors, int firstcolor, int ncolors);
		bool set_colors(vector<SDL_Color>& colors, int firstcolor, int ncolors);
		bool set_colors(vector<Color>& colors, int firstcolor, int ncolors);

		/**
		  Sets the color key (transparent pixel) in a blittable
		  surface and RLE acceleration.
		 */
		bool set_color_key(Uint32 flag, Uint32 key);

		/**
		  Sets the colors in the palette of an 8-bit surface.
		 */
		bool set_palette(int flags, SDL_Color* colors, int firstcolor, int ncolors);
		bool set_palette(int flags, vector<SDL_Color>& colors, int firstcolor, int ncolors);
		bool set_palette(int flags, vector<Color>& colors, int firstcolor, int ncolors);

		/**
		  @return true if the surface must be locked before access
		  pixel data.
		 */
		bool must_lock();

		class Lock
		{
			public:
				Lock(Surface& surface) :
					surface(surface),
					must_lock(surface.must_lock())
				{ if (must_lock) { surface.lock(); } }

				~Lock()
				{ if (must_lock) { surface.unlock(); } }

				inline void* pixels()
				{ return surface.pixels(); }

			private:
				Surface& surface;
				bool must_lock;

				Lock();
				Lock(const Lock& that);
				Lock& operator= (const Lock& that);
		};

		friend class Lock;

	private:
		/**
		  The default constructor.
		 */
		Surface();

		/**
		  Locks the surface.
		 */
		bool lock();

		/**
		  Unlocks the surface.
		 */
		void unlock();

		/**
		  @return The pointer to the actual pixel data of this Surface.
		 */
		inline void* pixels()
		{ return p->pixels; }
	};

	/**
	  The Surface_factory class is the interface to the SDL_LoadBMP and
	  SDL_SaveBMP functions and to the SDL_image library (if the client
	  requests the functionality by \#define'ing SDLPP_NEED_SDL_IMAGE.
	 */
	class Surface_factory
	{
	public:
		/**
		  Loads a Windows BMP into a Surface.
		 
		  @param file The BMP's file name.
		 
		  @note This is equivalent to calling SDL_LoadBMP.
		 
		  @throw runtime_error
		 */
		static Surface* Load_BMP(const string& file);

		/**
		  Saves a Surface as a Windows BMP.
		 
		  @param surface The surface to save.
		  @param file The file to save the surface as.
		 
		  @note This is equivalent to calling SDL_SaveBMP.
		 */
		static bool Save_BMP(Surface& surface, const string& file);

#ifdef SDLPP_NEED_SDL_IMAGE
		/**
		  Load file for use as an image in a new surface.
		 
		  @param file Image file name to load a surface from.
		 
		  @note This is equivalent to calling IMG_Load.
		 
		  @throw runtime_error
		 */
		static Surface* Load(const string& file)
		{
			Surface* surface = new Surface(IMG_Load(file.c_str()));
			if (surface == 0) {
				throw runtime_error(string()
						+ "IMG_Load returned NULL: "
						+ IMG_GetError());
			}
			return surface;
		}

		/**
		  Load RW_ops for use as an image in a new surface.
		 
		  @param src The source RW_ops to read the image from.
		  @param auto_close If true, we will automatically close/free the src
		  for you.
		  @param type Which format type to interpret the image as.
		 
		  @note This is equivalent to calling IMG_Load_RW if type is the empty
		  string, or IMG_LoadTyped_RW if it's not.
		  @note This method does not guarantee that the format specified by
		  type is the format of the loaded image, except in the case when TGA
		  format is specified (or any other non-magicable format).
		 
		  @throw runtime_error
		 */
		static Surface* Load(RW_ops& src, bool auto_close,
				const string& type = "")
		{
			SDL_RWops* wrap_ops = src.raw_ptr();
			Surface* surface = 0;

			if (type == "") {
				surface = new Surface(
						IMG_Load_RW(wrap_ops, auto_close));
				if (surface == 0) {
					throw runtime_error(string()
							+ "IMG_LoadTyped_RW returned NULL: "
							+ IMG_GetError());
				}
			}
			else {
				surface = new Surface(
						IMG_LoadTyped_RW(wrap_ops, auto_close,
							/*
							  This is ugly, but I confirmed that
							  IMG_LoadTyped_RW doesn't modify this parameter.
							 */
							const_cast<char*>(type.c_str())));
				if (surface == 0) {
					throw runtime_error(string()
							+ "IMG_Load_RW returned NULL: "
							+ IMG_GetError());
				}
			}
			
			return surface;
		}
#endif /* SDLPP_NEED_SDL_IMAGE */

	private:
		/* We declare these private to force Surface_factory uninstantiable. */
		Surface_factory();
		Surface_factory(const Surface_factory&);
	};
	
	/**
	  A Video_surface represents the video framebuffer.
	 */
	class Video_surface : public Surface
	{
	public:
		/**
		  The "SDL_SetVideoMode" constructor.
		 
		  Set up a video mode with the specified width, height and
		  bits-per-pixel.
		 
		  @throw runtime_error
		 */
		Video_surface(int width, int height, int bpp, Uint32 flags = 0);

		/**
		  The copy constructor.
		 
		  @throw runtime_error
		 */
		Video_surface(const Video_surface& that);

		/**
		  The deconstructor.
		 */
		virtual ~Video_surface();

		/**
		  @return a pointer to the current display surface as known
		  to SDL.
		 
		  @throw runtime_error if the is no current display surface.
		 */
		static auto_ptr<Video_surface> Get();

		/**
		  Swaps screen buffers.
		 */
		bool flip();

		/**
		  Makes sure the given area is updated.
		 
		  @note This is equivalent to calling SDL_UpdateRect.
		 */
		void update(Sint32 x, Sint32 y, Sint32 w, Sint32 h);

		/**
		  Makes sure the given area is updated.
		 
		  @note This is an SDL++ extension.
		  @note This is equivalent to calling SDL_UpdateRects.
		 */
		void update(Rect& r);

		/**
		  Makes sure the whole screen is updated.
		 
		  @note This is an SDL++ extension.
		  @note This is equivalent to calling SDL_UpdateRect with x, y, w,
		  and h parameters equal to 0.
		 */
		void update(void);

		/**
		  Makes sure the given list of rectangles is updated on the given
		  screen.
		 
		  @note This is equivalent to calling SDL_UpdateRects.
		 */
		void update(vector<Rect>& rects);

	private:
		/**
		  The wrapper constructor. Part of the private interface only
		  for the Get() function.
		 
		  Wraps a Video_surface around the given SDL_Surface object. The
		  wrapper becomes the new owner of the object.
		  @param surface the SDL_Surface to wrap
		 
		  @throw runtime_error
		 */
		Video_surface(SDL_Surface* screen);
	};

	// SDL_BlitSurface - This function performs a fast blit from the source surface to the destination surface.
	// SDL_ConvertSurface - Converts a surface to the same format as another surface.
	// SDL_CreateRGBSurface - ...
	// SDL_CreateRGBSurfaceFrom - ...
	// SDL_DisplayFormatAlpha - Converts a surface to the display format
	// SDL_DisplayFormat - Converts a surface to the display format.
	// SDL_FillRect - This function performs a fast fill of the given rectangle with some color
	// SDL_Flip - Swaps screen buffers.
	// SDL_FreeSurface - Frees (deletes) a SDL_Surface.
	// SDL_GetClipRect - Gets the clipping rectangle for a surface.
	// SDL_GetGammaRamp - Gets the color gamma lookup tables for the display.
	// SDL_GetVideoSurface - Returns a pointer to the current display surface. Implemented as class Surface.
	// SDL_LockSurface - Locks a surface for direct access.
	// SDL_SetAlpha - Adjusts the alpha properties of a surface
	// SDL_SetClipRect - Sets the clipping rectangle for a surface.
	// SDL_SetColorKey - Sets the color key (transparent pixel) in a blittable surface and RLE acceleration.
	// SDL_SetColors - Sets a portion of the colormap for the given 8-bit surface.
	// SDL_SetGammaRamp - Sets the color gamma lookup tables for the display.
	// SDL_SetGamma - Sets the color gamma function for the display.
	// SDL_SetPalette - Sets the colors in the palette of an 8-bit surface.
	// SDL_SetVideoMode - Sets up a video mode with the specified width, height and bits-per-pixel.
	// SDL_UnlockSurface - Unlocks a previously locked surface.
	// SDL_UpdateRect - Makes sure the given area is updated on the given screen.
	// SDL_UpdateRects - Makes sure the given list of rectangles is updated on the given screen.
}

#endif /* SDLPP_SURFACE_HPP_INCLUDED */
