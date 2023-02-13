#pragma once


#define DECLARE_ENUM(type,NAME,...)\
enum class NAME : type {\
	__VA_ARGS__,\
	COUNT,\
	LAST = COUNT - 1\
}