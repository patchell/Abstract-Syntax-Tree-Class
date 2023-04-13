#pragma once

constexpr auto TOTAL_TOKENS = 2;

class CToken
{
public:
	enum class Token {
		IDENT = 256,
		NUMBER
	};
private:
	struct TokenNames {
		Token TokenVal;
		const char* pName;
	};
	inline static TokenNames TNames[TOTAL_TOKENS] = {
		{Token::IDENT,"IDENT"},
		{Token::NUMBER,"NUMBER"}
	};
public:
	CToken();
	virtual ~CToken();
	BOOL Create();
	const char* LookupName(Token aToken);
};

