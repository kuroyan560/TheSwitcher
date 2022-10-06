#pragma once
#include <map>
#include <string>

using namespace std;

class Parameter {
public:
	const static int Error = -1;
	Parameter() = default;
	virtual ~Parameter() = default;

	void set(string key, int val);
	int  get(string key) const;
private:
	map<string, int> _map;
};

