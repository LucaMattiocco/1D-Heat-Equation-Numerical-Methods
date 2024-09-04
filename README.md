# 1D Heat Equation Solver using Numerical Methods

This project implements numerical solutions to the one-dimensional (1D) heat equation using both explicit and implicit models. The goal is to compare the performance of four different numerical schemes against an analytical solution for heat conduction within a wall.

## Project Overview

The project solves the 1D heat equation using the following numerical methods:

- Richardson method
- Dufort-Frankel method
- Laasonen method
- Crank-Nicolson method

These methods are implemented in C++ using an Object-Oriented Programming (OOP) approach. Detailed mathematical investigations reveal that explicit methods may not be well-suited for certain scenarios due to instability, whereas implicit methods, though more complex to implement, perform better in terms of convergence and stability.

The study is conducted with a particular focus on comparing computational results with the analytical solution.

## Code Structure

The project consists of several C++ files, each implementing various methods to solve the 1D heat equation.

### Main Program (main.cpp)
The main program initializes the simulation, calls the different numerical methods (both explicit and implicit), and saves the results in CSV files for post-processing. The methods are called for different time steps and a convergence study is done using the Laasonen method.

Key functionality in `main.cpp`:
- Initializes the temperature values and the time steps.
- Calls explicit methods such as Richardson and Dufort-Frankel.
- Calls implicit methods such as Laasonen and Crank-Nicholson.
- Saves the results in CSV files for further analysis.

### Initializer Class (Initializer.h and Initializer.cpp)
The `Initializer` class is responsible for initializing and storing the time step (`deltat`), the total simulation time (`t`), and the initial temperature distribution across the points.

Key methods:
- `getT_values`: Sets up the initial temperature distribution at discrete points.
- `gett` and `sett`: Getter and setter for the simulation time.
- `getDeltat` and `setDeltat`: Getter and setter for the time step.

### ExplicitMethods Class (ExplicitMethods.h and ExplicitMethods.cpp)
This class implements the explicit numerical methods to solve the heat equation.

Key methods:
- `richardsonMethods`: Solves the heat equation using the Richardson explicit scheme.
- `dufort_frankelMethods`: Solves the heat equation using the Dufort-Frankel scheme.
- `saveCSV`: Saves the temperature distribution results into CSV files.

### ImplicitMethods Class (ImplicitMethods.h and ImplicitMethods.cpp)
This class implements the implicit numerical methods, including solving a tridiagonal system of equations using the Thomas algorithm.

Key methods:
- `laasonenMethod`: Solves the heat equation using the Laasonen implicit method.
- `crankNicholsonMethod`: Solves the heat equation using the Crank-Nicholson scheme.
- `thomasAlgorithm`: Implements the Thomas algorithm (Tridiagonal Matrix Algorithm) to solve tridiagonal systems.
- `saveCSV`: Saves the temperature distribution results into CSV files.

## Development Environment Software
## Problem Description

The problem considered in this project explores heat conduction within a wall. The setup is as follows:

- The wall has a length $L = 31 \times 10^{-2}  \text{m}$ and is assumed to be infinite in the other directions.
- The initial temperature of the wall is $T_{\text{init}} = 38^\circ \ \text{C}$.
- The surface temperatures are $T_{\text{surf}}$ on both sides of the wall:
  - At $x = 0$, $T_{\text{surf}} = T_{\infty} = 38^\circ \ \text{C}$.
  - At $(x = L$, $T_{\text{surf}} = 149^\circ \ \text{C}$.
- The wall is made of a nickel steel alloy (40% nickel) with a thermal diffusivity $D = 93 \ \text{cm}^2/\text{hr}$.
  
 <p align="center">
  <img src="https://via.placeholder.com/500x250.png?text=Numerical+Heat+Equation+Diagram" alt="Numerical Heat Equation" width="500"/>
</p>
<p align="center">Numerical Heat Equation Example</p>

## Heat Equation

The heat equation governing this setup is derived using Fourier's Law:

$$
\frac{\partial T(x, t)}{\partial t} = D \frac{\partial^2 T(x, t)}{\partial x^2}
$$

Where:
- $T(x,t)$ is the temperature inside the wall at position \(x\) and time \(t\),
- $D = \frac{\lambda}{\rho c}$ is the thermal diffusivity in \(\text{m}^2/\text{s}\), where \(\lambda\) is the thermal conductivity, \(\rho\) is the density, and \(c\) is the specific heat capacity.



## Development Environment Software

C++ development took place on the campus computers using Visual Studio. Development also took place on personal computers using Visual Studio Code, but compilation was done on Linux. Post-processing was done in Matlab for easier and better data visualization. Both C++ and Matlab code are available in the appendix.

The code was compiled using GNU compilers on Linux, without any other external dependencies, libraries, or third-party source code. The following commands were used in the Linux terminal to compile the code:

```bash
$ ls
Initializer.h  main.cpp   PostProcess.cpp   result
ExplicitMethods.cpp  ImplicitMethods.cpp   Initializer.cpp
bash
Copy the code
$ g++ -c ImplicitMethods.cpp
$ g++ -c ExplicitMethods.cpp
$ g++ -c Initializer.cpp
$ g++ -c main.cpp
$ g++ ImplicitMethods.o ExplicitMethods.o Initializer.o main.o -o result
$ ./result
```
A Makefile has been included to streamline the compilation process. 

To compile:

1. Open the Linux terminal.
2. Enter the command 'make.'
3. Run the executable using the command './result.'

To delete '*.csv' and '*.o' files:
Use the command 'make clean.'





