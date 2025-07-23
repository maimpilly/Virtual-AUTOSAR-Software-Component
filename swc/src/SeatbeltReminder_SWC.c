// File: swc/src/SeatbeltReminder_SWC.c

#include "SeatbeltReminder_SWC.h"
#include "Rte_SeatbeltReminder_SWC.h" 

void RE_MainFunction_100ms(void)
{
    // 1. Declare variables for modes and data
    uint8 current_mode;
    uint16 vehicle_speed;
    uint16 speed_threshold;
    boolean is_seatbelt_fastened;
    Std_ReturnType status_speed;
    Std_ReturnType status_seatbelt;

    // 2. Read the current ECU mode
    (void)Rte_Switch_R_EcuMode_currentMode(&current_mode);

    // 3. Only execute logic if the mode is ECU_RUN
    if (current_mode == RTE_MODE_MDG_EcuMode_ECU_RUN)
    {
        (void)Rte_Prm_P_SpeedThreshold_SpeedThreshold_Kph(&speed_threshold); // Speed threshold
        // 4. Read data from the input ports using the RTE API
        status_speed = Rte_Read_R_VehicleSpeed_VehicleSpeed_Kph(&vehicle_speed);
        status_seatbelt = Rte_Read_R_SeatbeltStatus_IsSeatbeltFastened(&is_seatbelt_fastened);

        // 5. Implement the core logic
        if ((status_speed == RTE_E_OK) && (status_seatbelt == RTE_E_OK))
        {
            if ((vehicle_speed > speed_threshold) && (is_seatbelt_fastened == FALSE))
            {
                (void)Rte_Write_P_WarningLight_IsWarningLightActive(TRUE);
            }
            else
            {
                (void)Rte_Write_P_WarningLight_IsWarningLightActive(FALSE);
            }
        }
    }
    else
    {
        // If not in RUN mode, ensure the warning light is off
        (void)Rte_Write_P_WarningLight_IsWarningLightActive(FALSE);
    }
}