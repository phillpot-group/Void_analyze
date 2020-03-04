//
// Created by Linyuan Shi on 10/18/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#ifndef VOID_ANALYZE_BIN_H
#define VOID_ANALYZE_BIN_H

#include <array>
#include <vector>
#include <cmath>
#include "atom.h"
#include "grid_info.h"

class bin {
	friend double
		bin_distance_n(const bin& bin_first, const bin& bin_second, const grid_info& gr_nf, bool is_periodic);

	friend bool
		bin_if_adjacent(const bin& bin_first, const bin& bin_second, const grid_info& gr_nf, bool is_periodic);


public:
	bin() = default;

	bin(const int& xbx, const int& yby, const int& zbz, std::array<double, 3> grid_dr);

	void set_bin(const int& xbx, const int& yby, const int& zbz, atom* atm_ptr,
		std::array<double, 3> grid_dr);

	void set_bin(const int& xbx, const int& yby, const int& zbz, std::array<double, 3> grid_dr);

	void add_atm_ptr(atom* atm_ptr);

	[[nodiscard]] std::vector<atom*> get_atoms() const;

	[[nodiscard]] std::array<double, 3> get_bin_position() const;

	[[nodiscard]] bool is_empty(const int cutoff) const;

	[[nodiscard]] std::array<int, 3>
		relative_bin_pos(const int& dx, const int& dy, const int& dz, const grid_info& gr_nf, bool is_periodic) const;

	[[nodiscard]] bool has_atoms() const;

private:
	int xbin = 0, ybin = 0, zbin = 0; // bin number
	double x = 0.0, y = 0.0, z = 0.0;  // bin position
	int void_no = -1;
	std::vector<atom*> bin_atoms;
	bool flag_surface = false;
};

double
bin_distance_n(const bin& bin_first, const bin& bin_second, const grid_info& gr_nf, bool is_periodic = true);

bool
bin_if_adjacent(const bin& bin_first, const bin& bin_second, const grid_info& gr_nf, bool is_periodic = true);

#endif //VOID_ANALYZE_BIN_H
