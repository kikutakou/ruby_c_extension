1. prepare directory DIR
2. put your c code which includes function Init_{YOUR_LIBRARY_NAME}
3. run ruby_make.sh {DIR}, this automatically search Init_{YOUR_LIBRARY_NAME} and get library name, then create Bundle.
4. (this script also execute test.rb if exists.)
5. write your ruby script with "require '{YOUR_LIBRARY_NAME}' ".  don't forget it must be given as "./{LIBRARY_NAME}"

