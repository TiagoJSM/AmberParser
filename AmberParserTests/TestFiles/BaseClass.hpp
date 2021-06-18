#define AReflect()
#define AMethod()
#define AComponent()
#define ACtor()
#define AProperty(a)

namespace NS
{
	AReflect()
	class MyBaseClass
	{
	public:
		AProperty()
		int field1;
	};

	AReflect()
	class MyOtherClass : public MyBaseClass
	{
	public:
		AProperty()
		int field2;
	};

	AReflect()
	struct MyBaseStruct
	{
	public:
		AProperty()
		int field1;
	};

	AReflect()
	struct MyOtherStruct : public MyBaseStruct
	{
	public:
		AProperty()
		int field2;
	};
}
