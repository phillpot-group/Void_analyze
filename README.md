### Introduction

Perform void analysis from xyz structure.

### Install instruction

1. Make sure you have complier which support C++17. (Visual Studio 2017 or later, GCC 8 or later)
2. Install [Cmake](https://cmake.org/) and [Conan](https://conan.io/) from official website.
3. Go to the project directory
4. `make build & cd build`
5. `cmake .. -DCMAKE_BUILD_TYPE=Release`

### Usage

The pore size distribution surpport the following arguments:

```
"-f, --file" : The path of the input file. It should be in xyz format
"-o, --output": The destination of the output files
"-c, --circle": Optional argument, specify the coordinates of the center of the circle and the radius, ie. (center_x, center_y, radius)
"--rm-lg": Optional bool flag, true means remove the largest pores during the detection
"-h" : print help
```

#### Input structure:
Input structure should be in "xyz" format. The 2nd line of the input structure should have the same format as Ovito ie. `Lattice="208.0 0.0 0.0 0.0 208.0 0.0 0.0 0.0 25.5" Origin="-104.0 -104.0 -10.2" Properties=species:S:1:pos:R:3`. We recomend you to generate xyz file using Ovito software rather than mannually writing the second line.

#### Output file:
voids_analysis_info.txt: The volume fraction and size of each pore detected in the structure.

voids_position.xyz: This file records the pores position in enhanced xyz format. The last column is the label of each pore. 

voids_surface_position.xyz: This file records the atoms which form the surface of pores. The last column is the label of each pore.
