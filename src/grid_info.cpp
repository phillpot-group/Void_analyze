//
// Created by Linyuan Shi on 10/18/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include <array>
#include "grid_info.h"

grid_info::grid_info(const settings &config, const simulation_cell &sc) {
    const double grid_sz = config.get_grid_size();
    auto[cell_x, cell_y, cell_z] = sc.get_vectors();
    nx = static_cast<int>(cell_x / grid_sz);
    ny = static_cast<int>(cell_y / grid_sz);
    nz = static_cast<int>(cell_z / grid_sz);
    dx = cell_x / nx;
    dy = cell_y / ny;
    dz = cell_z / nz;
    total_no_bins_occupied_by_fiber = nx * ny * nz;
}

std::array<int, 3> grid_info::get_grid_no() const {
    return {nx, ny, nz};
}

std::array<double, 3> grid_info::get_grid_size() const {
    return {dx, dy, dz};
}

int grid_info::get_fiber_vol_by_bins() const
{
    return total_no_bins_occupied_by_fiber;
}

void grid_info::set_fiber_vol_by_bins(int vol)
{
    total_no_bins_occupied_by_fiber = vol;
}
