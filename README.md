# OpenGL basic open wondow example

The following example is a working example of rendering a single window on OSX (OS Ver 10.13). 
This example includes the necessary header and library file - GLEW and GLFW - for basic OpenGL rendering. 

Additionally, this example include GLUS, which is:

```
The cross platform and cross Graphic Library UtilitieS (GLUS) is an open-source C library, which provides a hardware (HW) and operating system (OS) abstraction plus many functions usually needed for graphics programming using OpenGL, OpenGL ES or OpenVG.
```

Currently this C Library is wired up in the `CmakeLists.txt` which includes all external resources. GLUS has been tested to working this example. You can find the example of GLUS basic implementation in in c file `glus-example.c`. 
NOTE! Currently to try GLUS you must relace the contents of `main.c` with that of `glus-example.c`, this is because the `CmakeLists.txt` is currently only set to compile one source.