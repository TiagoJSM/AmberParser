#define Custom(x) __attribute__((annotate(x)))
#define AReflect __attribute__((annotate("AReflect")))
#define AProperty __attribute__((annotate("AProperty")))
#define AMethod __attribute__((annotate("AMethod")))
#define AComponent __attribute__((annotate("AComponent")))

namespace NS
{
	class TemplateArg{};

	template<typename TType>
	class AReflect MyBaseTemplateClass
	{
	public:
		int AProperty field1;
	};

	class AReflect MyOtherTemplatedClass : public MyBaseTemplateClass<TemplateArg>
	{
	public:
		int AProperty field2;
	};
}