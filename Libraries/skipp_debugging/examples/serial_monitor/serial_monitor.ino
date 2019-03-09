// Example usage for debugging_base library by SkippyTheIdiot.

#include "debugging_base.h"

// Initialize objects from the lib
Debugging_base debugging_base;

void setup() {
    // Call functions on initialized library objects that require hardware
    debugging_base.begin();
}

void loop() {
    // Use the library's initialized objects and functions
    debugging_base.process();
}
