# Circuit-Network-Program
A C++ program that simulates a dynamic resistor network, allowing users to configure and analyze circuits with node voltage calculations, resistor management, and comprehensive error handling. This project showcases skills in dynamic memory management, OOP, and real-world circuit simulation.

## Key Features

- **Circuit Initialization**: Users can specify the maximum number of nodes and resistors, dynamically building and resizing the circuit to efficiently manage memory based on input size.
- **Resistor Management**: Supports adding, modifying, and deleting resistors within the network. Each resistor has a unique name, resistance value, and two endpoints connecting it to nodes.
- **Node Voltage Calculation**: Allows users to set voltage values for nodes, simulating voltage sources. An iterative calculation method determines unknown node voltages based on network connectivity.
- **Error Handling and Validation**: Robust error handling ensures command syntax and argument validity, allowing the program to manage various edge cases smoothly.

This project demonstrates practical experience with core C++ programming principles, including memory management, advanced I/O handling, and the application of object-oriented design to simulate complex, real-world systems.

## How to Use

1. **Start the Program**: Open a terminal and run the compiled executable. The program will wait for commands through the standard input.
2. **Initialize the Network**: Use the `maxVal` command to define the network size.
3. **Add a Resistor**: Use the `insertR` command to add a resistor with a specified name, resistance, and node connections.
4. **Modify a Resistor**: Change an existing resistor's resistance with `modifyR`.
5. **Print Resistor Information**: Display details for a specific resistor or all resistors using `printR`.
6. **Delete Resistors**: Remove all resistors with `deleteR all`.
7. **Set Node Voltage**: Assign a voltage to a node with `setV`.
8. **Solve Node Voltages (Bonus)**: Use the `solve` command to calculate and display voltages for all nodes based on their connections.
9. **Exit**: Send an EOF (End of File) signal by pressing `Ctrl+D` in the terminal to end the program.

Each command prompts output or error messages for invalid input, ensuring smooth interaction.
