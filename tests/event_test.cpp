#include <SDL++/SDL++.hpp>

using namespace SDL;

class MyFirstClass
{
	public:
		MyFirstClass()
		{ }

		virtual ~MyFirstClass()
		{ }

		virtual void OnTest(TestEvent* e)
		{ printf("OnTest in MyFirstClass\n"); }
};

class MySecondClass : public MyFirstClass
{
	public:
		MySecondClass() : MyFirstClass()
		{ }

		virtual ~MySecondClass()
		{ }

		virtual void OnTest(TestEvent* e)
		{ printf("OnTest in MySecondClass\n"); }
};

class MyEventSource : public EventDispatcher<TestEvent>
{
	public:
		MyEventSource() : EventDispatcher<TestEvent>()
		{ }
	
		void foo()
		{ dispatchEvent(new TestEvent()); }

		virtual void OnTest(TestEvent* e)
		{ printf("OnTest in MyEventSource\n"); }
};

int main(int ac, char* av[])
{
	MyFirstClass first;
	MySecondClass second;
	MyEventSource source;
	source.addEventListener(&source, &source::OnTest);
	source.addEventListener(&first, &first::OnTest);
	source.addEventListener(&second, &second::OnTest);
	return EXIT_SUCCESS;
}
