//
// Created by Linyuan Shi on 10/18/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include <fstream>
#include "color_codes.h"
#include "functions.h"

void write_xyz_voids_surface_atom(const vector<std::set<const bin*>>& bn_vs_srfc, const simulation_cell& sc,
	const settings& config) {
	std::ofstream File(config.get_filename_voids_surface_position_xyz());
	if (File) {
		int cnt = 0;
		for (const auto& bin_s : bn_vs_srfc)
			for (const auto& bin_ptr : bin_s) { cnt += bin_ptr->get_atoms().size(); };
		File << cnt << std::endl;
		File << std::endl;
		File << std::setprecision(6) << std::fixed;
		const auto [ox, oy, oz] = sc.get_origin();
		for (const auto& bin_s : bn_vs_srfc)
			for (const auto& bin_ptr : bin_s)
				for (const atom* atm_ptr : bin_ptr->get_atoms()) {
					auto [x, y, z] = atm_ptr->get_coordinates();
					File << "S " << x + ox << " " << y + oy << " " << z + oz << std::endl;
				}
	}
	else {
		std::cerr << RED << "The file " << config.get_filename_voids_surface_position_xyz().string()
			<< "cannot be opened" << RESET << std::endl;
		exit(EXIT_FAILURE);
	}
}
