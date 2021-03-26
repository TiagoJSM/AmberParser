#define Custom(x) __attribute__((annotate(x)))
#define AReflect __attribute__((annotate("AReflect")))
#define AProperty __attribute__((annotate("AProperty")))
#define AMethod __attribute__((annotate("AMethod")))
#define AComponent __attribute__((annotate("AComponent")))

namespace NS
{
	class AReflect MyBaseClass
	{
	public:
		int AProperty field1;
	};

	class AReflect MyOtherClass : public MyBaseClass
	{
	public:
		int AProperty field2;
	};

	struct AReflect MyBaseStruct
	{
	public:
		int AProperty field1;
	};

	struct AReflect MyOtherStruct : public MyBaseStruct
	{
	public:
		int AProperty field2;
	};
}
