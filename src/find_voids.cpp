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

#include <iostream>
using std::cout;
using std::endl;

#include "functions.h"



//typedef adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
//        property<vertex_name_t, const bin *>> Graph;
typedef adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::vertex_iterator Vertex_iterator;

vector<vector<const bin*>>
find_voids(const vector<const bin*>& empty_bins, const grid_info& gr_nf, const settings& config)
{
#ifdef DEBUG
	cout << "Begin to find voids" << endl;
#endif
	Graph g_bin(empty_bins.size());
	const bool flag_periodic = config.isPeriodic();
	const int empty_bins_size = empty_bins.size();
#ifdef DEBUG
	cout << "Begin to construct edges" << endl;
#endif
	for (int i = 0; i < empty_bins_size; ++i)
		for (int j = i + 1; j < empty_bins_size; ++j) {
			if (bin_if_adjacent(*empty_bins[i], *empty_bins[j], gr_nf, flag_periodic)) {
				boost::add_edge(i, j, g_bin);
			}
		}
#ifdef DEBUG
	cout << "Finish constructing edges" << endl;
#endif
	std::vector<int> component(boost::num_vertices(g_bin));
	//property_map<Vertex, Graph::vertices_size_type> c;
	int n = boost::connected_components(g_bin, &component[0]);
	vector<vector<const bin*>> bin_voids(n);
	for (int i = 0; i != component.size(); ++i) {
		bin_voids[component[i]].push_back(empty_bins[i]);
	}
#ifdef DEBUG
	cout << "Finish finding voids" << endl;
#endif
	return bin_voids;
}
