// header.hpp

#define INTERESTING __attribute__((annotate("interesting")))

class INTERESTING MyClass
{
public:
  int field;
  virtual void method() const = 0;

  static const int static_field;
  static int static_method();
};