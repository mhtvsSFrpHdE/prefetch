## Uninitialized default value

When a Qt component come to uninitialized static,  
it often bundled with a default constructor,  
so you don't get random stuff in uninitialized variable.

For example, uninitialized `QString` value is `""`,  
and call `.append()` to uninitialized `QStringList` is valid code.

In C++, a uninitialized **class** variable often use default constructor.  
But when it comes to pointer, you get dangerous random garbage when uninitialized.

### Clang tidy can help

In Qt Creator, goto Edit\Preferences\Analyzer\Clang Tools\Run Options\Diagnostic configuration\The Button,  
copy default settings, then enable Clang-Tidy Checks\cppcoreguidelines\pro\type\member-init  
Latern if you have uninitialized class variable,  
run clang tidy in Qt Creator will get related warning.

https://stackoverflow.com/a/3127473
