#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Pizza.h"

//template<>
//class Parser<Pizza>;

template<class T>
class Parser
{
public:
	enum class Status
	{
		ERR_PARSE,		//parsing error
		ERR_FOPEN,		//file access error
		ERR_FEMPTY,		//file is empty
		PARSEOK,		//parsing succesful
	};

private:
	//file to parse
	std::string fileToParse;

	//delimiting characters for string tokens
	const char delim[3] = { ',', '$', '|' };
	//line comment character
	const char c_com = '#';

	//array where parsed data is stored
	std::vector<std::string> toWrite;

	inline bool isIgnored(const std::string& src) const
	{
		return(src[0] == c_com || src.empty());
	}

public:
	Parser(const std::string & toParse);
	~Parser();

	inline const int find(const std::string & toFind, const std::vector <std::string> & src) const
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

	inline Status getParsedData(std::vector<std::string> & toReturn) const
	{
		if(toWrite.empty()) 
		{ 
			return Status::ERR_PARSE;
		}
		toReturn = toWrite;
		return Status::PARSEOK;
	}

	std::vector<std::string> getStringToken(const std::string& src, const char token);
	void trimWhitespace(std::string& src);

	const Status parseFile();

};

template<class T>
Parser<T>::Parser(const std::string & toParse) : fileToParse(toParse)
{

}

template<class T>
Parser<T>::~Parser(){}

template<class T>
std::vector<std::string> Parser<T>::getStringToken(const std::string& src, const char token)
{
	std::vector<std::string> stringToken;
	size_t pos = 0, lastPos = 0;

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

template<class T>
void Parser<T>::trimWhitespace(std::string& src)
{
	src.erase(src.find_last_not_of(" ") + 1);
	src.erase(0, src.find_first_not_of(" "));
}

template<>
const Parser<Ingredient>::Status Parser<Ingredient>::parseFile()
{
	std::ifstream fin(fileToParse);

	if (fin.is_open())
	{
		//buffer for storing each line
		std::string lineSrc;

		while (!fin.eof())
		{
			//lineSrc.clear();
			std::getline(fin, lineSrc);

			if (!isIgnored(lineSrc))
			{
				trimWhitespace(lineSrc);
				if (find(lineSrc, toWrite) < 0)
				{
					toWrite.push_back(lineSrc);
				}
			}
		}

		fin.close();
		return Status::PARSEOK;
	}
	return Status::ERR_FOPEN;
}

//TODO implement
template<>
const Parser<Pizza>::Status Parser<Pizza>::parseFile()
{
	std::ifstream fin(fileToParse);

	if (fin.is_open())
	{
		//buffer for product and recipe lines
		std::string prodLine, recLine;

		while (!fin.eof())
		{
			prodLine.clear();
			recLine.clear();

			std::getline(fin, prodLine);
			bool canAdd = false;
			if (!isIgnored(prodLine) && prodLine[0] == delim[1])
			{
				while (std::getline(fin, recLine))
				{
					if (!isIgnored(recLine) && recLine[0] != delim[1])
					{
						canAdd = true;
						break;
					}
				}
			}

			if (canAdd)
			{
				auto beg = prodLine.find_first_not_of(delim[1]);
				auto end = prodLine.length();
				prodLine = prodLine.substr(beg, end);
				trimWhitespace(prodLine);

				if (find(prodLine, toWrite) < 0 && find(recLine, toWrite) < 0)
				{
					toWrite.push_back(prodLine);
					recLine[0] = static_cast<char>(tolower(recLine[0]));
					toWrite.push_back(recLine);
				}

			}
		}
		fin.close();

		if (toWrite.empty() || toWrite.size() % 2 != 0)
		{
			return Status::ERR_PARSE;
		}
		return Status::PARSEOK;
	}
	return Status::ERR_FOPEN;
}
