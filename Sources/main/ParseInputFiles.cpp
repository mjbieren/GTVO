
#include "GlobalHelper.h"
long SetFileBuffer(char** pPos, std::string strFileName);
long SortFastaFilesAlphabeticallyMatchingName(std::vector<CFastaFile*> *pvecFastaFiles);


long ParseTPMFiles(std::vector<CTable*>* pvecTPMFiles)
{
	/*
	First we have to obtain all the possible files that has a tpm value
	As the Changed Protein Name files should have the exact same number, we use these as a reference for the TPM files. (as the TPM files are organized in a subdirectory manner).

	1) Get File names from the changed protein name folder
	2) Remove ".fa.headers_map.out" from the file
	3) Parse the Table with TPMFOLDERPATH/<ObtainedName>_1/abundance.tsv.genes
	4) Set Table name as the Obtained Name
	5) Pusbh back into vector
	6) Sort TPM Files
	*/

	long lReturn = ERR_NOERROR;

	std::string strChangedNamePath;
	lReturn = glb.propertyBag.GetProteinNameChangedFolderPath(&strChangedNamePath);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_PROTEINNAME_CHANGE_GTVO;

	std::string strTPMFolderPath;
	lReturn = glb.propertyBag.GetTPMFolderPath(&strTPMFolderPath);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_TPM_FOLDER_GTVO;


	//STEP ONE
	std::vector<std::string> vecChangedNames;
	size_t sizeChangedNameFiles = GetFilteredDirList(strChangedNamePath.c_str(), "*.fa.headers_map.out", &vecChangedNames);

	std::string strToRemove = ".fa.headers_map.out";
	size_t sizeStringToRemove = strToRemove.size();

	//STEP TWO
	std::vector<std::string> vecStringRemovedSuffixes;

	size_t sizeOriginalString = 0;
	std::string strIDX;

	for (size_t idx = 0; idx < sizeChangedNameFiles; idx++)
	{
		strIDX = vecChangedNames.at(idx);
		sizeOriginalString = strIDX.size();
		strIDX.resize(sizeOriginalString - sizeStringToRemove);
		vecStringRemovedSuffixes.push_back(strIDX);
	}

	//Sort the Vector
	std::sort(vecStringRemovedSuffixes.begin(), vecStringRemovedSuffixes.end());

	//STEP THREE
	std::string strFullTPMFilePath;

	CTable* pTPMTable = nullptr;

	for (size_t idx = 0; idx < sizeChangedNameFiles; idx++)
	{
		strIDX = vecStringRemovedSuffixes.at(idx);
		strFullTPMFilePath = strTPMFolderPath + strIDX + "_1/abundance.tsv.genes";
		pTPMTable = new CTable;

		lReturn = pTPMTable->ParseTableWithPath(strFullTPMFilePath);
		if (lReturn != ERR_NOERROR)
		{
			vecChangedNames.clear();
			vecStringRemovedSuffixes.clear();
			delete pTPMTable;
			return lReturn;
		}

		//STEP FOUR
		lReturn = pTPMTable->SetTableName(strIDX.c_str(), (strIDX.c_str() + strIDX.size()));
		if (lReturn != ERR_NOERROR)
		{
			vecChangedNames.clear();
			vecStringRemovedSuffixes.clear();
			delete pTPMTable;
			return lReturn;
		}
		//STEP FIVE
		pvecTPMFiles->push_back(pTPMTable);
	}

	//STEP SIX
	SortVectorTablesBasedOnTableNames(pvecTPMFiles); //We need to have it properly ordered :)

	return lReturn;
}


long ChangeTaxonomicGroupIDIncrement(CTaxonomicGroup* pTaxonomicGroup)
{
	/*
	* We have to do this because the order of the final result table is fixed (Based on the taxonomic group order of pTaxonomicGroup)
	* So all species with the object pTaxonomicGroup have to have their filter changed with an increment by 1 (first =1 , second = 2, etc)
	*/

	long lReturn = ERR_NOERROR;

	size_t sizeVector = pTaxonomicGroup->GetVectorSize();

	size_t idx_Increment = 1;

	CTaxonomicSpecies* pSpecies = nullptr;

	for (size_t idx = 0; idx < sizeVector; idx++)
	{
		pSpecies = pTaxonomicGroup->GetSpeciesVectorItem(idx);
		pSpecies->SetFilterNumber(idx_Increment);
		idx_Increment++;
	}

	return lReturn;

}

long ParseTaxonomicGroup(CTaxonomicGroup* pTaxonomicGroup, const char* pStart, const char* pEnd)
{
	//SpeciesName(HeaderName),SpeciesName2(HeaderName2),etc, EOL			#group 1
	
	long lReturn = ERR_NOERROR;

	const char* pPosStart = pStart;
	const char* pPos = pStart;
	const char* pPosEnd = pStart;

	CTaxonomicSpecies* pSpecies = nullptr;

	while (pPosEnd != pEnd)
	{
		while (*pPosEnd != ',' && pPosEnd != pEnd)		
			pPosEnd++;

		if (pPosEnd == pEnd) //Found the last one
			{
				//To make sure we don't end with a , at the end aka "SpeciesName(HeaderName),SpeciesName2(HeaderName2),"
				while (*pPos != '(' && pPos != pEnd)
					pPos++;

				if(pPos == pEnd) //Ended with a , at the end and not a header/species name.
					break;

				//Didn't end with a , instead of a ( meaning a headername start.
				pSpecies = new CTaxonomicSpecies;
				lReturn = pSpecies->SetSpeciesName(pPosStart, pPos - pPosStart);
				if (lReturn != ERR_NOERROR)
				{
					delete pSpecies;
					return lReturn;
				}


				pPosStart = pPos + 1; //we want to end it with 1 further than the (.
				
				while (*pPos != ')' && pPos != pEnd)
					pPos++;

				if (pPos == pEnd)
					{
						delete pSpecies;
						return PARSE_INPUT_FILE_TAXONOMICGROUPFILE_WRONG_FORMAT;//Error cuz we didn't end it at the right one.
					}

				lReturn = pSpecies->SetHeaderName(pPosStart, pPos - pPosStart);
				if (lReturn != ERR_NOERROR)
				{
					delete pSpecies;
					return lReturn;
				}
					
				//Push Back the taxonomic group
				pTaxonomicGroup->PushBack(pSpecies);

			}
		else //It's not the end
		{
			while (*pPos != '(' && pPos != pPosEnd)
				pPos++;
			
			if (pPos == pPosEnd)
				return PARSE_INPUT_FILE_TAXONOMICGROUPFILE_WRONG_FORMAT;
			
			pSpecies = new CTaxonomicSpecies;
			lReturn = pSpecies->SetSpeciesName(pPosStart, pPos - pPosStart);
			if (lReturn != ERR_NOERROR)
				{
					delete pSpecies;
					return lReturn;
				}

			pPosStart = pPos + 1; //we want to end it with 1 further than the (.

			while (*pPos != ')' && pPos != pPosEnd)
				pPos++;

			if (pPos == pPosEnd)
				return PARSE_INPUT_FILE_TAXONOMICGROUPFILE_WRONG_FORMAT;

			lReturn = pSpecies->SetHeaderName(pPosStart, pPos - pPosStart);
			if (lReturn != ERR_NOERROR)
				{
					delete pSpecies;
					return lReturn;
				}

			//Set them all time to push it back in the taxonomic group
			
			pTaxonomicGroup->PushBack(pSpecies);


			//move the pointers
			pPosEnd++;
			pPosStart = pPosEnd;
			pPos = pPosEnd;

		}



	}

	return lReturn;
}

long ParseTaxonomicGroups(std::vector<CTaxonomicGroup*> * pvecTaxonomicGroup, CTaxonomicGroup* pTaxonomicGroupsSorted)
{
	//This function parses the taxonomic group file into different taxonomic group objects and then add all the species into one taxonomic group sorted alphabetically.
	/*
	1) Parse the taxonomic group file into different taxonomic groups. 1 line = 1 group and push it back into one taxonomic group vector
	2) Set the idx of all taxanomic species to the same value in one taxonomic group.
	3) Parse all taxonomic species of each group into one taxanomic group object (everything in one object).
	4) Sort the taxonomic species vector within the taxonomic group sorted object alphabetically

	SpeciesName(HeaderName),SpeciesName2(HeaderName2),etc, EOL			#group 1
	SpeciesName3(HeaderName3),SpeciesName4(HeaderName4), etc, EOL		#group 2

	Every line is 1 HeadersFilters belonging to 1 group, every species within it belongs to 1 headerFilter.
	

	5) Extra for GTVO as we just want ot have a constant order for the table results (easy to look up), we have to change the group filter within the TaxonomicSpeices. with an increment of 1 (meaning every taxonomic species gets an unique "filter")
	*/
	long lReturn = ERR_NOERROR;

	std::string strTaxonomicGroupFile;

	lReturn = glb.propertyBag.GetTaxonomicGroupFilePath(&strTaxonomicGroupFile);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_TAXONOMICGROUPFILE_OSG;

	//Get the file buffer;
	char* pBuffer = nullptr;
	lReturn = SetFileBuffer(&pBuffer, strTaxonomicGroupFile);
	CSmartPtr<char> pAutoDelete = pBuffer;
	if (lReturn != ERR_NOERROR)
		return lReturn;

	char* pPos = pBuffer;
	char* pEnd = pBuffer;

	CTaxonomicGroup* pTaxonomicGroup = nullptr;


	//STEP ONE
	while (*pPos)
	{
		MOVE_PTR_TO_EOL_REAL(pEnd); //Looking at EOL or EOF. But not the one before
		pTaxonomicGroup = new CTaxonomicGroup;
		lReturn = ParseTaxonomicGroup(pTaxonomicGroup, pPos, pEnd);
		if (lReturn != ERR_NOERROR)
		{
			delete pTaxonomicGroup;
			return lReturn;
		}

		pvecTaxonomicGroup->push_back(pTaxonomicGroup);
		MOVE_PTR_TO_BOL(pEnd);
		pPos = pEnd;

	}

	//STEP TWO & STEP THREE
	size_t sizeTaxonomicGroupVector = pvecTaxonomicGroup->size();

	size_t sizeTaxonomicSpecies = 0;
	CTaxonomicSpecies* pSpecies = nullptr;
	
	for (size_t idx = 0; idx < sizeTaxonomicGroupVector; idx++)
	{
		pTaxonomicGroup = pvecTaxonomicGroup->at(idx);
		pTaxonomicGroup->SetDeleteTaxonomicSpecies(); //Also set that we delete the items, since this is the original.
		sizeTaxonomicSpecies = pTaxonomicGroup->GetVectorSize();
		for (size_t idx2 = 0; idx2 < sizeTaxonomicSpecies; idx2++)
		{
			pSpecies = pTaxonomicGroup->GetSpeciesVectorItem(idx2);
			pSpecies->SetFilterNumber(idx);
			pTaxonomicGroupsSorted->PushBack(pSpecies);
		}
	}



	//STEP FOUR
	lReturn = pTaxonomicGroupsSorted->SortTaxonomicGroupAlphabeticallyHeaders();
	if (lReturn != ERR_NOERROR)
		return lReturn;

	//STEP FIVE
	lReturn = ChangeTaxonomicGroupIDIncrement(pTaxonomicGroupsSorted);

	return lReturn;
}

long ParseOrthoGroups(std::vector<CTable*>* pvecOrthoGroups, size_t * pSizeOrthoGroups)
{
	//There are multiple orthogroup (.tsv files)
	/*
	Get A dir list of the tsv files
	Parse each individual tsv file into a table object
	push back the table object into the table vector.
	*/
	long lReturn = ERR_NOERROR;

	std::string strOrthoGroupFilePath;
	lReturn = glb.propertyBag.GetOrthoGroupDirPath(&strOrthoGroupFilePath);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_ORTHOGROUPDIR_OSG;

	std::vector<std::string> strDirList;

	size_t sizeOrthogroupDirList = GetFilteredDirList(strOrthoGroupFilePath.c_str(), "*.tsv", &strDirList);
	if (sizeOrthogroupDirList == 0)
	{
		printf_s("No orthogroup files in the folder %s %s", strOrthoGroupFilePath.c_str(), EOL);
		return DIRLIST_FAIL;
	}

	//We have now a list of file names in that folder time to parse the tables;

	std::string strFullPath;
	CTable* pOrthoGroupTable = nullptr;
	std::string strTableName;

	for (size_t idx = 0; idx < sizeOrthogroupDirList; idx++)
	{
		strTableName = strDirList.at(idx);
		strFullPath = strOrthoGroupFilePath + strTableName;
		pOrthoGroupTable = new CTable;
		pOrthoGroupTable->SetTableName(strTableName.c_str(), strTableName.c_str() + strTableName.length());
		printf_s("Working on Orthogroup file Nr.:%zu/%zu, %s %s",idx+1,sizeOrthogroupDirList, strDirList.at(idx).c_str(), EOL);
		lReturn = pOrthoGroupTable->ParseTableWithPath(strFullPath, 9, true); //They have headers, it's not a blast output file
		if (lReturn != ERR_NOERROR)
		{
			delete pOrthoGroupTable;
			return lReturn;
		}

		//We want to know the total amount of Orthogroups (for our summary file)
		*pSizeOrthoGroups += pOrthoGroupTable->GetAmountOfTableRows();
		//No Errors time to add the table into the vector
		pvecOrthoGroups->push_back(pOrthoGroupTable);

	}



	return lReturn;
}


long ParseChangedNameFiles(std::vector<CTable*>* pvecChangedNames)
{
	long lReturn = ERR_NOERROR;

	std::string strPathToChangedNameFiles;
	lReturn = glb.propertyBag.GetProteinNameChangedFolderPath(&strPathToChangedNameFiles);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_PROTEINNAME_CHANGE_GTVO;

	std::vector<std::string> vecChangedNameFiles;
	size_t sizeChangedNameFilesVector = 0;

	sizeChangedNameFilesVector = GetFilteredDirList(strPathToChangedNameFiles.c_str(), "*.fa.headers_map.out", &vecChangedNameFiles);

	CTable* pTable = nullptr;

	std::string strFileName;
	std::string strFullFilePath;
	std::string strSuffix = ".fa.headers_map.out";
	std::string strFileNameOnly;

	if (sizeChangedNameFilesVector != 0) //There are files whoohoo
	{
		for (size_t idx = 0; idx < sizeChangedNameFilesVector; idx++)
		{
			strFileName = vecChangedNameFiles.at(idx);
			strFullFilePath = strPathToChangedNameFiles + strFileName;

			pTable = new CTable;
			lReturn = pTable->ParseTableWithPath(strFullFilePath, 9, false);
			if (lReturn != ERR_NOERROR)
			{
				delete pTable;
				return lReturn;
			}

			strFileNameOnly = strFileName.substr(0, strFileName.length() - strSuffix.length());
			lReturn = pTable->SetTableName(strFileNameOnly.c_str(), strFileNameOnly.c_str() + strFileNameOnly.length());
			if (lReturn != ERR_NOERROR)
			{
				delete pTable;
				return lReturn;
			}
			pvecChangedNames->push_back(pTable);
		}
	}

	SortVectorTablesBasedOnTableNames(pvecChangedNames);

	return lReturn;
}

long ParseFastaFiles(std::vector<CFastaFile*> *pvecFastaFilesSource, std::vector<std::string> *pvecDirList, size_t sizeDirList, std::string strFolderPath, long lCutOffStrainName, size_t * pIdxFastaFile)
{
	long lReturn = ERR_NOERROR;

	CFastaFile* pFasta = nullptr;
	
	std::string strFileFullPath;
	std::string strFastaFileName;

	for (size_t idx = 0; idx < sizeDirList; idx++)
	{
		pFasta = new CFastaFile;
		strFastaFileName = pvecDirList->at(idx);
		//We want to copy the fasta file name, but we do not want to add .fasta/.fa/etc so we remove that.
		lReturn = pFasta->SetFastaFileName(strFastaFileName.c_str(), (strFastaFileName.c_str() + (strFastaFileName.length() - lCutOffStrainName)));
		lReturn = pFasta->SetMatchingName(strFastaFileName.c_str(), (strFastaFileName.c_str() + (strFastaFileName.length() - lCutOffStrainName)));
		if (lReturn != ERR_NOERROR)
		{
			delete pFasta;
			return lReturn;
		}

		//Set the full path
		strFileFullPath = strFolderPath + strFastaFileName;
		//Parse the fasta file into the object
		printf_s("Working on Fasta File Nr:%zu %s %s", *pIdxFastaFile,strFastaFileName.c_str(), EOL);
		*pIdxFastaFile = *pIdxFastaFile + 1;
		lReturn = pFasta->ParseFastaFile(strFileFullPath.c_str());
		//Check if there is an error;
		if (lReturn != ERR_NOERROR)
		{
			delete pFasta;
			return lReturn;
		}
		//if not order the fasta file now
		lReturn = pFasta->SortFastaFileAlphabetically();
		if (lReturn != ERR_NOERROR)
		{
			delete pFasta;
			return lReturn;
		}

		//It's sorted alphabetically now and there are no errors, we can add the file into the vector.
		pvecFastaFilesSource->push_back(pFasta);
		//NExt one :)
	}
	return lReturn;

}
long ParseFastaFilesPPPResult(std::vector<CFastaFile*>* pvecFastaFilesPPPResult)
{
	long lReturn = ERR_NOERROR;

	std::string strCOGSFilterPPPPath;
	lReturn = glb.propertyBag.GetCOGSFilterPPPFolderPath(&strCOGSFilterPPPPath);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_COGS_FPPP_GTVO;

	std::string strCOGSPPPPath;
	lReturn = glb.propertyBag.GetCOGSPPPFolderPath(&strCOGSPPPPath);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_COGS_PPP_GTVO;





	//Parse all fasta files into fasta file object.
	/*
	1) Get the Path of the fasta files from the Filtered PPP
	2) Get a dir list of all files in there, with .fasta, .fna, .ffn, .faa, .frn, .fa, .pep in them (7 in total).
	3) Check if there are some fasta files in them if not return error
	4) Parse the fasta files with the path of the COGS PPP + Fasta File Name
	5) Order the Fasta files as well.
	
	*/
	size_t sizeFastaFilesTotal = 0;
	size_t sizeFastaDirList = 0;

	
	//.FASTA
	std::vector<std::string> vecFastaFilesPaths;
	sizeFastaDirList = GetFilteredDirList(strCOGSFilterPPPPath.c_str(), "*.fasta", &vecFastaFilesPaths);
	sizeFastaFilesTotal += sizeFastaDirList;

	size_t idxFasta = 1;

	if (sizeFastaDirList != 0) //There are fasta files wtih the format .fasta
	{
		lReturn = ParseFastaFiles(pvecFastaFilesPPPResult, &vecFastaFilesPaths, sizeFastaDirList, strCOGSPPPPath, 6, &idxFasta);
		if (lReturn != ERR_NOERROR)
			return lReturn;
	}
	//Empty them
	vecFastaFilesPaths.clear();

	//.FNA
	sizeFastaDirList = GetFilteredDirList(strCOGSFilterPPPPath.c_str(), "*.fna", &vecFastaFilesPaths);
	sizeFastaFilesTotal += sizeFastaDirList;
	if (sizeFastaDirList != 0) //There are fasta files wtih the format .fna
	{
		lReturn = ParseFastaFiles(pvecFastaFilesPPPResult, &vecFastaFilesPaths, sizeFastaDirList, strCOGSPPPPath, 4,&idxFasta);
		if (lReturn != ERR_NOERROR)
			return lReturn;
	}
	//Empty them
	vecFastaFilesPaths.clear();

	//.FFN
	sizeFastaDirList = GetFilteredDirList(strCOGSFilterPPPPath.c_str(), "*.ffn", &vecFastaFilesPaths);
	sizeFastaFilesTotal += sizeFastaDirList;
	if (sizeFastaDirList != 0) //There are fasta files wtih the format .ffn
	{
		lReturn = ParseFastaFiles(pvecFastaFilesPPPResult, &vecFastaFilesPaths, sizeFastaDirList, strCOGSPPPPath, 4,&idxFasta);
		if (lReturn != ERR_NOERROR)
			return lReturn;
	}
	//Empty them
	vecFastaFilesPaths.clear();


	//.FAA
	sizeFastaDirList = GetFilteredDirList(strCOGSFilterPPPPath.c_str(), "*.faa", &vecFastaFilesPaths);
	sizeFastaFilesTotal += sizeFastaDirList;
	if (sizeFastaDirList != 0) //There are fasta files wtih the format .faa
	{
		lReturn = ParseFastaFiles(pvecFastaFilesPPPResult, &vecFastaFilesPaths, sizeFastaDirList, strCOGSPPPPath, 4, &idxFasta);
		if (lReturn != ERR_NOERROR)
			return lReturn;
	}
	//Empty them
	vecFastaFilesPaths.clear();
	

	//.FRN
	sizeFastaDirList = GetFilteredDirList(strCOGSFilterPPPPath.c_str(), "*.frn", &vecFastaFilesPaths);
	sizeFastaFilesTotal += sizeFastaDirList;
	if (sizeFastaDirList != 0) //There are fasta files wtih the format .frn
	{
		lReturn = ParseFastaFiles(pvecFastaFilesPPPResult, &vecFastaFilesPaths, sizeFastaDirList, strCOGSPPPPath, 4, &idxFasta);
		if (lReturn != ERR_NOERROR)
			return lReturn;
	}
	//Empty them
	vecFastaFilesPaths.clear();

	//.FA
	sizeFastaDirList = GetFilteredDirList(strCOGSFilterPPPPath.c_str(), "*.fa", &vecFastaFilesPaths);
	sizeFastaFilesTotal += sizeFastaDirList;
	if (sizeFastaDirList != 0) //There are fasta files wtih the format .fa
	{
		lReturn = ParseFastaFiles(pvecFastaFilesPPPResult, &vecFastaFilesPaths, sizeFastaDirList, strCOGSPPPPath, 3, &idxFasta);
		if (lReturn != ERR_NOERROR)
			return lReturn;
	}
	//Empty them
	vecFastaFilesPaths.clear();

	//.FAS
	sizeFastaDirList = GetFilteredDirList(strCOGSFilterPPPPath.c_str(), "*.fas", &vecFastaFilesPaths);
	sizeFastaFilesTotal += sizeFastaDirList;
	if (sizeFastaDirList != 0) //There are fasta files wtih the format .fas
	{
		lReturn = ParseFastaFiles(pvecFastaFilesPPPResult, &vecFastaFilesPaths, sizeFastaDirList, strCOGSPPPPath, 4, &idxFasta);
		if (lReturn != ERR_NOERROR)
			return lReturn;
	}
	//Empty them
	vecFastaFilesPaths.clear();


	//.PEP
	sizeFastaDirList = GetFilteredDirList(strCOGSFilterPPPPath.c_str(), "*.pep", &vecFastaFilesPaths);
	sizeFastaFilesTotal += sizeFastaDirList;
	if (sizeFastaDirList != 0) //There are fasta files wtih the format .pep
	{
		lReturn = ParseFastaFiles(pvecFastaFilesPPPResult, &vecFastaFilesPaths, sizeFastaDirList, strCOGSPPPPath, 4, &idxFasta);
		if (lReturn != ERR_NOERROR)
			return lReturn;
	}
	//Empty them
	vecFastaFilesPaths.clear();

	if (sizeFastaFilesTotal == 0)
		return DIRLIST_FAIL;


	//Sort the fasta files alphabetically
	lReturn = SortFastaFilesAlphabeticallyMatchingName(pvecFastaFilesPPPResult);
	return lReturn;
}

long ParseInputFiles(std::vector<CFastaFile*>* pvecFastaFilesPPPResult, std::vector<CTable*>* pvecOrthogroups, std::vector<CTable*> *pvecChangedNames, std::vector<CTable*>* pvecTPMFiles, std::vector<CTaxonomicGroup*>* pvecTaxonomicGroups, CTaxonomicGroup* pTaxonomicGroupSorted)
{
	long lReturn = ERR_NOERROR;


	//Parse the PPP Fasta Files into the vector, but only the fasta files that are part of the final set (Filter PPP Result).
	lReturn = ParseFastaFilesPPPResult(pvecFastaFilesPPPResult);
	if (lReturn != ERR_NOERROR)
		return lReturn;

	//Parse Changed Names
	lReturn = ParseChangedNameFiles(pvecChangedNames);
	if (lReturn != ERR_NOERROR)
		return lReturn;

	size_t SizeOrthogroup = 0; //We don't do something with this, but I copied this code from OSG :')
	//Parse Orthogroup file (Orthofinder N0.tsv file).
	lReturn = ParseOrthoGroups(pvecOrthogroups, &SizeOrthogroup);
	if (lReturn != ERR_NOERROR)
		return lReturn;

	//Parse Taxonomic Groups
	lReturn = ParseTaxonomicGroups(pvecTaxonomicGroups, pTaxonomicGroupSorted);
	if (lReturn != ERR_NOERROR)
		return lReturn;

	//Parse TPM FILES (Kallisto Output)
	lReturn = ParseTPMFiles(pvecTPMFiles);
	if (lReturn != ERR_NOERROR)
		return lReturn;



	return lReturn;
}