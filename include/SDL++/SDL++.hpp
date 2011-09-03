#ifndef SDLPP_HPP_INCLUDED
#define SDLPP_HPP_INCLUDED
/* vim:set cindent sw=4 ts=4 sts=4 */

/*! \mainpage SDL++ Front Page

  \section intro Introduction

  SDL++ is a C++ layer that sits on top of SDL. It provides wrapper classes
  for SDL functionality. Highlights include templated event, timer, and task
  classes that provide a type-safe way to send event data from event sources
  to listeners and decentralized event dispatch and handling, and handy
  wrapper classes for almost all SDL types.

  This is the introduction.

  \section library_support Support for additional SDL libraries

  SDL++ contains support for additional SDL libraries that you may activate
  when you define one of the following preprocessor macros before including
  the main SDL++ header:
  <ul>
    <li><em>SDLPP_NEED_SDL_IMAGE</em> - Enables support for loading a
    multitude of image formats.</li>
  </ul>
 */

#include <SDL++/callback.hpp>
#include <SDL++/cdrom.hpp>
#include <SDL++/color.hpp>
#include <SDL++/condition.hpp>
#include <SDL++/cursor.hpp>
#include <SDL++/event.hpp>
#include <SDL++/events.hpp>
#include <SDL++/joystick.hpp>
#include <SDL++/library_event.hpp>
#include <SDL++/mutex.hpp>
#include <SDL++/overlay.hpp>
#include <SDL++/pixel_format.hpp>
#include <SDL++/rect.hpp>
#include <SDL++/rw_ops.hpp>
#include <SDL++/semaphore.hpp>
#include <SDL++/shared_ptr_base.hpp>
#include <SDL++/source.hpp>
#include <SDL++/surface.hpp>
#include <SDL++/task.hpp>
#include <SDL++/thread.hpp>
#include <SDL++/time.hpp>
#include <SDL++/timer.hpp>
#include <SDL++/user_event.hpp>

#include <SDL++/library.hpp>

namespace SDL = sdlpp;

#endif /* SDLPP_HPP_INCLUDED */
