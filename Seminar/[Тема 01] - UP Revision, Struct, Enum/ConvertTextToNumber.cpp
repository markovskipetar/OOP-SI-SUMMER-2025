#include <iostream>

enum class ErrorCode
{
	NoError,
	NullptrError,
	DirtyTextError,
	EmptyTextError,
};

struct ParseResult
{
	ErrorCode errorCode;
	int number;
};

ParseResult convertTextToNumber(const char* text)
{
	int number = 0;

	for (int i = 0; text[i]; i++)
	{
		char symbol = text[i];

		if ('0' <= symbol && symbol <= '9')
		{
			number *= 10;
			number += (symbol - '0');
		}
		else
		{
			return ParseResult{ ErrorCode::DirtyTextError };
		}
	}

	return ParseResult{ ErrorCode::NoError, number };
}

ParseResult parseNumber(const char* text)
{
	if (!text)
	{
		return { ErrorCode::NullptrError }; // the name ParseResult may be ommited
	}

	int textLength = strlen(text);

	if (textLength == 0)
	{
		return ParseResult{ ErrorCode::EmptyTextError };
	}

	return convertTextToNumber(text);
}

const char* getErrorDescription(ErrorCode errorCode)
{
	switch (errorCode)
	{
	case ErrorCode::NullptrError:
		return "Text cannot be nullptr";
	case ErrorCode::DirtyTextError:
		return "Text contains dirty symbols";
	case ErrorCode::EmptyTextError:
		return "Text cannot be empty";
	}

	return nullptr;
}

bool isError(ErrorCode errorCode)
{
	switch (errorCode)
	{
	case ErrorCode::NoError:
		return false;
	}

	return true;
}

int main()
{
	char text[32]="";
	std::cin >> text;

	ParseResult parseResult = parseNumber(text);

	if (isError(parseResult.errorCode))
	{
		std::cout << getErrorDescription(parseResult.errorCode) << std::endl;
	}
	else
	{
		std::cout << parseResult.number;
	}
}
