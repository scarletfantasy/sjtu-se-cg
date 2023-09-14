# demo

basic homework architecture with minimum code
## bezier curve

a program of simple bezier curve implement

# request
* glfw
* glad
* imgui(recommend to install for easy ui operation)
* assimp(optional, for model operation)
* eigen(optional, for math calculation)

# install using vcpkg
安装和使用说明详见 [microsoft vcpkg](https://github.com/microsoft/vcpkg)

    vcpkg integrate install
    vcpkg install glfw3:x64-windows glad:x64-windows imgui[core,opengl3-binding,glfw-binding]:x64-windows
    vcpkg install assimp:x64-windows eigen3:x64-windows