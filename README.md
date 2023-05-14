# Hello, OpenGL!

## Libraries
https://www.glfw.org/download.html -- Install the binaries for your OS, or build it from source.
Make sure to get the static `libglfw3` binary.

Put all the libraries into the `lib/` folder, if it's not there, run init.bat.


## Building
`init.bat` initializes everything, make sure to run this before anything else.

Use any for the comp.bat files to compile the program you want.

For example, compiling `programs/hello/window.c` in debug, you'd do `./compd hello/window`.

Running with no parameters, it'll default to compiling hello/triangle.



`compd.bat` includes `stdio.h` and print statements, no optimizations.

`compr.bat` does not include `stdio.h`, and optimizes with `-O3 and -s`.


## Resources
https://learnopengl.com/