#pragma once

#include "color_codes.h"

#include <filesystem>
#include "grid_info.h"
#include "output.h"
#include <utility>

class output_analysis_info : output
{
public:	
	output_analysis_info(std::filesystem::path&& s, const std::shared_ptr<simulation_cell>& scp, const grid_info& gr_nf_) :output(std::forward<std::filesystem::path>(s), scp, 'A'), gr_nf(gr_nf_) {};
	void write_info(const std::unique_ptr<std::vector<std::vector<const bin*>>>& vd_ptr, const std::unique_ptr<std::vector<std::vector<const bin*>>>& srfc_ptr) const;

private:
	const grid_info gr_nf;
};
