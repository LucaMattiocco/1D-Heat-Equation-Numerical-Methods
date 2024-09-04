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

### Problem Description

The problem considered in this project explores heat conduction within a wall. The setup is as follows:

- The wall has a length \(L = 31 \times 10^{-2} \text{ m}\) and is assumed to be infinite in the other directions.
- The initial temperature of the wall is \(T_{init} = 38^\circ C\).
- The surface temperatures are \(T_{surf}\) on both sides of the wall:
  - At \(x = 0\), \(T_{surf} = T_{\infty} = 38^\circ C\).
  - At \(x = L\), \(T_{surf} = 149^\circ C\).
- The wall is made of a nickel steel alloy (40% nickel) with a thermal diffusivity \(D = 93 \, \text{cm}^2/\text{hr}\).

### Heat Equation

The heat equation governing this setup is derived using Fourier's Law:

\[
\frac{\partial T(x, t)}{\partial t} = D \frac{\partial^2 T(x, t)}{\partial x^2}
\]

where:
- \(T(x,t)\) is the temperature inside the wall at position \(x\) and time \(t\),
- \(D = \frac{\lambda}{\rho c}\) is the thermal diffusivity in \(\text{m}^2/\text{s}\), where \(\lambda\) is the thermal conductivity, \(\rho\) is the density, and \(c\) is the specific heat capacity.

### Structure of the Project

- `src/`: Contains the C++ source code for the project.
- `include/`: Contains the header files.
- `data/`: May contain output data files generated by the simulation.
- `README.md`: This file, containing the project overview and instructions.

### Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/1D-Heat-Equation-Numerical-Methods.git
