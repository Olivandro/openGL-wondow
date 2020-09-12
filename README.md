# OpenGL basic open wondow example

The following example is a working example of rendering a single window on OSX (OS Ver 10.13), and Linux (Arch 5.5.8). 
This example includes the necessary header and library file - GLEW and GLFW - for basic OpenGL rendering. Please note, that you will have to compile GLEW and GLFW before starting with this example.

Currently this C Library is wired up in the `CmakeLists.txt`, thus you should onlu have to compile each source once per os installation. What does this mean, if you download this repo to a mac computer and compile both GLEW & GLFW sources, you cannot use those compiled libraries with another system like linux (and probably even another mac os system). This is because each computer is different and GLFW in particular compiles to the operating system its being compiled on. 

## Compile deps and basic example

From the root of the project direct using the terminal, enter codes below:
```
$ cd glfw-3.3.2
$ cmake ./
$ make
$ cd ../glew-2.1.0
$ make
$ cd ..  # Let go back to the root of this project folder.
```

To explain, we are changing dir to the GLFW dir first, running `cmake` to prep the Makefile doc, and then finally running `make` from within the GLFW dir. Once its finished compiling we change dir to the glew-2.1.0 dir where we only run `make` (please see GLEW compile documentation if you would like to know more). After GLEW is finished compiling we change back to the root of the project. 

From here we can compile our `main.c` file without worrying about connecting to those specific libraries as everything should be taken care by the CMakeFile.txt doc. 

To compile the basic example with this repo, from the root of the project enter these commands:
```
$ mkdir build
$ cmake . build/ 

# If you are using VS Codium I would recommend running:

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 . build

# The reason for this is to generate a compile_commands.json file and the .clangd dir which will create links to your 
# dependancies and get clangd to work correctly

$ make
```

This should complete the compiling of the basic example. The output binary will be located in `build` dir and will be named `window`.
To run this binary on the terminal enter: `./build/window`.



### Notes:
GLUS has been removed from this example.... If you like to experiment with a more established library that uses GLEW and GLFW just like we are doing here (just not as bare bones), I recommended looking into [McNoppers](https://github.com/McNopper)'s [OpenGL](https://github.com/McNopper/OpenGL), and or his [GLUS repo](https://github.com/McNopper/GLUS).