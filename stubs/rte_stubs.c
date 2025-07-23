// File: rte_stubs.c
#include <stdio.h> // For printing to the console
#include "Rte_SeatbeltReminder_SWC.h"

// Simulate the vehicle speed port
Std_ReturnType Rte_Read_R_VehicleSpeed_VehicleSpeed_Kph(uint16* data) {
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