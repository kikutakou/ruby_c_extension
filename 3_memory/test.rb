require File.dirname(__FILE__) + "/myclass"

#GC.disable

my = MyArray.new
10000.times{ |i|
  my << "#{i}"
}
p my
p my[0]
