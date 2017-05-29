#include <ruby.h>
#include <stdio.h>
#include <ruby/encoding.h>

//define method

//VALUE: ruby object
VALUE hello(VALUE self) {
    printf("(printf works)\n");
    return rb_str_new2("Hello World");
}

VALUE is_object(VALUE self, VALUE arg1) {
    if(RTEST(arg1)) return Qtrue;
    else return Qfalse;
}

VALUE print_type(VALUE self, VALUE arg1) {
    
    switch (TYPE(arg1)) {
        case T_STRING:
            printf("type is T_STRING\n");
            printf("  RSTRING_LEN : %ld\n", RSTRING_LEN(arg1));
            printf("  RSTRING_PTR : %s\n", RSTRING_PTR(arg1));
        break;
        case T_FIXNUM:
            printf("type is T_FIXNUM\n");
            printf("  NUM2INT : %d\n", NUM2INT(arg1));
            printf("  NUM2UINT : %u\n", NUM2UINT(arg1));
        break;
        case T_FLOAT:
            printf("type is T_FLOAT\n");
            printf("  NUM2DBL : %f\n", NUM2DBL(arg1));
        break;
        case T_SYMBOL:
            printf("type is T_SYMBOL\n");
            printf("  SYM2ID : %lu\n", SYM2ID(arg1));
            VALUE id = rb_id2str(SYM2ID(arg1));
            printf("  SYM2ID : %s\n", RSTRING_PTR(id));
        break;
        case T_ARRAY:
            printf("type is T_ARRAY\n");
        break;
        case T_DATA:
            printf("type is T_DATA\n");
        break;
        default:
            printf("type is other\n");
        break;
    }
    
    return Qnil;
}

VALUE force_uppercase(VALUE self, VALUE arg1) {
  if(TYPE(arg1) == T_STRING){
    for(char* ptr = RSTRING_PTR(arg1); ptr < RSTRING_PTR(arg1) + RSTRING_LEN(arg1); ptr++){
      if(*ptr >= 'a' && *ptr <= 'z') *ptr -= ( 'a' - 'A');
    }
  }
  return arg1;
}

VALUE return_japanese(VALUE self) {
  
  char str[] = "テスト";
  int len = strlen(str);
  return rb_enc_str_new(str, len, rb_utf8_encoding());    //need "ruby/encoding.h"
  //return rb_utf8_str_new(str, len);   // from ruby 2.2
  //return rb_str_new2(str);    //returns str as ascii 
  
}

//push the method to ruby

void Init_mylibrary() {
	VALUE module = rb_define_module("MyModule");
  //bind the func name
  rb_define_method(module, "hello", hello, 0);
  rb_define_method(module, "is_object", is_object, 1);
  rb_define_method(module, "print_type", print_type, 1);
  rb_define_method(module, "force_uppercase", force_uppercase, 1);
  rb_define_method(module, "return_japanese", return_japanese, 0);
}

