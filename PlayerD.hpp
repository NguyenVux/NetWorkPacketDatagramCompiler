#pragma once
#include <memory>
class PlayerD{
public:
	std::unique_ptr<char[]> Serialize();
	char get_id() const;
	long get_type() const;
private:
	char id;
	long type;
};
