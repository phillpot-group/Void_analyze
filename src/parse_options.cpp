//
// Created by Linyuan Shi on 1/15/20.
// Copyright (c) 2020 University of Florida. All rights reserved.
//
#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include "cxxopts.hpp"
#include "color_codes.h"



cxxopts::ParseResult parse(int argc, char** argv) {
	cxxopts::Options options("Void_analyze", "Carbon fiber pore size distribution analysis program.");
	options.add_options()
		("h, help", "Print help")
		("f, file", "Carbon fiber structure file position", cxxopts::value<string>())
		("o,output", "The folder which will be used to store output files", cxxopts::value<string>())
		("circle", "Specify the coordinates of the center of the circle and the radius, ie. (center_x, center_y, radius)",
			cxxopts::value<vector<double>>());
	auto result = options.parse(argc, argv);
	if (result.count("help")) {
		cout << options.help() << endl;
		exit(EXIT_SUCCESS);
	}
	if (!result.count("f"))
	{
		cerr << RED << "please specify the position of the carbon fiber structure file." << RESET << endl;
		exit(EXIT_FAILURE);
	}
	return result;
}
