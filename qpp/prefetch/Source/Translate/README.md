# Translate

https://doc.qt.io/archives/qt-4.8/internationalization.html

## Qt lupdate bug

To scan project source code (`lupdate`), go to `prefetch.pro`,  
comment out the "Third party library" lines, or it will hang.  
https://bugreports.qt.io/browse/QTBUG-27936

## Translate process

Assume creating translate for `const_core.h`

### Declare extern header

- In `const_core.h`, declare variable as `extern QString`
- Declare two `extern void` function, "init()" and "tdummy()"

```
...
    namespace Message
    {
        extern QString ScanFolder;

        extern void init();

        // See translate_define.h for more information
        extern void tdummy();
    }
...
```

### Create tdummy cpp

- Name this file as `const_core_tdummy.cpp`
- Include `const_core.h` and `translate_tool.h`
- Define tscope variable and point to namespace path
- Implement tdummy, a `DEFINE_*` and an assign statement using `tr` macro,  
  put raw string to be translated as `tr` parameter, usually is English.  
  Assign and define close to each other, and will modify at same time in future.

```
#include "const_core.h"
#include "..\Translate\translate_tool.h"

#define tscope "Const_Core::Message"

void Const_Core::Message::tdummy()
{
#define DEFINE_ScanFolder "Scan folder..."
    ScanFolder = tr("Scan folder...");
...
}
```

### Header implementation

- Name this file as `const_core.cpp`
- Include `const_core_tdummy.cpp` in this file instead of `const_core.h`
- Define variable declare in header, assign using `DEFINE_*` in `const_core_tdummy.cpp`
- Implement `init()`, call trr at runtime using tscope and `DEFINE_*`

```
#include "const_core_tdummy.cpp"

QString Const_Core::Message::ScanFolder = DEFINE_ScanFolder;

void Const_Core::Message::init()
{
    ScanFolder = trr(tscope, DEFINE_ScanFolder);
    ...
}
...
```

### Call at runtime

- Go to `Source\Translate\init_message.cpp`, include "const_core.h"
- Call `init()` function in `initMessage()`

```
...
void TranslatorLoader::initMessage()
{
    ...
    Const_Core::Message::init();
    ...
}
...
```
