/* vim: set ts=4 sts=4 sw=4 tw=80: */
#include <SDL++/cdrom.hpp>
#include <string>

namespace sdlpp
{
	Cdrom::Cdrom(int index) :
		shared_ptr_base<SDL_CD>(SDL_CDOpen(index), SDL_CDClose)
	{
		if (p.get() == 0) {
			throw runtime_error(string()
					+ "SDL_CDOpen returned NULL: "
					+ SDL_GetError());
		}
	}

	Cdrom::Cdrom(SDL_CD* cdrom) :
		shared_ptr_base<SDL_CD>(cdrom, SDL_CDClose)
	{
		if (p.get() == 0) {
			throw runtime_error("Attempted to wrap a NULL cdrom");
		}
	}

	Cdrom::Cdrom(const Cdrom& that) :
		shared_ptr_base<SDL_CD>(that)
	{
		if (p.get() == 0) {
			throw runtime_error("Attempted to copy-construct a NULL cdrom");
		}
	}

	vector< shared_ptr<Cdrom> > Cdrom::Enumerate()
	{
		vector< shared_ptr<Cdrom> > cdroms;

		for (int i=0, N=SDL_CDNumDrives(); i<N; i++) {
			cdroms.push_back(shared_ptr<Cdrom>(new Cdrom(i)));
		}

		return cdroms;
	}
}
