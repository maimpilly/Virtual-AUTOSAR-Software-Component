// File: main.c
#include <stdio.h>
#include "SeatbeltReminder_SWC.h"
#include "Rte_SeatbeltReminder_SWC.h" // Include to get mode definitions

// Declare the global mode variable defined in rte_stubs.c
extern uint8 G_currentEcuMode;
extern boolean G_simulateVehicleSpeedFault;

int main() {
    printf("--- SWC Test Runner Initialized ---\n\n");

    // === SCENARIO 1: Normal Operation ===
    printf("--- SCENARIO: Normal Operation (No Faults) ---\n");
    G_currentEcuMode = RTE_MODE_MDG_EcuMode_ECU_RUN;
    G_simulateVehicleSpeedFault = FALSE; // Ensure no fault is active
    RE_MainFunction_100ms(); // Call the runnable

    printf("\n"); // Add a space between scenarios

    // === SCENARIO 2: Vehicle Speed Sensor Fault ===
    printf("--- SCENARIO: Vehicle Speed Sensor Fault ---\n");
    G_currentEcuMode = RTE_MODE_MDG_EcuMode_ECU_RUN; // Still in RUN mode
    G_simulateVehicleSpeedFault = TRUE; // Activate the fault
    RE_MainFunction_100ms(); // Call the runnable again

    printf("\n--- SWC Test Runner Finished ---\n");
    return 0;
}