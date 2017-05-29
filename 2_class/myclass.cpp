#include "myclass.h"                                                                                                                                                                                                    



MyClass::MyClass()
{
  printf("constructor\n");

}


MyClass::~MyClass()
{
  printf("destructor\n");
}



void MyClass::sayMyClass()
{
  printf("hello %s. num = %d\n", name.c_str(), num);
}
