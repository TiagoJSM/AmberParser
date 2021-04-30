#define Custom(x) __attribute__((annotate(x)))
#define AReflect __attribute__((annotate("AReflect")))
#define AProperty __attribute__((annotate("AProperty")))
#define AMethod __attribute__((annotate("AMethod")))
#define AComponent __attribute__((annotate("AComponent")))
#define ACtor __attribute__((annotate("ACtor")))

namespace NS
{
	class AReflect MyClass
	{
	public:
		int AProperty field;
		static ACtor MyClass New(std::string&& assetPath) { return MyClass(); }
	};
}
