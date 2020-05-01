#include <iostream>
#include <boost/multi_array.hpp>
#include <vector>
#include "settings.h"
#include "atom.h"
#include "bin.h"
#include "functions.h"
#include "grid_info.h"
#include "simulation_cell.h"
#include "output_analysis_info.h"
#include "output_surface_atoms.h"
#include "output_voids.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

typedef boost::multi_array<bin, 3> grid_bin_type;
typedef grid_bin_type::index bin_index;

int main(int argc, char** argv) {
	//const settings config("./test/first.xyz");
	//simulation_cell sc(228.520769 - 12.904845, 77.119013 - 2.776971, 70.576620 - 9.413978,
	//	12.904845, 2.776971, 9.413978);
	//settings config("./test/core.xyz");
	//simulation_cell sc(181.5, 181.5, 28, 0, 0, -12.25);
	
	auto parsed_options = parse(argc, argv);
	auto sc_ptr = std::make_shared<simulation_cell>(parsed_options);
	settings config(parsed_options, *sc_ptr);
	
	grid_info gr_nf(config, *sc_ptr);
	// Create bin array
	const auto [nx, ny, nz] = gr_nf.get_grid_no();
	grid_bin_type grid_bins(boost::extents[nx][ny][nz]);
	for (bin_index i = 0; i != nx; ++i)
		for (bin_index j = 0; j != ny; ++j)
			for (bin_index k = 0; k != nz; ++k) { grid_bins[i][j][k].set_bin(i, j, k, gr_nf.get_grid_size()); }

	vector<atom> vec_atoms;
	read_xyz_file(vec_atoms, grid_bins, config.get_path_structure_input(), *sc_ptr, gr_nf, cout);
	vector<const bin*> empty_bins = check_empty_bin(grid_bins, config);
	auto bin_voids_ptr = find_voids(empty_bins, gr_nf, config);
	filter_bins(bin_voids_ptr, config, gr_nf);
	auto bin_voids_surface_ptr = find_voids_sruface(bin_voids_ptr, grid_bins, gr_nf, config);
	output_voids op_v(config.get_filename_voids_position_xyz(), sc_ptr);
	op_v.write_xyz(bin_voids_ptr);
	output_surface_atoms op_s(config.get_filename_voids_surface_position_xyz(), sc_ptr);
	op_s.write_xyz(bin_voids_surface_ptr);
	output_analysis_info op_a(config.get_filename_voids_analysis_info(), sc_ptr, gr_nf);
	op_a.write_info(bin_voids_ptr, bin_voids_surface_ptr);
	//write_xyz_voids_surface_atom(bin_voids_surface, sc, config);
	//write_xyz_voids(bin_voids, sc, config);
	return 0;
}
