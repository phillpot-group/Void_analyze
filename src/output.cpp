//
// Created by Linyuan Shi on 03/07/20.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include <fstream>
#include <iomanip>
#include <iostream>
using std::cerr;
using std::endl;


#include "color.h"
#include "output.h"

void output::write_to_xyz_(std::ostream& os, const std::vector<std::vector<const bin*>>& voids) const
{
	size_t cnt = 0;
	size_t label = 1;
	for (const auto& bin_ptrs : voids) { cnt += bin_ptrs.size(); };
	os << cnt << endl;
	//os << "symbol x y z label" << endl;
	os << sc_ptr->get_xyz_info_line() << ":label:R:1" << endl;
	os << std::setprecision(6) << std::fixed;
	const auto [ox, oy, oz] = sc_ptr->get_origin();
	for (const auto& bin_ptrv : voids) {
		for (const auto& bin_ptr : bin_ptrv) {
			auto [x, y, z] = bin_ptr->get_bin_position();
			os << symbol << " " << x + ox << " " << y + oy << " " << z + oz << " " << label << std::endl;
		}
		++label;
	}
}
 
void output::error() const
{
	cerr << Color::Red << "The file " << file_name
		<< " cannot be opened" << Color::None << endl;
	exit(EXIT_FAILURE);
}

void output::write_xyz(const std::unique_ptr<std::vector<std::vector<const bin*>>>& voids_ptr) const
{
	std::ofstream File(file_name);
	if (File)
	{
		write_to_xyz_(File, *voids_ptr);
	}
	else
	{
		error();
	}
}
