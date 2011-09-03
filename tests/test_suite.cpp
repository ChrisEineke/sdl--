#define SDLPP_NEED_SDL_IMAGE
#include <SDL++/SDL++.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

using namespace SDL;

class test_fixture :
	public CppUnit::TestFixture,
	public Callback<SDL_ActiveEvent*>,
	public Callback<>,
	public Callback<bool*>,
	public Callback<bool*, bool*>,
	public Timer_callback<bool*>
{
	CPPUNIT_TEST_SUITE(test_fixture);
	CPPUNIT_TEST(test_initial_vector_mapping);
	CPPUNIT_TEST(test_fake_library_event);
	CPPUNIT_TEST(test_user_event);
	CPPUNIT_TEST(test_timer);
	CPPUNIT_TEST(test_task);
	CPPUNIT_TEST(test_max_events);
	CPPUNIT_TEST(test_stress);
	CPPUNIT_TEST(test_video_surface);
	CPPUNIT_TEST(test_video_surface_blit);
	CPPUNIT_TEST(test_mutex);
	CPPUNIT_TEST(test_semaphore);
	CPPUNIT_TEST(test_condition);
	CPPUNIT_TEST(test_overlay_1);
	CPPUNIT_TEST(test_overlay_2);
	//CPPUNIT_TEST(test_thread); XXX: segfaults
	CPPUNIT_TEST_SUITE_END();

	Library* init;
	bool reached_callback;
	bool a;
	bool b;
	bool c;
	User_event<bool*, bool*> bool_event;
	long counter;
	
public:
	virtual void setUp()
	{
		init = new Library;
		init->video().timer();
		reached_callback = a = b = c = false;
	}

	virtual void tearDown()
	{
		delete init;
	}

	/* implement Callback<SDL_ActiveEvent*> */
	Uint32 invoke(Source&, SDL_ActiveEvent* event, void* aux)
	{
		CPPUNIT_ASSERT(event != 0);
		CPPUNIT_ASSERT(aux == 0);

		reached_callback = true;
		
		return 0;
	}

	/* implement Callback<bool*, void*> for Task */
	Uint32 invoke(Source&, bool* data1, void* data2)
	{
		CPPUNIT_ASSERT(data1 != 0);
		CPPUNIT_ASSERT(data2 == 0);
		
		reached_callback = true;
		a = *data1;
		
		return 0;
	}

	/* implement Callback<bool*, bool*> for User_event */
	Uint32 invoke(Source&, bool* data1, bool* data2)
	{
		CPPUNIT_ASSERT(data1 != 0);
		CPPUNIT_ASSERT(data2 != 0);
		
		reached_callback = true;
		a = *data1;
		b = *data2;
		
		return 0;
	}

	/* implement timer_Callback<int*> for timer */
	Uint32 invoke(Source&, Uint32 interval, bool* user)
	{
		CPPUNIT_ASSERT(interval > 0);
		CPPUNIT_ASSERT(user != 0);

		reached_callback = true;
		a = *user;
		
		return interval;
	}

	/* implement Callback<> for stress_test */
	Uint32 invoke(Source&, void*, void*)
	{
		counter++;
		return 0;
	}

	void test_initial_vector_mapping()
	{
		/*
		 * Ensure that the events vector maps the indices to the correct
		 * events.
		 */
		CPPUNIT_ASSERT(events[SDL_ACTIVEEVENT] == &active_event);
		CPPUNIT_ASSERT(events[SDL_KEYDOWN] == &key_down_event);
		CPPUNIT_ASSERT(events[SDL_KEYUP] == &key_up_event);
		CPPUNIT_ASSERT(events[SDL_MOUSEMOTION] == &mouse_motion_event);
		CPPUNIT_ASSERT(events[SDL_MOUSEBUTTONDOWN] == &mouse_button_down_event);
		CPPUNIT_ASSERT(events[SDL_MOUSEBUTTONUP] == &mouse_button_up_event);
		CPPUNIT_ASSERT(events[SDL_JOYAXISMOTION] == &joy_axis_event);
		CPPUNIT_ASSERT(events[SDL_JOYBALLMOTION] == &joy_ball_event);
		CPPUNIT_ASSERT(events[SDL_JOYHATMOTION] == &joy_hat_event);
		CPPUNIT_ASSERT(events[SDL_JOYBUTTONDOWN] == &joy_button_down_event);
		CPPUNIT_ASSERT(events[SDL_JOYBUTTONUP] == &joy_button_up_event);
		CPPUNIT_ASSERT(events[SDL_QUIT] == &quit_event);
		CPPUNIT_ASSERT(events[SDL_SYSWMEVENT] == &syswm_event);
		CPPUNIT_ASSERT(events[SDL_VIDEORESIZE] == &video_resize_event);
		CPPUNIT_ASSERT(events[SDL_VIDEOEXPOSE] == &video_expose_event);
	}

	void test_fake_library_event()
	{
		SDL_ActiveEvent data;
		active_event.attach(*this);
		active_event.push(&data);
		WaitEvent();
		CPPUNIT_ASSERT(reached_callback == true);
		reached_callback = false;
	}

	void test_user_event()
	{
		bool data = true;
		bool_event.attach(*this);
		bool_event.push(&data, &data);
		WaitEvent();
		CPPUNIT_ASSERT(a == true);
		CPPUNIT_ASSERT(b == true);
		a = b = false;
	}
	
	void test_timer()
	{
		bool data = true;
		Timer<bool*> bool_timer(*this);
		bool result = bool_timer.addTimer(500, &data);
		CPPUNIT_ASSERT(result == true);
		SDL_Delay(800);
		bool_timer.removeTimer();
		CPPUNIT_ASSERT(reached_callback == true);
		CPPUNIT_ASSERT(a == true);
		reached_callback = false;
		a = false;
	}

	void test_task()
	{
		bool data = true;
		Task<bool*> long_task(500, 3);
		long_task.attach(*this);
		long_task.start(&data);
		WaitEvent();
		CPPUNIT_ASSERT(a == true);
		a = false;
		WaitEvent();
		CPPUNIT_ASSERT(a == true);
		a = false;
		WaitEvent();
		CPPUNIT_ASSERT(a == true);
		a = false;
	}

	void test_max_events()
	{
		/* empty the queue */
		while (PollEvent()) {
		}

		counter = 0;
		for (int i = 0; i < 256; i++) {
			User_event<>* tmp = new User_event<>;
			tmp->attach(*this);
			tmp->push(0, 0);
		}
		while (PollEvent()) {
		}

		/*
		 * SDL supports only 127 events on the queue until it
		 * overflows. So the above calls to push(0, 0) will return
		 * false after the 127th push.
		 */
		CPPUNIT_ASSERT(counter == 127);
		counter = 0;
	}

	void test_stress()
	{
		/* empty the queue */
		while (PollEvent()) {
		}

		counter = 0;
		for (int i = 0; i < 65535; i++) {
			User_event<>* tmp = new User_event<>;
			tmp->attach(*this);
			bool result = tmp->push_wait(0, 0, true);
			CPPUNIT_ASSERT(result == true);
		}
		while (PollEvent()) {
		}

		/*
		 * If the event queue is about to overflow with the next push,
		 * push_wait will work the queue for us.
		 */
		CPPUNIT_ASSERT(counter == 65535);
		counter = 0;
	}

	void test_video_surface()
	{
		Video_surface screen(100, 100, 32);
		Surface::Lock l(screen);
		SDL_Delay(1000);
	}

	void test_video_surface_blit()
	{
		Rect test_rect(0, 0, 250, 250);
		Video_surface screen(250, 250, 32);
		Surface test_image(SDL_LoadBMP("./test.bmp"));
		CPPUNIT_ASSERT(test_image.w() == 250);
		CPPUNIT_ASSERT(test_image.h() == 250);
		CPPUNIT_ASSERT_EQUAL(test_image.display_format(), true);
		CPPUNIT_ASSERT_EQUAL(test_image.blit(test_rect, screen, test_rect), true);
		CPPUNIT_ASSERT_EQUAL(screen.flip(), true);
		SDL_Delay(1000);
	}

	void test_mutex()
	{
		Mutex m;
		Mutex::Lock l(m);
	}

	void test_semaphore()
	{
		Semaphore s;
	}
	
	void test_condition()
	{
		Condition s;
	}

	class My_thread : public Thread<bool*>
	{
	public:
		My_thread(bool* change_me) : Thread<bool*>(change_me)
		{
		}

		virtual int func(bool* data)
		{
			CPPUNIT_ASSERT(data != 0);
			*data = true;
			return 23;
		}
	};

	void test_overlay_1()
	{
		Video_surface screen(250, 250, 32);
		CPPUNIT_ASSERT_THROW(Overlay(100, 100, 0xDEADBEEF, screen), runtime_error);
	}

	void test_overlay_2()
	{
		Video_surface screen(250, 250, 32);
		Overlay o(100, 100, Overlay::YV12, screen);
		Overlay::Lock l(o);
	}

	void test_thread()
	{
		bool change_me = false;
		My_thread foo(&change_me);
		foo.run();
		printf("back to the main thread\n");
		CPPUNIT_ASSERT(foo.wait() == 23);
		CPPUNIT_ASSERT(change_me == true);
	}
};

int main()
{
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(test_fixture::suite());
	return runner.run() == true ? EXIT_SUCCESS : EXIT_FAILURE;
}
