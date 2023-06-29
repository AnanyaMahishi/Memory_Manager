# Memory Manager

This program implements a simple memory manager that allows users to allocate and deallocate memory blocks within a fixed-size memory block.

## Functionality

The program provides the following functionality:

1. Allocate Memory: Users can allocate a memory block of a specified size.
2. Deallocate Memory: Users can deallocate a previously allocated memory block.
3. Display Memory Status: Users can view the current status of the memory block, showing which blocks are allocated and which are free.
4. Exit: Users can exit the program.

## Compilation and Execution

To compile the program, follow these steps:

1. Make sure you have a C++ compiler installed on your system (e.g., GCC, Clang).
2. Save the program code in a file named `memory_manager.cpp`.
3. Open a terminal or command prompt and navigate to the directory where you saved the file.
4. Run the following command to compile the code:

   ```
   g++ -o memory_manager memory_manager.cpp
   ```

   Note: If you're using a different compiler, replace `g++` with the appropriate command.

5. After successful compilation, an executable file named `memory_manager` will be generated in the same directory.

To run the program, execute the following command in the terminal or command prompt:

```
./memory_manager
```

Follow the on-screen prompts to interact with the program and test its functionality.

## Notes

- The program allows you to specify the size of the memory block at the beginning. Enter the desired size when prompted.
- The memory manager implements a best-fit algorithm to allocate memory blocks.
- The program handles memory fragmentation by performing memory compaction when necessary.
- The use of vectors provides dynamic memory allocation and automatically manages the memory block size. It eliminates the need for manual memory management, such as managing dynamic arrays or using raw pointers.
