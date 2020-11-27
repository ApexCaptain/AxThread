#include <AxThread.hpp>

#include <Arduino.h>
#include <deque>

class AxThread {
    public :
        unsigned int repeatCount;
        bool isForever;
        Axt::ThreadID threadId;
        Axt::AxCallback task;
        unsigned long awaitingMillis;

        int currentRepeatCount;
        bool isEnabled = true;
        long prevMills = millis();

        AxThread(unsigned int repeatCount, bool isForever, Axt::ThreadID threadId, Axt::AxCallback task, unsigned long awaitingMillis) {
            this -> repeatCount = repeatCount;
            this -> currentRepeatCount = repeatCount;
            this -> isForever = isForever;
            this -> threadId = threadId;
            this -> task = task;
            this -> awaitingMillis = awaitingMillis;
        }
};

class AxController {
    public :
        Axt::ThreadID threadIdGenreationCode = 1;
        Axt::ThreadID generateThreadId() { return threadIdGenreationCode++; }
        std::deque<AxThread*> threads;
        int getIndexByThreadId(const Axt::ThreadID threadId) {
            for(int index = 0 ; index < threads.size() ; index++) 
                if(threads[index] -> threadId == threadId) return index;
            return -1;
        }
        Axt::ThreadID addNewThread(unsigned int repeatCount, bool isForever, Axt::AxCallback task, unsigned long awaitingMillis) {
            Axt::ThreadID threadId = generateThreadId();
            AxThread* threadToAdd = new AxThread(
                repeatCount,
                isForever,
                threadId,
                task,
                awaitingMillis
            );
            threads.push_back(threadToAdd);
            return threadId;
        }

};

AxController *axController = new AxController();

void Axt::executeThreads() {
    long currentMillis = millis();
    std::deque<Axt::ThreadID> threadIdsToDelete;
    for(auto eachThread : axController -> threads) {
        if(currentMillis - eachThread -> prevMills < eachThread -> awaitingMillis
            || !eachThread -> isEnabled) continue;
        eachThread -> prevMills = currentMillis;
        Axt::AxSignal signal = eachThread -> task();
        switch(signal) {
            case CONTINUE :
                if(!eachThread -> isForever) eachThread -> currentRepeatCount--;
                if(eachThread -> currentRepeatCount == 0) threadIdsToDelete.push_back(eachThread -> threadId);
                break;
            case BREAK :
                threadIdsToDelete.push_back(eachThread -> threadId);
                break;
        }
    }
    for(Axt::ThreadID eachThreadIdToDelete : threadIdsToDelete) Axt::clear(eachThreadIdToDelete);
}

Axt::ThreadID Axt::setInterval(unsigned long millis, Axt::AxCallback task) { return axController -> addNewThread(-1, true, task, millis); }
Axt::ThreadID Axt::setTimeout(unsigned long millis, Axt::AxCallback task) { return axController -> addNewThread(1, false, task, millis); }
Axt::ThreadID Axt::setImmediate(Axt::AxCallback task) { return axController -> addNewThread(1, false, task, 0L); }
Axt::ThreadID Axt::setRepetition(unsigned long millis, unsigned int repeatCount, Axt::AxCallback task) { return axController -> addNewThread(repeatCount, false, task, millis); }


void Axt::clear(Axt::ThreadID) {
    
}