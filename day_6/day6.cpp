#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <cmath>
#include <bits/stdc++.h> 
#include "../aoc.h"

int part_1(std::vector<std::string>* lines);
long part_2(std::vector<std::string>* lines);

int main (int argc, char *argv[]) 
{
	std::ifstream input_file;
	input_file.open("actual.txt");
	assert(input_file.is_open());
	std::vector<std::string> lines;
	std::string line;
	while ( std::getline (input_file,line) )
    {
      lines.push_back(line);
    }
	
    input_file.close();
	int result = part_2(&lines);
	std::cout << result << std::endl;
	return 0;
}

int part_1(std::vector<std::string>* lines)
{
    std::string line_1 = lines->at(0);
    size_t line_1_start = line_1.find(':');
    std::string line_1_sub = line_1.substr(line_1_start + 1);
    line_1_sub += ' ';
    std::string line_2 = lines->at(1);
    size_t line_2_start = line_2.find(':');
    std::string line_2_sub = line_2.substr(line_2_start + 1);
    line_2_sub += ' ';
    std::string delimiter = " ";
    std::vector<std::string> line_1_split = string_split(line_1_sub, delimiter);
    std::vector<std::string> line_2_split = string_split(line_2_sub, delimiter);
    std::vector<int> times;
    std::vector<int> distances;
    for (std::string str : line_1_split)
    {
        times.push_back(std::stoi(str));
    }
    for (std::string str : line_2_split)
    {
        distances.push_back(std::stoi(str));
    }
    int result = 1;
    for (int i = 0; i < times.size(); i++)
    {
        long time = times.at(i);
        long distance = distances.at(i);
        std::cout << "time = " << time << " distance = " << distance << std::endl;
        int det_int = (time * time) - (4 * distance);
        double det = sqrt(det_int);
        // std::cout << "det = " << det << std::endl;
        double min = (time - det) / 2;
        min += 0.000001;
        std::cout << "det = " << det << " det_int = " << det_int <<  std::endl;
        double min_ceil = ceil(min);
        std::cout << "min = " << min << " min_ceil = " << min_ceil << std::endl;
        double max = (time + det) / 2;
        max -= 0.000001;
        double max_floor = floor(max);
        std::cout << "max = " << max << " max_ceil = " << max_floor << std::endl;
        double ways_to_win = max_floor - min_ceil + 1;
        result *= ways_to_win;
    }
    return result;
}

long part_2(std::vector<std::string>* lines)
{
    std::string line_1 = lines->at(0);
    size_t line_1_start = line_1.find(':');
    std::string line_1_sub = line_1.substr(line_1_start + 1);
    std::string line_2 = lines->at(1);
    size_t line_2_start = line_2.find(':');
    std::string line_2_sub = line_2.substr(line_2_start + 1);
    long time = std::stol(line_1);
    long distance = std::stol(line_2);
    std::cout << "time = " << time << " distance = " << distance << std::endl;
    long det_int = (time * time) - (4 * distance);
    double det = sqrt(det_int);
    // std::cout << "det = " << det << std::endl;
    double min = (time - det) / 2;
    min += 0.000001;
    std::cout << "det = " << det << " det_int = " << det_int <<  std::endl;
    double min_ceil = ceil(min);
    std::cout << "min = " << min << " min_ceil = " << min_ceil << std::endl;
    double max = (time + det) / 2;
    max -= 0.000001;
    double max_floor = floor(max);
    std::cout << "max = " << max << " max_ceil = " << max_floor << std::endl;
    long ways_to_win = max_floor - min_ceil + 1;
    return ways_to_win;
}