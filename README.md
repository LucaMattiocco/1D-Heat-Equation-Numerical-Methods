# 1D Heat Equation Solver using Numerical Methods

This project implements numerical solutions to the one-dimensional (1D) heat equation using both explicit and implicit models. The objective is to compare the performance of four different numerical schemes against an analytical solution for heat conduction within a wall.

## Project Overview

The 1D heat equation is solved using the following numerical methods:

- Richardson method
- Dufort-Frankel method
- Laasonen method
- Crank-Nicolson method

These methods are implemented in C++ using an Object-Oriented Programming (OOP) approach. This study focuses on comparing computational results with the analytical solution.










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










## Numerical Methods

### 1. Richardson Method (Explicit)

The Richardson method is an explicit finite difference scheme. It uses forward differences for time and central differences for space, making it a straightforward but conditionally stable method. The heat equation in the Richardson method can be discretized as:

$$
\frac{T_i^{n+1} - T_i^n}{\Delta t} = D \frac{T_{i+1}^n - 2T_i^n + T_{i-1}^n}{\Delta x^2}
$$

This can be rearranged to solve for the temperature at the next time step $T_i^{n+1}$:

$$
T_i^{n+1} = T_i^n + \beta \left( T_{i+1}^n - 2T_i^n + T_{i-1}^n \right)
$$

where $\beta = \frac{D \Delta t}{\Delta x^2}$.

**Key Point**: The Richardson method is conditionally stable and is prone to instability if $\beta > 0.5$.

### 2. Dufort-Frankel Method (Explicit)

The Dufort-Frankel method is an explicit scheme that improves stability compared to Richardson by introducing a time-splitting scheme. It discretizes the heat equation as:

$$
\frac{T_i^{n+1} - T_i^{n-1}}{2 \Delta t} = D \frac{T_{i+1}^n - 2T_i^n + T_{i-1}^n}{\Delta x^2}
$$

This can be solved for $T_i^{n+1}$:

$$
T_i^{n+1} = \frac{2 \beta T_{i+1}^n + 2 \beta T_{i-1}^n + (1 - 2\beta) T_i^{n-1}}{1 + 2\beta}
$$

where $\beta = \frac{D \Delta t}{\Delta x^2}$.

**Key Point**: This method is more stable than the Richardson method but can be more complex due to its time-splitting nature.

### 3. Laasonen Method (Implicit)

The Laasonen method is an implicit scheme, meaning it is unconditionally stable. However, it requires solving a system of linear equations at each time step. The discretization of the heat equation is as follows:

$$
\frac{T_i^{n+1} - T_i^n}{\Delta t} = D \frac{T_{i+1}^{n+1} - 2T_i^{n+1} + T_{i-1}^{n+1}}{\Delta x^2}
$$

Rearranging this, we get a system of equations for $T_i^{n+1}$, which can be written in matrix form and solved using methods such as the Thomas algorithm.

**Key Point**: The Laasonen method is unconditionally stable, making it a good choice for simulations with large time steps.

### 4. Crank-Nicolson Method (Implicit)

The Crank-Nicolson method is a second-order accurate implicit method that averages the explicit and implicit formulations, making it both stable and more accurate. The discretization is:

$$
\frac{T_i^{n+1} - T_i^n}{\Delta t} = \frac{D}{2} \left( \frac{T_{i+1}^{n+1} - 2T_i^{n+1} + T_{i-1}^{n+1}}{\Delta x^2} + \frac{T_{i+1}^n - 2T_i^n + T_{i-1}^n}{\Delta x^2} \right)
$$

Rearranging this yields a system of equations that can be solved similarly to the Laasonen method.

**Key Point**: Crank-Nicolson provides a good balance between stability and accuracy, making it one of the most popular methods for solving diffusion-type problems.

---











## Code Structure

The project consists of several C++ files, each implementing various methods to solve the 1D heat equation.

### Main Program (main.cpp)

The main program initializes the simulation, calls the different numerical methods (both explicit and implicit), and saves the results in CSV files for post-processing. The methods are called for different time steps, and a convergence study is conducted using the Laasonen method.

Key functionality in `main.cpp`:

- Initializes the temperature values and time steps.
- Calls explicit methods such as Richardson and Dufort-Frankel.
- Calls implicit methods such as Laasonen and Crank-Nicholson.
- Saves the results in CSV files for further analysis.

### Initializer Class (Initializer.h and Initializer.cpp)

The `Initializer` class is responsible for initializing and storing the time step (`deltat`), the total simulation time (`t`), and the initial temperature distribution across the points.

Key methods:

- `getT_values`: Sets up the initial temperature distribution at discrete points.
- `gett` and `sett`: Getters and setters for the simulation time.
- `getDeltat` and `setDeltat`: Getters and setters for the time step.

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
A Makefile is included to simplify the compilation process.

### How to Compile:

1. Open a terminal in a Linux environment.
2. Compile the project by running the following command:  
   make  
3. Once the compilation is complete, execute the program by running:  
   ./result

### Cleaning Up:

To remove all `*.csv` and `*.o` files generated during compilation, use the following command:  
  ``` make clean
```


## Suggestions for Improvement

While the overall design is solid, there are a few potential areas of improvement:

### Unifying Explicit and Implicit Methods into a Common Interface:

**Current Issue**: Both explicit and implicit methods work towards the same goal (solving the heat equation). However, they reside in separate classes without a shared interface.

**Suggested Improvement**: You could introduce a base class or an interface, such as `HeatEquationSolver`, that both `ExplicitMethods` and `ImplicitMethods` inherit from. This would provide a unified way to call any method without worrying about whether it’s explicit or implicit. For example:

```cpp
class HeatEquationSolver {
public:
    virtual std::vector<double> solve(double deltax, int numberOfPoints, double tsurf, double tinit, double D, double deltat, double t, std::vector<double> temperatureInit) = 0;
};
```
Then, both ExplicitMethods and ImplicitMethods could implement this interface:

class ExplicitMethods : public HeatEquationSolver {
    std::vector<double> solve(double deltax, int numberOfPoints, double tsurf, double tinit, double D, double deltat, double t, std::vector<double> temperatureInit) override {
        // Call richardsonMethods or dufort_frankelMethods
    }
};

Refactor Repeated Logic:
Current Issue: Both ExplicitMethods and ImplicitMethods classes appear to have methods that follow a similar workflow (e.g., setting boundary conditions, iterating over time, solving equations).

Suggested Improvement: You could extract shared logic (such as time-stepping or handling boundary conditions) into a helper class or a base class to reduce code duplication.

Benefit: This would make the code more DRY (Don’t Repeat Yourself) and easier to maintain.



