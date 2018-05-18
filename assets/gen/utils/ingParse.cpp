//ingParse.cpp: Simple utility for generating a list of (priced) standalone unique* ingredients from a menu.
//should be run when adding new recipes to the menu (for now) - read 'with new ingredients'

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

std::vector<std::string> getStringToken(const std::string& src, const char token)
{
	std::vector<std::string> stringToken;
	int pos = 0, lastPos = 0;

	lastPos = src.find_first_not_of(token, 0);
	pos = src.find_first_of(token, lastPos);
	auto npos = std::string::npos;

	while (npos != pos || npos != lastPos)
	{
		stringToken.push_back(src.substr(lastPos, pos - lastPos));
		lastPos = src.find_first_not_of(token, pos);
		pos = src.find_first_of(token, lastPos);
	}

	return stringToken;
}

const int find(const std::string & toFind, const std::vector <std::string> & src)
{
	for (size_t i = 0; i < src.size(); i++)
	{
		if (src[i] == toFind)
		{
			return i;
		}

	}
	return -1;
}

void trimWhitespace(std::string& src)
{
	src.erase(src.find_last_not_of(" ") + 1);
	src.erase(0, src.find_first_not_of(" "));
}

int main(int argc, char** argv)
{
	if (argc < 2) { return -1; }

	std::string file(argv[1]);
	std::string parsedFile(file.substr(0, file.find_last_of(".")) + ".parsed");

	std::ifstream fin(file);
	std::ofstream fout(parsedFile);

	if (!fin.is_open() || !fout.is_open()){ return -1; }

	const char delim[3] = { ',', '$', '|' };
	const char c_com = '#';
	std::string lineSrc;
	std::vector<std::string> toWrite;

	while (!fin.eof())
	{
		lineSrc.clear();
		std::getline(fin, lineSrc);

		// ignore comments
		bool isComment = false;
		if (lineSrc[0] == c_com || lineSrc.empty() || lineSrc[0]=='$'){ isComment = true; }

		if (!isComment)
		{
			std::vector<std::string> strTok = getStringToken(lineSrc, delim[0]);
			for (auto & elem : strTok)
			{
				auto temp = getStringToken(elem, delim[2]);
				elem = temp[0];
				trimWhitespace(elem);
				elem[0] = tolower(elem[0]);
				if (find(elem, toWrite) < 0)
				{
					toWrite.push_back(elem);
				}
			}
		}
	}

	fin.close();

	if (toWrite.empty()) { return -1; }

	srand(time(nullptr));

	for (const auto & elem : toWrite)
	{
		//add random product prices
		fout << elem <<" | "<< 0.05*elem.length()+ rand() % elem.size()<<"\n";
	}

	fout.close();

	return 0;
}
