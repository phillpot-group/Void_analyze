//
// Created by Linyuan Shi on 10/18/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include <boost/multi_array.hpp>
#include <cmath>
#include <iostream>
using std::cerr;
using std::endl;

#include <fstream>
using std::istringstream;

#include <filesystem>

#include <vector>
using std::vector;

#include "atom.h"
#include "simulation_cell.h"
#include "grid_info.h"
#include "bin.h"
#include "color_codes.h"

typedef boost::multi_array<bin, 3> grid_bin_type;

void read_xyz_file(vector<atom>& vec_atoms, grid_bin_type& grid_bins, const std::filesystem::path& path_structure,
	const simulation_cell& sc, const grid_info& gr_if, std::ostream& os) {

	unsigned int count = 2;
	constexpr size_t max_character_per_line = 512;
	size_t n_atoms;
	string line, element;
	double x, y, z; // atom position
	grid_bin_type::size_type xbx, yby, zbz; // indexes of the bin
	istringstream line_s;
	std::ifstream file(path_structure);
	const std::array<double, 3> gr_dr = gr_if.get_grid_size();
	const auto [ox, oy, oz] = sc.get_origin();
	const auto [vx, vy, vz] = sc.get_vectors();
	const auto [gr_dx, gr_dy, gr_dz] = gr_dr;
	const auto [gr_nx, gr_ny, gr_nz] = gr_if.get_grid_no();

	if (!file.is_open()) {
		cerr << RED << "Failed to read file: " << path_structure.filename() << endl;
		cerr << "The program is aborted." << RESET << endl;
		exit(EXIT_FAILURE);
	}
	else {
		os << "Begin to read xyz file: " << path_structure.filename() << endl;
	}
	file >> n_atoms;
	os << n_atoms << " atoms are in this system." << endl;
	file.ignore(max_character_per_line, '\n');
	file.ignore(max_character_per_line, '\n');
	if (!file) {
		cerr << RED << "Incorrect xyz file format." << endl;
		cerr << "The program is aborted." << RESET << endl;
		exit(EXIT_FAILURE);
	}
	vec_atoms.reserve(n_atoms);
	while (std::getline(file, line)) {
		++count;
		line_s.clear();
		line_s.str(line);
		line_s >> element >> x >> y >> z;

		// reset origin
		x -= ox;
		y -= oy;
		z -= oz;
		x = std::fmod(x, vx);
		y = std::fmod(y, vy);
		z = std::fmod(z, vz);
		if (x >= vx || x < 0) {
			cerr << RED << path_structure << " Line " << count << " :atom is outside the cell at x direction." << endl;
			cerr << "The program is aborted." << RESET << endl;
			exit(EXIT_FAILURE);
		}
		if (y >= vy || y < 0) {
			cerr << RED << path_structure << " Line " << count << " :atom is outside the cell at y direction." << endl;
			cerr << "The program is aborted." << RESET << endl;
			exit(EXIT_FAILURE);
		}
		if (z >= vz || z < 0) {
			cerr << RED << path_structure << " Line " << count << " :atom is outside the cell at z direction." << endl;
			cerr << "The program is aborted." << RESET << endl;
			exit(EXIT_FAILURE);
		}
		vec_atoms.emplace_back(element, x, y, z);

		// set bin values
		xbx = static_cast<grid_bin_type::size_type> (x / gr_dx);
		yby = static_cast<grid_bin_type::size_type> (y / gr_dy);
		zbz = static_cast<grid_bin_type::size_type> (z / gr_dz);

		if (xbx >= gr_nx || yby >= gr_ny || zbz >= gr_nz) {
			cerr << RED << "The bin_index of bin is over the max number of bins on one direction." << endl;
			cerr << "The program is aborted." << RESET << endl;
			exit(EXIT_FAILURE);
		}

		grid_bins[xbx][yby][zbz].add_atm_ptr(&vec_atoms.back());
	}
	if (n_atoms != vec_atoms.size()) {
		cerr << RED << "The actual number of atoms: " << vec_atoms.size()
			<< "is different with the declared number: " << n_atoms << endl;
		cerr << "The program is aborted." << RESET << endl;
		exit(EXIT_FAILURE);
	}
	os << "Finish reading xyz position file." << endl;
	file.close();
}