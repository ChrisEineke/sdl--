#ifndef SDLPP_OVERLAY_HPP_INCLUDED
#define SDLPP_OVERLAY_HPP_INCLUDED
/* vim: set ts=4 sts=4 sw=4 tw=80: */

#include <SDL++/shared_ptr_base.hpp>
#include <SDL++/surface.hpp>
#include <stdexcept>
#include <string>

namespace sdlpp
{
	using std::runtime_error;
	using std::string;

	/**
	 * The concrete class Overlay.
	 *
	 * Overlay provides a wrapper around an SDL_Overlay struct and related
	 * functions.  Internally, the pointer to a SDL_Overlay is managed by a
	 * shared_ptr so you don't have to. We provide the helper class
	 * Overlay::Lock for safe locking and unlocking of a Overlay.
	 *
	 * An Overlay is similar to a Surface except it stores a YUV overlay.
	 *
	 * @todo We provide direct access to the pixels array. A naive
	 * programmer could a) forget to lock/unlock the overlay before
	 * accessing the surface, and b) not calculate the offsets correctly
	 * that are needed for, say, a IYUV/I420 overlay. Could we provide a
	 * wrapper class that will lock the surface on construction, unlock the
	 * surface on destruction and provide operator()(...) access to the
	 * pixels of the overlay?
	 */
	class Overlay : public shared_ptr_base<SDL_Overlay>
	{
	public:
		/**
		 * The default constructor.
		 *
		 * Creates an Overlay on a Video_surface.
		 *
		 * @throw runtime_error If an error occured while constructing an
		 * Overlay.
		 */
		Overlay(int width,
				int height,
				Uint32 format,
				Video_surface& display);
		
		/**
		 * The wrapper constructor.
		 *
		 * Wraps an Overlay around the given SDL_Overlay object. The
		 * wrapper becomes the new owner of the object.
		 *
		 * @param overlay the SDL_Overlay to wrap
		 *
		 * @throw runtime_error If overlay is 0.
		 */
		Overlay(SDL_Overlay* overlay);

		/**
		 * The copy constructor.
		 *
		 * Constructs a shallow copy of the wrapped overlay.
		 *
		 * @param that the Overlay to copy
		 *
		 * @throw runtime_error If that is an invalid Overlay.
		 */
		Overlay(const Overlay& that);

		/**
		 * @see http://www.libsdl.org/cgi/docwiki.cgi/SDL_Overlay
		 * @see http://www.fourcc.org/indexyuv.htm
		 * @return The format of this overlay.
		 */
		inline Uint32 format() const
		{ return p->format; }

		/**
		 * @return The width (in pixels) of this overlay.
		 */
		inline int w() const
		{ return p->w; }

		/**
		 * @return The height (in pixels) of this overlay.
		 */
		inline int h() const
		{ return p->h; }

		/**
		 * @note Usually either 1 or 3.
		 * @return The number of planes in this overlay.
		 */
		inline int planes() const
		{ return p->planes; }

		/**
		 * @note Pitch is the length of a row in bytes.
		 * @return The array of pitches, one for each plane, of this Overlay.
		 */
		inline Uint16* pitches()
		{ return p->pitches; }

		/**
		 * @return Whether or not this overlay is hardware accelerated.
		 */
		inline bool hw_overlay() const
		{ return p->hw_overlay; }

		/**
		 * Blits the overlay to the display.
		 * @note Since SDL doesn't allow a NULL rectangle in the call to
		 * SDL_DisplayYUVOverlay, we turned dstrect into a reference.
		 *
		 * @note This is equivalent to calling SDL_DisplayYUVOverlay.
		 */
		inline bool display(Rect& dstrect)
		{ return SDL_DisplayYUVOverlay(p.get(), &dstrect); }

		enum {
			/** Planar mode: Y + U + V */
			IYUV = SDL_IYUV_OVERLAY,
			/** Packed mode: U0+Y0+V0+Y1 */		
			UYVY = SDL_UYVY_OVERLAY,
			/** Packed mode: Y0+U0+Y1+V0 */	
			YUY2 = SDL_YUY2_OVERLAY,
			/** Planar mode: Y + V + U */
			YV12 = SDL_YV12_OVERLAY,
			/** Packed mode: Y0+V0+Y1+U0 */	
			YVYU = SDL_YVYU_OVERLAY,
		};

		class Lock
		{
			public:
				Lock(Overlay& overlay) : overlay(overlay)
				{ overlay.lock(); }

				~Lock()
				{ overlay.unlock(); }

				inline Uint8** pixels()
				{ return overlay.pixels(); }

			private:
				Overlay& overlay;

				Lock();
				Lock(const Lock& that);
				Lock& operator= (const Lock& that);
		};

	private:
		friend class Lock;

		/**
		 * @return The array of pointers to the data of each plane of this
		 * Overlay.
		 */
		inline Uint8** pixels()
		{ return p->pixels; }

		/**
		 * Locks an overlay.
		 * @return Whether or locking was successful.
		 */
		inline bool lock()
		{ return SDL_LockYUVOverlay(p.get()) == 0; }

		/**
		 * Unlocks an overlay.
		 */
		inline void unlock()
		{ SDL_UnlockYUVOverlay(p.get()); }
	};
}

#endif /* SDLPP_OVERLAY_HPP_INCLUDED */
