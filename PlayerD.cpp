#include "PlayerD.h"
std::unique_ptr<char[]> PlayerD::Serialize() {
	std::unique_ptr<char[]> buffer = std::make_unique<char[]>(5);
	size_t index = 0;
	{
		char temp = id;
		memcpy(buffer.get() + index,&temp,1);
		index+=1;
	}
	{
		long temp = htonl(type);
		memcpy(buffer.get() + index,&temp,4);
		index+=4;
	}
	return std::move(buffer);
}
