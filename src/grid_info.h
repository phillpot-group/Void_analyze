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
    [[nodiscard]] int get_fiber_vol_by_bins() const;
    void set_fiber_vol_by_bins(int vol);
private:
    int nx, ny, nz; // number of grids or bins on x, y, z direction respectively
    int total_no_bins_occupied_by_fiber; // total number of bins;
    double dx, dy, dz; // sizes of the grid on x, y, z direction respectively
};


#endif //VOID_ANALYZE_GRID_INFO_H
