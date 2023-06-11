#ifndef Define_Runtime_h
#define Define_Runtime_h

class Define_Runtime
{
public:
    static bool getConsoleEnabled()
    {
#if CONSOLE_ENABLED
        return true;
#endif
        return false;
    }
};

#endif
