## Return by reference

Look at debugger, create class object in function, get it's address,  
return to caller, get address again, they are the same.

This is called "return value optimization" to avoid copy.  
So exist code will not refactor to return pointer.

https://stackoverflow.com/a/10479595
