/* vim: set ts=4 sts=4 sw=4 tw=80: */
#include <SDL++/surface.hpp>

namespace
{
	void Video_surface_deleter(SDL_Surface*)
	{
		/**
		 * "The surface returned is freed by SDL_Quit() and should'nt
		 * be freed by the caller." - SDL_SetVideoMode man page
		 */
	}

	using std::runtime_error;
	using std::string;

	SDL_Surface* CreateRGBSurface(Uint32 flags, int width, int height,
			int bitsPerPixel, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask,
			Uint32 Amask)
	{
		SDL_Surface* surface = SDL_CreateRGBSurface(flags, width, height,
				bitsPerPixel, Rmask, Gmask, Bmask, Amask);
		if (surface == 0) {
			throw runtime_error(string()
					+ "SDL_CreateRGBSurface returned NULL: "
					+ SDL_GetError());
		}
		return surface;
	}

	SDL_Surface* CreateRGBSurfaceFrom(void *pixels, int width, int height,
			int bitsPerPixel, int pitch, Uint32 Rmask, Uint32 Gmask,
			Uint32 Bmask, Uint32 Amask)
	{
		SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, width, height,
				bitsPerPixel, pitch, Rmask, Gmask, Bmask, Amask);
		if (surface == 0) {
			throw runtime_error(string()
					+ "SDL_CreateRGBSurfaceFrom returned NULL: "
					+ SDL_GetError());
		}
		return surface;
	}
	
	SDL_Surface* SetVideoMode(int width, int height, int bpp,
			Uint32 flags)
	{
		SDL_Surface* screen = SDL_SetVideoMode(width, height, bpp, flags);
		if (screen == 0) {
			throw runtime_error(string()
					+ "SDL_CreateRGBSurfaceFrom returned NULL: "
					+ SDL_GetError());
		}
		return screen;
	}
}

namespace sdlpp
{
	Surface::Surface(Uint32 flags, int width, int height, int depth, Uint32
			Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) :
			shared_ptr_base<SDL_Surface>(CreateRGBSurface(flags, width, height,
						depth, Rmask, Gmask, Bmask, Amask), SDL_FreeSurface)
			/* SDL guarantees clip_rect to be non-NULL */
	{
		/*
		 * If SDL_CreateRGBSurface returns a NULL pointer,
		 * CreateRGBSurface will throw the exception.
		 */
	}

	Surface::Surface(void* pixels, int width, int height, int depth, int pitch,
			Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) :
			shared_ptr_base<SDL_Surface>(CreateRGBSurfaceFrom(pixels, width,
						height, depth, pitch, Rmask, Gmask, Bmask, Amask),
					SDL_FreeSurface)
			/* SDL guarantees clip_rect to be non-NULL */
	{
		/*
		 * If SDL_CreateRGBSurfaceFrom returns a NULL pointer,
		 * CreateRGBSurfaceFrom will throw the exception.
		 */
	}
	
	Surface::Surface(SDL_Surface* surface) :
		shared_ptr_base<SDL_Surface>(surface, SDL_FreeSurface)
	{
		if (p.get() == 0) {
			throw runtime_error("Attempted to wrap a NULL surface");
		}
	}

	Surface::Surface(const Surface& that) :
		shared_ptr_base<SDL_Surface>(that)
	{
		if (p.get() == 0) {
			throw runtime_error("Attempted to copy-construct a NULL surface");
		}
	}

	Surface::~Surface()
	{
	}

	bool Surface::blit(Surface& dst)
	{
		return SDL_BlitSurface(
				p.get(), 0,
				dst.raw_ptr(), 0) == 0;
	}

	bool Surface::blit(Rect& src_rect, Surface& dst)
	{
		return SDL_BlitSurface(
				p.get(), &src_rect,
				dst.raw_ptr(), 0) == 0;
	}

	bool Surface::blit(Rect& src_rect, Surface& dst, Rect& dst_rect)
	{
		return SDL_BlitSurface(
				p.get(), &src_rect,
				dst.raw_ptr(), &dst_rect) == 0;
	}

	bool Surface::blit(Surface& dst, Rect& dst_rect)
	{
		return SDL_BlitSurface(
				p.get(), 0,
				dst.raw_ptr(), &dst_rect) == 0;
	}

	bool Surface::fill(Rect* rect, Uint32 color)
	{
		return SDL_FillRect(p.get(), rect, color) == 0;
	}

	bool Surface::convert(SDL_PixelFormat* fmt, Uint32 flags)
	{
		/**
		 * SDL_ConvertSurface makes a real copy of the surface.
		 */
		SDL_Surface* converted_surface = SDL_ConvertSurface(p.get(), fmt, flags);
		if (converted_surface == 0) {
			return false;
		}
		else {
			p.reset(converted_surface, SDL_FreeSurface);
			return true;
		}
	}

	bool Surface::display_format()
	{
		/*
		 * SDL_DisplayFormat makes a real copy of the surface.
		 */
		SDL_Surface* formatted_surface = SDL_DisplayFormat(p.get());
		if (formatted_surface == 0) {
			return false;
		}
		else {
			p.reset(formatted_surface, SDL_FreeSurface);
			return true;
		}
	}

	bool Surface::display_format_alpha()
	{	
		/*
		 * SDL_DisplayFormatAlpha makes a real copy of the surface.
		 */
		SDL_Surface* formatted_surface = SDL_DisplayFormatAlpha(p.get());
		if (formatted_surface == 0) {
			return false;
		}
		else {
			p.reset(formatted_surface, SDL_FreeSurface);
			return true;
		}
	}

	bool Surface::set_alpha(Uint32 flag, Uint8 alpha)
	{
		return SDL_SetAlpha(p.get(), flag, alpha) == 0;
	}

	bool Surface::set_clip(Rect* rect)
	{
		return SDL_SetClipRect(p.get(), rect);
	}

	Rect Surface::get_clip()
	{
		SDL_Rect rect;
		SDL_GetClipRect(p.get(), &rect);
		return Rect(rect);
	}

	bool Surface::set_colors(SDL_Color* colors, int firstcolor, int ncolors)
	{
		return SDL_SetColors(p.get(), colors, firstcolor, ncolors);
	}

	bool Surface::set_colors(vector<SDL_Color>& colors, int firstcolor, int ncolors)
	{
		return SDL_SetColors(p.get(), &colors[0], firstcolor, ncolors);
	}

	bool Surface::set_colors(vector<Color>& colors, int firstcolor, int ncolors)
	{
		return SDL_SetColors(p.get(), &colors[0], firstcolor, ncolors);
	}

	bool Surface::set_color_key(Uint32 flag, Uint32 key)
	{
		return SDL_SetColorKey(p.get(), flag, key) == 0;
	}

	bool Surface::set_palette(int flags, SDL_Color* colors, int firstcolor, int ncolors)
	{
		return SDL_SetPalette(p.get(), flags, colors, firstcolor, ncolors);
	}
	
	bool Surface::set_palette(int flags, std::vector<SDL_Color>& colors, int firstcolor, int ncolors)
	{
		return SDL_SetPalette(p.get(), flags, &colors[0], firstcolor, ncolors);
	}

	bool Surface::set_palette(int flags, std::vector<Color>& colors, int firstcolor, int ncolors)
	{
		return SDL_SetPalette(p.get(), flags, &colors[0], firstcolor, ncolors);
	}

	bool Surface::must_lock()
	{
		return SDL_MUSTLOCK(p.get());
	}

	bool Surface::lock()
	{
		if (must_lock()) {
			return SDL_LockSurface(p.get()) == 0;
		}
		return false;
	}

	void Surface::unlock()
	{
		if (must_lock()) {
			SDL_UnlockSurface(p.get());
		}
	}

/* Surface_factory */

	Surface* Surface_factory::Load_BMP(const string& file)
	{
		Surface* surface = new Surface(SDL_LoadBMP(file.c_str()));
		if (surface == 0) {
			throw runtime_error(string()
					+ "SDL_LoadBMP returned NULL: "
					+ SDL_GetError());
		}
		return surface;
	}

	bool Surface_factory::Save_BMP(Surface& surface, const string& file)
	{
		return SDL_SaveBMP(surface.raw_ptr(), file.c_str()) == 0;
	}

/* Video_surface */

	Video_surface::Video_surface(int width, int height, int bpp, Uint32 flags) :
			Surface(SDL_SetVideoMode(width, height, bpp, flags))
	{
		if (p.get() == 0) {
			throw runtime_error("SDL_SetVideoMode returned NULL");
		}
		p.reset(p.get(), Video_surface_deleter);
	}

	Video_surface::Video_surface(const Video_surface& that) :
		Surface(that)
	{
		if (p.get() == 0) {
			throw runtime_error("Attempted to copy-construct a NULL video surface");
		}
	}

	Video_surface::~Video_surface()
	{
	}
	
	auto_ptr<Video_surface> Video_surface::Get()
	{
		return auto_ptr<Video_surface>(new Video_surface(SDL_GetVideoSurface()));
	}

	bool Video_surface::flip()
	{
		return SDL_Flip(p.get()) == 0;
	}

	void Video_surface::update(Sint32 x, Sint32 y, Sint32 w, Sint32 h)
	{
		SDL_UpdateRect(p.get(), x, y, w, h);
	}
	
	void Video_surface::update(Rect& r)
	{
		SDL_UpdateRects(p.get(), 1, &r);
	}

	void Video_surface::update(void)
	{
		SDL_UpdateRect(p.get(), 0, 0, 0, 0);
	}

	void Video_surface::update(vector<Rect>& rects)
	{
		SDL_UpdateRects(p.get(), rects.size(), &rects[0]);
	}

	Video_surface::Video_surface(SDL_Surface* screen) :
		Surface(screen)
	{
		if (p.get() == 0) {
			throw runtime_error("Attempt to wrap a NULL video surface");
		}
		p.reset(p.get(), Video_surface_deleter);
	}
}
