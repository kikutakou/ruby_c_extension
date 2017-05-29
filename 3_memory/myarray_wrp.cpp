#include "myarray.h"                                                                                                                                                                                                    


//convert ruby VALUE to MyArray
static MyArray* getMyArray(VALUE self)
{
  MyArray* my;
  Data_Get_Struct(self, MyArray, my);
  return my;
}


/* --------- new, init, free --------- */

//free
static void wrap_MyArray_free(MyArray* my)
{
  my->~MyArray();
  ruby_xfree(my);
}

//free
static void wrap_MyArray_mark(MyArray* vec)
{
  for(int i = 0 ; i < vec->size() ; i++){
    rb_gc_mark((*vec)[i]);
  }

}


//alloc(new)
static VALUE wrap_MyArray_alloc(VALUE klass)
{
  MyArray* ary = new MyArray();
  return Data_Wrap_Struct(klass, wrap_MyArray_mark, wrap_MyArray_free, ary);
}


//initialize
static VALUE wrap_MyArray_init(VALUE self)
{
  return Qnil;
}



/* --------- instance methods --------- */

static VALUE wrap_MyArray_inspect(VALUE self)
{
  MyArray* vec = getMyArray(self);
  stringstream ss;
  ss << "[";
  for(int i = 0 ; i < vec->size() ; i++){
    if(i) ss << ", ";
    ss << RSTRING_PTR(rb_inspect((*vec)[i]));
  }
  ss << "]";
  return rb_str_new2(ss.str().c_str());
}


static VALUE wrap_MyArray_pushback(VALUE self, VALUE arg1)
{
  MyArray* vec = getMyArray(self);
  rb_gc_mark(arg1);
  vec->push_back(arg1);
  return self;
}

static VALUE wrap_MyArray_at(VALUE self, VALUE arg1)
{
  MyArray* vec = getMyArray(self);
  int i = NUM2INT(arg1);
  
  return (*vec)[i];
}







/* --------- at library init --------- */


extern "C" void Init_myclass()
{
  VALUE c = rb_define_class("MyArray", rb_cObject);

  //register alloc func
  rb_define_alloc_func(c, wrap_MyArray_alloc);
  
  //register initialize
  rb_define_private_method(c, "initialize", RUBY_METHOD_FUNC(wrap_MyArray_init), 0);
  
  //register methods
  rb_define_method(c, "inspect", RUBY_METHOD_FUNC(wrap_MyArray_inspect), 0);
  rb_define_method(c, "<<", RUBY_METHOD_FUNC(wrap_MyArray_pushback), 1);
  rb_define_method(c, "[]", RUBY_METHOD_FUNC(wrap_MyArray_at), 1);
}







