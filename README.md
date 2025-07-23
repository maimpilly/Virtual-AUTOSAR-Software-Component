# Virtual AUTOSAR SWC: A Seatbelt Reminder

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Standard](https://img.shields.io/badge/Standard-AUTOSAR-orange.svg)
![Version](https://img.shields.io/badge/Version-2.0-brightgreen.svg)

## About This Project

This repository documents my journey in building a complete AUTOSAR Application Software Component (SWC) from the ground up. The goal was to go beyond simple coding and dive deep into the AUTOSAR methodology, demonstrating how real-world automotive software is designed, implemented, and tested.

The entire project was developed in a virtual environment, without any physical hardware. This proves an understanding of the development workflow and the ability to create robust, testable software components.

***

## My Development & Testing Strategy

To simulate the environment, I structured the project into three distinct parts, each with a clear role:

#### 1. The Component (`swc/`)
This is the core product: the `SeatbeltReminder_SWC`. Designed it as a self-contained "black box" that fulfills its requirements based on inputs from the AUTOSAR Run-Time Environment (RTE). 

#### 2. The Simulated Car (`stubs/`)
The stubs represent the **rest of the car** from the component's perspective. The `rte_stubs.c` file simulates the RTE and the underlying Basic Software (BSW), providing the necessary inputs like sensor data, ECU modes, and calibration values. This helps to create a configurable "real world" for the component to work.

#### 3. The Test Engineer (`main.c`)
The `main.c` file is my **test script orchestrator**. Its job is to manipulate the state of the "Simulated Car" (by changing variables in the stubs) and then trigger the component to see how it reacts. This approach allowed me to create specific, repeatable test scenarios to validate every feature that was built.

***

## Final Component Design (`v2.0`)

The `SeatbeltReminder_SWC` evolved from a simple reminder to a robust component aware of its environment.

* **Purpose:** To activate a warning light if the vehicle is moving faster than a configurable speed threshold while the seatbelt is unfastened. It only operates when the ECU is in a `RUN` state and can report sensor failures to the diagnostic system.

* **Ports & Interfaces:**

| Port Name            | Type        | Direction | Interface           | Description                                          |
| :------------------- | :---------- | :-------: | :------------------ | :--------------------------------------------------- |
| `R_VehicleSpeed`     | S/R         | Required  | `IF_VehicleSpeed`   | Receives the current vehicle speed.                  |
| `R_SeatbeltStatus`   | S/R         | Required  | `IF_SeatbeltStatus` | Receives the driver's seatbelt status.               |
| `P_WarningLight`     | S/R         | Provided  | `IF_WarningLight`   | Sends the activation status for the warning light.   |
| `R_EcuMode`          | Mode-Switch | Required  | `MDG_EcuMode`       | Receives the current ECU operational mode.           |
| `P_SpeedThreshold`   | Parameter   | Provided  | `IF_SpeedThreshold` | Provides access to the speed threshold calibration.  |
| `P_Dem_VehicleSpeed` | Diagnostic  | Provided  | `IF_Dem_VehicleSpeed` | Reports the health of the vehicle speed signal to the Dem. |

***

## Project Evolution

This project was built incrementally, with each version adding a significant new capability.

* **v1.0:** Initial implementation of the core logic and a basic test harness.
* **v1.1:** Added **Mode Management**, making the SWC aware of the ECU's `RUN` and `SLEEP` states. This is crucial for managing power consumption and ensuring components are only active when needed.
* **v1.2:** Introduced a **Calibration Parameter** for the speed threshold, replacing a hardcoded value. This allows the same software to be used across different vehicle models by changing parameter sets, a core principle of automotive software reuse.
* **v1.3:** Implemented **Diagnostic Fault Reporting**, allowing the SWC to report sensor failures to the Dem (Diagnostic Event Manager). This ensures system robustness by allowing the ECU to react to hardware failures and store Diagnostic Trouble Codes (DTCs).
* **v2.0:** Created a final, **Comprehensive Test Application** that validates all features in a single run.

***

## How to Build and Run

#### Dependencies
* A C compiler, such as **GCC** (I used the one from [MSYS2](https://www.msys2.org/) on Windows).

#### Build & Execution
1.  Clone the repository.
2.  Open a `bash` terminal in the project's root directory.
3.  Compile everything with the following command:
    ```bash
    gcc main.c swc/src/SeatbeltReminder_SWC.c stubs/rte_stubs.c -I swc/include/ -I stubs/ -o test_runner.exe
    ```
4.  Run the final test application:
    ```bash
    ./test_runner.exe
    ```

#### Final Test Output (`v2.0`)
```
--- SWC Comprehensive Test Runner Initialized ---

--- SCENARIO 1: Normal Operation --- 
RTE STUB: Reading EcuMode: RUN 
RTE STUB: Reading SpeedThreshold Parameter: 10 kph 
RTE STUB: Reading VehicleSpeed: 25 kph 
DEM STUB: Received Event ID 1 with Status: PASSED 
RTE STUB: Reading IsSeatbeltFastened: FALSE 
RTE STUB: Writing IsWarningLightActive -> TRUE

--- SCENARIO 2: ECU in Sleep Mode --- 
RTE STUB: Reading EcuMode: SLEEP 
RTE STUB: Writing IsWarningLightActive -> FALSE

--- SCENARIO 3: Vehicle Speed Sensor Fault --- 
RTE STUB: Reading EcuMode: RUN 
RTE STUB: Reading SpeedThreshold Parameter: 10 kph 
RTE STUB: Simulating fault for VehicleSpeed. Returning NO DATA. 
DEM STUB: Received Event ID 1 with Status: FAILED

--- SCENARIO 4: High Calibration Value --- 
RTE STUB: Reading EcuMode: RUN 
RTE STUB: Reading SpeedThreshold Parameter: 30 kph 
RTE STUB: Reading VehicleSpeed: 25 kph 
DEM STUB: Received Event ID 1 with Status: PASSED 
RTE STUB: Reading IsSeatbeltFastened: FALSE 
RTE STUB: Writing IsWarningLightActive -> FALSE

--- SWC Comprehensive Test Runner Finished ---
```

***
