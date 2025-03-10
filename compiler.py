import subprocess
import glob

file_name = "main"
include_dirs = ["dependencies/include", "utils"]
lib_dir = "dependencies/lib"
lib = ["-lglfw", "-lGLEW", "-lGL", "-lpthread", "-lX11", "-lXrandr", "-lXi", "-lXinerama", "-lXcursor"]
preprocessor = ["-DGLEW_STATIC"]

def main():
    # Compile source files
    subprocess.run(["clang++", "-I"] + include_dirs + preprocessor + ["-c", "main.cpp", "-o", "main.o"], check=True)
    subprocess.run(["clang", "-I"] + include_dirs + ["-c", "glad.c", "-o", "glad.o"], check=True)
    subprocess.run(["clang++", "-I"] + include_dirs + ["-c", "utils/Utils.cpp", "-o", "Utils.o"], check=True)

    # Create static library for glad
    subprocess.run(["ar", "rcs", "libglad.a", "glad.o"], check=True)

    # Gather object files
    object_files = glob.glob("*.o")

    if not object_files:
        print("Error: No object files found. Ensure all sources compiled successfully.")
        return

    # Link the executable
    subprocess.run(["g++"] + object_files + ["-o", file_name, "-L", lib_dir, "-L.", "-lglad"] + lib, check=True)
    subprocess.run(["./main"], check=True)

if __name__ == "__main__":
    main()
