#include <QStringList>
#include <QDir>

#include "read_file.h"
#include "..\Setting\setting.h"
#include "..\Output\stdout.h"

// Read all file in QFileInfoList
void start_readFile(QDir *prefetchFolder)
{
    prefetchFolder->setFilter(QDir::Files);
    auto subFileList = prefetchFolder->entryInfoList();

    for (int i = 0; i < subFileList.size(); ++i)
    {
        *StdOut::consoleOutput << subFileList[i].absoluteFilePath()
                               << endl;
    }
}

// iterated function
void start_scanFolder(QString prefetchFolderName)
{
    // ReadFile::count_start_scanFolder++;
    // *StdOut::consoleOutput << "Enter start_scanFolder times: "
    //                        << ReadFile::count_start_scanFolder
    //                        << endl;

    auto prefetchFolder = QDir(prefetchFolderName);

    // Get sub folder information

    // Cool stuff
    // Pass multiple at once
    // https://www.qtcentre.org/threads/22178-QDir-NoDotAndDotDot-hidding-all-files
    prefetchFolder.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    auto subFolderList = prefetchFolder.entryInfoList();
    auto subFolderListSize = subFolderList.size();

    if (subFolderListSize > 0)
    {
        for (int i = 0; i < subFolderListSize; ++i)
        {
            // Cool stuff
            // Even this is a folder
            // https://doc.qt.io/qt-5/qfileinfo.html#absoluteFilePath
            auto subFolderName = subFolderList[i].absoluteFilePath();

            // Save folder tree on stack but not read file immediately
            start_scanFolder(subFolderName);
        }
    }

    // Folder tree scan complete, create read file threads
    start_readFile(&prefetchFolder);
};

void ReadFile::start()
{
    // Get prefetch folder
    QStringList prefetchFolders = Setting::getArray("PrefetchFolder", Setting::setting);

    // Get exclude folder
    QStringList excludeFolders = Setting::getArray("ExcludeFolder", Setting::setting);

    for (int i = 0; i < prefetchFolders.size(); ++i)
    {
        auto prefetchFolderName = prefetchFolders[i];

        start_scanFolder(prefetchFolderName);
    }

    bool doNothing = true;
}

int ReadFile::count_start_scanFolder = 0;
