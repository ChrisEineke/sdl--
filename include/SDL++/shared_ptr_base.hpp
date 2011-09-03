#ifndef SDLPP_SHARED_PTR_BASE_INCLUDED
#define SDLPP_SHARED_PTR_BASE_INCLUDED

#include <tr1/memory> // for shared_ptr<T>

namespace sdlpp
{
	using std::tr1::shared_ptr;

	template <typename T>
	class shared_ptr_base
	{
	public:
		template <void (D)(T*)> shared_ptr_base(T* ptr) : p(ptr, D) { }
		template <typename D> shared_ptr_base(T* ptr, D d) : p(ptr, d) { }

		shared_ptr_base(T* ptr) : p(ptr) { }
		shared_ptr_base() : p() { }
		shared_ptr_base(const shared_ptr_base<T>& that) : p(that.p) { }
		
		T* raw_ptr() { return p.get(); }
		
		virtual ~shared_ptr_base() { }

	protected:
		shared_ptr<T> p;
	};
}

#endif /* SDLPP_SHARED_PTR_BASE_INCLUDED */
