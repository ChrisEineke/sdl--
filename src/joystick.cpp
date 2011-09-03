#include <SDL++/joystick.hpp>

namespace sdlpp
{
	/**
	  @throw runtime_error
	 */
	Joystick::Joystick(int index) :
		shared_ptr_base<SDL_Joystick>(SDL_JoystickOpen(index), SDL_JoystickClose)
	{
		if (p.get() == 0) {
			throw runtime_error("SDL_JoystickOpen returned NULL");
		}
	}

	/**
	  @throw runtime_error
	 */
	Joystick::Joystick(SDL_Joystick* joystick) :
		shared_ptr_base<SDL_Joystick>(joystick, SDL_JoystickClose)
	{
		if (p.get() == 0) {
			throw runtime_error("Attempted to wrap a NULL joystick");
		}
	}

	/**
	  @throw runtime_error
	 */
	Joystick::Joystick(const Joystick& that) :
		shared_ptr_base<SDL_Joystick>(that)
	{
		if (p.get() == 0) {
			throw runtime_error("Attempted to copy-construct a NULL joystick");
		}
	}

	int Joystick::index()
	{
		return SDL_JoystickIndex(p.get());
	}

	int Joystick::num_axes()
	{
		return SDL_JoystickNumAxes(p.get());
	}
	
	int Joystick::num_balls()
	{
		return SDL_JoystickNumBalls(p.get());
	}

	int Joystick::num_buttons()
	{
		return SDL_JoystickNumButtons(p.get());
	}

	int Joystick::num_hats()
	{
		return SDL_JoystickNumHats(p.get());
	}

	Sint16 Joystick::axis(int axis)
	{
		return SDL_JoystickGetAxis(p.get(), axis);
	}

	bool Joystick::ball(int ball, int* dx, int* dy)
	{
		return SDL_JoystickGetBall(p.get(), ball, dx, dy) == 0;
	}

	Uint8 Joystick::button(int button)
	{
		return SDL_JoystickGetButton(p.get(), button);
	}

	Uint8 Joystick::hat(int hat)
	{
		return SDL_JoystickGetHat(p.get(), hat);
	}

	string Joystick::name()
	{
		return string(SDL_JoystickName(index()));
	}

	vector<Joystick> Joystick::Enumerate(bool include_opened)
	{
		vector<Joystick> joysticks;
		int N = SDL_NumJoysticks();

		for (int i=0; i<N; i++) {
			if (include_opened || !SDL_JoystickOpened(i)) {
				joysticks.push_back(Joystick(i));
			}
		}

		return joysticks;
	}
}
