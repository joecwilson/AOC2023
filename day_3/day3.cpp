#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

typedef struct part_number
{
    int number;
    int start_col;
    int end_col;
    int row;
    bool used = false;
} part_number_t;

typedef struct symbol
{
    int row;
    int col;
    char symbol;
} symbol_t;

int part_1(std::vector<std::string>* lines);
int part_2(std::vector<std::string>* lines);

int main (int argc, char *argv[]) 
{
	std::ifstream input_file;
	input_file.open("day3actual.txt");
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
    std::vector<part_number_t> part_numbers;
    std::vector<symbol_t> symbols;
    for (size_t i = 0; i < lines->size(); i++) 
    { 
        std::string line = lines->at(i);
        size_t token_start = 0;
        bool in_digit = false;
        for (size_t j = 0; j < line.length(); j++)
        {
            if (in_digit && !isdigit(line[j]))
            {
                part_number_t new_part = 
                {
                    stoi(line.substr(token_start, j)), // the number represented
                    token_start,
                    j - 1,
                    i,
                    false,
                };
                in_digit = false;
                part_numbers.push_back(new_part);
                token_start = j;
                j--;
            }
            else if (line[j] == '.')
            {
                token_start = j;
                in_digit = false;
            }
            else if (isdigit(line[j]))
            {
                if (!in_digit)
                {
                    token_start = j;
                    in_digit = true;
                }
            }
            else 
            {
                token_start = j;
                in_digit = false;
                symbol_t symbol = 
                {
                    i,
                    j,
                    line[j],
                };
                symbols.push_back(symbol);
            }

        }
        if (in_digit)
            {
                part_number_t new_part = 
                {
                    stoi(line.substr(token_start, line.length())), // the number represented
                    token_start,
                    line.length() - 1,
                    i,
                    false,
                };
                in_digit = false;
                part_numbers.push_back(new_part);
            }
    }

    int sum = 0;
    // Part numbers and symbols are posted, they are sorted by row number

    for (part_number_t number : part_numbers)
    {
        std::cout << number.number << std::endl;
    }
    size_t start_cutoff = 0;
    for (symbol_t symbol : symbols)
    {
        bool row_valid = true;
        std::cout << "symbol = " << symbol.symbol << std::endl;
        for (size_t i = start_cutoff; i < part_numbers.size() && row_valid; i++)
        {
            // Maybe determine how to update start cutoff
            part_number_t part_number = part_numbers.at(i);
            // std::cout << part_number.used << std::endl;
            if (part_number.row < symbol.row - 1)
            {
                // std::cout << "row too small for part number " << part_number.number << std::endl;
                start_cutoff = i + 1;
            }
            else if (part_number.row > symbol.row + 1)
            {
                // std::cout << "row too big for part number " << part_number.number << std::endl;
                row_valid = false;
            }
            else if (!part_number.used && 
                     !(part_number.start_col - 1 > symbol.col) && 
                     !(part_number.end_col + 1 < symbol.col))
            {
                part_numbers[i].used = true;
                // part_number.used = true;
                sum += part_number.number;
                // std::cout << "number = " << part_number.number << std::endl;
                // std::cout << "end_col = " << part_number.end_col << std::endl;
                // std::cout << "start_col = " << part_number.start_col << std::endl;
                // std::cout << "row = " << part_number.row << std::endl;
            }
        }
    }
    return sum;
}

int part_2(std::vector<std::string>* lines)
{
    std::vector<part_number_t> part_numbers;
    std::vector<symbol_t> symbols;
    for (size_t i = 0; i < lines->size(); i++) 
    { 
        std::string line = lines->at(i);
        size_t token_start = 0;
        bool in_digit = false;
        for (size_t j = 0; j < line.length(); j++)
        {
            if (in_digit && !isdigit(line[j]))
            {
                part_number_t new_part = 
                {
                    stoi(line.substr(token_start, j)), // the number represented
                    token_start,
                    j - 1,
                    i,
                    false,
                };
                in_digit = false;
                part_numbers.push_back(new_part);
                token_start = j;
                j--;
            }
            else if (line[j] == '.')
            {
                token_start = j;
                in_digit = false;
            }
            else if (isdigit(line[j]))
            {
                if (!in_digit)
                {
                    token_start = j;
                    in_digit = true;
                }
            }
            else 
            {
                token_start = j;
                in_digit = false;
                symbol_t symbol = 
                {
                    i,
                    j,
                    line[j],
                };
                symbols.push_back(symbol);
            }

        }
        if (in_digit)
            {
                part_number_t new_part = 
                {
                    stoi(line.substr(token_start, line.length())), // the number represented
                    token_start,
                    line.length() - 1,
                    i,
                    false,
                };
                in_digit = false;
                part_numbers.push_back(new_part);
            }
    }

    int sum = 0;
    // Part numbers and symbols are posted, they are sorted by row number

    size_t start_cutoff = 0;
    for (symbol_t symbol : symbols)
    {
        bool row_valid = true;
        bool is_gear = symbol.symbol == '*';
        int gear_ratio = 1;
        int gears_multiplied = 0;
        std::cout << "symbol = " << symbol.symbol << std::endl;
        for (size_t i = start_cutoff; i < part_numbers.size() && row_valid; i++)
        {
            // Maybe determine how to update start cutoff
            part_number_t part_number = part_numbers.at(i);
            if (part_number.row < symbol.row - 1)
            {
                start_cutoff = i + 1;
            }
            else if (part_number.row > symbol.row + 1)
            {
                row_valid = false;
            }
            else if (is_gear && !part_number.used && 
                     !(part_number.start_col - 1 > symbol.col) && 
                     !(part_number.end_col + 1 < symbol.col))
            {
                part_numbers[i].used = true;
                gears_multiplied += 1;

                // part_number.used = true;
                gear_ratio *= part_number.number;
                // std::cout << "number = " << part_number.number << std::endl;
                // std::cout << "end_col = " << part_number.end_col << std::endl;
                // std::cout << "start_col = " << part_number.start_col << std::endl;
                // std::cout << "row = " << part_number.row << std::endl;
            }
        }
        if (is_gear && gears_multiplied == 2)
        {
            sum += gear_ratio;
        }
    }
    return sum;
}