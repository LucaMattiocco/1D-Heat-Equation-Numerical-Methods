# 1D Heat Equation Solver using Numerical Methods

This project implements numerical solutions to the one-dimensional (1D) heat equation using both explicit and implicit models. The goal is to compare the performance of four different numerical schemes against an analytical solution for heat conduction within a wall.

## Project Overview

The project solves the 1D heat equation using the following numerical methods:

- Richardson method
- Dufort-Frankel method
- Laasonen method
- Crank-Nicolson method

These methods are implemented in C++ using an Object-Oriented Programming (OOP) approach. Les méthodes peuvent être divisié en deux : Explicit et Implicit lesquels ont beneficié d'implementation dans des classes différentes.


The study is conducted with a particular focus on comparing computational results with the analytical solution.

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





