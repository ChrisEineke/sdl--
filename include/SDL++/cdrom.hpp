#ifndef SDLPP_CDROM_HPP_INCLUDED
#define SDLPP_CDROM_HPP_INCLUDED
/* vim: set ts=4 sts=4 sw=4 tw=80: */

#include "SDL.h"
#include <SDL++/shared_ptr_base.hpp>
#include <stdexcept>
#include <vector>
#include <string>

namespace sdlpp
{
	using std::runtime_error;
	using std::vector;
	using std::string;

	typedef SDL_CDtrack CDtrack;

	/**
	 * The concrete class Cdrom.
	 *
	 * Cdrom provides a wrapper around an SDL_CD struct and related functions.
	 * Internally, the pointer to a SDL_CD is managed by a shared_ptr so you don't
	 * have to.
	 *
	 * @note There is no equivalent for the SDL_CDNumDrives function. Instead,
	 * we have provided a static function called Enumerate that will return all
	 * drives in the system.
	 */
	class Cdrom : public shared_ptr_base<SDL_CD>
	{
	public:
		/**
		 * The default constructor.
		 *
		 * Opens a CD-ROM.
		 *
		 * @param index The index of the CD-ROM. The default CD-ROM is 0.
		 *
		 * @throw runtime_error If an error occured while opening a CD-ROM.
		 */
		Cdrom(int index = 0);

		/**
		 * The wrapper constructor.
		 *
		 * Wraps an existing CD-ROM.
		 *
		 * @throw runtime_error If cdrom is 0.
		 */
		Cdrom(SDL_CD* cdrom);

		/**
		 * The copy constructor.
		 *
		 * @throw runtime_error If that is an invalid instance of Cdrom.
		 */
		Cdrom(const Cdrom& that);

		/**
		 * @return The private drive identifier.
		 */
		inline int id() const
		{ return p->id; }

		/**
		 * @return The drive status.
		 */
		inline CDstatus status() const
		{ return p->status; }

		/**
		 * @return The number of tracks on the CD.
		 */
		inline int num_tracks() const
		{ return p->numtracks; }

		/**
		 * @return The current track.
		 */
		inline int cur_track() const
		{ return p->cur_track; }

		/**
		 * @return The current frame offset within the track.
		 */
		inline int cur_frame() const
		{ return p->cur_frame; }

		/**
		 * @return The array of track descriptions;
		 */
		inline CDtrack* track() const
		{ return p->track; }

		/**
		 * @return Whether or not there is a CD in the drive.
		 */
		inline bool in_drive() const
		{ return CD_INDRIVE(p->status); }

		/**
		 * @return Whether or not the CD is not playing.
		 */
		inline bool stopped() const
		{ return p->status == CD_STOPPED; }

		/**
		 * @return Whether or not the CD is playing.
		 */
		inline bool playing() const
		{ return p->status == CD_PLAYING; }

		/**
		 * @return Whether or not the CD is playing, but paused.
		 */
		inline bool paused() const
		{ return p->status == CD_PAUSED; }

		/**
		 * Ejects the CD-ROM.
		 *
		 * @return True if the CD was successfully ejected. False otherwise.
		 */
		inline bool eject()
		{ return SDL_CDEject(p.get()) == 0; }

		/**
		 * @return A human-readable, system-dependent identifier for the CD-ROM.
		 */
		inline string name()
		{ return string(SDL_CDName(p->id)); }

		/**
		 * Pauses a CD.
		 *
		 * @return True if the CD was successfully paused. False otherwise.
		 */
		inline bool pause()
		{ return SDL_CDPause(p.get()) == 0; }

		/**
		 * Plays a CD.
		 *
		 * @param start Frame to start playing at.
		 * @param length Number of frames to play.  
		 *
		 * @return True if the CD was successfully started to play. False
		 * otherwise.
		 */
		inline bool play(int start = 0, int length = 0)
		{ return SDL_CDPlay(p.get(), start, length) == 0; }

		/**
		 * Plays the given CD track(s).
		 *
		 * @return True if the CD was successfully started to play. False
		 * otherwise.
		 */
		inline bool play_tracks(int start_track = 0, int start_frame = 0, int ntracks = 0, int nframes = 0)
		{ return SDL_CDPlayTracks(p.get(), start_track, start_frame, ntracks, nframes); }

		/**
		 * Resumes playback.
		 *
		 * @return True if the CD successfully resumed to play. False otherwise.
		 */
		inline bool resume()
		{ return SDL_CDResume(p.get()) == 0; }

		/**
		 * Stops playback.
		 *
		 * @return True if the CD successfully stopped to play. False otherwise.
		 */
		inline bool stop()
		{ return SDL_CDStop(p.get()) == 0; }

		/**
		 * Creates instances for every available CD-ROM.
		 *
		 * @return a vector of CdromS.
		 */
		static vector< shared_ptr<Cdrom> > Enumerate();
	};
}

#endif /* SDLPP_CDROM_HPP_INCLUDED */
