#pragma once
#include <string>
#include <type_traits>
#include <optional>
#include <utility>

namespace VuxNguyen
{

struct success_t
{
	success_t(){}
};

static const success_t success;

template<class ErrorCode>
class error {
private:
	static_assert(std::is_enum<ErrorCode>::value,"Only Enum are accepted");
	std::string m_what;
	ErrorCode m_errorCode;
public:
	error(ErrorCode i_errorCode, std::string i_message): 
		m_errorCode(i_errorCode),
		m_what(i_message)
	{

	}
	error(ErrorCode i_errorCode): 
		m_errorCode(i_errorCode),
		m_what("")
	{

	}

	std::string what() const
	{
		return m_what;
	}

	ErrorCode errorCode() const{
		return m_errorCode;
	}
};

template<class T,template<class> class BASE_TEMPLATE>
struct is_template_of : std::false_type{

};

template<class T,template<class> class BASE_TEMPLATE>
struct is_template_of<BASE_TEMPLATE<T>,BASE_TEMPLATE> : std::true_type{

};

template<class Payload_t,class error_t>
class result{
private:
	static_assert(is_template_of<error_t,error>::value,"Error_t is not an instance of error Template");
	std::optional<error_t> m_error;
public:
	std::optional<Payload_t> m_payload;
	result(Payload_t i_payload): m_payload(i_payload) {

	}

	result(error_t i_error): m_error(i_error) {

	}

	inline const error_t& error()
	{
		return m_error.value();
	}

	inline Payload_t extract_payload(){
		return std::exchange(m_payload, std::nullopt).value();
	}

	inline bool operator==(const success_t& success) const
	{
		return m_payload.has_value();
	}
	inline bool operator!=(const success_t& success) const
	{
		return !m_payload.has_value();
	}
};
template<class error_t>
class result<void,error_t>{
private:
	static_assert(is_template_of<error_t,error>::value,"Error_t is not an instance of error Template");
	std::optional<error_t> m_error;
public:

	result(){}

	result(error_t i_error): m_error(i_error) {

	}

	inline const error_t& error()
	{
		return m_error.value();
	}

	inline void extract_payload(){
	}

	inline bool operator==(const success_t& success) const
	{
		return !m_error.has_value();
	}
	inline bool operator!=(const success_t& success) const
	{
		return m_error.has_value();
	}
};
}

