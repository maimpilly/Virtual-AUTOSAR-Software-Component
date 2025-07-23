// File: main.c
#include <stdio.h>
#include "SeatbeltReminder_SWC.h" // Your component's header

int main() {
    printf("--- SWC Test Runner Initialized ---\n");

    // Simulate calling the runnable 3 times
    for (int i = 0; i < 3; i++) {
        printf("--- Simulating OS Tick %d (Calling Runnable) ---\n", i + 1);
        RE_MainFunction_100ms(); // This calls your SWC's main logic
    }

    printf("--- SWC Test Runner Finished ---\n");
    return 0;
}