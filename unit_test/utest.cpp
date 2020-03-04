//
// Created by Linyuan Shi on 1/15/20.
// Copyright (c) 2020 University of Florida. All rights reserved.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;

#include <utility>

#include <vector>

using std::vector;

#include "Argv.h"
#include "settings.h"
#include "parse_options.cpp"
#include "simulation_cell.cpp"

template<typename Tuple, typename Vec, size_t... Is>
bool compare_tuple(Tuple&& t, Vec&& v, std::index_sequence<Is...>&&) {
	return ((std::get<Is>(t) == v[Is]) &&...);
}

template<size_t N, typename Tuple>
bool compare(Tuple&& t, std::vector<double>&& il) {
	return compare_tuple(std::forward<Tuple>(t), std::forward<std::vector<double>>(il), std::make_index_sequence<N>());
}

template<typename T>
bool compare(const vector<T>& vec, std::initializer_list<T>&& il)
{
	if (vec.size() != il.size())
	{
		return false;
	}
	return std::equal(vec.begin(), vec.end(), il.begin());
}

TEST_CASE("Check CLI option parse function") {
	SUBCASE("Basic options") {
		Argv argv({
						  "tester",
						  "-f",
						  "test.xyz",
						  "--circle",
						  "15,20,25"
			});
		auto result = parse(argv.argc(), argv.argv());
		CHECK(result.count("f") == 1);
		CHECK(result.count("file") == 1);
		CHECK(result.count("circle") == 1);
		CHECK(result["f"].as<string>() == "test.xyz");
		CHECK(result["file"].as<string>() == "test.xyz");
		CHECK(compare(result["circle"].as<vector<double>>(), { 15.0, 20.0, 25.0 }));
	}
}

TEST_CASE("Check simulation_cell class") {
	simulation_cell sc("./test/thin_ovito.xyz");
	CHECK(compare<3>(sc.get_vectors(), { 280.0, 280.0, 76.5 }));
	CHECK(compare<3>(sc.get_origin(), { -140.0, -140.0, -38.25 }));
}

TEST_CASE("Setting class")
{
	std::filesystem::path structure_path = std::filesystem::canonical("./test/thin_ovito.xyz");
	settings config(structure_path.string());
	SUBCASE("File system related functions") {
		CHECK(config.get_path_folder_input() == structure_path.parent_path());
		CHECK(config.get_path_structure_input() == structure_path);
		CHECK(config.get_path_folder_output() == structure_path.parent_path());
		config.set_path_folder_output(".");
		CHECK(config.get_path_folder_output() == structure_path.parent_path().parent_path());
	}
	SUBCASE("Flag related functions") {
		CHECK(config.get_flag_rm_bigggest_void() == false);
		config.set_flag_rm_biggest_void(true);
		CHECK(config.get_flag_rm_bigggest_void() == true);
	}
}
