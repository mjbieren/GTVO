#pragma once
#include "stdafx.h"
#include "Management.h"

#define ERROR_PARSE_ROW_SIZE_TOO_SMALL 10000
#define ERROR_PARSE_ROW_SIZE_TOO_BIG 10001

long SetFileBuffer(char** ppPos, std::string strFileName);
long SetFileBufferReuse(char** ppExistingBuffer, std::string strFileName, size_t* pSizeBuffer);
long DetermineFilebufferSize(size_t* psizeBuffer, std::string strFileName);
long WriteOutputFile(char* pFileBuffer, std::string strFilePath);
long SetBufferFromPositions(char* pStart, char* pEnd, char** ppBuffer, bool bGetEndChar = false);
long SplitStringByDelimitedCharacter(std::vector<char*>* pvecStringSplitted, std::string strStringToBeSplit, char cDelimitedChar);
long SplitColumnInObjects(std::string strStringToBeSplit, std::vector<char*>* pvecSplitColumn, char cDelimitedChar);
long ReplaceStringForSzObject(char** ppColumnToFill, std::string strColumnBase);
long DuplicateZeroTerminatedString(std::string strToDuplicate, size_t SizeToDuplicate, char** pZeroTerminatedToFill);
size_t CountHowManyOccurancesCharacterInBuffer(char* pBuffer, char cCharToFind, bool bBoolAlwaysOne = false);

