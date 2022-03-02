#include "read_file.h"
#include "..\Setting\setting.h"
#include "..\Output\stdout.h"
#include "Thread\read_thread.h"

int ReadFile::count_start_scanFolder;
QList<QRunnable *> ReadFile::readThreadQueue;
QThreadPool *ReadFile::readThreadPool;

void ReadFile::init()
{
    count_start_scanFolder = 0;
    readThreadQueue = QList<QRunnable *>();
    readThreadPool = QThreadPool::globalInstance();
}

void ReadFile::start()
{
    // Get prefetch folder
    QStringList prefetchFolders = Setting::getArray("PrefetchFolder", Setting::setting);

    // Get exclude folder
    QStringList excludeFolders = Setting::getArray("ExcludeFolder", Setting::setting);

    for (int i = 0; i < prefetchFolders.size(); ++i)
    {
        auto prefetchFolderName = prefetchFolders[i];

        ReadFile::start_scanFolder(prefetchFolderName);
    }

    auto readThreadQueueRef = readThreadQueue;

    bool doNothing = true;
}

void ReadFile::start_readFile_ququeThread(QString filePath)
{
    auto readThread = new ReadThread(filePath);
    ReadFile::readThreadQueue.append(readThread);
}

void ReadFile::start_readFile(QDir *prefetchFolder)
{
    prefetchFolder->setFilter(QDir::Files);
    auto subFileList = prefetchFolder->entryInfoList();

    for (int i = 0; i < subFileList.size(); ++i)
    {
        auto filePath = subFileList[i].absoluteFilePath();

        start_readFile_ququeThread(filePath);
    }
}

void ReadFile::start_scanFolder(QString prefetchFolderName)
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

void ReadFile::start_runThread()
{
    // TODO: Consume thread(simply print file name for now)
    // TODO: Clear thread allocated memory after thread done
    // TODO: Clear thread queue
}
