//
// Created by linyuan on 10/18/19.
//

#ifndef VOID_ANALYZE_FUNCTIONS_H
#define VOID_ANALYZE_FUNCTIONS_H

#include <boost/multi_array.hpp>
#include <filesystem>
#include <set>
#include <vector>
using std::vector;

#include "atom.h"
#include "bin.h"
#include "grid_info.h"
#include "settings.h"
#include "simulation_cell.h"
#include "cxxopts.hpp"

typedef boost::multi_array<bin, 3> grid_bin_type;

void read_xyz_file(vector<atom>& vec_atoms, grid_bin_type& grid_bins, const std::filesystem::path& path_structure,
	const simulation_cell& sc, const grid_info& gr_if, std::ostream& os);

[[nodiscard]] vector<const bin*> check_empty_bin(const grid_bin_type& grid_bins, const settings& config);

[[nodiscard]] vector<vector<const bin*>>
find_voids(const vector<const bin*>& empty_bins, const grid_info& gr_nf, const settings& config);

void filter_small_bins(vector<vector<const bin*>>& voids, const settings& config);

vector<std::set<const bin*>>
find_voids_sruface(const vector<vector<const bin*>>& bn_vds, const grid_bin_type& grid_bins, const grid_info& gr_nf,
	const settings& config);

void write_xyz_voids_surface_atom(const vector<std::set<const bin*>>& bn_vs_srfc, const simulation_cell& sc,
	const settings& config);

void write_xyz_voids(const vector<vector<const bin*>>& bn_vods, const simulation_cell& sc,
	const settings& config);

bool is_in_circle(double ox_circle, double oy_circle, const double radius, const simulation_cell& sc, const double x,
	const double y, const double z);

void set_parameter(settings&, const simulation_cell&, const cxxopts::ParseResult&);

cxxopts::ParseResult parse(int argc, char** argv);

#endif //VOID_ANALYZE_FUNCTIONS_H
