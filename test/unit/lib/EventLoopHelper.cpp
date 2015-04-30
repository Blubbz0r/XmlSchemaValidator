#include "EventLoopHelper.h"

#include "gmock/gmock.h"

void EventLoopHelper::run(int& result)
{
    result = RUN_ALL_TESTS();
    emit finished();
}
