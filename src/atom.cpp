//
// Created by linyuan on 10/18/19.
//

#include "atom.h"
#include <cmath>

double distance_atom(const atom& lhs, const atom& rhs, std::shared_ptr<simulation_cell> sc_ptr)
{
	const auto [lx, ly, lz] = sc_ptr->get_vectors();
	double delta_x = lhs.x - rhs.x;
	double delta_y = lhs.y - rhs.y;
	double delta_z = lhs.z - rhs.z;
	if (delta_x > lx / 2)
		delta_x = lx - delta_x;
	if (delta_y > ly / 2)
		delta_y = ly - delta_y;
	if (delta_z > lz / 2)
		delta_z = lz - delta_z;
	//double dist_square = (lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y) + (lhs.z - rhs.z) * (lhs.z - rhs.z);
	double dist_square = delta_x * delta_x + delta_y * delta_y + delta_z * delta_z;
	return sqrt(dist_square);
}

atom::atom(const string& name, const double& xx, const double& yy, const double& zz)
	: elementName(name), x(xx), y(yy), z(zz), xbin(0), ybin(0), zbin(0) {}

void atom::set_coordinates(const double& xx, const double& yy, const double& zz) {
	x = xx;
	y = yy;
	z = zz;
}

std::tuple<double, double, double> atom::get_coordinates() const {
	return std::make_tuple(x, y, z);
}