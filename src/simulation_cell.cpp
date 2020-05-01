//
// Created by Linyuan Shi on 10/18/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//
#include <algorithm>
#include <filesystem>
#include <fstream>
using std::ifstream;

#include <iostream>
using std::endl;
using std::cout;
using std::cerr;

#include <sstream>
using std::istringstream;

#include <string>
using std::string;

#include "color.h"
#include "simulation_cell.h"

simulation_cell::simulation_cell(double vx, double vy, double vz) :
	simulation_cell(vx, vy, vz, 0.0, 0.0, 0.0) {}

simulation_cell::simulation_cell(double vx, double vy, double vz, double ox, double oy, double oz) :
	vector_x(vx), vector_y(vy), vector_z(vz), origin_x(ox), origin_y(oy), origin_z(oz) {}

simulation_cell::simulation_cell(const string& path)
{
	std::filesystem::path path_structure;
	try {
		path_structure = std::filesystem::canonical(path);
	}
	catch (const std::filesystem::filesystem_error & e) {
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	std::ifstream file(path);
	if (!file.is_open()) {
		cerr << Color::Red << "Failed to read file: " << path_structure.filename() << endl;
		cerr << "The program is aborted." << Color::None << endl;
		exit(EXIT_FAILURE);
	}
	string line;
	std::getline(file, line);
	std::getline(file, line);
	xyz_file_info_line = line;
	auto lattice_beg = std::find(line.begin(), line.end(), '"');
	auto lattice_end = std::find(++lattice_beg, line.end(), '"');
	auto origin_beg = std::find(lattice_end + 1, line.end(), '"');
	auto origin_end = std::find(++origin_beg, line.end(), '"');
	if (lattice_beg == line.end() || lattice_end == line.end() || origin_beg == line.end() || origin_end == line.end())
	{
		cerr << Color::Red << "Failed to construct the simulation cell class from file: " << path_structure.filename() << endl;
		cerr << "The program is aborted." << Color::None << endl;
		exit(EXIT_FAILURE);
	}
	double garbage_one, garbage_two;
	istringstream lattice(string(lattice_beg, lattice_end));
	lattice >> vector_x >> garbage_one >> garbage_two;
	lattice >> garbage_one >> vector_y >> garbage_two;
	lattice >> garbage_one >> garbage_two >> vector_z;

	istringstream origin(string(origin_beg, origin_end));
	origin >> origin_x >> origin_y >> origin_z;
	file.close();
}

std::tuple<double, double, double> simulation_cell::get_vectors() const {
	return std::make_tuple(vector_x, vector_y, vector_z);
}

std::tuple<double, double, double> simulation_cell::get_origin() const {
	return std::make_tuple(origin_x, origin_y, origin_z);
}

std::string simulation_cell::get_xyz_info_line() const
{
	return  xyz_file_info_line;
}
