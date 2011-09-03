/* vim: set ts=4 sts=4 sw=4 tw=80: */
#include <SDL++/rw_ops.hpp>

namespace
{
	using std::runtime_error;
	using std::string;

	/**
	 * Opens a file.
	 * @throw runtime_error
	 */
	SDL_RWops* RWFromFile(const char* file, const char* mode)
	{
		SDL_RWops* ops = SDL_RWFromFile(file, mode);
		if (ops == 0) {
			throw runtime_error(string()
					+ "SDL_RWFromFile returned NULL: "
					+ SDL_GetError());
		}
		return ops;
	}

	/**
	 * Opens a file from a stdio file pointer.
	 * @throw runtime_error
	 */
	SDL_RWops* RWFromFP(FILE *fp, int autoclose)
	{
		SDL_RWops* ops = SDL_RWFromFP(fp, autoclose);
		if (ops == 0) {
			throw runtime_error(string()
					+ "SDL_RWFromFP returned NULL: "
					+ SDL_GetError());
		}
		return ops;
	}

	/**
	 * Prepares a memory area for use with RWops.
	 * @throw runtime_error
	 */
	SDL_RWops* RWFromMem(void *mem, int size)
	{
		SDL_RWops* ops = SDL_RWFromMem(mem, size);
		if (ops == 0) {
			throw runtime_error(string()
					+ "SDL_RWFromMem returned NULL: "
					+ SDL_GetError());
		}
		return ops;
	}
	/**
	 * Prepares a constant memory area for use with RWops.
	 * @throw runtime_error
	 */
	SDL_RWops* RWFromConstMem(const void *mem, int size)
	{
		SDL_RWops* ops = SDL_RWFromConstMem(mem, size);
		if (ops == 0) {
			throw runtime_error(string()
					+ "SDL_RWFromConstMem returned NULL: "
					+ SDL_GetError());
		}
		return ops;
	}
}

namespace sdlpp
{
	RW_ops::RW_ops(const string& file_name, const string& file_mode) :
			shared_ptr_base<SDL_RWops>(
					RWFromFile(file_name.c_str(), file_mode.c_str()),
					SDL_FreeRW)
	{
	}
	
	RW_ops::RW_ops(FILE* fp, bool auto_close) :
			shared_ptr_base<SDL_RWops>(RWFromFP(fp, auto_close), SDL_FreeRW)
	{
	}
	
	RW_ops::RW_ops(void* mem, int size) :
			shared_ptr_base<SDL_RWops>(RWFromMem(mem, size), SDL_FreeRW)
	{
	}
	
	RW_ops::RW_ops(const void* mem, int size) :
			shared_ptr_base<SDL_RWops>(RWFromConstMem(mem, size), SDL_FreeRW)
	{
	}

	int RW_ops::seek(int offset, int whence)
	{
		return SDL_RWseek(p.get(), offset, whence);
	}

	int RW_ops::read(void* ptr, int size, int maxnum)
	{
		return SDL_RWread(p.get(), ptr, size, maxnum);
	}

	int RW_ops::write(const void* ptr, int size, int num)
	{
		return SDL_RWwrite(p.get(), ptr, size, num);
	}

	int RW_ops::close(void)
	{
		return SDL_RWclose(p.get());
	}
}
