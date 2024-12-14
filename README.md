# Simulation Project

## Overview
This project simulates a dynamic environment involving vehicles such as trucks, choppers, and state troopers interacting with warehouses. The system is designed using the MVC (Model-View-Controller) pattern and features robust simulation, user interaction, and error handling capabilities.

## Features
- **Vehicles**: Includes Trucks, Choppers, and State Troopers, each with distinct behaviors.
- **Warehouses**: Manage inventory levels and serve as points of interaction for vehicles.
- **Simulation**: Time-based simulation of vehicle movements and interactions.
- **Commands**: Interactive commands for users to control and monitor the system.
- **Error Handling**: Custom exception classes to handle errors gracefully.

## Project Structure
The project consists of multiple components organized in a modular manner:

### Core Components

1. **Model**
   - Singleton class that maintains the state of all objects (vehicles, warehouses).
   - Responsible for initialization and validation of trucks and warehouses.
   - Provides command functions for creating elements, updating positions, and simulating movements.

2. **View**
   - Handles user interaction and visualization of the simulation.
   - Supports commands like `default`, `size`, `zoom`, `pan`, and `show`.

3. **Controller**
   - Manages the interaction between the user and the model.
   - Parses user commands and triggers corresponding actions in the model.

4. **Vehicles**
   - **Truck**: Implements specific behavior for trucks, including routes and inventory management.
   - **Chopper**: Includes movement based on position or course, and supports attack commands.
   - **State Trooper**: Patrols and manages a course among warehouses.

5. **Warehouses**
   - Manage inventory levels.
   - Provide interaction points for vehicles.

6. **Validation**
   - Ensures data integrity and validates input files and commands.

7. **Geometry**
   - Includes mathematical utilities for handling positions, angles, and distances.

### Files
- `Controller.cpp` and `Controller.h`: Implements the controller logic.
- `Model.cpp` and `Model.h`: Defines the simulation model.
- `View.cpp` and `View.h`: Handles user interface commands and visualization.
- `Vehicle.cpp` and `Vehicle.h`: Base class for vehicles with shared functionality.
- `Truck.cpp` and `Truck.h`: Truck-specific implementation.
- `Chopper.cpp` and `Chopper.h`: Chopper-specific implementation.
- `State_trooper.cpp` and `State_trooper.h`: State trooper-specific implementation.
- `Warehouse.cpp` and `Warehouse.h`: Warehouse-related logic.
- `Validation.cpp` and `Validation.h`: Input validation and error handling.
- `Geometry.cpp` and `Geometry.h`: Mathematical utilities for the simulation.
- `ObjectFactory.cpp` and `ObjectFactory.h`: Factory pattern for creating objects dynamically.
- `Exception.cpp` and `Exception.h`: Custom exception handling.
- `Time.h`: Manages time calculations.
- `main.cpp`: Entry point of the application.

### Data Files
- `depot.dat`: Example input data for initializing warehouses or trucks.

## How to Run
1. Compile the project using a C++ compiler that supports C++11 or higher.
2. Provide necessary input files (e.g., `depot.dat`) for initializing the program.
3. Run the program and interact with it using supported commands.

### Example Commands
- `create <name> <type> <params>`: Create a new vehicle.
- `go`: Simulate the next time step.
- `status`: Print the current status of all objects.
- `view`: Adjust visualization parameters.
- `exit`: Terminate the program.

## Key Features
### Command Parsing
The system supports various commands that allow users to:
- Initialize warehouses and trucks.
- Create and manage vehicles dynamically.
- Adjust simulation parameters and visualize results.

### Error Handling
Custom exceptions are implemented to ensure graceful handling of:
- Invalid inputs.
- Runtime errors during simulation.

### Simulation
Vehicles interact with each other and with warehouses. Movement, inventory management, and state updates occur dynamically based on user commands and simulation logic.

## Development Notes
- **Design Pattern**: The project is implemented using the MVC pattern for modularity and scalability.
- **Code Reusability**: Leveraged inheritance and the factory pattern to simplify object creation.
- **Testing**: Ensure robust validation and error handling for all user inputs and file operations.

## Dependencies
- Standard C++ library.
- No external libraries are required.

## Future Improvements
- Enhance visualization with graphical components.
- Extend simulation features to include more vehicle types and behaviors.
- Add support for multi-threaded simulation to improve performance.

## Contributors
- Eran Helvitz
