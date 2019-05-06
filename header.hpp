// header.hpp

#define ACLASS __attribute__((annotate("ACLASS")))

class T {};

class ACLASS MyClass : public T
{
public:
  int field;
  virtual void method() const = 0;

  static const int static_field;
  static int static_method();
};