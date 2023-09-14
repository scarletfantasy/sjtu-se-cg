# sjtu-se-cg
a repo for tutorial

# demos

## demo

basic homework architecture with minimum code
## bezier curve

a program of simple bezier curve implement

![](bezier.png)
## tessellation
a program of simple tesselation example

![](tess.png)

## particles
a program of simple cs particles

![](particle.png)


# request
* imgui
* glfw
* glad
* assimp(optional)
* eigen(optional)

# install using vcpkg
安装和使用说明详见 [microsoft vcpkg](https://github.com/microsoft/vcpkg)

    vcpkg integrate install
    vcpkg install glfw3:x64-windows glad:x64-windows imgui[core,opengl3-binding,glfw-binding]:x64-windows
    vcpkg install assimp:x64-windows eigen3:x64-windows
