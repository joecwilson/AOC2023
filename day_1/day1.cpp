#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

int day_1(std::vector<std::string>* lines);
int day_2(std::vector<std::string>* lines);
char get_num(std::string *line);

int main (int argc, char *argv[]) 
{
	std::ifstream input_file;
	input_file.open("day1actual.txt");
	assert(input_file.is_open());
	std::vector<std::string> lines;
	std::string line;
	while ( std::getline (input_file,line) )
    {
      lines.push_back(line);
    }
	
    input_file.close();
	int result = day_2(&lines);
	std::cout << result << std::endl;
	return 0;
}

int day_1(std::vector<std::string>* lines) 
{
	int result = 0;
	for (std::string line : *lines)
	{
		std::string first;
		for (char digit : line)
		{
			if (std::isdigit(digit))
			{
				first += digit;
				break;
			}
		}
		for (std::size_t i = line.length()- 1; i >= 0; i--)
		{
			if (std::isdigit(line[i]))
			{
				first += line[i];
				break;
			}
		}
		// std::cout << first << "\n";
		int num = std::stoi(first);
		result += num;

	}

	return result;
}

int day_2(std::vector<std::string>* lines) 
{
	int result = 0;
	for (std::string line : *lines) 
	{
		std::string cal_str;
		std::cout << "line = " << line << std::endl;
		for (std::size_t i = 0; i < line.length(); i++)
		{
			// std::cout << "i = " << i << ", line[i] = " << line[i] << std::endl;
 			if (std::isdigit(line[i]))
			{
				cal_str += line[i];
				// std::cout << "found digit " << cal_str << std::endl;
				break;
			}
			std::string substr = line.substr(0, i + 1);
			// std::cout << "substr = " << substr << ", i = " << i << std::endl;
			char num = get_num(&substr);
			if (num != 'A')
			{
				cal_str += num;
				// std::cout << "found number " << cal_str << std::endl;
				break;
			}
		}
		for (std::size_t i = line.length()- 1; i >= 0; i--)
		{
			if (std::isdigit(line[i]))
			{
				cal_str += line[i];
				// std::cout << "found digit end " << cal_str << std::endl;
				break;
			}
			std::string substr = line.substr(i, line.length());
			char num = get_num(&substr);
			if (num != 'A')
			{
				cal_str += num;
				// std::cout << "found number end " << cal_str << std::endl;
				break;
			}
		}

		int cal_val = std::stoi(cal_str);
		result += cal_val;
	}
	return result;
}

char get_num(std::string *line)
{
	if (line->find("zero") != std::string::npos)
	{
		return 0;
	}
	if (line->find("one") != std::string::npos)
	{
		return '1';
	}
	if (line->find("two") != std::string::npos)
	{
		return '2';
	}
	if (line->find("three") != std::string::npos)
	{
		return '3';
	}
	if (line->find("four") != std::string::npos)
	{
		return '4';
	}
	if (line->find("five") != std::string::npos)
	{
		return '5';
	}
	if (line->find("six") != std::string::npos)
	{
		return '6';
	}
	if (line->find("seven") != std::string::npos)
	{
		return '7';
	}
	if (line->find("eight") != std::string::npos)
	{
		return '8';
	}
	if (line->find("nine") != std::string::npos)
	{
		return '9';
	}
	return 'A';
}