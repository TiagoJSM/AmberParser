// header.hpp

#define Custom(x) __attribute__((annotate(x)))
#define AClass __attribute__((annotate("AClass")))
#define AProperty __attribute__((annotate("AProperty")))
#define AMethod __attribute__((annotate("AMethod")))

namespace NS
{
	class AClass MyClass
	{
	public:
		int AProperty field;
		virtual AMethod void method() const = 0;

		static const int static_field;
		static int static_method();
	private:
		int _privField;
	};
}

namespace NS2
{
	class AClass MyClass
	{
	public:
		AProperty int field;
		virtual AMethod void method() const = 0;

		static const int static_field;
		static int static_method();
	private:
		int _privField;
	};
}