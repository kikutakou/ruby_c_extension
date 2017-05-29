#ifndef __MYCLASS_H_
#define __MYCLASS_H_

#include <ruby.h>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

class MyClass
{
  public:
  
  //member
  string name;
  int num;
  
  
  //constructor, destoructor
  MyClass();
  ~MyClass();
  
  //hello
  void sayMyClass();
};

#endif
