//
// Created by Linyuan Shi on 10/18/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include "bin.h"

bin::bin(const int& xbx, const int& yby, const int& zbz, const std::array<double, 3> grid_dr) :
	xbin(xbx), ybin(yby), zbin(zbz), void_no(-1)
{
	x = grid_dr[0] * (xbin + 0.5);
	y = grid_dr[1] * (ybin + 0.5);
	z = grid_dr[2] * (zbin + 0.5);
}

void bin::set_bin(const int& xbx, const int& yby, const int& zbz, atom* const atm_ptr,
                  const std::array<double, 3> grid_dr)
{
	set_bin(xbx, yby, zbz, grid_dr);
	add_atm_ptr(atm_ptr);
}

void bin::add_atm_ptr(atom* atm_ptr)
{
	bin_atoms.push_back(atm_ptr);
}

void bin::set_bin(const int& xbx, const int& yby, const int& zbz, std::array<double, 3> grid_dr)
{
	xbin = xbx;
	ybin = yby;
	zbin = zbz;
	x = grid_dr[0] * (xbin + 0.5);
	y = grid_dr[1] * (ybin + 0.5);
	z = grid_dr[2] * (zbin + 0.5);
}

std::vector<atom*> bin::get_atoms() const
{
	return bin_atoms;
}

std::array<double, 3> bin::get_bin_position() const
{
	return {x, y, z};
}

bool bin::is_empty(const int cutoff) const
{
	return bin_atoms.size() < cutoff;
}

std::array<int, 3> bin::relative_bin_pos(const int& dx, const int& dy, const int& dz, const grid_info& gr_nf,
                                         const bool is_periodic) const
{
	auto [nx, ny, nz] = gr_nf.get_grid_no();
	int bin_newx = xbin + dx;
	int bin_newy = ybin + dy;
	int bin_newz = zbin + dz;
	if (is_periodic)
	{
		auto pbc_func = [](int& bin_new, const int& nbin) -> void
		{
			if (bin_new < 0) { bin_new += nbin; }
			else if (bin_new >= nbin) { bin_new -= nbin; }
		};
		pbc_func(bin_newx, nx);
		pbc_func(bin_newy, ny);
		pbc_func(bin_newz, nz);
	}
	return std::array<int, 3>{bin_newx, bin_newy, bin_newz};
}

bool bin::has_atoms() const
{
	return !bin_atoms.empty();
}

double bin_distance_n(const bin& bin_first, const bin& bin_second, const grid_info& gr_nf, const bool is_periodic)
{
	auto [nx, ny, nz] = gr_nf.get_grid_no();
	int dxbin = std::abs(bin_first.xbin - bin_second.xbin);
	int dybin = std::abs(bin_first.ybin - bin_second.ybin);
	int dzbin = std::abs(bin_first.zbin - bin_second.zbin);
	if (is_periodic)
	{
		if (dxbin > nx / 2) { dxbin = nx - dxbin; }
		if (dybin > ny / 2) { dybin = ny - dybin; }
		if (dzbin > nz / 2) { dzbin = nz - dzbin; }
	}
	return std::sqrt(dxbin * dxbin + dybin * dybin + dzbin * dzbin);
}

bool
bin_if_adjacent(const bin& bin_first, const bin& bin_second, const grid_info& gr_nf, const bool is_periodic)
{
	auto [nx, ny, nz] = gr_nf.get_grid_no();
	int dxbin = std::abs(bin_first.xbin - bin_second.xbin);
	int dybin = std::abs(bin_first.ybin - bin_second.ybin);
	int dzbin = std::abs(bin_first.zbin - bin_second.zbin);
	if (is_periodic)
	{
		if (dxbin > nx / 2) { dxbin = nx - dxbin; }
		if (dybin > ny / 2) { dybin = ny - dybin; }
		if (dzbin > nz / 2) { dzbin = nz - dzbin; }
	}
	return dxbin * dxbin + dybin * dybin + dzbin * dzbin == 1;
}
