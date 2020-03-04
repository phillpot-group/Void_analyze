
//
// Created by Linyuan Shi on 10/18/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#ifndef VOID_ANALYZE_ATOM_H
#define VOID_ANALYZE_ATOM_H

#include <string>
#include <tuple>

using std::string;

class atom {
public:
    atom() = default;

    atom(const string &name, const double &xx, const double &yy, const double &zz);

    void set_coordinates(const double &xx, const double &yy, const double &zz);

    std::tuple<double, double, double> get_coordinates() const;

private:
    string elementName;
    double x, y, z;
    int xbin, ybin, zbin;
};


#endif //VOID_ANALYZE_ATOM_H
