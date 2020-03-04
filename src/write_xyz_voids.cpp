//
// Created by Linyuan Shi on 10/22/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include <fstream>
#include "color_codes.h"
#include "functions.h"

void write_xyz_voids(const vector<vector<const bin*>>& bn_vods, const simulation_cell& sc,
	const settings& config) {
	std::ofstream File(config.get_filename_voids_position_xyz());
	if (File) {
		int cnt = 0;
		for (const auto& bin_ptrs : bn_vods) { cnt += bin_ptrs.size(); };
		File << cnt << std::endl;
		File << std::endl;
		File << std::setprecision(6) << std::fixed;
		const auto [ox, oy, oz] = sc.get_origin();
		for (const auto& bin_ptrv : bn_vods)
			for (const auto& bin_ptr : bin_ptrv) {
				auto [x, y, z] = bin_ptr->get_bin_position();
				File << "S " << x + ox << " " << y + oy << " " << z + oz << std::endl;
			}
	}
	else {
		std::cerr << RED
			<< "The file " << config.get_filename_voids_surface_position_xyz().string() << "cannot be opened"
			<< RESET << std::endl;
		exit(EXIT_FAILURE);
	}
}
