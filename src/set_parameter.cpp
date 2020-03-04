//
// Created by Linyuan Shi on 03/02/20.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#pragma once
#include  <iostream>
using std::cerr;
using std::endl;

#include  "color_codes.h"
#include  "functions.h"

void set_parameter(settings& config, const simulation_cell& sc, const cxxopts::ParseResult& parsed_options)
{
	if (parsed_options.count("circle"))
	{
		auto data = parsed_options["circle"].as<vector<double>>();
		double ox_c, oy_c, r;
		if (data.size() != 3)
		{
			cerr << RED << "Please specify the radius and position of the circle function" << RESET << endl;
			exit(EXIT_FAILURE);
		}
		ox_c = data[0];
		oy_c = data[1];
		r = data[2];
		auto f = [ox_c, oy_c, r, &sc](const double x, const double y, const double z)-> bool
		{
			return is_in_circle(ox_c, oy_c, r, sc, x, y, z);
		};
		config.set_filter_func(f);
		config.set_flag_rm_biggest_void(true);
		//config.set_filter_func(std::bind(is_in_circle, ox_c, oy_c, r, sc, std::placeholders::_1, std::placeholders::_2,
		//	std::placeholders::_3));
	}
};
