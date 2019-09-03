# RendeRays raytracer
## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Usage](#usage)
### General info
Rendering static images of a scene using ray-tracing technique. 
Used for rendering studies and computer vision applications as a source for test images.
### Technologies
*RendeRays* is developed in C++ and compiled with C++17 compatable compiler.
The application is tested with Visual Studio 2019, however, any C++17 compiler should work.
### Usage
To use *RendeRays* application, launch executable file and provide command line arguments to specify
file name of a scene to be rendered *(option -f)* and whether rendered image should be immediately displayed *(option -s)*.
Scene description file should be present in *'/scenes'* folder.
Rendered output images are placed in *'/output'* folder.
#### Usage example
To start rendering the scene described in 'scene/test_scene.json' file and display images immediately after each render, write:
> RendeRays.exe -f test_scene.json -s
