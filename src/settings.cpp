//
// Created by Linyuan Shi on 10/18/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include <iostream>
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include "color_codes.h"
#include "settings.h"


settings::settings(const string& path_strctr) {
	try {
		path_structure_input_ = std::filesystem::canonical(path_strctr);
	}
	catch (const std::filesystem::filesystem_error & e) {
		cerr << RED << e.what() << RESET << endl;
		exit(EXIT_FAILURE);
	}
	path_folder_input_ = path_structure_input_.parent_path();
	path_folder_output_ = path_folder_input_;
}

bool settings::isPeriodic() const { return flag_periodic; }

bool settings::isVoidAnalysis() const { return flag_void_analysis; }

int settings::get_empty_bin_cutoff() const { return empty_bin_cutoff; }

int settings::get_voids_bin_cutoff() const { return voids_bin_cutoff; }

double settings::get_grid_size() const { return grid_size; }

bool settings::get_flag_rm_bigggest_void() const { return flag_rm_biggest_void; }

void settings::set_flag_rm_biggest_void(bool flag) { flag_rm_biggest_void = flag; }

void  settings::set_filter_func(std::function<bool(double, double, double)> filter_) { filter = filter_; }

const std::function<bool(double, double, double)>& settings::get_filter_func() const { return filter; }

std::filesystem::path settings::get_filename_voids_position_xyz() const {
	return path_folder_output_ / filename_voids_position_xyz;
}

std::filesystem::path settings::get_filename_voids_surface_position_xyz() const {
	return path_folder_output_ / filename_voids_surface_position_xyz;
}

std::filesystem::path settings::get_path_folder_input() const { return path_folder_input_; }

std::filesystem::path settings::get_path_structure_input() const { return path_structure_input_; }

[[nodiscard]] std::filesystem::path settings::get_path_folder_output() const { return  path_folder_output_; };

void settings::set_path_folder_output(const string& path_str)
{
	try {
		path_folder_output_ = std::filesystem::canonical(path_str);
	}
	catch (const std::filesystem::filesystem_error & e) {
		cerr << RED << e.what() << RESET << endl;
		exit(EXIT_FAILURE);
	}
	if (!std::filesystem::is_directory(path_folder_output_))
	{
		cerr << RED << "Output path should be a folder path rather than a file path." << RESET << endl;
		exit(EXIT_FAILURE);
	}
}