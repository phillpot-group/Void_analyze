//
// Created by Linyuan Shi on 10/23/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include "functions.h"

bool is_in_circle(double ox_circle, double oy_circle, const double radius, const simulation_cell&sc, const double x, const double y, const double z)
{
	auto [ox, oy, oz] = sc.get_origin();
	ox_circle -= ox;
	oy_circle -= oy;
	return (x - ox_circle) * (x - ox_circle) + (y - oy_circle) * (y - oy_circle) < radius * radius;
}
