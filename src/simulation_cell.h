//
// Created by Linyuan Shi on 10/18/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#ifndef VOID_ANALYZE_SIMULATION_CELL_H
#define VOID_ANALYZE_SIMULATION_CELL_H

#include <tuple>
#include <string>
#include "cxxopts.hpp"

class simulation_cell {
public:
	simulation_cell(double vx, double vy, double vz);

	simulation_cell(double vx, double vy, double vz,
		double ox, double oy, double oz);

	simulation_cell(const std::string& path);

	simulation_cell(const cxxopts::ParseResult& parsed_options) : simulation_cell(parsed_options["f"].as<std::string>()){};

	[[nodiscard]] std::tuple<double, double, double> get_vectors() const;

	[[nodiscard]] std::tuple<double, double, double> get_origin() const;

	[[nodiscard]] std::string get_xyz_info_line() const;

private:
	double vector_x, vector_y, vector_z;
	double origin_x, origin_y, origin_z;
	std::string xyz_file_info_line = "";
};


#endif //VOID_ANALYZE_SIMULATION_CELL_H
