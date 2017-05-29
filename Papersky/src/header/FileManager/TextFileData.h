#ifndef TEXTFILEDATA_H
#define TEXTFILEDATA_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Shlwapi.h>
#include <algorithm>

/// <summary>
/// Contains single variable in table.
/// </summary>
struct Variable
{ 
	std::string name = "NULL";
	std::vector <std::string> var;
	//Return all variables changed to int
	std::vector <int> to_int();
	//REturn all variables changed to float
	std::vector <float> to_float();
	//Return variable changed to int, if not found return 0.
	int to_int(unsigned int index);
	//Return variable changed to float, if not found return 0.
	float to_float(unsigned int index);
	//True if empty.
	bool is_null()
	{
		if (var.size() < 0)return 1;
		return 0;
	}
};


/// <summary>
/// Contains one region with variables.
/// </summary>
class TextElement
{
public:
	TextElement();
	~TextElement();

	std::string name;
	std::vector <Variable > variable;
	Variable null;
	std::string display();

	Variable *get_variable_by_name(std::string var_name);

private:

};





/// <summary>
/// Loading data from file.
/// </summary>
class TextFileData
{
public:
	std::string display();

	std::vector <TextElement*> get_all_elements_by_name(std::string element_name);


	TextElement *get_first_element_by_name(std::string element_name);


	/// <summary>
	/// Load data from file.
	/// </summary>
	/// <param name="file_txt">File location</param>
	/// <changed>Tomasz,10.03.2017</changed>
	bool read_file(std::string file_txt);
	TextFileData();
	~TextFileData();
	void set_elements(std::vector < TextElement > set)
	{
		element = set;
	}
	void replace_element(TextElement replace, std::string id)
	{
	
		for (int i = 0; i < element.size();i++)
		{
			if (element[i].get_variable_by_name("Id")->var[0] == id)
			{
				element[i] = replace;
				break;
			}
		}
	}
	bool save_to_file(std::string localization);
	std::vector < TextElement > get_all_elements()
	{
		return element;
	}
private:
	std::string name;
	std::vector < TextElement > element;

	//Empty variable
	TextElement null;

	//Get location of executable
	std::string getExeLocation();
};

#endif