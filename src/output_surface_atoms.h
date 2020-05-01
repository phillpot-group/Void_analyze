#pragma once
//
// Created by Linyuan Shi on 03/07/20.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include "output.h"

class output_surface_atoms :public output
{
public:
	output_surface_atoms(std::filesystem::path&& s, std::shared_ptr<simulation_cell> scp) : output(std::move(s), scp, 'S') {}
	virtual void write_to_xyz_(std::ostream&, const std::vector<std::vector<const bin*>>&) const override;
};
