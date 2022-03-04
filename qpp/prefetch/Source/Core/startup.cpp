#include <QProcess>

#include "startup.h"
#include "..\Setting\setting.h"

bool Startup::started = false;

void Startup::startOnce()
{
    // Disable after fist run
    if (started)
    {
        return;
    }
    started = true;

    // Get startup items
    auto afterPrefetch = Setting::getArray("AfterPrefetch", Setting::setting);
    for (int i = 0; i < afterPrefetch.size(); ++i)
    {
        auto fileName = afterPrefetch[i];

        QProcess process;

        // Cool stuff
        // Use startDetached to avoid print to console
        // QProcess: Destroyed while process is still running.
        process.startDetached(fileName);
    }
}
