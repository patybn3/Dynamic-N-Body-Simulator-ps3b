# PS#: Universe

## Contact
Name: Patricia Antlitz
Section: 202
Time to Complete: days

## Description
This program simulates a celestial body system, modeling the motion of celestial bodies in a two-dimensional space. It consists of two main classes, "Universe" and "CelestialBody", which are responsible for storing information about celestial bodies and their interactions. The "Universe" class manages a collection of celestial bodies and can read and write their data from and to input/output streams. The "CelestialBody" class represents individual celestial bodies with properties such as position, velocity, mass, and an associates image. The program reads data from an input source, simulates the motion of the celestial bodies based on gravitational interactions, and visualized the system using the SFML library.

### Features
CelestialBody class defines the properties of individual celestial bodies and methods for position and velocity updates.
The Universe class manages the entire NBody system. It calculated the gravitational interactions and advancing the simulation. Operator overloading is used to seamless data input and output

### Memory
This program manages the objects using auto storage duration for local variables and dynamic memory allocations for the vector that stores the celestial bodies in the Universe class. No smart pointers were used.

### Issues

translating the math from the instructions into code was a challenge for me. I didn't find a lot of resources in terms of code examples. The ones I found are mentioned below, but they were not very helpful. I met with a tutor for 1 hour and he helped me with some of the calculations and a step-by-step pseudo code to help me out.

### Extra Credit

For the extra credit I added the elapsed time with units to the top right corner of the screen. I also
added flickering starts on the background. I also added sound.
whatLifeFeelsLike.txt is the name of a universe file in which nothing makes sense, some planets seem like the are doing things right, the others are all over the place and lost in space, like us.

### Sources:

https://www.geeksforgeeks.org/universal-law-of-gravitation/

Java example:
https://github.com/tlehman/newton

https://phys.libretexts.org/Bookshelves/College_Physics/College_Physics_1e_(OpenStax)/06%3A_Uniform_Circular_Motion_and_Gravitation/6.05%3A_Newtons_Universal_Law_of_Gravitation

stars:
https://www.youtube.com/watch?v=pR8Lb2Zq-BU
