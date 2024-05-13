# atari-breakout
Atari Breakout game developed in C for mz_apo(educational kit based on MicroZed board) with Debian

# Breakout Game on MicroZed

Welcome to the repository for the Breakout game on the MicroZed board. This README provides an overview of how to set up and build the project using the provided Makefile.

## Prerequisites

Before getting started, ensure you have the following:

- A MicroZed board
- GCC (GNU Compiler Collection) installed
- `make` build automation tool installed
- SSH and SCP tools for connecting to and transferring files to the MicroZed board

## Working with MicroZed

For detailed instructions on working with the MicroZed board, refer to the documentation [here](http://cw.fel.cvut.cz/wiki/courses/b35apo/en/documentation/mz_apo-howto/start).

## Makefile Overview

The Makefile is a crucial component of the build process for the Breakout game. It is a script used by the `make` build automation tool to compile and link the game. Here are some key points about the Makefile:

1. **Compiler**: The Makefile specifies the compiler to be used. By default, it is set to use the GCC (GNU Compiler Collection) for compiling the C source files.
2. **Compiler Flags**: The Makefile also specifies compiler flags, which control various aspects of compilation, such as optimization level, warning level, and the inclusion of debug information.
3. **Dependencies**: The Makefile lists the dependencies for each object file. This means that if any of the source files listed as a dependency changes, the object file will be recompiled.
4. **Build Targets**: The Makefile defines several build targets, such as `all` (to build everything), `clean` (to remove all compiled files), and `run` (to run the game). These targets can be executed by running `make <target>`.
5. **IP Address**: The Makefile includes a variable for the target IP address. This is used when running the game on the MicroZed board. You can set this variable in the Makefile, or you can specify it when running `make run` by using `make run TARGET_IP=<ipaddr>`.
6. **SSH and SCP**: The Makefile uses SSH (Secure Shell) to connect to the MicroZed board and SCP (Secure Copy) to transfer the compiled game to the board.

Remember to check the Makefile and adjust any settings as necessary for your specific setup and requirements.

## Additional Information

For more information about the `make` utility, visit the [GNU Make](https://www.gnu.org/software/make/) website.

For detailed documentation of the code, check `doc/Breakout APO.pdf`.

