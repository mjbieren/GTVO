#include "ProcessFile.h"



long SetFileBuffer(char** ppPos, std::string strFileName)
{
	//stat the file
	//Open the file and fread into the buffer
	long lReturn = ERR_NOERROR;

	struct stat statInfo; //stat info about our file of interest;

	if (stat(strFileName.c_str(), &statInfo) || !(statInfo.st_mode & S_IFMT))
	{
		printf_s("Error ERR_FILE_OF_INTEREST_DOES_NOT_EXIST File: %s%s", strFileName.c_str(), EOL);
		return ERR_FILE_OF_INTEREST_DOES_NOT_EXIST_SET_FILE_BUFFER;
	}

	uint64_t sizeFile = statInfo.st_size;
	char* pBuffer = new char[sizeFile + 100];
	memset(pBuffer, '\0', sizeFile + 100); // just to be sure since the computer have a habit to overwrite old buffers :').

	FILE* hFileOfInterest;

	errno_t ernum = fopen_s(&hFileOfInterest, strFileName.c_str(), "rb");

	//If we got an error, we will do a proper error handling
	if (ernum)
	{
		char szError[SIZE_BUFFER_MEDIUM];
		sprintf_s(szError, sizeof(szError), "Error ERR_FOPEN_FILE_OF_INTEREST err: %i on line: %i in file %s while opening file %s%s", ernum, __LINE__, __FILE__, strFileName.c_str(), EOL);
		perror(szError);

		if(pBuffer)
			delete pBuffer;
		return ERR_FOPEN_SET_FILE_BUFFER_COULD_NOT_OPEN_FILE;
	}

	//Now we read the file into our buffer
	size_t sizeData = fread(pBuffer, 1, sizeFile, hFileOfInterest);
	sizeData = sizeData;
	ASSERT(sizeData == sizeFile);

	//we of course close our file again
	fclose(hFileOfInterest);

	//Zero terminates the file buffer
	pBuffer[sizeFile] = '\0';

	*ppPos = pBuffer; //will be cleaned up in the other file.

	return lReturn;
}

long SetFileBufferReuse(char** ppExistingBuffer, std::string strFileName, size_t* pSizeBuffer)
{
	//stat the file
	//Open the file and fread into the buffer
	long lReturn = ERR_NOERROR;

	//Check first if existing buffer actually looks at something. If not create a file buffer that's big enough. (1gb)
	if (!*ppExistingBuffer)
	{
		//Buffer doesn't actually exist.

		*ppExistingBuffer = new char[SIZE_BUFFER_HUNDRED_MB];
		*pSizeBuffer = SIZE_BUFFER_HUNDRED_MB;

		memset(*ppExistingBuffer, '\0', SIZE_BUFFER_HUNDRED_MB);
	
	}

	struct stat statInfo; //stat info about our file of interest;

	if (stat(strFileName.c_str(), &statInfo) || !(statInfo.st_mode & S_IFMT))
	{
		printf_s("Error ERR_FILE_OF_INTEREST_DOES_NOT_EXIST File: %s%s", strFileName.c_str(), EOL);
		return ERR_FILE_OF_INTEREST_DOES_NOT_EXIST_SET_FILE_BUFFER;
	}

	uint64_t sizeFile = statInfo.st_size;
	
	char* pBuffer = nullptr;

	//Now we have to check if the current buffer size is big enough for our file otherwise we replace the old buffer!.

	if (sizeFile >= *pSizeBuffer) //New file size is bigger than old buffer.
	{
		if (*ppExistingBuffer) //Check if file exist and delete, should actually exist but you never know!
			delete* ppExistingBuffer;

		*ppExistingBuffer = new char[sizeFile + 100];
		*pSizeBuffer = sizeFile + 100;
		memset(*ppExistingBuffer, '\0', *pSizeBuffer);
	}

	//Reset the memory with memset
	memset(*ppExistingBuffer, '\0', *pSizeBuffer);


	pBuffer = *ppExistingBuffer;

	FILE* hFileOfInterest;

	errno_t ernum = fopen_s(&hFileOfInterest, strFileName.c_str(), "rb");

	//If we got an error, we will do a proper error handling
	if (ernum)
	{
		char szError[SIZE_BUFFER_MEDIUM];
		sprintf_s(szError, sizeof(szError), "Error ERR_FOPEN_FILE_OF_INTEREST err: %i on line: %i in file %s while opening file %s%s", ernum, __LINE__, __FILE__, strFileName.c_str(), EOL);
		perror(szError);

		delete pBuffer;
		return ERR_FOPEN_SET_FILE_BUFFER_COULD_NOT_OPEN_FILE;
	}

	//Now we read the file into our buffer
	size_t sizeData = fread(pBuffer, 1, sizeFile, hFileOfInterest);
	sizeData = sizeData;
	ASSERT(sizeData == sizeFile);

	//we of course close our file again
	fclose(hFileOfInterest);

	//Zero terminates the file buffer
	pBuffer[sizeFile] = '\0';

	*ppExistingBuffer = pBuffer; //will be cleaned up in the other file.

	return lReturn;
}

long DetermineFilebufferSize(size_t* psizeBuffer, std::string strFileName)
{
	long lReturn =  ERR_NOERROR;

	struct stat statInfo; //stat info about our file of interest;

	if (stat(strFileName.c_str(), &statInfo) || !(statInfo.st_mode & S_IFMT))
	{
		printf_s("Error ERR_FILE_OF_INTEREST_DOES_NOT_EXIST File: %s%s", strFileName.c_str(), EOL);
		return ERR_FILE_OF_INTEREST_DOES_NOT_EXIST_GET_BUFFER_SIZE;
	}

	if (statInfo.st_size == 0)
		return ERR_FILE_OF_INTEREST_BUFFER_SIZE_BUFFER_TOO_SMALL;


	*psizeBuffer = statInfo.st_size;
	

	return lReturn;
}

long WriteOutputFile(char* pFileBuffer, std::string strFilePath)
{
	long lReturn = ERR_NOERROR;

	FILE* hFileOutputFile = nullptr;
	errno_t errFopen_s = fopen_s(&hFileOutputFile, strFilePath.c_str(), "wb");
	if (errFopen_s != ERR_NOERROR)
	{
		printf_s("Error in opening output file %s, on line %i in file %s %s", strFilePath.c_str(), __LINE__, __FILE__, EOL);
		return WRITE_OUTPUT_FILE_ERROR_FOPEN;
	}
	else
	{
		fputs(pFileBuffer, hFileOutputFile);
	}
	fclose(hFileOutputFile);


	return lReturn;
}

long SetBufferFromPositions(char* pStart, char* pEnd, char** ppBuffer, bool bGetEndChar)
{
	/*
	Basically a function to set a buffer based on two file positions (a start and end positions)
	the bGetEndChar is basically made to have an option to also obtain the character that pEnd is looking at or not.
	e.g. you would do an EOL and you do not want to copy the EOL then you wouldn't copy the EOL aka the bGetEndChar = false. "ThisIsAStringToCopy/r/n" (pEnd is looking at /r or /n)
	But if you would have your pEnd looking at EOL but move it back to before the EOL aka the bGetEndChar = true "ThisIsAStringToCopy" (pEnd is looking at y"

	*/
#ifdef _DEBUG
	size_t sizeBuffer = pEnd - pStart;
	sizeBuffer = sizeBuffer; //Prevent warning, SizeBuffer variable not used.
#endif

	long lReturn = ERR_NOERROR;

	if ((pEnd - pStart) <= 0)
		return ERROR_PARSE_ROW_SIZE_TOO_SMALL;

	if ((pEnd - pStart) > SIZE_BUFFER_ONE_GIG)//Just to be sure this file has EOLs, keep in mind that certain orthogroup files have rows that are longer than 15k characters. Hence why SIZE_BUFFER_BIG will be too small!
		return ERROR_PARSE_ROW_SIZE_TOO_BIG;


	char* pBuffer = new char[pEnd - pStart + 10];
	memset(pBuffer, '\0', pEnd - pStart + 10);

	if(bGetEndChar == false)
		memcpy(pBuffer, pStart, (pEnd - pStart));
	else
		memcpy(pBuffer, pStart, (pEnd - pStart+ (strlen(EOL))));

	*ppBuffer = pBuffer;
	return lReturn;
}

long SplitStringByDelimitedCharacter(std::vector<char*>* pvecStringSplitted, std::string strStringToBeSplit, char cDelimitedChar)
{
	//This function split the string into little zero terminated strings basd on the delimited character (cDelimitedChar). E.g. Tab, comma, space etc.
	//First determine how big the string is.
	//Second determine how many columsn there are
	//Third
	size_t sizeStringToBeSplit = strStringToBeSplit.length();
	if (sizeStringToBeSplit <= 0)
		return 1; //Todo Error Message

	const char* pStart = strStringToBeSplit.c_str();
	const char* pPos = pStart;
	const char* pEnd = pStart + sizeStringToBeSplit;

	std::string::difference_type n = std::count(strStringToBeSplit.begin(), strStringToBeSplit.end(), cDelimitedChar);

	char* pStringBuffer = nullptr;
	size_t sizeStringBuffer = 0;

	for (size_t idx = 0; idx < (size_t) n; idx++)
	{
		//Move pPos to the delimited character.
		MOVE_PTR_TO_CHAR(pPos, cDelimitedChar);
		
		sizeStringBuffer = pPos - pStart;
		pStringBuffer = new char[sizeStringBuffer + 10]; //we want to zero terminate the string
		memset(pStringBuffer, '\0', sizeStringBuffer + 10);
		memcpy(pStringBuffer, pStart, sizeStringBuffer);


		pvecStringSplitted->push_back(pStringBuffer);

		pPos++;
		pStart = pPos;


	}

	//Get the last one
	sizeStringBuffer = pEnd - pPos;
	pStringBuffer = new char[sizeStringBuffer + 10]; //we want to zero terminate the string
	memset(pStringBuffer, '\0', sizeStringBuffer + 10);
	memcpy(pStringBuffer, pStart, sizeStringBuffer);


	pvecStringSplitted->push_back(pStringBuffer);


	return ERR_NOERROR;

}

long SplitColumnInObjects(std::string strStringToBeSplit, std::vector<char*>* pvecSplitColumn, char cDelimitedChar)
{
	//e.g of Column ko00760,ko01100,map00760,map01100

	long lReturn = ERR_NOERROR;

	//Count how many "delimiteted objects there are

	std::string strColumnSet = strStringToBeSplit;

	size_t sizeColumns = 0;

	for (size_t idx = 0; idx < strColumnSet.size(); idx++)
	{
		if (strColumnSet[idx] == cDelimitedChar)
			sizeColumns++;
	}

	const char* pStart = strColumnSet.c_str();
	const char* pEnd = strColumnSet.c_str();

	char* pColumnSplit = nullptr;


	if (sizeColumns == 0) //Only one item
	{
		pColumnSplit = new char[strColumnSet.size() + 10];
		memset(pColumnSplit, '\0', strColumnSet.size() + 10);
		memcpy(pColumnSplit, pStart, strColumnSet.size());

		pvecSplitColumn->push_back(pColumnSplit);

		return lReturn;

	}


	size_t sizeColumn = 0;

	for (size_t idx = 0; idx < sizeColumns; idx++)
	{
		MOVE_PTR_TO_ASCII_CHAR(pEnd, cDelimitedChar);
		sizeColumn = pEnd - pStart;
		if (sizeColumn == 0)
			return ERR_SPLIT_STRING_SEPARATE_SUBS;

		pColumnSplit = new char[sizeColumn + 10];
		memset(pColumnSplit, '\0', sizeColumn + 10);
		memcpy(pColumnSplit, pStart, sizeColumn);

		pvecSplitColumn->push_back(pColumnSplit);
		pEnd++;
		pStart = pEnd;

	}

	//Add The last one (or if the user ended it with a , skip this step

	if (*pEnd && *pEnd != '\0') //Meaning we still have data in our memory to read from
	{
		while (*pEnd) //Move it to the end
			pEnd++;

		sizeColumn = pEnd - pStart;
		if (sizeColumn == 0)
			return ERR_SPLIT_STRING_SEPARATE_SUBS;

		pColumnSplit = new char[sizeColumn + 10];
		memset(pColumnSplit, '\0', sizeColumn + 10);
		memcpy(pColumnSplit, pStart, sizeColumn);

		pvecSplitColumn->push_back(pColumnSplit);
	}

	return lReturn;

}

long ReplaceStringForSzObject(char** ppColumnToFill, std::string strColumnBase)
{
	long lReturn = ERR_NOERROR;

	size_t sizeColumnBase = strColumnBase.size();

	if (sizeColumnBase == 0) //when it's not filled
		return REPLACE_STRING_FOR_SZOBJECT_ZERO_STRING_SIZE;

	char* pColumnToFill = new char[sizeColumnBase + 10];
	memset(pColumnToFill, '\0', sizeColumnBase + 10);
	memcpy(pColumnToFill, strColumnBase.c_str(), sizeColumnBase);

	*ppColumnToFill = pColumnToFill;

	return lReturn;
}


size_t CountHowManyOccurancesCharacterInBuffer(char* pBuffer, char cCharToFind, bool bBoolAlwaysOne)
{
	char* pPos = nullptr;
	pPos = pBuffer;

	size_t sizeOccurances = 0; 

	if (bBoolAlwaysOne == true)
		sizeOccurances = 1; //In this case the char can be used as a delimited character

	while (*pPos)
	{
		while (*pPos != ',' && *pPos)
			pPos++;

		if (*pPos == ',')
			sizeOccurances++; //plus one occurance

		pPos++;
	}

	return sizeOccurances;
}

long DuplicateZeroTerminatedString(std::string strToDuplicate, size_t SizeToDuplicate, char** pZeroTerminatedToFill)
{
	long lReturn = ERR_NOERROR;

	//Check if strToDuplicate have something in there;
	if (strToDuplicate.size() == 0)
		return DUPLICATE_ZERO_TERMINATED_STRING_SIZE_ZERO;


	size_t sizeBuffer = (strToDuplicate.size() * SizeToDuplicate) + (SizeToDuplicate * 2) +10 ; //We repeat it x number of times + use the delimited ", ". + 10 for file buffer range.
	size_t sizeBufferLeft = sizeBuffer;
	char* szToFill = new char[sizeBuffer];
	memset(szToFill, '\0', sizeBuffer);

	char* pBufferToFillPos = szToFill;

	for (size_t idx = 0; idx < SizeToDuplicate; idx++)
	{
		sizeBufferLeft = sizeBufferLeft - (pBufferToFillPos - szToFill);
		pBufferToFillPos += sprintf_s(pBufferToFillPos, sizeBufferLeft, "%s, ", strToDuplicate.c_str());
	}

	//Remove the last two characters ", "

	pBufferToFillPos--;
	*pBufferToFillPos = '\0';
	pBufferToFillPos--;
	*pBufferToFillPos = '\0';
	

	*pZeroTerminatedToFill = szToFill;

	return lReturn;
}