#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <utility>
#include <unordered_set>

int part_1(std::vector<std::string> *lines);
int part_1_process_lines(std::string *line);

int main (int argc, char *argv[]) 
{
	std::ifstream input_file;
	input_file.open("day4sample.txt");
	assert(input_file.is_open());
	std::vector<std::string> lines;
	std::string line;
	while ( std::getline (input_file,line) )
    {
      lines.push_back(line);
    }
	
    input_file.close();
	int result = part_1(&lines);
	std::cout << result << std::endl;
	return 0;
}

int part_1(std::vector<std::string> *lines)
{
    int result = 0;
    for (std::string line : *lines)
    {
        result += part_1_process_lines(&line);
    }
    return result;
}

int part_1_process_lines(std::string *line)
{
    std::size_t card_delim = line->find(": ");
    std::size_t winning_pos = line->find("| ");
    std::string winning_numbers = line->substr(card_delim + 1, winning_pos - (card_delim + 1));
    std::string my_numbers = line->substr(winning_pos + 1);
    std::cout << "Winning_numbers = \"" << winning_numbers << "\"" << std::endl;
    std::cout << "my_numbers = \"" << my_numbers << "\"" << std::endl;
    my_numbers += ' ';

    std::unordered_set<int> winning_set;
    std::unordered_set<int> my_set;

    std::size_t pos = 0;
    std::string delimiter = " ";
    bool start = true;
    while ((pos = winning_numbers.find(delimiter)) != std::string::npos) 
    {
        std::string token = winning_numbers.substr(0, pos);
        winning_numbers.erase(0, pos + delimiter.length());
        std::cout << "token = \"" << token << "\"" << std::endl;
        if (!start)
        {
            winning_set.insert(std::stoi(token));
        }
        start = false;
    }
    pos = 0;
    start = true;
    while ((pos = my_numbers.find(delimiter)) != std::string::npos) 
    {
        std::string token = my_numbers.substr(0, pos);
        my_numbers.erase(0, pos + delimiter.length());
        if (!start)
        {
            my_set.insert(std::stoi(token));
        }
        start = false;
        
    }
    return 0;
}