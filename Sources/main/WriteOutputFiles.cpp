#include "GlobalHelper.h"

long WriteOutputFiles(CTable* pTableAllOrthogroups, CTable* pTableFinalSetOrthogroups)
{
	long lReturn = ERR_NOERROR;


	/*
	Write the TSV files
	*/
	
	
	//Set the File Prefix
	std::string strPrefix;
	bool bPrefix = false;
	std::string strOutputPath;
	std::string strFullOutputPath;
	size_t sizeTableRows = 0;
	size_t sizeVectorRow = 0;
	std::vector<char*>* pvecCurrentRow = nullptr;

	char* pFileBuffer = new char[SIZE_BUFFER_ONE_GIG];
	CSmartPtr<char> pAutoDelete = pFileBuffer; //Create smart pointer so that we do not have to keep track of it.
	memset(pFileBuffer, '\0', SIZE_BUFFER_BIG); //Set all characters as zero terminated.
	size_t sizeBufferLeft = SIZE_BUFFER_BIG;
	char* pBufferPos = pFileBuffer;

	lReturn = glb.propertyBag.GetBoolPrefix(&bPrefix);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_BOOL_PREFIX_GTVO;

	if (bPrefix == false) //No Prefix
	{
		strPrefix = std::to_string(std::time(0)); //Get a timeStamp
	}
	else //we have a prefix;
	{
		lReturn = glb.propertyBag.GetPrefixFiles(&strPrefix);
		if (lReturn != ERR_NOERROR)
			return PROPERTYBAG_PREFIX_OUTPUT_GTVO;
	}

	//Get Output Path
	lReturn = glb.propertyBag.GetOutputFolderPath(&strOutputPath);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_OUTPUTFOLDER_GTVO;

	//Make the output folder if it doesn't exist yet
	std::string strMakeOutputDir = "mkdir -p " + strOutputPath;
	system(strOutputPath.c_str());

	/*
	Write pTableAllOrthogroup Then pTableFinalSet
	1) Obtain the size of the rows
	2) Loop over every Row
	3) Write every column to the file buffer
		A Get Column and place + \t
		Till End
		Replace last character with \n
	4) Put the file
	
	*/


	//pTableAllOrthogroups
	strFullOutputPath = strOutputPath + strPrefix + "_AllOrthoGroups_Orthofinder.tsv";
	
	printf_s("Create a TSV file containing all orthogroups and samples corresponding with their TPM Values.%s",EOL);

	//STEP 1

	sizeTableRows = pTableAllOrthogroups->GetAmountOfTableRows();
	//STEP 2
	for (size_t idx = 0; idx < sizeTableRows; idx++)
	{
		pvecCurrentRow = pTableAllOrthogroups->GetRow(idx);
		sizeVectorRow = pvecCurrentRow->size();
		//STEP 3
		for (size_t idx2 = 0; idx2 < sizeVectorRow; idx2++)
		{
			sizeBufferLeft = sizeBufferLeft - (pBufferPos - pFileBuffer);
			pBufferPos += sprintf_s(pBufferPos, sizeBufferLeft, "%s\t", pvecCurrentRow->at(idx2));

		}
		//Replace last \t for a 'n
		pBufferPos--;
		*pBufferPos = '\n';
		pBufferPos++;
	}

	//Remove last EOL
	pBufferPos--;
	*pBufferPos = '\0';

	//STEP 4
	lReturn = WriteOutputFile(pFileBuffer, strFullOutputPath);
	if (lReturn != ERR_NOERROR)
		return lReturn;
	


	////
	//Reset File Buffer.
	////

	memset(pFileBuffer, '\0', SIZE_BUFFER_BIG); //Set all characters as zero terminated.
	pBufferPos = pFileBuffer;
	sizeBufferLeft = SIZE_BUFFER_BIG;


	strFullOutputPath = strOutputPath + strPrefix + "_Final_Set_Orthogroups.tsv";
	
	printf_s("Create a TSV file containing the orthogroups used for the final set (+samples) corresponding with their TPM Values.%s",EOL);

	//STEP 1

	sizeTableRows =pTableFinalSetOrthogroups->GetAmountOfTableRows();
	//STEP 2
	for (size_t idx = 0; idx < sizeTableRows; idx++)
	{
		pvecCurrentRow = pTableFinalSetOrthogroups->GetRow(idx);
		sizeVectorRow = pvecCurrentRow->size();
		//STEP 3
		for (size_t idx2 = 0; idx2 < sizeVectorRow; idx2++)
		{
			sizeBufferLeft = sizeBufferLeft - (pBufferPos - pFileBuffer);
			pBufferPos += sprintf_s(pBufferPos, sizeBufferLeft, "%s\t", pvecCurrentRow->at(idx2));

		}
		//Replace last \t for a 'n
		pBufferPos--;
		*pBufferPos = '\n';
		pBufferPos++;
	}

	//Remove last EOL
	pBufferPos--;
	*pBufferPos = '\0';

	//STEP 4
	lReturn = WriteOutputFile(pFileBuffer, strFullOutputPath);
	if (lReturn != ERR_NOERROR)
		return lReturn;





	return lReturn;
}