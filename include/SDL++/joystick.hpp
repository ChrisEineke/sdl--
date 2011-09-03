#ifndef SDLPP_JOYSTICK_HPP_INCLUDED
#define SDLPP_JOYSTICK_HPP_INCLUDED

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

	class Joystick : public shared_ptr_base<SDL_Joystick>
	{
	public:
		/**
		 * The default constructor.
		 *
		 * Opens a joystick.
		 *
		 * @throw runtime_error
		 */
		Joystick(int index);

		/**
		 * The wrapper constructor.
		 *
		 * Wraps an exisiting joystick.
		 *
		 * @throw runtime_error
		 */
		Joystick(SDL_Joystick* joystick);

		/**
		 * The copy constructor.
		 *
		 * @throw runtime_error
		 */
		Joystick(const Joystick& that);

		/**
		 * @return the index.
		 */
		int index();

		/**
		 * @return the number of axes.
		 */
		int num_axes();

		/**
		 * @return the number of trackballs.
		 */
		int num_balls();
		
		/**
		 * @return the number of buttons.
		 */
		int num_buttons();

		/**
		 * @return the number of hats.
		 */
		int num_hats();

		/**
		 * @return the current state of an axis.
		 */
		Sint16 axis(int axis = 0);

		/**
		 * Stores the relative trackball motion in dx and dy.
		 *
		 * @return true if successful, false otherwise.
		 */
		bool ball(int ball, int* dx, int* dy);

		/**
		 * @return the current state of the indexed button.
		 */
		Uint8 button(int button = 0);

		/**
		 * @return the current state of the indexed hat.
		 */
		Uint8 hat(int hat = 0);

		/**
		 * @return the name.
		 */
		string name();

		/**
		 * Creates instances for every available joystick. A joystick
		 * with index K will be at position K in the vector, only if
		 * include_opened is true.
		 *
		 * @return a vector of JoystickS.
		 */
		static vector<Joystick> Enumerate(bool include_opened = true);
	};
}

#endif /* SDLPP_JOYSTICK_HPP_INCLUDED */
