//
// Created by Linyuan Shi on 10/22/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include <algorithm>
#include <memory>
using std::unique_ptr;

#include "functions.h"

void filter_bins(unique_ptr<vector<vector<const bin *>>> &voids_ptr, const settings &config, grid_info& gr_nf) {
    auto iter_end = std::remove_if(voids_ptr->begin(), voids_ptr->end(), [&config](vector<const bin *> bin_single_void) -> bool {
        return bin_single_void.size() <= config.get_voids_bin_cutoff();
    });
    voids_ptr->erase(iter_end, voids_ptr->end());
	if (config.get_flag_rm_bigggest_void())
	{
		auto comp = [](vector<const bin*>lhs, vector<const bin*>rhs) {return lhs.size() < rhs.size(); };
		std::sort(voids_ptr->begin(), voids_ptr->end(), comp);
		gr_nf.set_fiber_vol_by_bins(gr_nf.get_fiber_vol_by_bins() - (voids_ptr->back()).size());
		voids_ptr->pop_back();
	}
}
