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

		ACtor()
		static MyClass New(std::string&& assetPath) { return MyClass(); }
	};
}
