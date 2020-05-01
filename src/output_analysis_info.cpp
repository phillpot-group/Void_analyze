#include "atom.h"
#include <algorithm>
#include <boost/range/combine.hpp>
#include "color.h"
#include <iostream>
#include <iterator>
#include <fstream>
#include "output_analysis_info.h"

using std::endl;
using std::unique_ptr;
using std::vector;

void output_analysis_info::write_info(const unique_ptr<vector<vector<const bin*>>>& vd_ptr, const unique_ptr<vector<vector<const bin*>>>& srfc_ptr) const  // voids_surface_pointer
{
	std::ofstream File(file_name);
	if (File)
	{
		File << "Volume fraction, pore size" << endl;
		File << std::setprecision(6) << std::fixed;
		const auto [nx, ny, nz] = gr_nf.get_grid_no();
		double total_bins = gr_nf.get_fiber_vol_by_bins();
		if (vd_ptr->size() != srfc_ptr->size())
		{
			std::cerr << Color::Red << "vd_ptr should have the same size with the srfc_ptr!" << endl;
			exit(EXIT_FAILURE);
		}
		for (auto iter_vd = vd_ptr->begin(), iter_surf = srfc_ptr->begin(); iter_vd != vd_ptr->end(); ++iter_vd, ++iter_surf)
		{
			double vol_frac = iter_vd->size() / total_bins;
			vector<atom*> surf_atoms;
			for (auto bin_ptr : *iter_surf)
			{
				vector<atom*> bin_atoms = bin_ptr->get_atoms();
				std::copy(bin_atoms.begin(), bin_atoms.end(), std::back_inserter(surf_atoms));
			}
			double max_distance = 0;
			for (auto iter_first_atom = surf_atoms.begin(); iter_first_atom != surf_atoms.end(); ++iter_first_atom)
			{
				for (auto iter_second_atom = iter_first_atom + 1; iter_second_atom != surf_atoms.end(); ++iter_second_atom)
				{
					double distance = distance_atom(**iter_first_atom, **iter_second_atom, sc_ptr);
					if (distance > max_distance)
					{
						max_distance = distance;
					}
				}
			}
			File << vol_frac << " " << max_distance << endl;
		}
	}
	else
	{
		error();
	}
}
