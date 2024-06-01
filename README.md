# Wave-Equation
A numerical solver for the wave equation written in C++

## Theory

### Wave Equation

The wave equation is a second-order linear partial differential equation that describes the motion of waves in a medium. The two dimensional equation reads:

$$
\frac{\partial^2 u}{\partial t^2} = c^2 \left( \frac{\partial^2 u}{\partial x^2} + \frac{\partial^2 u}{\partial y^2} \right)
$$

where $u(x, y, t)$ is the amplitude of the wave, $c$ is the wave speed, and $x$ and $y$ are the spatial coordinates.



## Dependencies
- [SFML](https://www.sfml-dev.org/)

## Compilation
Compiling is done using the `make` command. The executable is generated as `main`.
