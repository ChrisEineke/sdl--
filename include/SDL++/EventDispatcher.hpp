#ifndef SDLPP_EVENTDISPATCHER_HPP_INCLUDED
#define SDLPP_EVENTDISPATCHER_HPP_INCLUDED

#include <list>
#include <utility>
#include <algorithm>
#include <SDL++/EventListener.hpp>
#include <SDL++/EventType.hpp>

namespace sdlpp
{
	template
	<
		typename EventType,
		typename Collection = std::list<EventDispatcher::Delegate>
	>
	class EventDispatcher
	{
		public:
			friend class SDLLibrary;

			class Delegate
			{
				public:
					template <typename T, void (T::*TMethod)(EventType*)>
					Delegate(T * const instance, TMethod * const method)
						: instance(static_cast<void *>(instance))
						, method_stub(&method_stub_t<T, TMethod>)
					{ }

					void operator ()(EventType * const event)
					{ (*stub)(instance, event); }

				private:
					void * const instance;
					method_stub_t const stub;

					template <typename T, void (T::TMethod*)(EventType*)>
					static void method_stub_t(void * const instance, EventType * const e)
					{
						T * t = static_cast<T*>(instance);
						(t->*TMethod)(e);
					}
			};

			EventDispatcher() : m_listeners()
			{ }

			virtual ~EventDispatcher() = 0
			{ m_listeners.clear(); }

			template <typename T, void (T::*TMethod)(EventType*)>
			void addEventListener(T * const instance, TMethod * const method)
			{ addEventListener(Delegate(instance, method)); }

			template <typename T, void (T::*TMethod)(EventType*)>
			void hasEventListener(T * const instance, TMethod * const method)
			{ hasEventListener(Delegate(instance, method)); }

			template <typename T, void (T::*TMethod)(EventType*)>
			void removeEventListener(T * const instance, TMethod * const method)
			{ removeEventListener(Delegate(instance, method)); }

			bool dispatchEvent(EventType * const event, bool queue = false)
			{
				if (!queue) {
					return distributeEvent(event);
				}
				else {
					SDL_Event evt = {
						.type = SDL_USEREVENT,
						.user.code = 0,
						.user.data1 = this,
						.user.data2 = event
					};
					return SDL_PushEvent(&evt);
				}
			}

		protected:
			typedef Collection<Delegate> List;
			typedef Collection::iterator Iterator;

			void addEventListener(Delegate& delegate)
			{
				if (hasEventListener(delegate)) {
					removeEventListener(delegate);
				}
				m_listeners.push_back(delegate);
			}

			void hasEventListener(Delegate& delegate)
			{
				return
					std::find(
							m_listeners.begin(),
							m_listeners.end(),
							delegate)
					!= m_listeners.end();
			}

			void removeEventListener(Delegate& delegate)
			{
				m_listeners.erase(
						std::remove(
							m_listeners.begin(),
							m_listeners.end(),
							listener),
						m_listeners.end());
			}

			void distributeEvent(SDL_Event& event)
			{ distributeEvent(static_cast<EventType *>(event.user.data2)); }

			void distributeEvent(EventType* event)
			{
				/*
				 * Make a copy of the subscriber list to avoid iteration while the list
				 * could be modified.
				 */
				List cp(m_listeners);
				for (Iterator i=cp.begin(), end=cp.end() ; i != end ; ++i) {
					(*i)->handle(event, this);
				}
				return true;
			}
			
			List m_listeners;
	};
}

#endif /* SDLPP_EVENTDISPATCHER_HPP_INCLUDED */
