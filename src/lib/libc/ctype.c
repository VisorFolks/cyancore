/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: ctype.h
 * Description		: This file contains sources of libc-ctypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <ctype.h>

bool isWhitespace(int c)
{
	return ((c == ' ') || (c == '\t'));
}

bool isSpace(int c)
{
	return (isWhitespace(c) || (c == '\f') || (c == '\n') ||
			(c == '\r') || (c == '\v'));
}

bool isLowercase(int c)
{
	return ((c >= 'a') && (c <= 'z'));
}

bool isUppercase(int c)
{
	return ((c >= 'A') && (c <= 'Z'));
}

bool isDigit(int c)
{
	return ((c >= '0') && (c <= '9'));
}

bool isAlpha(int c)
{
	return (isLowercase(c) || isUppercase(c));
}

bool isAlphaNumeric(int c)
{
	return (isAlpha(c) || isDigit(c));
}

bool isHexDigit(int c)
{
	return (isDigit(c) || ((c >= 'a') && (c <= 'f')) ||
			((c >= 'A') && (c <= 'F')));
}

bool isGraph(int c)
{
	return ((c > ' ') && (c < 0x7f));
}

bool isControl(int c)
{
	return ((c < ' ') || (c == 0x7f));
}

bool isPrintable(int c)
{
	return ((c >= 0x20) && (c < 0x7f));
}
bool isPunct(int c)
{
	return (isGraph(c) && !isAlphaNumeric(c));
}

bool isASCII(int c)
{
	return (c < 0x80);
}

int toLowercase(int c)
{
	if(isUppercase(c))
		return c + ('a' - 'A');
	return c;
}

int toUppercase(int c)
{
	if(isLowercase(c))
		return c - ('a' - 'A');
	return c;
}
