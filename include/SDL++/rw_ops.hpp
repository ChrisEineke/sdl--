#ifndef SDLPP_RW_OPS_HPP_INCLUDED
#define SDLPP_RW_OPS_HPP_INCLUDED
/* vim: set ts=4 sts=4 sw=4 tw=80: */

#include "SDL.h"
#include <SDL++/shared_ptr_base.hpp>
#include <stdexcept>
#include <string>

namespace sdlpp
{
	using std::runtime_error;
	using std::auto_ptr;
	using std::string;

	class RW_ops : public shared_ptr_base<SDL_RWops>
	{
	public:
		int seek(int offset, int whence);
		int read(void *ptr, int size, int maxnum);
		int write(const void *ptr, int size, int num);
		int close(void);

		/**
		 * @note This is equivalent to calling SDL_RWFromFile.
		 * @throw runtime_error
		 */
		RW_ops(const string& file_name, const string& file_mode);
		
		/**
		 * @note This is equivalent to calling SDL_RWFromFP.
		 * @throw runtime_error
		 */
		RW_ops(FILE* fp, bool auto_close);
		
		/**
		 * @note This is equivalent to calling SDL_RWFromMem.
		 * @throw runtime_error
		 */
		RW_ops(void* mem, int size);
		
		/**
		 * @note This is equivalent to calling SDL_RWFromConstMem.
		 * @throw runtime_error
		 */
		RW_ops(const void* mem, int size);
	};
}

#endif /* SDLPP_RW_OPS_HPP_INCLUDED */
