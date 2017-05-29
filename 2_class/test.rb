require File.dirname(__FILE__) + "/myclass"

my = MyClass.new
p my
my.hello
my[40] = "John"
my.hello
my[40] = "あはは"
my.hello

sleep 1
my.hello
