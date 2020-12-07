#ifndef VirtualDelay_H
#define VirtualDelay_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif

class VirtualDelay {
private:
    bool pulse=0;
    bool running = 0;
    bool manualElapse = 0;
    unsigned long timeOut, (*timerFunctionPtr)();

public:
    VirtualDelay(unsigned long (*timerFunctionPtr)() = millis);
    void start(signed long delay);
    bool elapsed();
    void stop(bool isElapsed);
    void elapse();
};

#define DO_ONCE(x)     \
    {                  \
        static bool b; \
        if (!b) {      \
            b = 1;     \
            x;         \
        }              \
    }

#endif
