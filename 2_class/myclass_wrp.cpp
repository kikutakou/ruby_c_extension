#include "myclass.h"                                                                                                                                                                                                    


//convert ruby VALUE to MyClass
static MyClass* getMyClass(VALUE self)
{
  MyClass* my;
  Data_Get_Struct(self, MyClass, my);
  return my;
}


/* --------- new, init, free --------- */

//free
static void wrap_MyClass_free(MyClass* my)
{
  my->~MyClass();
  ruby_xfree(my);
}


//alloc(new)
static VALUE wrap_MyClass_alloc(VALUE klass)
{
  MyClass* my = new MyClass();
  return Data_Wrap_Struct(klass, NULL, wrap_MyClass_free, my);
}


//initialize
static VALUE wrap_MyClass_init(VALUE self)
{
  getMyClass(self)->name = string("myname");
  getMyClass(self)->num = 10;
  return Qnil;
}



/* --------- instance methods --------- */

static VALUE wrap_MyClass_inspect(VALUE self)
{
  MyClass* my = getMyClass(self);
  stringstream ss;
  ss << "<MyClass Name = \"" << my->name << "\" num = " << my->num << ">";
  return rb_str_new2(ss.str().c_str());
}


static VALUE wrap_MyClass_set(VALUE self, VALUE arg1, VALUE arg2)
{
  MyClass* my = getMyClass(self);
  my->num = NUM2INT(arg1);
  my->name = string(RSTRING_PTR(arg2));   //BAD CODE - object arg2 will disappear on Ruby side.  should copy
  
  return self;
}


static VALUE wrap_MyClass_hello(VALUE self)
{
  getMyClass(self)->sayMyClass();
  return Qnil;
}








/* --------- at library init --------- */


extern "C" void Init_myclass()
{
  VALUE c = rb_define_class("MyClass", rb_cObject);

  //register alloc func
  rb_define_alloc_func(c, wrap_MyClass_alloc);
  
  //register initialize
  rb_define_private_method(c, "initialize", RUBY_METHOD_FUNC(wrap_MyClass_init), 0);
  
  //register methods
  rb_define_method(c, "inspect", RUBY_METHOD_FUNC(wrap_MyClass_inspect), 0);
  rb_define_method(c, "hello", RUBY_METHOD_FUNC(wrap_MyClass_hello), 0);
  rb_define_method(c, "[]=", RUBY_METHOD_FUNC(wrap_MyClass_set), 2);
}







