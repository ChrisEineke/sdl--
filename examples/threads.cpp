/* vim: set ts=4 sts=4 sw=4 tw=80: */
#include <SDL++/SDL++.hpp>
#include <stdexcept>
#include <iostream>

using namespace std;
using namespace SDL;

/*
 * Tells the threads whether we want to keep looping or not.
 */
bool keep_running = true;

/*
 * Define a thread class that keeps incrementing a counter.
 */
class My_thread : public Thread<int*>
{
public:
	My_thread(const string& name, Mutex& mutex, int* cnt) :
		Thread<int*>(cnt), name(name), mutex(mutex)
	{
	}

	/*
	 * The method we need to implement as defined in the abstract base class
	 * Thread<int*>.
	 */
	virtual int func(int* data)
	{
		while (keep_running) {
			mutex.lock();
			(*data)++;
			cout << name << ": " << *data << endl;
			mutex.unlock();
		}

		return 0;
	}

private:
	string name;
	Mutex& mutex;
};

int main(int ac, char* av[])
{
	/* Initialize the SDL library. */
	Library lib;
	lib.everything();

	/*
	 * Initialize a counter and the associatied locking primitive to avoid
	 * race conditions when updating the counter.
	 */
	int cnt = 0;
	Mutex m;

	/*
	 * Instanciate the threads. Due to some race conditions we must kick them
	 * on ourselves (see the class documentation).
	 */
	My_thread a("Alpha", m, &cnt);
	My_thread b("Beta", m, &cnt);

	/*
	 * Kick both threads on.
	 */
	a.run();
	b.run();

	/*
	 * Keep printing for 5 seconds.
	 */
	SDL_Delay(5000);
	keep_running = false;

	/*
	 * Wait for ThreadS to finish their activity.
	 */
	a.wait();
	b.wait();

	return 0;
}
