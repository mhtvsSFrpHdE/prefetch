#ifndef Const_Translator_Loader_h
#define Const_Translator_Loader_h

#include <QString>
#include <string>

namespace Const_TranslatorLoader
{
    namespace Message
    {
        const QString TranslateLoaded = "Translate loaded: ";
    }

    namespace Exception
    {
        const std::string &FailedToLoadAnyTranslateFile = "FailedToLoadAnyTranslateFile";
    }
}

#endif
