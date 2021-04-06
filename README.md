# raytrace
This repository demonstrates raytracing by implementing interaction between 'point light' & 'sphere and plane'. This started as raytracing project for my 2018-1 CG class. Legacy branch includes MSVC project, but is no longer maintained. Default compile environment is now Linux/Ubuntu.

# Prerequisite
You need 'g++' and 'freeglut' To compile this code. To install these libraries, run the following:

	sudo apt-get install freeglut3-dev g++

# How to Run
Go to 'sources' directory, and simply run 'make'.<br/>
This will make a binary 'out'. Simply run by typing './out' to run the program with default settings.<br/>
Currently, following optional parameters are supported.<br/><br/>
![argument_display](assets/argument_display.JPG)

# Example
Included code as is features 3 spheres under 3 different light source in the reflective room, with x9 anti-alising.<br/>
Since this code uses only CPUs, rendering may take a while.<br/><br/>
![raytrace_example](assets/raytrace_example.JPG)
