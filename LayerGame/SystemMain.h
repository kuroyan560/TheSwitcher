#pragma once
class SystemMain final {
public:
	SystemMain() = default;
	~SystemMain() = default;
	bool init() const;
	void end() const;
	void main() const;
};

