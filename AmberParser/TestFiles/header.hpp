// header.hpp

#define Custom(x) __attribute__((annotate(x)))
#define AReflect __attribute__((annotate("AReflect")))
#define AProperty __attribute__((annotate("AProperty")))
#define AMethod __attribute__((annotate("AMethod")))
#define AComponent __attribute__((annotate("AComponent")))

namespace NS
{
	class AReflect MyClass
	{
	public:
		int AProperty field;
		virtual AMethod void method() const = 0;

		static const int static_field;
		static int static_method();
	private:
		int _privField;
	};

	struct AReflect MyStruct
	{
	public:
		int AProperty field;
		virtual AMethod void method() const = 0;

		static const int static_field;
		static int static_method();
	private:
		int _privField;
	};

	struct AComponent MyComponent
	{
	public:
		int field;
		float otherField;
	};
}

namespace NS2
{
	class AReflect MyClass
	{
	public:
		AProperty int the_field;
		virtual AMethod void method() const = 0;

		static const int static_field;
		static int static_method();
	private:
		int _privField;
	};
}