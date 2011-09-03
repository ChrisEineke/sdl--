#ifndef SDLPP_LIBRARYEVENTLISTENER_HPP_INCLUDED
#define SDLPP_LIBRARYEVENTLISTENER_HPP_INCLUDED
/* vim: set ts=2 sts=2 sw=2 tw=80: */

namespace sdlpp
{
	template <typename T>
	class LibraryEventListener
	{
	public:
		EventListener() { }
		virtual void handle(T* event, LibraryEventDispatcher* source) { } = 0;
		virtual ~EventListener() { } = 0;
	};
}

#endif /* SDLPP_LIBRARYEVENTLISTENER_HPP_INCLUDED */
