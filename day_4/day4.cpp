#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <utility>
#include <unordered_set>

int part_1(std::vector<std::string> *lines);
int part_1_process_lines(std::string *line);
int part_2(std::vector<std::string> *lines);
int part_2_process_lines(std::string *line);

int main (int argc, char *argv[]) 
{
	std::ifstream input_file;
	input_file.open("day4actual.txt");
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

    std::string token = "";
    for (char num : winning_numbers)
    {
        if (isdigit(num))
        {
            token += num;
            continue;
        }
        if (token.compare("") != 0)
        {
            winning_set.insert(std::stoi(token));
        }
        token = "";
    }
    token = "";
    for (char num : my_numbers)
    {
        if (isdigit(num))
        {
            token += num;
            continue;
        }
        if (token.compare("") != 0)
        {
            my_set.insert(std::stoi(token));
        }
        token = "";
    }
    int value = 0;
    for (int number : my_set)
    {
        if (winning_set.find(number) != winning_set.end())
        {
            if (value == 0)
            {
                value = 1;
            } 
            else 
            {
                value *= 2;
            }
        }
    }
    return value;
}

int part_2(std::vector<std::string> *lines)
{
    int result = 0;
    int card = 0;
    std::vector<int> copies;
    for (std::string line: *lines)
    {
        copies.push_back(1); // 1 copy of each card
    }
    for (std::string line : *lines)
    {
        std::cout << "Game = " << card + 1 << std::endl;
        int my_copies = copies.at(card);
        std::cout << "My_copies = " << my_copies << std::endl; 
        int cards_won = part_2_process_lines(&line);
        for (int i = card + 1; i < (cards_won + card + 1); i++)
        {
            copies.at(i) += my_copies;
            // std::cout << "copies[" << i + 1 << "] = " << copies.at(i) << std::endl;
        }
        card++;
    }
    int cards = 0;
    for (int number : copies)
    {
        cards += number;
    }
    return cards;
}

int part_2_process_lines(std::string *line)
{
    std::size_t card_delim = line->find(": ");
    std::size_t winning_pos = line->find("| ");
    std::string winning_numbers = line->substr(card_delim + 1, winning_pos - (card_delim + 1));
    std::string my_numbers = line->substr(winning_pos + 1);
    my_numbers += ' ';

    std::unordered_set<int> winning_set;
    std::unordered_set<int> my_set;

    std::string token = "";
    for (char num : winning_numbers)
    {
        if (isdigit(num))
        {
            token += num;
            continue;
        }
        if (token.compare("") != 0)
        {
            winning_set.insert(std::stoi(token));
        }
        token = "";
    }
    token = "";
    for (char num : my_numbers)
    {
        if (isdigit(num))
        {
            token += num;
            continue;
        }
        if (token.compare("") != 0)
        {
            my_set.insert(std::stoi(token));
        }
        token = "";
    }
    int value = 0;
    for (int number : my_set)
    {
        if (winning_set.find(number) != winning_set.end())
        {
            value++;
        }
    }
    std::cout << "value = " << value << std::endl;
    return value;
}