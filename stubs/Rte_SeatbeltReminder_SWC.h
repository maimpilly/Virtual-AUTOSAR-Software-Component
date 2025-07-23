// File: Rte_SeatbeltReminder_SWC.h

#ifndef RTE_SEATBELTREMINDER_SWC_H
#define RTE_SEATBELTREMINDER_SWC_H

#include "Std_Types.h"

// Function declarations for the RTE API calls you used
Std_ReturnType Rte_Read_R_VehicleSpeed_VehicleSpeed_Kph(uint16* data);
Std_ReturnType Rte_Read_R_SeatbeltStatus_IsSeatbeltFastened(boolean* data);
Std_ReturnType Rte_Write_P_WarningLight_IsWarningLightActive(boolean data);

#endif // RTE_SEATBELTREMINDER_SWC_H