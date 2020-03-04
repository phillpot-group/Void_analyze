//
// Created by linyuan on 10/18/19.
//

#include "atom.h"

atom::atom(const string &name, const double &xx, const double &yy, const double &zz)
        : elementName(name), x(xx), y(yy), z(zz), xbin(0), ybin(0), zbin(0) {}

void atom::set_coordinates(const double &xx, const double &yy, const double &zz) {
    x = xx;
    y = yy;
    z = zz;
}

std::tuple<double, double, double> atom::get_coordinates() const {
    return std::make_tuple(x, y, z);
}