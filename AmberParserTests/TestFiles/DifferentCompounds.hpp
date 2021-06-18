// header.hpp

#define AReflect()
#define AMethod()
#define AComponent()
#define ACtor()
#define AProperty(a)

namespace NS
{
	AReflect()
	class MyClass
	{
	public:
		AProperty()
		int field;
		AMethod()
		virtual void method() const = 0;

		static const int static_field;
		static int static_method();
	private:
		int _privField;
	};

	AReflect()
	struct MyStruct
	{
	public:
		AProperty()
		int field;
		AMethod()
		virtual void method() const = 0;

		static const int static_field;
		static int static_method();
	private:
		int _privField;
	};

	AComponent()
	struct MyComponent
	{
	public:
		int field;
		float otherField;
	};
}

namespace NS2
{
	AReflect()
	class MyClass
	{
	public:
		AProperty()
		int the_field;
		AMethod()
		virtual void method() const = 0;

		static const int static_field;
		static int static_method();
	private:
		int _privField;
	};
}