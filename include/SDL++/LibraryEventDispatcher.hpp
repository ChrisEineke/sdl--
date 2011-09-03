#ifndef SDLPP_LIBRARYEVENTDISPATCHER_HPP_INCLUDED
#define SDLPP_LIBRARYEVENTDISPATCHER_HPP_INCLUDED

#include <list>
#include <utility>
#include <algorithm>
#include <SDL++/EventListener.hpp>

namespace sdlpp
{
	template <typename LibraryEventType> class LibraryEventDispatcher
	{
		public:
			friend class SDLLibrary;

			typedef EventListener<LibraryEventType> TypedListener;

			EventDispatcher() : m_ListenerList()
			{ }

			virtual ~EventDispatcher() = 0
			{ m_ListenerList.clear(); }

			void addEventListener(TypedListener * const listener)
			{
				if (hasEventListener(type, listener)) {
					return;
				}
				else {
					m_ListenerList.push_back(listener);
				}
			}

			bool hasEventListener(TypedListener * const listener)
			{
				return std::find(
						  m_ListenerList.begin()
						, m_ListenerList.end()
						, listener)
					!= m_ListenerList.end();
			}

			void removeEventListener(TypedListener * const listener)
			{
				m_ListenerList.erase(
						std::remove(
							  m_ListenerList.begin()
							, m_ListenerList.end()
							, listener)
						, m_ListenerList.end());
			}

			bool dispatchEvent(LibraryEventType& event, bool queue = false)
			{
				if (queue) {
					return SDL_PushEvent(static_cast<union SDL_Event*>(&event));
				}
				else {
					return distributeEvent(event);
				}
			}

		protected:
			void distributeEvent(LibraryEventType& event)
			{
				/*
				 * Make a copy of the subscriber list to avoid iteration while the list
				 * could be modified.
				 */
				TypedList cp(m_ListenerList);
				for (TypedIterator i=cp.begin(), end=cp.end() ; i != end ; ++i) {
					(*i)->handle(event);
				}
				return true;
			}

		private:
			typedef std::list<TypedListener*> TypedList;
			typedef TypedList::iterator TypedIterator;

			TypedList m_ListenerList;
	};
}

#endif /* SDLPP_LIBRARYEVENTDISPATCHER_HPP_INCLUDED */
