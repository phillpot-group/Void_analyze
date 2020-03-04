//
// Created by Linyuan Shi on 10/19/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include <algorithm>
#include "functions.h"

#include <iostream>
using std::cout;
using std::endl;

using bin_index = grid_bin_type::index;

vector<const bin*> check_empty_bin(const grid_bin_type& grid_bins, const settings& config) {
#ifdef DEBUG
	cout << "Begin to check empty bins" << endl;
#endif
	vector<const bin*> empty_bins;
	const grid_bin_type::size_type* shape = grid_bins.shape();
	const grid_bin_type::size_type nx(shape[0]), ny(shape[1]), nz(shape[2]);
	const int empty_bin_cutoff = config.get_empty_bin_cutoff();

	empty_bins.reserve(nx * ny * nz);
	for (bin_index i = 0; i != nx; ++i)
		for (bin_index j = 0; j != ny; ++j)
			for (bin_index k = 0; k != nz; ++k) {
				const bin& grid_bin_single = grid_bins[i][j][k];
				if (grid_bin_single.is_empty(empty_bin_cutoff)) {
					empty_bins.push_back(&grid_bin_single);
				}
			}
	empty_bins.shrink_to_fit();
	auto filter = config.get_filter_func();
	if (filter) {
		auto iter = empty_bins.begin();
		auto begin_rm = std::remove_if(empty_bins.begin(), empty_bins.end(),
			[&filter](const bin* iter)->bool {auto [x, y, z] = iter->get_bin_position(); return !filter(x, y, z); });
		empty_bins.erase(begin_rm, empty_bins.end());
	}
#ifdef DEBUG
	cout << "Finish checking empty bins" << endl;
#endif
	return empty_bins;
}