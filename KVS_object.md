# Object #
In KVS, the vizualized dat is called as 'object' and is classified into geomtric object and volumetric object.

The geometric object is composed of point, line or polygon, and is normally supported as graphic primitives in well-known graphics library, such as OpenGL and DirectX. In KVS, the user can represent it as point object, line object or polygon object.

On the other hand, the volumentric object is represented as numerical values, which are discreately distributed in the 3D space. Moreover, the 3D space is divided into multiple sub-spaces called grid, and then the numerical value is defined at the vertex of the grid (element). In KVS, the volumetric object can be classified into the structured volume object and unstructured volume object depending on the complexity of the grid structure.

![https://lh3.googleusercontent.com/_X4cB5gzzR7o/TdKMhGy0fuI/AAAAAAAAAC0/wTL77ongyZI/s800/KVSObjects.png](https://lh3.googleusercontent.com/_X4cB5gzzR7o/TdKMhGy0fuI/AAAAAAAAAC0/wTL77ongyZI/s800/KVSObjects.png)

The data structures of the each object implemented in KVS will be explained here.