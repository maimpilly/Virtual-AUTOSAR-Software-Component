// File: main.c
#include <stdio.h>
#include "SeatbeltReminder_SWC.h"
#include "Rte_SeatbeltReminder_SWC.h"

// Declare the global simulation variables defined in rte_stubs.c
extern uint8 G_currentEcuMode;
extern boolean G_simulateVehicleSpeedFault;
extern uint16 G_speedThresholdCal;

int main() {
    printf("--- SWC Comprehensive Test Runner Initialized ---\n\n");

    // === SCENARIO 1: Normal Operation ===
    // ECU is running, no faults, standard calibration. Expect warning light ON.
    printf("--- SCENARIO 1: Normal Operation ---\n");
    G_currentEcuMode = RTE_MODE_MDG_EcuMode_ECU_RUN;
    G_simulateVehicleSpeedFault = FALSE;
    G_speedThresholdCal = 10;
    RE_MainFunction_100ms();
    printf("----------------------------------------\n\n");

    // === SCENARIO 2: Sleep Mode ===
    // ECU is sleeping. Expect no logic execution and light OFF.
    printf("--- SCENARIO 2: ECU in Sleep Mode ---\n");
    G_currentEcuMode = RTE_MODE_MDG_EcuMode_ECU_SLEEP;
    RE_MainFunction_100ms();
    printf("----------------------------------------\n\n");

    // === SCENARIO 3: Sensor Fault ===
    // ECU is running, but the speed sensor reading fails. Expect a FAILED diagnostic report.
    printf("--- SCENARIO 3: Vehicle Speed Sensor Fault ---\n");
    G_currentEcuMode = RTE_MODE_MDG_EcuMode_ECU_RUN;
    G_simulateVehicleSpeedFault = TRUE;
    RE_MainFunction_100ms();
    printf("----------------------------------------\n\n");

    // === SCENARIO 4: Different Calibration ===
    // ECU running, no faults, but with a higher speed threshold. Expect warning light OFF.
    printf("--- SCENARIO 4: High Calibration Value ---\n");
    G_simulateVehicleSpeedFault = FALSE; // Reset fault flag
    G_speedThresholdCal = 30; // Set a new calibration value higher than the speed
    RE_MainFunction_100ms();
    printf("----------------------------------------\n\n");

    printf("--- SWC Comprehensive Test Runner Finished ---\n");
    return 0;
}