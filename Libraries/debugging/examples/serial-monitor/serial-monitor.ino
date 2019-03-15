// Example usage for debugging library by SkippyTheIdiot.

#include "debugging.h"

// Initialize objects from the lib
Debugging debugging;

void setup() {
    // Call functions on initialized library objects that require hardware
    debugging.begin();
}

void loop() {
    // Use the library's initialized objects and functions
    debugging.process();
}
