# PARTICLE SYSTEM


A simple **Particle System** based on Euler's Integration for updating particle dynamics.


Acceleration Enabled             |  Acceleration Disabled
:-------------------------:|:-------------------------:
![](/demo/particle_system_demo1.gif)  |  ![](/demo/particle_system_demo2.gif)




## Functionalities and Design Choices
- **Visualization:** The simulation uses [SFML (Simple and Fast Multimedia Library)](https://www.sfml-dev.org) to create and display circular particles. 
- **Particle Movement:** Particle positions are updated each frame based on velocity and acceleration, resulting in continuous movement and realistic physics.

- **Collision Detection:** Collisions between particles are detected based on distance and radii. When a collision occurs, velocities are adjusted using impulse (momentum exchange) for realistic bounces. To prevent particle overlap, a repulsion factor is included in the collision response.

- **Boundary Collisions:** When a particle hits the edges of the window, its velocity is reversed, making the particle "bounce" off the walls.

## Get Started
This project uses SFML for graphical rendering and event handling. You need to install SFML on your system.
More on that [here](https://www.sfml-dev.org/tutorials/3.0/).


1. Clone this Repository.

2. Copy and paste the .dll files from SFML to the project directory. 

3. Build the Project and Run the Simulation.


