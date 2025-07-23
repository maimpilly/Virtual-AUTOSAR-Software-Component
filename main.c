// File: main.c
#include <stdio.h>
#include "SeatbeltReminder_SWC.h"
#include "Rte_SeatbeltReminder_SWC.h" // Include to get mode definitions

// Declare the global mode variable defined in rte_stubs.c
extern uint8 G_currentEcuMode;

int main() {
    printf("--- SWC Test Runner Initialized ---\n\n");

    // === SCENARIO 1: ECU is in RUN Mode ===
    printf("--- SETTING ECU MODE TO: RUN ---\n");
    G_currentEcuMode = RTE_MODE_MDG_EcuMode_ECU_RUN;
    printf("--- Simulating OS Tick 1 (Calling Runnable) ---\n");
    RE_MainFunction_100ms();

    // === SCENARIO 2: ECU is in SLEEP Mode ===
    printf("\n--- SETTING ECU MODE TO: SLEEP ---\n");
    G_currentEcuMode = RTE_MODE_MDG_EcuMode_ECU_SLEEP;
    printf("--- Simulating OS Tick 2 (Calling Runnable) ---\n");
    RE_MainFunction_100ms();

    printf("\n--- SWC Test Runner Finished ---\n");
    return 0;
}