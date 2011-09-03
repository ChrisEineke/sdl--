/* vim: set ts=4 sts=4 sw=4 tw=80: */
#include <SDL++/SDL++.hpp>
#include <stdexcept>
#include <iostream>

using namespace std;
using namespace SDL;

/*
 * Tells the main loop whether we want to keep looping or not.
 */
bool keep_running = true;

/*
 * Define a quit event listener that sets the above bool to false if the user
 * closes the window or hits CTRL+C.
 */
class Quit_listener : public Callback<SDL_QuitEvent*>
{
	/*
	 * The method we need to implement as defined in the abstract base class
	 * Callback<SDL_QuitEvent*>.
	 */
	virtual Uint32 invoke(Source& src, SDL_QuitEvent*, void*)
	{
		cout << "Quit event raised. Exiting." << endl;
		keep_running = false;
		return 0;
	}
};

int main(int ac, char* av[])
{
	/* Initialize the SDL library. */
	Library lib;
	lib.everything();

	try {
		/*
		 * Initialize a screen that is of the same dimension as the test image.
		 */
		Video_surface screen(250, 250, 32);

		/*
		 * Load a BMP image using the Surface_factory. If you #define
		 * SDLPP_NEED_SDL_IMAGE, you could use Load instead of Load_BMP.
		 */
		Surface* surface = Surface_factory::Load_BMP("../tests/test.bmp");

		/*
		 * Instantiate the quit listener.
		 */
		Quit_listener listener;

		/*
		 * Attach the listener to the library quit event.
		 */
		quit_event.attach(listener);

		/*
		 * Keep blitting and flipping until a quit event is raised or
		 * WaitEvent() returns an error.
		 */
		while ((keep_running == true) && (WaitEvent() == true)) {
			/*
			 * Blit the whole test image to the whole screen.
			 */
			surface->blit(screen);

			/*
			 * Make the image show up.
			 */
			screen.flip();
		}
	}
	catch (runtime_error& re) {
		/*
		 * In case an error occurs, we catch any exceptions here and print the
		 * message.
		 */
		cout << re.what() << endl;
	}
}
