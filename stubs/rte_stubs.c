// File: rte_stubs.c
#include <stdio.h> // For printing to the console
#include "Rte_SeatbeltReminder_SWC.h"

// Global variable to simulate the ECU's current mode
uint8 G_currentEcuMode = RTE_MODE_MDG_EcuMode_ECU_RUN; // Start in RUN mode

uint16 G_speedThresholdCal = 10; // Default calibration value

// Global variable to simulate a failure
boolean G_simulateVehicleSpeedFault = FALSE;

// Simulate the vehicle speed port
Std_ReturnType Rte_Read_R_VehicleSpeed_VehicleSpeed_Kph(uint16* data) {
    if (G_simulateVehicleSpeedFault == TRUE)
    {
        printf("RTE STUB: Simulating fault for VehicleSpeed. Returning NO DATA.\n");
        return RTE_E_NO_DATA; // Return error code
    }
    *data = 25; // Hardcode speed to 25 kph for this test
    printf("RTE STUB: Reading VehicleSpeed: %d kph\n", *data);
    return RTE_E_OK; // Return OK status
}

// Simulate the seatbelt status port
Std_ReturnType Rte_Read_R_SeatbeltStatus_IsSeatbeltFastened(boolean* data) {
    *data = FALSE; // Hardcode seatbelt status to FALSE for this test
    printf("RTE STUB: Reading IsSeatbeltFastened: %s\n", *data == TRUE ? "TRUE" : "FALSE");
    return RTE_E_OK; // Return OK status
}

// Simulate the warning light port
Std_ReturnType Rte_Write_P_WarningLight_IsWarningLightActive(boolean data) {
    // Instead of turning on a real light, we just print the state
    printf("RTE STUB: Writing IsWarningLightActive -> %s\n\n", data == TRUE ? "TRUE" : "FALSE");
    return RTE_E_OK;
}

// Implementation of the new Rte_Switch function
Std_ReturnType Rte_Switch_R_EcuMode_currentMode(uint8* mode) {
    *mode = G_currentEcuMode; // Provide the current mode to the SWC
    printf("RTE STUB: Reading EcuMode: %s\n", *mode == RTE_MODE_MDG_EcuMode_ECU_RUN ? "RUN" : "SLEEP");
    return RTE_E_OK;
}

// Function simulates what the AUTOSAR BSW would do in a real ECU: provide the actual calibration value. 
// By setting it to 10, we can test if our SWC correctly uses this new value instead of the old hardcoded one.
Std_ReturnType Rte_Prm_P_SpeedThreshold_SpeedThreshold_Kph(uint16* value) {
    *value = G_speedThresholdCal; // Simulate a calibrated value of 10 kph
    printf("RTE STUB: Reading SpeedThreshold Parameter: %d kph\n", *value);
    return RTE_E_OK;
}

Std_ReturnType Rte_SetEventStatus(uint8 EventId, uint8 EventStatus) {
    printf("DEM STUB: Received Event ID %d with Status: %s\n",
           EventId,
           EventStatus == DEM_EVENT_STATUS_PASSED ? "PASSED" : "FAILED");
    return RTE_E_OK;
}