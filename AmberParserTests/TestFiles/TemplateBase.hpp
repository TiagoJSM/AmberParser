#define AReflect()
#define AMethod()
#define AComponent()
#define ACtor()
#define AProperty(a)

namespace NS
{
	class TemplateArg{};

	template<typename TType>
	AReflect()
	class MyBaseTemplateClass
	{
	public:
		AProperty()
		int field1;
	};

	AReflect()
	class MyOtherTemplatedClass : public MyBaseTemplateClass<TemplateArg>
	{
	public:
		AProperty()
		int field2;
	};
}