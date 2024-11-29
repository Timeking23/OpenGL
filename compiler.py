import subprocess
import glob
import os

file_name = "main"
include_dir = "dependencies/include"
lib_dir = "dependencies/lib"
lib = ["-lglfw", "-lGLEW", "-lGL", "-lX11", "-lpthread", "-lXrandr", "-lXi", "./libglad.a"]
preprocessor = ["-DGLEW_STATIC"]

def main():
    # Compile the main.cpp and glad.c files
    subprocess.call(["clang", "-I", include_dir, "-c", "main.cpp", "-o", "main.o"] + preprocessor)
    subprocess.call(["clang", "-I", include_dir, "-c", "glad.c", "-o", "glad.o"])

    # Gather all object files
    object_files = glob.glob("*.o")
    
    if not object_files:
        print("Error: No object files found. Ensure 'main.cpp' and 'glad.c' compiled successfully.")
        return

    # Create static library
    subprocess.call(["ar", "rcs", "libglad.a", "glad.o"])

    # Link object files with the static library
    subprocess.call(["g++"] + object_files + ["-o", file_name, "-L", lib_dir] + lib)

if "__main__" == __name__:
    main()
