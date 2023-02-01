#ifndef run_cpp_cpp
#define run_cpp_cpp

#include "parent_define.h"
#include "..\..\..\..\Core\StartProcess\start_process.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"

void Parent_Prefetch::run_quiet(QString command)
{
    Core_StartProcess::startProcess(command);
}

void Parent_Prefetch::run(QString command)
{
    using namespace Const_Input::Message;

    StdOut::printLine(TryingToRun1);
    StdOut::printLine(TryingToRun2 + command);

    run_quiet(command);
}

#endif
