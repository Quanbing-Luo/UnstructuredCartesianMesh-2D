# UnstructuredCartesianMesh-2D
 This repository includes the source code for the paper: 
-  **Quanbing Luo**, Automatic unstructured Cartesian mesh generation method and its application for diffusion problems with finite volume method, Submitted to Journal. 

<!-- [Engineering with Computers](https://doi.org/10.1007/s00366-020-01262-x), 2021 (Published Online) -->

The source code is divided to two parts: (1) Unstructured Cartesian Mesh and (2) Poisson Equation on Unit Disk. 

## Unstructured Cartesian Mesh

Unstructured Cartesian Mesh was divided to two parts: (1) Geometry (Provide the geometries) and (2) CartesianMesh (Generate unstructured Cartesian mesh). In order to obtaining unstructured Cartesian mesh, the two parts must be run in order. The data generated by Geometry are needed by the CartesianMesh program. 


## Poisson Equation on Unit Disk

Poisson Equation on Unit Disk was divided to three parts: (1) FVM of Unstructured Mesh, (2) FVM of Cartesian Mesh and (3) FVM of Unstructured Cartesian Mesh. 
For the program of (3), the mesh of unit disk can be generated with the method provided in previous section. 
For the other two programs, their meshes can be generated by MATLAB (Unstructured Mesh) or easily generated with C++ (Structured Cartesian Mesh).    


**Notice:** The source codes do not provide the intermediate data and final data. You should generate these data from the Geometry (or Meshing) programs step by step. There is a Figure.m program in each program directory to draw the figure of generated data.    
