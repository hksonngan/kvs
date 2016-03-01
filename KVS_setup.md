# Setup #
In order to compile KVS, the C++ compiler is required. Microsoft Visual C++ can be used for Windows environment, and for Linux and Mac OS X, g++ and make can be used. If the user develop a visualization application, OpenGL Utility Toolkit (GLUT) is required to display the window for the rendering results. And, in order to use the GPU accelerations, OpenGL Extension Wrangler Library (GLEW) is utilized in KVS. If you have no restrictions, we suggest you install these libraries.

## Windows ##
Microsoft Visual C++ can be used for Windows. Please download it from the following URL and then install it on your PC.

> [Microsoft Visual Studio](http://www.microsoft.com/japan/msdn/vstudio/express/)

GLUT and GLEW can be download from the following URLs.

> [Nate Robins - OpenGL - GLUT for Win32](http://www.xmission.com/~nate/glut.html)

> [GLEW: The OpenGL Extension Wrangler Library](http://glew.sourceforge.net/)


## Linux ##
In case of Linux, user can easily install compilers (g++ and make), GLUT and GLEW by using the package manager, such as apt or synaptic on Ubuntu. Note that these packages should be installed as developper version. If freeglut is listed in the package manager, please install it instead of original GLUT.

## Mac OS X ##
For Mac OS X, g++ and make will be available by installing Xcode. You can donwload Xcode from [Mac Dev Center](http://developer.apple.com/devcenter/mac/index.action). GLUT has already been installed and GLEW can be installed by using [MacPorts](http://www.macports.org/) as follows.

```
sudo port install glew
```