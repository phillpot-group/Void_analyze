//
// Created by Linyuan Shi on 10/19/19.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_traits.hpp>
using boost::adjacency_list;
using boost::property;
using boost::property_map;
using boost::vertex_name;
using boost::vertex_name_t;
using boost::graph_traits;

#include <memory>
using std::unique_ptr;

#include <iostream>
using std::cout;
using std::endl;

#include "functions.h"

#ifdef DEBUG
#include "timer.h"
#endif



//typedef adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
//        property<vertex_name_t, const bin *>> Graph;
typedef adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::vertex_iterator Vertex_iterator;
typedef std::pair<int, int> Edge;

auto find_voids(const vector<const bin*>& empty_bins, const grid_info& gr_nf, const settings& config) ->unique_ptr<vector<vector<const bin*>>>
{
#ifdef DEBUG
	const timer timer_voids(std::cout, "Finding voids");
#endif
	const int empty_bins_size = empty_bins.size();
	const bool flag_periodic = config.isPeriodic();
#ifdef DEBUG
	const timer timer_edges(std::cout, "Constructing edges");
#endif
	vector<Edge> edges;
	for (int i = 0; i < empty_bins_size; ++i)
		for (int j = i + 1; j < empty_bins_size; ++j) {
			if (bin_if_adjacent(*empty_bins[i], *empty_bins[j], gr_nf, flag_periodic)) {
				edges.emplace_back(i, j);
			}
		}
	const Graph g_bin(edges.begin(), edges.end(), empty_bins_size);
#ifdef DEBUG
	timer_edges.span();
#endif
	std::vector<int> component(boost::num_vertices(g_bin));
	int n = boost::connected_components(g_bin, &component[0]);
	auto bin_voids_ptr = std::make_unique<vector<vector<const bin*>>>(n);
	for (size_t i = 0; i != component.size(); ++i) {
		(*bin_voids_ptr)[component[i]].push_back(empty_bins[i]);
	}

#ifdef DEBUG
	timer_voids.span();
#endif
	return bin_voids_ptr;
}
