# Support Library #
KVS supports several third-party libraries.

## Library ##

| **Library name** | **Flag name** | **Description** |
|:-----------------|:--------------|:----------------|
| CUDA             | KVS\_SUPPORT\_CUDA | Parallel computing environment developed by NVIDIA |
| GLEW             | KVS\_SUPPORT\_GLEW | OpenGL extension wrangler library |
| GLUT             | KVS\_SUPPORT\_GLUT | OpenGL utility toolkit |
| OpenCV           | KVS\_SUPPORT\_OPENCV | A library of programming functions for real time computer vision |
| Qt               | KVS\_SUPPORT\_QT | A cross-platform application and UI framework developed by Nokia |
| SAGE             | KVS\_SUPPORT\_SAGE | Scalable adaptive graphics environment developed by EVL |
| OpenCABIN        | KVS\_SUPPORT\_OPENCABIN | A library for multiple display system |

## Example of Configuration ##

```
KVS_SUPPORT_CAVE      = 0
KVS_SUPPORT_CUDA      = 0
KVS_SUPPORT_GLEW      = 1
KVS_SUPPORT_GLUT      = 1
KVS_SUPPORT_OPENCV    = 0
KVS_SUPPORT_QT        = 0
KVS_SUPPORT_SAGE      = 0
KVS_SUPPORT_OPENCABIN = 0
```