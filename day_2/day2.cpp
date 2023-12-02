#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <string.h>
#include <array>

int part_1(std::vector<std::string>* lines);
int part_2(std::vector<std::string>* lines);
bool is_possible(std::string *game);
std::array<int,3> get_number(std::string *game);

int main (int argc, char *argv[]) 
{
	std::ifstream input_file;
	input_file.open("day2actual.txt");
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
    int result = 0;
    std::string delimiter = "; ";
    int id = 1;
    for (std::string line : *lines) 
    {   
        std::size_t pos = 0;
        std::size_t start = line.find(": ");
        line = line.substr(start + 2);
        std::cout << "line" << id << "= \"" << line << "\"" << std::endl;
        bool is_valid = true;
        while (is_valid && ((pos = line.find(delimiter)) != std::string::npos)) 
        {
            std::string token = line.substr(0, pos);
            // std::cout << token << std::endl;
            line.erase(0, pos + delimiter.length());
            token += ',';
            token += ' ';
            if (!is_possible(&token))
            {
                is_valid = false;
            }
        }
        if (is_valid)
        {
            result += id;
        }
        id ++;
    }
    return result;
}

bool is_possible(std::string *game)
{
    int red_cubes = 12;
    int green_cubes = 13;
    int blue_cubes = 14;
    std::size_t pos = 0;
    std::string delimiter = ", ";
    std::string space = " ";
    // std::cout << "game = \"" << *game << "\"" << std::endl;
    while ((pos = game->find(delimiter)) != std::string::npos) 
    {
        std::string token = game->substr(0, pos);
        // std::cout << token << std::endl;
        game->erase(0, pos + delimiter.length());
        // std::cout << "token = \"" << token << "\"" << std::endl; 
        // std::cout << "new_game = \"" << *game << "\"" << std::endl;
        std::size_t space_pos = token.find(space, 1);
        assert(space_pos != std::string::npos);
        std::string num_str = token.substr(0, space_pos);
        // std::cout << "space_pos = " << space_pos << std::endl;
        // std::cout << "num_str = \"" << num_str << "\""<< std::endl;
        std::string col_str = token.substr(space_pos + 1);
        int num = std::stoi(num_str);
        if (col_str.compare("blue") == 0) 
        {
            blue_cubes -= num;
            // std::cout << "blue cubes = " << blue_cubes << std::endl;
        }
        else if (col_str.compare("red") == 0)
        {
            red_cubes -= num;
            // std::cout << "red cubes = " << red_cubes << std::endl;
        }
        else if (col_str.compare("green") == 0)
        {
            green_cubes -= num;
            // std::cout << "green cubes = " << green_cubes << std::endl;
        }
        else {
            std::cout << "bad col_str = \"" << col_str << "\""<< std::endl;
            std::cout << "game = \"" << *game << "\""<< std::endl;
            assert(false);
        }
    }
    bool possible = red_cubes >= 0 && blue_cubes >= 0 && green_cubes >= 0;
    // std::cout << "The game was " << possible << std::endl;
    return possible;
}

int part_2(std::vector<std::string>* lines)
{
    int result = 0;
    std::string delimiter = "; ";
    int id = 1;
    for (std::string line : *lines) 
    {   
        std::size_t pos = 0;
        std::size_t start = line.find(": ");
        line = line.substr(start + 2);
        std::cout << "line" << id << " = \"" << line << "\"" << std::endl;
        int red_cubes = 0;
        int blue_cubes = 0;
        int green_cubes = 0;
        while (((pos = line.find(delimiter)) != std::string::npos)) 
        {
            std::string token = line.substr(0, pos);
            // std::cout << token << std::endl;
            line.erase(0, pos + delimiter.length());
            token += ',';
            token += ' ';
            std::array<int, 3> nums = get_number(&token);
            // std::cout << "result = " << nums[0] << nums[1] << nums[2] << std::endl;
            red_cubes = std::max(red_cubes, nums[0]);
            blue_cubes = std::max(blue_cubes, nums[1]);
            green_cubes = std::max(green_cubes, nums[2]);
        }
        int power = red_cubes * blue_cubes * green_cubes;
        result  += power;
        id ++;
    }
    return result;
}

std::array<int,3> get_number(std::string *game)
{
    int red_cubes = 0;
    int green_cubes = 0;
    int blue_cubes = 0;
    std::array<int, 3> ret_arr;
    std::size_t pos = 0;
    std::string delimiter = ", ";
    std::string space = " ";
    // std::cout << "game = \"" << *game << "\"" << std::endl;
    while ((pos = game->find(delimiter)) != std::string::npos) 
    {
        std::string token = game->substr(0, pos);
        // std::cout << token << std::endl;
        game->erase(0, pos + delimiter.length());
        // std::cout << "token = \"" << token << "\"" << std::endl; 
        // std::cout << "new_game = \"" << *game << "\"" << std::endl;
        std::size_t space_pos = token.find(space, 1);
        assert(space_pos != std::string::npos);
        std::string num_str = token.substr(0, space_pos);
        // std::cout << "space_pos = " << space_pos << std::endl;
        // std::cout << "num_str = \"" << num_str << "\""<< std::endl;
        std::string col_str = token.substr(space_pos + 1);
        int num = std::stoi(num_str);
        if (col_str.compare("blue") == 0) 
        {
            blue_cubes += num;
            // std::cout << "blue cubes = " << blue_cubes << std::endl;
        }
        else if (col_str.compare("red") == 0)
        {
            red_cubes += num;
            // std::cout << "red cubes = " << red_cubes << std::endl;
        }
        else if (col_str.compare("green") == 0)
        {
            green_cubes += num;
            // std::cout << "green cubes = " << green_cubes << std::endl;
        }
        else {
            std::cout << "bad col_str = \"" << col_str << "\""<< std::endl;
            std::cout << "game = \"" << *game << "\""<< std::endl;
            assert(false);
        }
    }
    ret_arr[0] = red_cubes;
    ret_arr[1] = blue_cubes;
    ret_arr[2] = green_cubes;
    return ret_arr;

}