#include "VirtualDelay.h"

bool pulse;

VirtualDelay::VirtualDelay(
    unsigned long (*timerFunctionPtr)())
    : timerFunctionPtr(timerFunctionPtr)
{
}

void VirtualDelay::start(signed long delay) // 0...2^31
{
    if (!this->running) {
        this->running = 1;
        this->timeOut = (*timerFunctionPtr)() + abs(delay);
    }
}

void VirtualDelay::stop(bool isElapsed)
{
  this->running = 0;
  if (isElapsed) this->manualElapse = 1;
}

bool VirtualDelay::elapsed()
{
    this->pulse = 0;
    if (this->running) {
        // bug
        // if((signed long)(*timerFunctionPtr)() >= timeOut)
        // not the same as
        if ((signed long)((*timerFunctionPtr)() - this->timeOut) >= 0) {
            // fix rollover bug:
            // https://arduino.stackexchange.com/questions/12587/how-can-i-handle-the-millis-rollover/12588#12588
            this->running = 0;
            this->pulse = 1;
        }
    } else if (this->manualElapse) {
        this->manualElapse = 0;
        return true;
    }
    return this->pulse; // still in delay timer
}
