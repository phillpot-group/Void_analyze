#pragma once
//
// Created by Linyuan Shi on 03/07/20.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>

#include "bin.h"
#include "simulation_cell.h"

class output
{
public:
	output(std::filesystem::path&& s, const std::shared_ptr<simulation_cell>& scp, const char sym):file_name(std::move(s)), sc_ptr(scp), symbol(sym) {}
	void error() const;
	void write_xyz(const std::unique_ptr<std::vector<std::vector<const bin*>>>&) const;
	virtual ~output() {};

protected:
	//protected member functions
	virtual void write_to_xyz_(std::ostream&, const std::vector<std::vector<const bin*>>&) const;
	//protected members
	std::filesystem::path file_name;
	std::shared_ptr<simulation_cell> sc_ptr;
	char symbol;
};
