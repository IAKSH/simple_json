#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <regex>

class json
{
public:
	json();
	json(std::string _path);
	std::map<std::string, std::string>& get();
private:
	void loadJson(std::string _path);
	void cutJson(std::string aimed_str, std::map<std::string, std::string>& buffer);
	std::map<std::string, std::string> index;
};

// 使用例
// json data("C:\\Users\\ASKmenot\\Desktop\\load_me.json");
// std::cout << data.get()["message"] << '\n';
