#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <bits/stdc++.h> 
#include "../aoc.h"

typedef struct seed_map
{
    long destination;
    long source;
    long range;
} seed_map_t;

typedef struct seed_range
{
    long start;
    long size;
    long range;
} seed_range_t;


int part_1(std::vector<std::string>* lines);
long part_2(std::vector<std::string>* lines);
bool compare_seed_map(seed_map_t map_1, seed_map_t map_2);
std::vector<seed_map_t>  get_seed_map(std::vector<std::string> *input, int start_line, int end_line);
std::vector<seed_map_t>  get_seed_map_pt_2(std::vector<std::string> *input, int start_line, int end_line);
long translocate_seed(long seed, std::vector<seed_map_t> *lookup_table);

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
    // Get seeds into a nice format
    std::string seed_line = lines->at(0);
    size_t seed_header_pos = seed_line.find(": ");
    std::string just_the_seeds = seed_line.substr(seed_header_pos + 2);
    just_the_seeds += ' ';

    size_t pos = 0;
    std::string delimiter = " ";
    std::vector<std::string> seeds_split = string_split(just_the_seeds, delimiter);
    
    std::vector<long> seeds_arr;
    for (std::string seed : seeds_split)
    {
        seeds_arr.push_back(std::stol(seed));
    }
    std::vector<int> empty_lines;
    for (size_t i = 0; i < lines->size(); i++)
    {
        if (lines->at(i).compare("") == 0)
        {
            empty_lines.push_back(i);
        }
    }
    
    empty_lines.push_back(lines->size());
    // for (int line : empty_lines)
    // {
    //     std::cout << "Line " << line + 1 << " is empty" << std::endl;
    // }
    int line_idx = 1;
    // Seed to soil
    // for (int loc : seeds_arr)
    // {
    //     std::cout << loc << std::endl;
    // }
    std::vector<seed_map_t> seed_to_soil = get_seed_map(lines, empty_lines.at(0) + 2, empty_lines.at(1));
    std::cout << "seed map generated" << std::endl;
    std::vector<long> soil_arr;
    for (long seed : seeds_arr)
    {
        soil_arr.push_back(translocate_seed(seed, &seed_to_soil));
    }

    // soil to fertilizer
    std::vector<seed_map_t> soil_to_fertilizer = get_seed_map(lines, empty_lines.at(1) + 2, empty_lines.at(2));
    std::cout << "fertilizer map generated" << std::endl;
    std::vector<long> fertilizer_arr;
    for (long seed : soil_arr)
    {
        fertilizer_arr.push_back(translocate_seed(seed, &soil_to_fertilizer));
    }
    // fertilzier to water
    std::vector<seed_map_t> fertilizer_to_water = get_seed_map(lines, empty_lines.at(2) + 2, empty_lines.at(3));
    std::cout << "water map generated" << std::endl;
    std::vector<long> water_arr;
    for (long seed : fertilizer_arr)
    {
        water_arr.push_back(translocate_seed(seed, &fertilizer_to_water));
    }
    // water to light
    std::vector<seed_map_t> water_to_light = get_seed_map(lines, empty_lines.at(3) + 2, empty_lines.at(4));
     std::cout << "light map generated" << std::endl;
    std::vector<long> light_arr;
    for (long seed : water_arr)
    {
        light_arr.push_back(translocate_seed(seed, &water_to_light));
    }

    std::vector<seed_map_t> light_to_temperature = get_seed_map(lines, empty_lines.at(4) + 2, empty_lines.at(5));
    std::cout << "temperatrue map generated" << std::endl;
    std::vector<long> temp_arr;
    for (long seed : light_arr)
    {
        temp_arr.push_back(translocate_seed(seed, &light_to_temperature));
    }
    // temp to humidity
    std::vector<seed_map_t> temperature_to_humidity = get_seed_map(lines, empty_lines.at(5) + 2, empty_lines.at(6));
    std::cout << "humidity map generated" << std::endl;
    std::vector<long> hum_arr;
    for (long seed : temp_arr)
    {
        hum_arr.push_back(translocate_seed(seed, &temperature_to_humidity));
    }

    std::vector<seed_map_t> humidity_to_location = get_seed_map(lines, empty_lines.at(6) + 2, empty_lines.at(7));
    std::cout << "location map generated" << std::endl;
    std::vector<long> loc_arr;
    for (long seed : hum_arr)
    {
        loc_arr.push_back(translocate_seed(seed, &humidity_to_location));
    }
    // for (long loc : loc_arr)
    // {
    //     std::cout << loc << std::endl;
    // }
    sort(loc_arr.begin(), loc_arr.end());
    return loc_arr.at(0);
}

std::vector<seed_map_t>  get_seed_map(std::vector<std::string> *input, int start_line, int end_line)
{
    std::vector<seed_map_t> ret;
    std::string space = " ";
    for (int i = start_line; i < end_line; i++)
    {
        std::string input_line = input->at(i);
        input_line += ' ';
        // std::cout << "input_line = \"" << input_line << "\"" << std::endl;
        std::vector<std::string> line_split = string_split(input_line, space);
        // std::cout << line_split.size() << std::endl;
        seed_map_t map = {
            std::stol(line_split.at(0)), 
            std::stol(line_split.at(1)), 
            std::stol(line_split.at(2))
        };
        // std::cout << "Map destination " << map.destination << " source " << map.source << " range " << map.range << std::endl;
        ret.push_back(map);
    }
    // std::sort(ret.begin(), ret.end(), compare_seed_map);
    return ret;
}

bool compare_seed_map(seed_map_t map_1, seed_map_t map_2)
{
    return map_1.source < map_2.source;
}

long translocate_seed(long seed, std::vector<seed_map_t> *lookup_table)
{
    long result = 0;
    for (seed_map_t table : *lookup_table)
    {
        if (table.source <= seed && table.source + table.range >= seed)
        {
            // std::cout << "table source = " << table.source;
            // std::cout << " table.dest  = " << table.destination;
            // std::cout << " seed  = " << seed;
            // std::cout << " range = " << table.range << std::endl;
            return (seed - table.source) + table.destination;
        }
    }
    return seed;
}



long part_2(std::vector<std::string>* lines)
{
    long result = 0;
    std::string seed_line = lines->at(0);
    size_t seed_header_pos = seed_line.find(": ");
    std::string just_the_seeds = seed_line.substr(seed_header_pos + 2);
    just_the_seeds += ' ';

    size_t pos = 0;
    std::string delimiter = " ";
    std::vector<std::string> seeds_split = string_split(just_the_seeds, delimiter);
    std::vector<seed_range_t> seed_arr;
    for (size_t i = 0; i < seeds_split.size(); i++)
    {
        seed_range_t range = {std::stol(seeds_split.at(0)), std::stol(seeds_split.at(1))};
        seed_arr.push_back(range);
    }


    std::vector<int> empty_lines;
    for (size_t i = 0; i < lines->size(); i++)
    {
        if (lines->at(i).compare("") == 0)
        {
            empty_lines.push_back(i);
        }
    }
    
    empty_lines.push_back(lines->size());

    std::vector<seed_map_t> seed_to_soil = get_seed_map_pt_2(lines, empty_lines.at(0) + 2, empty_lines.at(1));
    std::vector<seed_map_t> soil_to_fertilizer = get_seed_map_pt_2(lines, empty_lines.at(1) + 2, empty_lines.at(2));
    std::vector<seed_map_t> fertilizer_to_soil = get_seed_map_pt_2(lines, empty_lines.at(2) + 2, empty_lines.at(3));
    std::vector<seed_map_t> water_to_light = get_seed_map_pt_2(lines, empty_lines.at(3) + 2, empty_lines.at(4));
    std::vector<seed_map_t> light_to_temperature = get_seed_map_pt_2(lines, empty_lines.at(4) + 2, empty_lines.at(5));
    std::vector<seed_map_t> temperature_to_humidity = get_seed_map_pt_2(lines, empty_lines.at(5) + 2, empty_lines.at(6));
    std::vector<seed_map_t> humidity_to_location = get_seed_map_pt_2(lines, empty_lines.at(6) + 2, empty_lines.at(7));

    while (true)
    {
        long location = result;
        // std::cout << "location = " << location << std::endl;
        location = translocate_seed(location, &humidity_to_location);
        // std::cout << "humdidity = " << location << std::endl;
        location = translocate_seed(location, &temperature_to_humidity);
        // std::cout << "temperature = " << location << std::endl;
        location = translocate_seed(location, &light_to_temperature);
        // std::cout << "light = " << location << std::endl;
        location = translocate_seed(location, &water_to_light);
        // std::cout << "water = " << location << std::endl;
        location = translocate_seed(location, &fertilizer_to_soil);
        // std::cout << "fertilizer = " << location << std::endl;
        location = translocate_seed(location, &soil_to_fertilizer);
        // std::cout << "soil = " << location << std::endl;
        location = translocate_seed(location, &seed_to_soil);
        // std::cout << "seed = " << location << std::endl;
        // std::cout << std::endl;
        for ( seed_range_t range : seed_arr)
        {
            if (range.start <= location && range.start + range.size >= location)
            {
                std::cout << result << std::endl;
                return result;
            }
        }
        if (result % 10000 == 0)
        {
            std::cout << "working on location " << result << std::endl;
        }
        result++;
    }

    // return result;
    // Can get the maps, but need to go backwards
}

std::vector<seed_map_t>  get_seed_map_pt_2(std::vector<std::string> *input, int start_line, int end_line)
{
    std::vector<seed_map_t> ret;
    std::string space = " ";
    for (int i = start_line; i < end_line; i++)
    {
        std::string input_line = input->at(i);
        input_line += ' ';
        std::vector<std::string> line_split = string_split(input_line, space);
        seed_map_t map = {
            std::stol(line_split.at(1)), 
            std::stol(line_split.at(0)), 
            std::stol(line_split.at(2))
        };
        ret.push_back(map);
    }
    return ret;
}