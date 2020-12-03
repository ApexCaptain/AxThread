#pragma once 
#ifndef AX_THREAD_HPP
#define AX_THREAD_HPP

#include <functional>
namespace Axt {
    void executeThreads();

    enum AxSignal {
        CONTINUE = 0,
        BREAK
    };

    typedef std::function<AxSignal(void)> AxCallback;
    typedef unsigned long ThreadID;

    ThreadID setInterval(unsigned long millis, AxCallback task);
    ThreadID setTimeout(unsigned long millis, AxCallback task);
    ThreadID setImmediate(AxCallback task);
    ThreadID setRepetition(unsigned long millis, unsigned int repeatCount, AxCallback task);

    void clear(const ThreadID threadId);
    void restart(const ThreadID threadId);
    bool isEnabled(const ThreadID threadId);
    void enable(const ThreadID threadId);
    void disable(const ThreadID threadId);
    void toggle(const ThreadID threadId);
    bool doesExist(const ThreadID threadId);
    unsigned int getThreadCount();

}

#endif