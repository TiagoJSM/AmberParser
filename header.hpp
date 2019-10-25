// header.hpp

#define INTERESTING __attribute__((annotate("interesting")))

namespace NS
{
	class INTERESTING MyClass
	{
	public:
		int INTERESTING field;
		virtual INTERESTING void method() const = 0;

		static const int static_field;
		static int static_method();
	private:
		int _privField;
	};
}

namespace NS2
{
	class INTERESTING MyClass
	{
	public:
		INTERESTING int field;
		virtual INTERESTING void method() const = 0;

		static const int static_field;
		static int static_method();
	private:
		int _privField;
	};
}