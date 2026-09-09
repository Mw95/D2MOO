#pragma once


#include <algorithm>
#include <filesystem>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>


template <typename T>
auto read_bin_file(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error("Cannot open file");
	}

	auto record_count = 0;
	file.read(reinterpret_cast<char*>(&record_count), sizeof(record_count));

	auto data = std::make_unique<T[]>(record_count);
	file.read(reinterpret_cast<char*>(data.get()), sizeof(T) * record_count);

	return std::pair{ record_count, std::move(data) };
}


template <typename T>
auto read_bin_file(const std::filesystem::path& path)
{
	return read_bin_file<T>(path.string());
}
