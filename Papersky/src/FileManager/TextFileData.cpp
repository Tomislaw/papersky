#include "FileManager\TextFileData.h"

std::vector <int> Variable::to_int()
{
	std::vector <int> table;
	for (int i = 0; i < var.size();i++)
	{
		table.push_back(atoi(var[i].c_str()));
	}
	return table;
}

std::vector <float> Variable::to_float()
{
	std::vector <float> table;
	for (int i = 0; i < var.size();i++)
	{
		table.push_back(atoi(var[i].c_str()));
	}
	return table;
}

int Variable::to_int(unsigned int index)
{
	if (index < var.size())
	{
		return atoi(var[index].c_str());
	}
	return 0;
}

float Variable::to_float(unsigned int index)
{
	if (index < var.size())
	{
		return atof(var[index].c_str());
	}
	return 0;
}


Variable set_variable(std::string variable_line)
{
	char cudzyslow = 34;
	char przecinek = ',';
	if (variable_line.size() < 7 || variable_line.find(" = ") == std::string::npos || variable_line.find(cudzyslow) == std::string::npos)
	{
		Variable var;
		var.name == "ERROR";
		var.var.push_back("ERROR");
		std::cout << "Error, wrong variable -> " << variable_line << std::endl;
		return var;
	}
	else
	{
		Variable var1;
		std::string name = variable_line;
		name.erase(variable_line.find(" = "), name.size());
		var1.name = name;
		std::string variable_all = variable_line;
		variable_all.erase(0, variable_line.find(" = ") + 4);
		int variable_count = 1;

		for (int i = 0; i < variable_all.size(); i++)
		{
			if (variable_all[i] == ',') variable_count += 1;
			if (variable_count > 999)
			{
				std::cout << "Variable " << name << "have too many args, max is 999" << std::endl;
				break;
			}
		}

		std::string variable_value;
		char variable_char;
		for (int i = 0; i < variable_all.size();i++)
		{
			variable_char = variable_all[i];
			if (variable_char == przecinek)
			{
				var1.var.push_back(variable_value);
				variable_value.clear();
			}
			else
			{
				if (variable_char == cudzyslow)
				{
					var1.var.push_back(variable_value);
					return var1;
				}
				else
				{
					variable_value += variable_char;
				}
			}

		}


		return var1;
	}

}

////////////////////////////////////TEXTELEMENT

TextElement::TextElement()
{
	name == "Empty element";
}

TextElement::~TextElement()
{

}

std::string TextElement::display()
{
	std::string displaytext;
	displaytext += "Name " + name + "\n";
	for (int i = 0; i < variable.size();i++)
	{
		displaytext += variable[i].name + " ";
		for (int j = 0; j < variable[i].var.size();j++)
		{
			displaytext += variable[i].var[j] + " ";
		}
		displaytext += '\n';
	}
	displaytext += '\n';
	return displaytext;
}
Variable *TextElement::get_variable_by_name(std::string var_name)
{
	for (int i = 0; i < variable.size();i++)
	{
		if (variable[i].name == var_name) return &variable[i];
	}


	std::cout << "ERROR IN FILEREADER" << ", VARIABLE " << var_name << " NOT FOUND!" << std::endl;

	return nullptr;
}


////////////////////////////////TEXTFILEDATA


TextFileData::TextFileData()
{
}

TextFileData::~TextFileData()
{
}

TextElement *TextFileData::get_first_element_by_name(std::string element_name)
{
	for (int i = 0; i < element.size();i++)
	{
		if (element[i].name == element_name) return &element[i];
	}

	return &null;
}

std::vector <TextElement*> TextFileData::get_all_elements_by_name(std::string element_name)
{
	std::vector <TextElement*> all_elements;
	for (int i = 0; i < element.size();i++)
	{
		if (element[i].name == element_name) all_elements.push_back(&element[i]);
	}
	return all_elements;
}

std::string TextFileData::display()
{
	std::string displaytext;
	displaytext += "File name " + name + "\n";
	for (int i = 0; i < element.size();i++)
	{
		displaytext += element[i].display();
	}
	return displaytext;
}

bool TextFileData::read_file(std::string file_txt)
{
	//std::string file_txt = getExeLocation();
	//if (location.size() == 0)return false;
	//if (location[0] != '/')file_txt.push_back('/');
	//file_txt += location;


	std::fstream plik;
	plik.open(file_txt);
	if (!plik.good()) 
	{
		std::cout << "Can't open file " << file_txt << std::endl;
		return false; //Nie uda�o si� otworzy� pliku
	}
		

	std::string sWiersz;
	while (!plik.eof())
	{
		std::getline(plik, sWiersz);
	//	std::cout << sWiersz << std::endl; // Nazwa typu pliku
		if (sWiersz != "PAPERSKY") { plik.close(); return 0; }
		name = file_txt;
		while (sWiersz != "PAPERSKY_END")
		{
			/////////Wczytywanie danych do struktury
			std::getline(plik, sWiersz);
			if (sWiersz == "CORPOSFILE_END")return 1;
			if (sWiersz.size() > 1)
			{
				TextElement txtelement;
				txtelement.name = sWiersz;
			//	std::cout << sWiersz << std::endl;
				std::getline(plik, sWiersz);
				if (sWiersz != "{") return 0;
				for (int i = 0; i < 2000; i++)
				{

					std::getline(plik, sWiersz);
					if (sWiersz == "}") break;
					if(sWiersz == "{") return 0;
					txtelement.variable.push_back(set_variable(sWiersz));

				}
				element.push_back(txtelement);
			}
		}
	}
	plik.close();
	return true;
};

bool TextFileData::save_to_file(std::string localization)
{
	std::fstream plik;
	plik.open(localization,std::ios::trunc);

	std::string text_data;

	text_data += "CORPOSFILE\r\n";
	for (int i = 0; i < element.size(); i++)
	{ 
		text_data += element[i].name + "\r\n";
		text_data += "{\r\n";
		for (int j = 0; j < element[i].variable.size();j++)
		{
			text_data += element[i].variable[j].name + " = " + '"';
			for (int k = 0; k < element[i].variable[j].var.size()-1;k++)
			{
				text_data += element[i].variable[j].var[k] + ',';
			}
			if (element[i].variable[j].var.size() > 0)
			{
				text_data += element[i].variable[j].var[element[i].variable[j].var.size()-1] + '"'+"\r\n";
			}

		}
		text_data += "}\r\n";
	}
	text_data += "CORPOSFILE_END";
	std::cout << text_data << std::endl;
	plik.close();
	return 0;
}

std::string TextFileData::getExeLocation()
{
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(hModule, path, MAX_PATH);

	std::wstring wpath(path);
	std::replace(wpath.begin(), wpath.end(), '\\', '/');
	auto pos = wpath.find_last_of('/');
	wpath.erase(wpath.begin() + pos, wpath.end());

	// your new String
	return std::string(wpath.begin(), wpath.end());
}