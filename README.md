# OpenGL
Compile command:
    python compiler.py
    main.py
    
#arch linux pre-install
# Update system and install packages  
sudo pacman -Syu  
  
# Install C++ development tools, Clang, and make  
sudo pacman -S clang make g++  
  
# Install OpenGL, GLFW, and GLEW  
sudo pacman -S mesa glfw glew  
  
# Install X11 libraries (needed for GLFW and OpenGL)  
sudo pacman -S libx11 libxrandr libxi libxinerama libxcursor  
  
# Install static library creation tool  
sudo pacman -S binutils  
  