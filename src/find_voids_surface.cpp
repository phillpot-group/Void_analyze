//
// Created by Linyuan Shi on 10/22/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include <set>
#include "functions.h"

vector<std::set<const bin*>> find_voids_sruface(const vector<vector<const bin*>>& bn_vds, const grid_bin_type& grid_bins, const grid_info& gr_nf, const settings& config)
{
	auto surface_bin = [&grid_bins, &gr_nf, &config](const bin* sgnl_bin, const int& dbinx, const int& dbiny, const int& dbinz) -> const bin* {
		auto [nx, ny, nz] = sgnl_bin->relative_bin_pos(dbinx, dbiny, dbinz, gr_nf, config.isPeriodic());
		return &grid_bins[nx][ny][nz];
	};

	vector<std::set<const bin*>> bin_voids_surface;
	bin_voids_surface.reserve(bn_vds.size());
	std::set<const bin*> tmp_set;

	for (const auto& vbin_ptr : bn_vds)
	{
		tmp_set.clear();
		for (const auto& bin_ptr : vbin_ptr)
		{
			if (surface_bin(bin_ptr, 1, 0, 0)->has_atoms()) { tmp_set.insert(surface_bin(bin_ptr, 1, 0, 0)); }
			if (surface_bin(bin_ptr, -1, 0, 0)->has_atoms()) { tmp_set.insert(surface_bin(bin_ptr, -1, 0, 0)); }
			if (surface_bin(bin_ptr, 0, 1, 0)->has_atoms()) { tmp_set.insert(surface_bin(bin_ptr, 0, 1, 0)); }
			if (surface_bin(bin_ptr, 0, -1, 0)->has_atoms()) { tmp_set.insert(surface_bin(bin_ptr, 0, -1, 0)); }
			if (surface_bin(bin_ptr, 0, 0, 1)->has_atoms()) { tmp_set.insert(surface_bin(bin_ptr, 0, 0, 1)); }
			if (surface_bin(bin_ptr, 0, 0, -1)->has_atoms()) { tmp_set.insert(surface_bin(bin_ptr, 0, 0, -1)); }
		}
		bin_voids_surface.push_back(tmp_set);
	}
	bin_voids_surface.shrink_to_fit();
	return bin_voids_surface;
}
