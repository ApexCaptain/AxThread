# <img src="asset/axt.png" alt="AxThread Logo" width="70" height="70"> Dynamic AxThread : A Platform IO Library for handling asynchronous multiple processes. 

# Table of Contents
- [Installation](#Installation)
- [Introduction](#Introduction)
- [Methods](#Methods)
- [License](#License)

# Installation
Type lib name and version into your platformio.ini file.
```
lib_deps =
    apexcaptain/AxThread @ 1.0.1
```
Current version is `1.0.1`.

# Introduction
There are lots of conventional ways to implement asynchronous processes in Arduino environment. But if I have to create a Thread instance for each and every single time I want to use it and also controll, stop or delete'em manually, that is not simple to me. Furthermore, total number of threads are limited and also need to set strong connection between parent and child instances. These are probably due to some sort of memory management.

Instead, with [AxThread](https://github.com/ApexCaptain/AxThread), you `don't` need to...

- Create thread instance.
- Connect parent and child instance, of course.
- Count number of threads manually.

There are one header file and one cpp file. There's no public class. You don't have to take care of inner Thread or ThreadController classes. Instead, you can use namespace. Let's take a look at following example.


```cpp
#include <Arduino.h>
#include <AxThread.hpp>

void setup() {
    Serial.begin(115200);

    /* Setting interavl thread. */
    Axt::setInterval(1000 /* Repeat Cycle. 1000ms | 1sec */, []() -> Axt::AxSignal {
        Serial.println("Hello AxT!");
        return Axt::CONTINUE;
    });

}

void loop() {
    Axt::executeThreads();
}

```
This is an example printing out `Hello AxT!` text every second through [AxThread](https://github.com/ApexCaptain/AxThread). As you can see, there's no `Class` at all but only `namespace` : `Axt`. 

`Axt::setInterval` function automatically creates, adds new task into its inner thread deque and returns new thread id. First argument is interval milli seconds for each repetition cycle. Second one is callback. A task, a thread, process or behavior whatever you call it, this is the actual action body that is gonna run. You can have a check more detail at the following Methods section.

# Methods

## Periodic process repeated a certain number of times : `setRepetition`
### Syntax
```cpp
Axt::ThreadId id = Axt::setRepetition(delay, count, lambda);
```

### Parameters
- `Delay`, the time in milliseconds(thousandths of asecond), inner thread controller delays in between executions of the specified lambda for certain count.
- `Count` is the number of repetition of the thread.
- `Lambda` is literally the lambda function block to be executed at every delay for count times.


## Signle instant Process : `setImmediate`
### Syntax
```cpp
Axt::ThreadId id = Axt::setImmediate(lambda);
```

### Parameters
- `Lambda` is literally the lambda function block to be executed at the very next moment. 

### Example
Printing out text and expires.
```cpp
#include <Arduino.h>
#include <AxThread.hpp>

void setup() {
    Serial.begin(115200);
    Axt::setImmediate([]() -> Axt::AxSignal {
        Serial.println("Hello AxT!");
        return Axt::Continue;
    });
}

void loop() {
    Axt::executeThreads();
}
```

## Single Retarded Process. : `setTimeout` 
### Syntax
```cpp
Axt::ThreadId id = Axt::setTimeout(delay, lambda);
```

### Parameters
- `Delay`, the time in milliseconds(thousandths of a second), inner thread controller waits before the specified lambda is executed.
- `Lambda` is literally the lambda function block to be executed after delay and expires.

### Example
Printing out text after 2 seconds.
```cpp
#include <Arduino.h>
#include <AxThread.hpp>

void setup() {
    Serial.begin(115200);
    Axt::setTimeout(2000, []() -> Axt::AxSignal {
        Serial.println("Hello AxT!");
        return Axt::CONTINUE;
    });
}

void loop() {
    Axt::executeThreads();
}
```

## Periodic Repetition Cycle. : `setInterval` 

### Syntax
```cpp
Axt::ThreadId id = Axt::setInterval(delay, lambda);
```

### Parameters
- `Delay`, the time in milliseconds(thousandths of a second), inner thread controller delays in between executions of the specified lambda. 
- `Lambda` is literally the lambda function block to be executed every delay milliseconds.

### Example
Printing out text every second.
```cpp
#include <Arduino.h>
#include <AxThread.hpp>

void setup() {
    Serial.begin(115200);

    /* Setting interavl thread. */
    Axt::setInterval(1000 /* Repeat Cycle. 1000ms | 1sec */, []() -> Axt::AxSignal {
        Serial.println("Hello AxT!");
        return Axt::CONTINUE;
    });

}

void loop() {
    Axt::executeThreads();
}
```

Printing out text every second, when inner code executed more than 5 times, delete the thread.
```cpp
#include <Arduino.h>
#include <AxThread.hpp>

void setup() {
    Serial.begin(115200);
    int repeatCount = 0;
    Axt::setInterval(1000, [repeatCount]() mutable -> Axt::AxSignal {
        Serial.println("Hello AxT!");
        repeatCount++;
        if(repeatCount >= 5) return Axt::BREAK;
        return Axt::CONTINUE;
    });
}

void loop() {
    Axt::executeThreads();
}
```

### ETC
- `Axt::clear(Axt::ThreadId)` -- Stop the thread matching the given thread id and delete it.
- `Axt::restart(Axt::ThreadId)` -- Restart the thread matching the given thread id. If the thread is disabled, enable it.
- `Axt::isEnabled(Axt::ThreadId)` -- Check if the thread matching the given thread id is acitvated and returns it. (boolean)
- `Axt::enabled(Axt::ThreadId)` -- Activate thread matching the given thread id.
- `Axt::disabled(Axt::ThreadId)` -- Deactivate thread matching the given thread id.
- `Axt::toggle(Axt::ThreadId)` -- Toggle availability of thread matching the given thread id.
- `Axt::doesExists` -- Check whether certain thread matching the given thread id does exists and returns it. (boolean)
- `Axt::getThreadCount()` -- Get the number of currently registered threads.

# License
    MIT License

    Copyright (c) 2020 SangHun Lee

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
