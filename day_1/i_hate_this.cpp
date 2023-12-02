char get_num(std::string *line)
{
	if (line->find("zero") != std::string::npos)
	{
		return '0';
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