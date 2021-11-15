#include <cstddef>
#include <new>
#include <iostream>

#include "my_string.h"

char* Exercise_1::CMyString::TryToAllocate(const size_t nLength) noexcept {
	char *pcAllocated;
	try
	{
		pcAllocated = new char[nLength];
	} catch(std::bad_alloc& err)
	{
		pcAllocated = nullptr;
		printf("Failed to allocate character of length: %ld\n", nLength);
	}
	return pcAllocated;
}

std::size_t Exercise_1::CMyString::GetStringLength(const char *cszStringToCount) noexcept {
	std::size_t nStringLength = 0;
	char cCurrentChar = cszStringToCount[0];
	while(cCurrentChar != '\0')
	{
		++nStringLength;
		cCurrentChar = cszStringToCount[nStringLength];
	}
	// Adding 1 because string is zero terminated
	return nStringLength + 1;
}

void Exercise_1::CMyString::CopyString(const char *cszStringToCopy, char *szStringToPaste, std::size_t nCountOfChars)
{
	for(std::size_t nIndex = 0; nIndex < nCountOfChars; nIndex++)
	{
		szStringToPaste[nIndex] = cszStringToCopy[nIndex];
	}
}

Exercise_1::CMyString::CMyString(const char* cszCharsSequence) 
{
	m_nSize = GetStringLength(cszCharsSequence);
	m_szData = TryToAllocate(m_nSize);

	CopyString(cszCharsSequence, m_szData, m_nSize);
}

Exercise_1::CMyString::CMyString(const Exercise_1::CMyString& cStringToCopy)
{
	// Cleaning data we used before
	bool bShouldCleanup = m_szData != nullptr && m_nSize != cStringToCopy.m_nSize;
	if(bShouldCleanup)
	{
		delete[] m_szData;
	}
	// Doing check if we need to reinitialize the char array
	if(m_szData == nullptr || bShouldCleanup)
	{
		m_nSize = cStringToCopy.m_nSize;
		m_szData = TryToAllocate(m_nSize);
	}
	
	CopyString(cStringToCopy.data(), m_szData, m_nSize);
}

Exercise_1::CMyString& Exercise_1::CMyString::operator=(const Exercise_1::CMyString& cStringToCopy)
{
	if(&cStringToCopy == this) 
	{
		return *this;
	}
	// Cleaning data we used before
	bool bShouldCleanup = m_szData != nullptr && m_nSize != cStringToCopy.m_nSize;
	if(bShouldCleanup)
	{
		delete[] m_szData;
	}
	// Doing check if we need to reinitialize the char array
	if(m_szData == nullptr || bShouldCleanup)
	{
		m_nSize = cStringToCopy.m_nSize;
		m_szData = TryToAllocate(m_nSize);
	}
	
	CopyString(cStringToCopy.data(), m_szData, m_nSize);

	return *this;
}

// Destructor
Exercise_1::CMyString::~CMyString()
{
	if(m_szData != nullptr)
	{
		delete[] m_szData;
	}
}
