//
// Created by looperX on 2019-01-07.
//
#pragma once
#include <stdint.h>


namespace CurrentThread
{
    // internal
    extern __thread int tCacheTid;
    extern __thread char tidString[32];
    extern __thread int tidStringLen;
    extern __thread const char* threadName;
    void cacheTid();
    inline int tid()
    {
        if (__builtin_expect(tCacheTid == 0, 0))
        {
            cacheTid();
        }
        return tCacheTid;
    }

    inline const char* _tidString() // for logging
    {
        return tidString;
    }

    inline int tidStringLength() // for logging
    {
        return tidStringLen;
    }

    inline const char* name()
    {
        return threadName;
    }
}
