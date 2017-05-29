
require File.dirname(__FILE__) + "/mylibrary"

include MyModule

# Call and print the result from the test1 method

puts hello

puts is_object(30)

print_type("text")
print_type(-10)
print_type(1.1)
print_type(:this_is_symbol)

txt = "text"
p txt
force_uppercase(txt)
p txt

puts return_japanese
p return_japanese
p "テスト"
