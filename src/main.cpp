#include <iostream>
#include <boost/multi_array.hpp>
#include <vector>
#include "settings.h"
#include "atom.h"
#include "bin.h"
#include "simulation_cell.h"
#include "grid_info.h"
#include "functions.h"

using std::cout;
using std::cin;
using std::endl;
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
	settings config(parsed_options["f"].as<string>());
	simulation_cell sc(parsed_options["f"].as<string>());
	set_parameter(config, sc, parsed_options);

	grid_info gr_nf(config, sc);
	// Create bin array
	const auto [nx, ny, nz] = gr_nf.get_grid_no();
	grid_bin_type grid_bins(boost::extents[nx][ny][nz]);
	for (bin_index i = 0; i != nx; ++i)
		for (bin_index j = 0; j != ny; ++j)
			for (bin_index k = 0; k != nz; ++k) { grid_bins[i][j][k].set_bin(i, j, k, gr_nf.get_grid_size()); }

	vector<atom> vec_atoms;
	read_xyz_file(vec_atoms, grid_bins, config.get_path_structure_input(), sc, gr_nf, cout);
	vector<const bin*> empty_bins = check_empty_bin(grid_bins, config);
	vector<vector<const bin*>> bin_voids = find_voids(empty_bins, gr_nf, config);
	filter_small_bins(bin_voids, config);
	vector<std::set<const bin*>> bin_voids_surface = find_voids_sruface(bin_voids, grid_bins, gr_nf, config);
	write_xyz_voids_surface_atom(bin_voids_surface, sc, config);
	write_xyz_voids(bin_voids, sc, config);
	return 0;
}
