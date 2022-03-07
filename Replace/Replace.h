#pragma once
#include <string>
#include <fstream>

std::string Replace(const std::string& str, 
			const std::string& search, const std::string& replace)
{
	size_t pos{};
	std::string result{};

	while (pos < str.length())
	{
		if (search.empty())
			return str;

		size_t searchPos = str.find(search, pos);
		result.append(str, pos, searchPos - pos);

		if (searchPos != std::string::npos)
		{
			result.append(replace);
			pos = searchPos + search.length();
		}
		else
		{
			break;
		}
	}

	return result;
}

void CopyAndReplace(std::ifstream& in, std::ofstream& out, 
	const std::string& search, const std::string& replace)
{
	std::string line{};
		
	while (std::getline(in, line))
		out << Replace(line, search, replace) << "\n";
}