# Phaba - 2D physics engine
My hobby project I am writing in my spare time. The idea is to perform all computations (bodies moving, collisions detection and resolving) on a GPU via compute shaders. For sure it will put some limitation on its possible functionality - e.g. we can't call collisions callbacks from compute shader immediately, but at least it should be (in theory) faster to compute everything on GPU instead of CPU.
# Ideas for the future
* Collision callbacks
* Event callbacks with client`s compute shader code (e.g. to manipulate on bodies somehow when they collide)
* Add support for Vulkan API (it is just easier to start with OpenGL)
* Linux/macOS support (though it is CMake+Conan project, it is currently tested only on Windows)