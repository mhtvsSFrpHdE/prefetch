# Translate

https://doc.qt.io/archives/qt-4.8/internationalization.html

## Qt lupdate bug

To scan project source code (`lupdate`), go to `prefetch.pro`,  
comment out the "Third party library" lines, or it will hang.  
https://bugreports.qt.io/browse/QTBUG-27936
