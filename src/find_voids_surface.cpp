//
// Created by Linyuan Shi on 10/22/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include <set>
#include <memory>
using std::unique_ptr;

#include "functions.h"

#ifdef DEBUG

#include <iostream>
#include "timer.h"
using std::cout;
using std::endl;

#endif

auto find_voids_sruface(unique_ptr<vector<vector<const bin*>>>& bn_vds_ptr, const grid_bin_type& grid_bins, const grid_info& gr_nf, const settings& config)->std::unique_ptr<vector<vector<const bin*>>>
{

#ifdef  DEBUG
	const timer Timer(std::cout, "Looking for the surface atoms of voids");
#endif

	auto surface_bin = [&grid_bins, &gr_nf, &config](const bin* sgnl_bin, const int& dbinx, const int& dbiny, const int& dbinz) -> const bin* {
		auto [nx, ny, nz] = sgnl_bin->relative_bin_pos(dbinx, dbiny, dbinz, gr_nf, config.isPeriodic());
		return &grid_bins[nx][ny][nz];
	};

	vector<std::set<const bin*>> bin_voids_surface;
	bin_voids_surface.reserve(bn_vds_ptr->size());
	std::set<const bin*> tmp_set;

	for (const auto& vbin_ptr : *bn_vds_ptr)
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
	auto bin_voids_surface_ptr = std::make_unique<vector<vector<const bin*>>>();
	for (const auto& s : bin_voids_surface)
	{
		bin_voids_surface_ptr->emplace_back(s.begin(), s.end());
	}

#ifdef  DEBUG
	Timer.span();
#endif
	return bin_voids_surface_ptr;
}
