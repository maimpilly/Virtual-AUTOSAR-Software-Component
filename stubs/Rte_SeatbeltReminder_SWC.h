// File: stubs/Rte_SeatbeltReminder_SWC.h

#ifndef RTE_SEATBELTREMINDER_SWC_H
#define RTE_SEATBELTREMINDER_SWC_H

#include "Std_Types.h"

// Define Mode Constants (matching the ARXML)
#define RTE_MODE_MDG_EcuMode_ECU_RUN   0
#define RTE_MODE_MDG_EcuMode_ECU_SLEEP 1

// Define for diagnostic constants
#define EV_VehicleSpeedSignalLost   1
#define DEM_EVENT_STATUS_PASSED     0
#define DEM_EVENT_STATUS_FAILED     1

// ... (existing Rte_Read/Write function declarations) ...
Std_ReturnType Rte_Read_R_VehicleSpeed_VehicleSpeed_Kph(uint16* data);
Std_ReturnType Rte_Read_R_SeatbeltStatus_IsSeatbeltFastened(boolean* data);
Std_ReturnType Rte_Write_P_WarningLight_IsWarningLightActive(boolean data);

// New function declaration for the RTE Switch API
Std_ReturnType Rte_Switch_R_EcuMode_currentMode(uint8* mode);

// New function prototype for the new Rte_Prm API 
Std_ReturnType Rte_Prm_P_SpeedThreshold_SpeedThreshold_Kph(uint16* value);

// New function prototype for the new Dem API call
Std_ReturnType Rte_SetEventStatus(uint8 EventId, uint8 EventStatus);

#endif // RTE_SEATBELTREMINDER_SWC_H