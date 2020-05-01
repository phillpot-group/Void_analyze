#include "output_surface_atoms.h"
#include <iostream>
using std::endl;

void output_surface_atoms::write_to_xyz_(std::ostream& os, const std::vector<std::vector<const bin*>>& voids) const
{
	size_t cnt = 0;
	size_t label = 1;
	for (const auto& bin_ptrs : voids)
		for (const auto& bin : bin_ptrs)
			cnt += bin->get_atoms().size();
	os << cnt << endl;
	//os << "symbol x y z label" << endl;
	os << sc_ptr->get_xyz_info_line()<< ":label:R:1" << endl;
	os << std::setprecision(6) << std::fixed;
	const auto [ox, oy, oz] = sc_ptr->get_origin();
	for (const auto& bin_ptrv : voids) {
		for (const auto& bin_ptr : bin_ptrv) {
			for (const auto atm_ptr : bin_ptr->get_atoms())
			{
				auto [x, y, z] = atm_ptr->get_coordinates();
				os << symbol << " " << x + ox << " " << y + oy << " " << z + oz << " " << label << std::endl;
			}
		}
		++label;
	}
}
