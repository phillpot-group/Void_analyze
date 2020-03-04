//
// Created by Linyuan Shi on 10/18/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#ifndef VOID_ANALYZE_GRID_INFO_H
#define VOID_ANALYZE_GRID_INFO_H

#include "simulation_cell.h"
#include "settings.h"

class grid_info {
public:
    grid_info(const settings &config, const simulation_cell &sc);
    [[nodiscard]] std::array<int, 3> get_grid_no() const;
    [[nodiscard]] std::array<double, 3> get_grid_size() const;

private:
    int nx, ny, nz; // number of grids or bins on x, y, z direction respectively
    double dx, dy, dz; // sizes of the grid on x, y, z direction respectively
};


#endif //VOID_ANALYZE_GRID_INFO_H
