#pragma once
#include "ClearVector.h"
#include "Management.h"
#include "GlobalHelper.h"
#include "ProcessFile.h"

long SplitHeaderNameAndNumber(const char* szToMatch, char** ppHeader, unsigned long* ulHeaderNumber, size_t* psizeBuffer);

class CFastaBlock
{
private:
	char * m_szFastaHeaderComplete = nullptr;
	char * m_szFastaHeaderStrain = nullptr;
	char* m_szFastaHeaderRest = nullptr;
	char* m_szFastaHeaderAddOn = nullptr;
	unsigned long m_ulHeaderNumber = 0;
	char* m_szFastaSequence = nullptr;
	bool m_bWriteFastaBlock = true;
	bool m_bFastaheaderAddOn = false;
	bool m_bFastaKeggmatrix = false;
	std::vector<char*>* m_pKEGGMatrixRow = nullptr; //don't have to be deleted since it's looking at somethign else
public:
	CFastaBlock() {};
	~CFastaBlock() 
	{
		if (m_szFastaHeaderComplete)
			delete m_szFastaHeaderComplete;

		if (m_szFastaSequence)
			delete m_szFastaSequence;

		if (m_szFastaHeaderStrain)
			delete m_szFastaHeaderStrain;

		if (m_szFastaHeaderAddOn)
			delete m_szFastaHeaderAddOn;
	};

	long SetKeggMatrixBool(bool bKeggMatrix = true);
	long GetKeggMatrixBool(bool* bpKeggMatrix);
	bool GetKeggMatrixBool();
	long SetKeggMatrixRow(std::vector<char*>* pKeggMatrix);
	long GetKeggMatrixRow(std::vector<char*>** ppKegMatrix);
	std::vector<char*>* GetKeggMatrixRow();

	long SetHeaderNumber(unsigned long ulHeaderNumber);
	long SetHeaderNumber();
	long GetHeaderNumber(unsigned long* pulHeaderNumber);
	unsigned long GetHeaderNumber();

	char * GetFastaHeader();	
	long GetFastaHeader(char** ppFastaHeader);

	long GetFastaHeaderStrain(char ** ppFastaHeaderStrain);
	char* GetFastaHeaderStrain();

	long GetFastaHeaderRest(char** ppFastHeaderRest);
	char* GetFastaHeaderRest();

	long GetFastaSequence(char** ppFastaSequence);
	char* GetFastaSequence();

	long SetFastaHeader(const char* pFastaHeader);

	long SetFastaHeader(const char* pStart, const char* pEnd, bool bSetHeaderNumber = true);
	
	long SetFastaSequence(char* pFastaSequence);

	long SetFastaSequence(const char* pStart, const char* pEnd);

	long SetFastaBlock(const char* pStart, const char* pEnd, bool bSetHeaderNumber = true);

	long SetHeaderStrain(const char* pStart, const char* pEnd);
	long SetHeaderStrain(char* pHeaderStrain);

	long SetHeaderRest(const char* pStart, const char* pEnd);
	long SetHeaderRest(char* szHeaderRest);

	long SetBoolFastaBlockWrite(bool bFastaBlockWrite = true);

	long GetBoolFastaBlockWrite(bool* bpFastaBlockToWrite);
	bool GetBoolFastaBlockWrite();

	long SetFastaAddonHeader(const char* pFastaAddOnHeader);
	long SetFastaAddOnHeader(const char* pStart, const char* pEnd);
	
	long GetFastaAddOnHeader(char** ppFastaHeaderAddOn);
	char* GetFastaAddonHeader();

	long SetBoolFastaHeaderAddOn(bool bFastaHeaderAddOn = true);

	long RemoveGapsFromSequence();
	bool GetBoolFastaHeaderAddOn();

};

class CFastaFile
{
private:
	std::vector<CFastaBlock*> m_vecFastaBlock;
	char* m_szFastaFileName = nullptr;
	char* m_szMatchingName = nullptr;
	bool m_bDecontaminant = true;
	bool m_bFastaBlockSorted = false;
	bool m_bDeleteRows = true;
public:
	CFastaFile() {};
	~CFastaFile()
	{
		if (m_bDeleteRows == true)
			ClearVector<CFastaBlock>(&m_vecFastaBlock);
		else
			m_vecFastaBlock.clear(); //Objects does not get cleaned up (they are somehwere else). but the vector still have to be cleared.ss

		if (m_szFastaFileName)
			delete m_szFastaFileName;

	};

	long PushBackRowSafe(CFastaBlock* pFastablock)
	{
		if (!pFastablock)
			return MANAGEMENT_ERRORS::FASTA_PUSBACKBLOCK_ADD_VECTOR;
		m_vecFastaBlock.push_back(pFastablock);

		return ERR_NOERROR;
	}
	std::vector<CFastaBlock*>::iterator GetIteratorFirstItem()
	{
		return m_vecFastaBlock.begin();

	}

	std::vector<CFastaBlock*>::iterator GetIteratorLastItem()
	{
		return (m_vecFastaBlock.end() - 1);
	}


	static std::string StringToUpper(std::string strInput);


	long SetFastaFileName(const char* pStart, const char* pEnd);
	long SetFastaFileName(std::string strFileName);
	long GetFastaFileName(char** ppFastaFileName);
	char* GetFastaFileName();

	long SetMatchingName(const char* pStart, const char* pEnd);
	long SetMatchingName(std::string strMatchingName);
	long GetMatchingName(char* pMatchingName);
	char* GetMatchingName();

	void SetDeleteRows(bool bDelete = true) { m_bDeleteRows = bDelete; };
	void SetDecontaminant(bool bDecontaminant = true) { m_bDecontaminant = bDecontaminant; };
	
	bool GetDecontaminant() { return m_bDecontaminant; };


	long SortFastaFileAlphabetically();
	long SortFastasFilesOnHeaderNumbers();


	size_t GetVectorSize()
	{
		return m_vecFastaBlock.size();
	}

	std::vector<CFastaBlock*>* GetFastaBlockVector()
	{
		return &m_vecFastaBlock;
	}

	CFastaBlock* GetFastaBlock(size_t idx)
	{
		return m_vecFastaBlock.at(idx);
	}

	void PrintHeadersToScreen();

	long ParseFastaFile(const char* pPath, bool bSetHeaderNumber = true);

	long GetMatchingFastaBlock(const char* szMatch, CFastaBlock** ppFastaBlock);
	long GetFirstAndLastMatchingBlockWithStrain(const char* szMatch, std::vector<CFastaBlock*>::iterator* pIterLowPos, std::vector<CFastaBlock*>::iterator* pIterHighPos);
	long GetFirstAndLastMatchingBlockWithCompleteHeader(const char* szMatch, std::vector<CFastaBlock*>::iterator* pIterLowPos, std::vector<CFastaBlock*>::iterator* pIterHighPos);
	long GetMatchingFastaBlockNumber(unsigned long ulHeaderNumber, CFastaBlock** ppFastaBlock);
	long RemoveGapsFromFastaBlocks();

};

long FindMatchingFastaFile(std::vector<CFastaFile*>* pvecGenesFastaFile, const char* szToMatch, CFastaFile** ppFastaFileMatched, bool bDecontaminant = false, bool bSplitHeader = false);
long SplitHeaderNameAndNumber(const char* szToMatch, char** ppHeader, unsigned long* ulHeaderNumber, size_t* psizeBuffer);
long SortFastaFilesAlphabeticallyFileName(std::vector<CFastaFile*>* pvecFastaFiles);
long SortFastaFilesAlphabeticallyMatchingName(std::vector<CFastaFile*>* pvecFastaFiles);
long FindMatchingFastaFileFileName(std::vector<CFastaFile*>* pvecFastaFiles, char* pszFileName, CFastaFile** ppFoundFastaFile);
long FindMatchingFastaFileMatchingName(std::vector<CFastaFile*>* pvecFastaFiles, char* pszMatchingName, CFastaFile** ppFoundFastaFile);