# Virtual AUTOSAR SWC: Seatbelt Reminder

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Standard](https://img.shields.io/badge/Standard-AUTOSAR-orange.svg)

## Project Overview

This project is a complete, virtual development of an AUTOSAR Application Software Component (SWC) from design to implementation and testing. The goal is to demonstrate a thorough understanding of the AUTOSAR methodology, component-based design, and the standard development workflow used in the automotive industry.

The entire project is self-contained and developed in a virtual environment, proving the ability to create and validate software components without the need for physical ECU hardware.

***

## SWC Design Specification

### Component Purpose

The `SeatbeltReminder_SWC` is designed to monitor vehicle speed and driver seatbelt status. It activates a dashboard warning light if the vehicle is moving faster than a predefined threshold (5 kph) while the seatbelt is unfastened.

### Ports

| Port Name          | Direction | Interface           | Description                                |
| :----------------- | :-------: | :------------------ | :----------------------------------------- |
| `R_VehicleSpeed`   | Required  | `IF_VehicleSpeed`   | Receives the current vehicle speed.        |
| `R_SeatbeltStatus` | Required  | `IF_SeatbeltStatus` | Receives the driver's seatbelt status.     |
| `P_WarningLight`   | Provided  | `IF_WarningLight`   | Sends the activation status for the warning light. |

### Interfaces & Data Types

| Interface           | Data Element           | Data Type |
| :------------------ | :--------------------- | :-------: |
| `IF_VehicleSpeed`   | `VehicleSpeed_Kph`     | `uint16`  |
| `IF_SeatbeltStatus` | `IsSeatbeltFastened`   | `boolean` |
| `IF_WarningLight`   | `IsWarningLightActive` | `boolean` |

### Internal Behavior

The component contains a single runnable entity that implements the control logic.

* **Runnable:** `RE_MainFunction_100ms`
* **Trigger:** Activated by a periodic **Timing Event** every **100 milliseconds**.

***

## Project Structure

The repository is organized to separate the SWC deliverables from the simulation environment.
```
.
├── swc/
│   ├── arxml/
│   │   └── SeatbeltReminder_SWC.arxml   (AUTOSAR Component Description)
│   ├── include/
│   │   └── SeatbeltReminder_SWC.h       (SWC Public Header)
│   └── src/
│       └── SeatbeltReminder_SWC.c       (SWC Implementation)
│
├── stubs/
│   ├── Rte_SeatbeltReminder_SWC.h     (Simulated RTE Header)
│   ├── Std_Types.h                    (Simulated AUTOSAR Types)
│   └── rte_stubs.c                    (Simulated RTE Functions)
│
├── main.c                               (Test Runner/Harness)
├── .gitignore                           (Ignores build artifacts)
└── README.md                            (Project Documentation)
```

***

## How to Build and Run

### Dependencies

* A C compiler, such as **GCC** (installed via [MSYS2](https://www.msys2.org/) on Windows).
* Ensure `gcc.exe` is added to your system's PATH environment variable.

### Build & Execution Steps

1.  Clone the repository to your local machine.
2.  Open a `bash` terminal in the root directory of the project.
3.  Compile the project using the following command:
    ```bash
    gcc main.c swc/src/SeatbeltReminder_SWC.c stubs/rte_stubs.c -I swc/include/ -I stubs/ -o test_runner.exe
    ```
4.  Run the simulation:
    ```bash
    ./test_runner.exe
    ```
5.  **Expected Output:**
    ```
    --- SWC Test Runner Initialized ---
    --- Simulating OS Tick 1 (Calling Runnable) ---
    RTE STUB: Reading VehicleSpeed: 25 kph
    RTE STUB: Reading IsSeatbeltFastened: FALSE
    RTE STUB: Writing IsWarningLightActive -> TRUE

    --- Simulating OS Tick 2 (Calling Runnable) ---
    RTE STUB: Reading VehicleSpeed: 25 kph
    RTE STUB: Reading IsSeatbeltFastened: FALSE
    RTE STUB: Writing IsWarningLightActive -> TRUE

    --- Simulating OS Tick 3 (Calling Runnable) ---
    RTE STUB: Reading VehicleSpeed: 25 kph
    RTE STUB: Reading IsSeatbeltFastened: FALSE
    RTE STUB: Writing IsWarningLightActive -> TRUE

    --- SWC Test Runner Finished ---
    ```

***

### v1.1 - Mode Management
* The SWC is now aware of the ECU's operational state (`ECU_RUN`, `ECU_SLEEP`).
* Component logic is only executed when the system is in the `ECU_RUN` mode, ensuring safe and efficient operation.
* The test harness has been updated to simulate mode switches and validate the component's state-dependent behavior.

### v1.2 - Parameter Calibration
* The hardcoded speed threshold (`5`) has been replaced with a formal calibration parameter.
* The SWC now reads the threshold value from the RTE using the standard `Rte_Prm_` API, making the component's logic independent of the specific value.
* This demonstrates a key automotive concept: separating software logic from calibration data for flexibility and reusability across different vehicle platforms.

### v1.3 - Diagnostic Fault Reporting
* The SWC is now robust against sensor input failures.
* It monitors the return status of the `Rte_Read` API call for the vehicle speed sensor.
* If the reading fails, it reports a `FAILED` status to the Diagnostic Event Manager (Dem). On success, it reports `PASSED`.
* Demonstrates AUTOSAR diagnostics, fault detection, and robust error handling.