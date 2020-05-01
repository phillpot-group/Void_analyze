#pragma once
//
// Created by Linyuan Shi on 03/07/20.
// Copyright (c) 2019 University of Florida. All rights reserved.
//

#include "output.h"

class output_voids:public output
{
public:
	output_voids(std::filesystem::path&& s, std::shared_ptr<simulation_cell> scp): output(std::move(s), scp, 'V') {}
};
