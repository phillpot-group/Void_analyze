//
// Created by Linyuan Shi on 10/22/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include <algorithm>
#include "functions.h"

void filter_small_bins(vector<vector<const bin *>> &voids, const settings &config) {
    auto iter_end = std::remove_if(voids.begin(), voids.end(), [&config](vector<const bin *> bin_single_void) -> bool {
        return bin_single_void.size() <= config.get_voids_bin_cutoff();
    });
    voids.erase(iter_end, voids.end());
}
