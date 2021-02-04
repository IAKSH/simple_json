#include "lite_json.h"

json::json() {};
json::json(std::string _path)
{
	loadJson(_path);
}

void json::loadJson(std::string _path)
{
	std::fstream file(_path, std::ios::in);
	if (!file.is_open())
	{
		std::cerr << "Unable to load JSON [" << _path << "]\n";
		abort();
	}

	std::string buffer;

	while (file.good()) {
		buffer += file.get();
	}

	file.close();

	cutJson(buffer, index);
}

std::map<std::string, std::string>& json::get()
{
	return index;
}

void json::cutJson(std::string _aimed_str, std::map<std::string, std::string>& _buffer)
{
	std::regex rg("\"(.*?)\":\"(.*?)\",?.*?");
	std::smatch sm;

	std::regex_search(_aimed_str, sm, rg);

	int count = 0;
	bool isKey = true;
	std::string buf_key = "";
	for (auto item : sm)
	{
		//忽略每组的第一个结果("完全匹配")
		if (count == 0)
		{
			++count;
			continue;
		}
		else if (count == 3) {
			count = 0;
			continue;
		}

		++count;

		if (isKey)
		{
			buf_key = item.str();
			isKey = false;
		}

		// is value
		_buffer[buf_key] = item.str();
		isKey = false;
	}

	if (sm.suffix() == "") {
		return;
	}

	cutJson(sm.suffix(), _buffer);
}
