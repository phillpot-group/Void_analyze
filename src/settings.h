//
// Created by Linyuan Shi on 10/18/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#ifndef VOID_ANALYZE_SETTINGS_H
#define VOID_ANALYZE_SETTINGS_H

#include <string>
#include <filesystem>
#include <functional>

class settings {
public:
	settings(const std::string& path_strctr);

	bool isPeriodic() const;

	bool isVoidAnalysis() const;

	[[nodiscard]] int get_empty_bin_cutoff() const;

	[[nodiscard]] int get_voids_bin_cutoff() const;

	[[nodiscard]] double get_grid_size() const;

	[[nodiscard]] bool get_flag_rm_bigggest_void() const;

	void set_flag_rm_biggest_void(bool);

	void set_filter_func(std::function<bool(double, double, double)> filter_);

	[[nodiscard]] const std::function<bool(double, double, double)>& get_filter_func() const;

	[[nodiscard]] std::filesystem::path get_filename_voids_position_xyz() const;

	[[nodiscard]] std::filesystem::path get_filename_voids_surface_position_xyz() const;

	[[nodiscard]] std::filesystem::path get_path_folder_input() const;

	[[nodiscard]] std::filesystem::path get_path_structure_input() const;

	[[nodiscard]] std::filesystem::path get_path_folder_output() const;

	void set_path_folder_output(const std::string& path_str);

private:
	bool flag_periodic = true;
	bool flag_void_analysis = true;
	bool flag_rm_biggest_void = false;
	int empty_bin_cutoff = 1;               // The number of atoms in one empty bin should be smaller than this cutoff
	int voids_bin_cutoff = 1;               // The minimal number of bins in one void should be larger than this cutoff
	double cutoff_distance = 1.8;
	double grid_size = 3.2;
	std::string filename_voids_position_xyz = "voids_position.xyz";
	std::string filename_voids_surface_position_xyz = "voids_surface_position.xyz";
	std::filesystem::path path_folder_input_;
	std::filesystem::path path_structure_input_;
	std::filesystem::path path_folder_output_;
	std::function<bool(double, double, double)> filter;           // filter function pointer, default value is nullptr
};


#endif //VOID_ANALYZE_SETTINGS_H
