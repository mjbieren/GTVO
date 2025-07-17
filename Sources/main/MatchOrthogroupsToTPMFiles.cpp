#include "GlobalHelper.h"

long CreateTableHeaderForGTVO(CTaxonomicGroup* pTaxonomicGroupSorted, std::vector<char*>* pRow)
{
	long lReturn = ERR_NOERROR;

	char* pColumn = nullptr;

	size_t sizeTaxonomicSpecies = pTaxonomicGroupSorted->GetVectorSize();

	//Very First Column
	pColumn = new char[15];
	memset(pColumn, '\0', 15);
	memcpy(pColumn, "OrthoGroup", 10);

	pRow->push_back(pColumn);

	CTaxonomicSpecies* pSpecies = nullptr;
	char* pSpeciesName = nullptr;
	size_t sizeSpeciesName = 0;

	for (size_t idx = 0; idx < sizeTaxonomicSpecies; idx++)
	{
		pSpecies = pTaxonomicGroupSorted->GetSpeciesVectorItem(idx);
		lReturn = pSpecies->GetSpeciesName(&pSpeciesName);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		sizeSpeciesName = strlen(pSpeciesName);

		if (sizeSpeciesName == 0)
			return GTVO_HEADER_CREATION_SPECIES_NAME_EMPTY;

		char* pColumn = new char[sizeSpeciesName + 10];
		memset(pColumn, '\0', (sizeSpeciesName + 10));
		memcpy(pColumn, pSpeciesName, sizeSpeciesName);
		pRow->push_back(pColumn);
	}


	return lReturn;
}

long MatchAllOrthoGroupsToTPM(CTaxonomicGroup* pTaxonomicGroupSorted, std::vector<CTable*>* pvecOrthoGroups, std::vector<CTable*>* pvecChangedNames,std::vector<CTable*>* pvecTPMFiles,CTable* pTableAllOrthogroups)
{
	long lReturn = ERR_NOERROR;
	
	/*
	Now we are matching all the orthogroups (output of orthofinder) against hte TPM values.

	1) Set Table Header
	2) Step over every tsv file
	3) Step over every row (starting from the 3rd? column), See OSG
	4) Take Header and species Name
	5) Obtain right table based on Species (Changed Name table), if not there the column should be changed to "Empty TPM"
	6) Obtain the 2nd row of the Changed Name and copy the protein name till . (minus the .) and minus the >
	7) Search TPM and obtain value from the fifth column ([4])
	8) Get the right idx number based on the pTaxonomicGroup
	9) Replace the column with the value (Delete it first).
	*/


	std::vector<char*>* pRow = nullptr;

	size_t sizeSpeciesVector = pTaxonomicGroupSorted->GetVectorSize();
	

	//STEP ONE
	//Start with add the header to the table Which is based on the TaxonomicGroupSorted.
	pRow = new std::vector<char*>;
	lReturn = CreateTableHeaderForGTVO(pTaxonomicGroupSorted, pRow);
	if (lReturn != ERR_NOERROR)
	{
		ClearVector(pRow);
		delete pRow;
		return lReturn;
	}
	lReturn = pTableAllOrthogroups->PushBackRowSafe(pRow);
	if (lReturn != ERR_NOERROR)
	{
		ClearVector(pRow);
		delete pRow;
		return lReturn;
	}

	//STEP TWO
	std::vector<char*>* pRowSearch = nullptr;
	size_t sizeOrthogroupFiles = pvecOrthoGroups->size();
	size_t sizeOrthogroupRowvector = 0;
	CTable* pTableOrthoGroupCurrent = nullptr;
	CTableRowHeader* pTableHeaderOrthogroupCurrent = nullptr;
	std::vector<char*> * pvecOrthogroupRow = nullptr;
	std::string strToClearWith = "N/A";
	std::string strTPMColumn;
	char* pSpeciesName = nullptr;
	
	CTable* pChangedNameTable = nullptr;
	CTable* pTPMFile = nullptr;
	CTaxonomicSpecies * pTaxSpecies = nullptr;
	size_t sizeidxSpecies = 0;
	
	char* pColumnToFill = nullptr;
	char* pCurrentColumn = nullptr;

	char szSearchBuffer[100];
	memset(szSearchBuffer, '\0', 100);
	char szSearchBufferForChanged[100];
	memset(szSearchBufferForChanged, '\0', 100);
	char* pStart = nullptr;
	char* pEnd = nullptr;

	char* pStartChangedName = nullptr;
	char* pEndChangedName = nullptr;
	size_t sizeColumns = 0;
	std::string strOrthoGroupName;

	size_t sizePosOfCharacterToBeReplaced = 0;
	size_t sizeCountCharacter = 0;


	//For loop for all TSV files
	for (size_t idx = 0; idx < sizeOrthogroupFiles; idx++)
	{
		pTableOrthoGroupCurrent = pvecOrthoGroups->at(idx);
		sizeOrthogroupRowvector = pTableOrthoGroupCurrent->GetAmountOfTableRows();
		lReturn = pTableOrthoGroupCurrent->GetHeaderRowTable(&pTableHeaderOrthogroupCurrent);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		//STEP THREE (Loop over every Row)
		for (size_t idx2 = 0; idx2 < sizeOrthogroupRowvector; idx2++)
		{
			pvecOrthogroupRow = pTableOrthoGroupCurrent->GetRow(idx2);
			sizeColumns = pvecOrthogroupRow->size();

			strOrthoGroupName = pvecOrthogroupRow->at(0); //Set first column of our row
			sizePosOfCharacterToBeReplaced = strOrthoGroupName.find('.', 0);
			strOrthoGroupName.replace(sizePosOfCharacterToBeReplaced, 1, "_"); //Replacing N0.000000001 for N0_000000001

			pRow = new std::vector<char*>;

			lReturn = CreateRowAndClearColumn(strToClearWith, sizeSpeciesVector + 1, pRow); //+1 because the orthogroup name is also a column
			if (lReturn != ERR_NOERROR)
			{
				ClearVector(pRow);
				delete pRow;
				return lReturn;
			}	

			//Replace the first column for the orthogroup name.

			lReturn = ReplaceStringForSzObject(&pColumnToFill, strOrthoGroupName);
			if (lReturn != ERR_NOERROR)
			{
				ClearVector(pRow);
				delete pRow;
				return lReturn;
			}	

			lReturn = ReplaceColumnData(&pRow, 0, pColumnToFill);
			if (lReturn != ERR_NOERROR)
			{
				ClearVector(pRow);
				delete pRow;
				return lReturn;
			}	

			//Now we go over every column but we skip the first 3, since we don't need them.
			for (size_t idx3 = 3; idx3 < sizeColumns; idx3++) //We will stepp over every species/sample within the orthogroup file. (From column 3 on)
			{
				strTPMColumn.clear(); //Empty it.
				//Check if the column is empty (can happen)
				if (memcmp(" ", pvecOrthogroupRow->at(idx3), 1) == 0) //No mathing gene families for this species.
					continue; //It's empty so we skip it!

				
				//Get the species name so we can get the right Matching File.
				pSpeciesName = pTableHeaderOrthogroupCurrent->GetVectorItem(idx3)->GetHeaderName();
				//Get the ColumnIdx for our column
				lReturn = pTaxonomicGroupSorted->FindTaxonomicSpeciesFromSpeciesName(pSpeciesName,&pTaxSpecies);
				if (lReturn != ERR_NOERROR)
				{
					ClearVector(pRow);
					delete pRow;
					return lReturn;
				}
				lReturn = FindMatchingTable(pSpeciesName, pvecChangedNames, &pChangedNameTable);
				if (lReturn == TABLE_FIND_TABLE_IN_TABLE_VECTOR_DOES_NOT_EXIST)
				{
					//Species does not have a TPM file :')
					//STEP 8
					lReturn = pTaxonomicGroupSorted->FindTaxonomicSpeciesFromSpeciesName(pSpeciesName,&pTaxSpecies);
					if (lReturn != ERR_NOERROR)
					{
						ClearVector(pRow);
						delete pRow;
						return lReturn;
					}

					sizeCountCharacter = CountHowManyOccurancesCharacterInBuffer(pvecOrthogroupRow->at(idx3),',',true);
					lReturn = DuplicateZeroTerminatedString("Empty TPM", sizeCountCharacter, &pColumnToFill); //with what we have to replace it		
					if (lReturn != ERR_NOERROR)
					{
						if (pRow)
						{
							ClearVector(pRow);
							delete pRow;
						}

						if(pChangedNameTable)
							delete pColumnToFill;
						return lReturn;
					}
			
					lReturn = pTaxSpecies->GetFilterNumber(&sizeidxSpecies);
					if (lReturn != ERR_NOERROR)
					{
						ClearVector(pRow);
						delete pRow;
						delete pColumnToFill;
						return lReturn;
					}

					lReturn = ReplaceColumnData(&pRow, sizeidxSpecies, pColumnToFill);
					if (lReturn != ERR_NOERROR)
					{
						ClearVector(pRow);
						delete pRow;
						delete pColumnToFill;
						return lReturn;
					}
					
					continue;
				}
				else if (lReturn != ERR_NOERROR)
				{
					ClearVector(pRow);
					delete pRow;
					return lReturn;
				}	


				lReturn = FindMatchingTable(pSpeciesName, pvecTPMFiles, &pTPMFile);
				if (lReturn == TABLE_FIND_TABLE_IN_TABLE_VECTOR_DOES_NOT_EXIST)
				{
					//Species does not have a TPM file :') but exist
					//STEP 8
					lReturn = pTaxonomicGroupSorted->FindTaxonomicSpeciesFromSpeciesName(pSpeciesName,&pTaxSpecies); //We need to find which column in the result have to be replaced (first the taxonomic species object)
					if (lReturn != ERR_NOERROR)
					{
						ClearVector(pRow);
						delete pRow;
						return lReturn;
					}

					sizeCountCharacter = CountHowManyOccurancesCharacterInBuffer(pvecOrthogroupRow->at(idx3),',',true);
					lReturn = DuplicateZeroTerminatedString("Empty TPM", sizeCountCharacter, &pColumnToFill); //with what we have to replace it		
					if (lReturn != ERR_NOERROR)
					{
						if (pRow)
						{
							ClearVector(pRow);
							delete pRow;
						}

						if(pChangedNameTable)
							delete pColumnToFill;
						return lReturn;
					}

					lReturn = pTaxSpecies->GetFilterNumber(&sizeidxSpecies); //which idx of the result table
					if (lReturn != ERR_NOERROR)
					{
						if (pRow)
						{
							ClearVector(pRow);
							delete pRow;
						}

						if(pChangedNameTable)
							delete pColumnToFill;
						return lReturn;
					}

					

					lReturn = ReplaceColumnData(&pRow, sizeidxSpecies, pColumnToFill); //And Replace it.
					if (lReturn != ERR_NOERROR)
					{
						if (pRow)
						{
							ClearVector(pRow);
							delete pRow;
						}

						if(pChangedNameTable)
							delete pColumnToFill;
						return lReturn;
					}

				
					continue; //We continue since even if there are more columns it's going to be zero as we don't have tpm values.
				}
				else if (lReturn != ERR_NOERROR)
				{
					ClearVector(pRow);
					delete pRow;
					return lReturn;
				}	
				
				
				//Get Orthogroup Table column
				pCurrentColumn = pvecOrthogroupRow->at(idx3);
				pStart = pCurrentColumn;
				pEnd = pCurrentColumn;

				//Find the corresponding fasta Headers from the corresponding Orthogroup file
				//It looks like "A1-1, A1-2, A1-3" And they all have to be found.
				while (*pEnd)
				{
					while (*pEnd != ',' && *pEnd)
						pEnd++;

					memset(szSearchBuffer, '\0', 100);
					memcpy(szSearchBuffer, pStart, pEnd - pStart);

					memset(szSearchBufferForChanged, '\0', 100);
					sprintf_s(szSearchBufferForChanged, 100, ">%s", szSearchBuffer);

					//Find Matching gene from Changed Name File
					lReturn = pChangedNameTable->FindMatchingRow(szSearchBufferForChanged, &pRowSearch);
					if (lReturn != ERR_NOERROR)
					{
						if (pRow)
						{
							ClearVector(pRow);
							delete pRow;
						}
						return lReturn;
					}

					pStartChangedName = pRowSearch->at(1);
					pStartChangedName++; //To go byond the >
					pEndChangedName = pStartChangedName;
					while (*pEndChangedName != '.' && pEndChangedName)
						pEndChangedName++;

					memset(szSearchBuffer, '\0', 100);
					memcpy(szSearchBuffer, pStartChangedName, pEndChangedName - pStartChangedName);

					//Find Matching TPM Value
					lReturn = pTPMFile->FindMatchingRow(szSearchBuffer, &pRowSearch);
					if (lReturn != ERR_NOERROR)
					{
						if (pRow)
						{
							ClearVector(pRow);
							delete pRow;
						}
						return lReturn;
					}

					strTPMColumn = strTPMColumn + pRowSearch->at(4) + ", ";
					while (*pEnd == ' ' || *pEnd == ',')
						pEnd++;
					pStart = pEnd;

					pEnd++;
				}
				
				//Remove the last two characters from the column "tpmvalue1, tpmvalue2, "
				strTPMColumn.pop_back();
				strTPMColumn.pop_back();

				lReturn = ReplaceStringForSzObject(&pColumnToFill, strTPMColumn);
				if(lReturn != ERR_NOERROR)
				{
					ClearVector(pRow);
					delete pRow;
					delete pColumnToFill;
					return lReturn;
				}
				

				lReturn = pTaxSpecies->GetFilterNumber(&sizeidxSpecies);
				if (lReturn != ERR_NOERROR)
				{
					ClearVector(pRow);
					delete pRow;
					delete pColumnToFill;
					return lReturn;
				}

				//Replace the old column for the new column
				lReturn = ReplaceColumnData(&pRow, sizeidxSpecies, pColumnToFill); //And Replace it.
				if(lReturn != ERR_NOERROR)
				{
					ClearVector(pRow);
					delete pRow;
					delete pColumnToFill;
					return lReturn;
				}

				
			}
			lReturn = pTableAllOrthogroups->PushBackRowSafe(pRow);
			if(lReturn != ERR_NOERROR)
			{
				ClearVector(pRow);
				delete pRow;
				delete pColumnToFill;
				return lReturn;
			}
		}
	}

	return lReturn;
}

long MatchFinalOrthogroupSetToTPM(CTaxonomicGroup* pTaxonomicGroupSorted, std::vector<CFastaFile*>* pvecFastaFilesPPPResult, std::vector<CTable*>* pvecChangedNames,std::vector<CTable*>* pvecTPMFiles,CTable* pFinalSetOrthogroups)
{

	/*
	Now we are matching the Final orthogroup set against the TPM values.
	1) Set Table Header
	2) Step over Every Fasta File
	3) Step over Every Fasta Header
	4) Take full header & Species Name
	5) Obtain right table based on Species (Changed Name table), if not there the column should be changed to "0"
	6) Obtain the 2nd row of the Changed Name and copy the protein name till . (minus the .) and minus the >
	7) Search TPM and obtain value from the fifth column ([4])
	8) Get the right idx number based on the pTaxonomicGroup
	9) Replace the column with the value (Delete it first).
	*/

	long lReturn = ERR_NOERROR;

	std::vector<char*>* pRow = nullptr;

	size_t sizeSpeciesVector = pTaxonomicGroupSorted->GetVectorSize();
	

	//STEP ONE
	//Start with add the header to the table Which is based on the TaxonomicGroupSorted.
	pRow = new std::vector<char*>;
	lReturn = CreateTableHeaderForGTVO(pTaxonomicGroupSorted, pRow);
	if (lReturn != ERR_NOERROR)
	{
		ClearVector(pRow);
		delete pRow;
		return lReturn;
	}
	lReturn = pFinalSetOrthogroups->PushBackRowSafe(pRow);
	if (lReturn != ERR_NOERROR)
	{
		ClearVector(pRow);
		delete pRow;
		return lReturn;
	}

	
	//STEP TWO
	std::vector<char*>* pRowSearch = nullptr;
	size_t sizeFastaFiles = pvecFastaFilesPPPResult->size();
	size_t sizeFastaBlockvector = 0;
	CFastaFile* pFastasFile = nullptr;
	CFastaBlock * pFastaBlock = nullptr;
	std::string strToClearWith = "N/A";
	std::string strOrthoGroupName;
	char* pSpeciesName = nullptr;
	char* pFullHeader = nullptr;
	char* pOrthoGroupname = nullptr;
	CTable* pChangedNameTable = nullptr;
	CTable* pTPMFile = nullptr;
	CTaxonomicSpecies * pTaxSpecies = nullptr;
	size_t sizeidxSpecies = 0;
	
	char* pColumnToFill = nullptr;

	char szSearchBuffer[100];
	memset(szSearchBuffer, '\0', 100);
	char* pStart = nullptr;
	char* pEnd = nullptr;

	std::string strSearchChangedNamesRow;
	


	for (size_t idx = 0; idx < sizeFastaFiles; idx++) //One Fasta File = One Row in pFinalOrthoGroups
	{
		pFastasFile = pvecFastaFilesPPPResult->at(idx);
		pRow = new std::vector<char*>;

		lReturn = CreateRowAndClearColumn(strToClearWith, sizeSpeciesVector + 1, pRow);
		if (lReturn != ERR_NOERROR)
		{
			ClearVector(pRow);
			delete pRow;
			return lReturn;
		}

		lReturn = pFastasFile->GetFastaFileName(&pOrthoGroupname);
		if (lReturn != ERR_NOERROR)
		{
			ClearVector(pRow);
			delete pRow;
			return lReturn;
		}

		//Replace the first column for the orthogroup name.
		strOrthoGroupName = pOrthoGroupname;
		lReturn = ReplaceStringForSzObject(&pColumnToFill, strOrthoGroupName);
		if (lReturn != ERR_NOERROR)
		{
			ClearVector(pRow);
			delete pRow;
			if (pColumnToFill)
				delete pColumnToFill;
			return lReturn;
		}
		
		lReturn = ReplaceColumnData(&pRow, 0, pColumnToFill);
		if(lReturn != ERR_NOERROR)
		{
			ClearVector(pRow);
			delete pRow;
			if (pColumnToFill)
				delete pColumnToFill;
			return lReturn;
		}

		

		//STEP THREE
		sizeFastaBlockvector = pFastasFile->GetVectorSize();
		for (size_t idx2 = 0; idx2 < sizeFastaBlockvector; idx2++)
		{
			
			//STEP FOUR
			pFastaBlock = pFastasFile->GetFastaBlock(idx2);
			lReturn = pFastaBlock->GetFastaHeaderStrain(&pSpeciesName);
			if (lReturn != ERR_NOERROR)
			{
				ClearVector(pRow);
				delete pRow;
				return lReturn;
			}

			lReturn = pFastaBlock->GetFastaHeader(&pFullHeader);
			if (lReturn != ERR_NOERROR)
			{
				ClearVector(pRow);
				delete pRow;
				return lReturn;
			}

			//Replace the @ sign (for the PPP format back to "-"
			pEnd = pFullHeader;
			while (*pEnd)
			{
				if (*pEnd == '@')
					*pEnd = '-'; //Replace
				pEnd++;
			}


			lReturn = FindMatchingTable(pSpeciesName, pvecChangedNames, &pChangedNameTable);
			//STEP FIVE
			if (lReturn == TABLE_FIND_TABLE_IN_TABLE_VECTOR_DOES_NOT_EXIST)
			{
				//Species does not have a TPM file :')
				//STEP 8
				lReturn = pTaxonomicGroupSorted->FindTaxonomicSpeciesFromSpeciesName(pSpeciesName,&pTaxSpecies);
				if (lReturn != ERR_NOERROR)
				{
					ClearVector(pRow);
					delete pRow;
					return lReturn;
				}

				lReturn = ReplaceStringForSzObject(&pColumnToFill, "Empty TPM");
				if (lReturn != ERR_NOERROR)
				{
					ClearVector(pRow);
					delete pRow;
					if (pColumnToFill)
						delete pColumnToFill;
					return lReturn;
				}	

				lReturn = pTaxSpecies->GetFilterNumber(&sizeidxSpecies);
				if (lReturn != ERR_NOERROR)
				{
					ClearVector(pRow);
					delete pRow;
					delete pColumnToFill;
					return lReturn;
				}

				lReturn = ReplaceColumnData(&pRow, sizeidxSpecies, pColumnToFill);
				if (lReturn != ERR_NOERROR)
				{
					ClearVector(pRow);
					delete pRow;
					delete pColumnToFill;
					return lReturn;
				}
				continue;

			}
			else if (lReturn != ERR_NOERROR)
			{
				ClearVector(pRow);
				delete pRow;
				return lReturn;
			}

			//STEP SIX
			memset(szSearchBuffer, '\0', 100);
			sprintf_s(szSearchBuffer, 100, ">%s", pFullHeader);

			lReturn = pChangedNameTable->FindMatchingRow(szSearchBuffer, &pRowSearch);
			if(lReturn != ERR_NOERROR)
			{
				ClearVector(pRow);
				delete pRow;
				return lReturn;
			}

			pStart = pRowSearch->at(1);
			pStart++; //To go byond the >
			pEnd = pStart;
			while (*pEnd != '.' && pEnd)
				pEnd++;

			memset(szSearchBuffer, '\0', 100);
			memcpy(szSearchBuffer, pStart, pEnd - pStart);

			//Now we have the Gene name Now we have to find the right TPM Table and the TPM value
			//STEP 7

			lReturn = FindMatchingTable(pSpeciesName, pvecTPMFiles, &pTPMFile);
			if (lReturn == TABLE_FIND_TABLE_IN_TABLE_VECTOR_DOES_NOT_EXIST)
			{
				//Species does not have a TPM file :')
				//STEP 8
				lReturn = pTaxonomicGroupSorted->FindTaxonomicSpeciesFromSpeciesName(pSpeciesName,&pTaxSpecies);
				if (lReturn != ERR_NOERROR)
				{
					ClearVector(pRow);
					delete pRow;
					return lReturn;
				}

				lReturn = ReplaceStringForSzObject(&pColumnToFill, "Empty TPM");
				if (lReturn != ERR_NOERROR)
				{
					ClearVector(pRow);
					delete pRow;
					if(pColumnToFill)
						delete pColumnToFill;
					return lReturn;
				}

				lReturn = pTaxSpecies->GetFilterNumber(&sizeidxSpecies);
				if (lReturn != ERR_NOERROR)
				{
					ClearVector(pRow);
					delete pRow;
					delete pColumnToFill;
					return lReturn;
				}

				lReturn = ReplaceColumnData(&pRow, sizeidxSpecies, pColumnToFill);
				{
					ClearVector(pRow);
					delete pRow;
					delete pColumnToFill;
					return lReturn;
				}
				

			}
			else if (lReturn != ERR_NOERROR)
			{
				ClearVector(pRow);
				delete pRow;
				return lReturn;
			}

			lReturn = pTPMFile->FindMatchingRow(szSearchBuffer, &pRowSearch);
			if(lReturn != ERR_NOERROR)
			{
				ClearVector(pRow);
				delete pRow;
				return lReturn;
			}

			pStart = pRowSearch->at(4);
			pEnd = pStart;
			MOVE_PTR_TO_EOL(pEnd);

			lReturn = pTaxonomicGroupSorted->FindTaxonomicSpeciesFromSpeciesName(pSpeciesName,&pTaxSpecies);
			if (lReturn != ERR_NOERROR)
			{
				ClearVector(pRow);
				delete pRow;
				return lReturn;
			}

			pColumnToFill = new char[pEnd-pStart+10];
			memset(pColumnToFill, '\0', (pEnd-pStart+10));
			memcpy(pColumnToFill, pStart, (pEnd-pStart+1));

			lReturn = pTaxSpecies->GetFilterNumber(&sizeidxSpecies);
			if (lReturn != ERR_NOERROR)
			{
				ClearVector(pRow);
				delete pRow;
				delete pColumnToFill;
				return lReturn;
			}

			lReturn = ReplaceColumnData(&pRow, sizeidxSpecies, pColumnToFill);
			if(lReturn != ERR_NOERROR)
			{
				ClearVector(pRow);
				delete pRow;
				delete pColumnToFill;
				return lReturn;
			}



		}

		lReturn = pFinalSetOrthogroups->PushBackRowSafe(pRow);
		if (lReturn != ERR_NOERROR)
		{
				ClearVector(pRow);
				delete pRow;
				delete pColumnToFill;
				return lReturn;
		}
	}


	return lReturn;
}

long MatchOrthogroupsWithTPMValues(std::vector<CFastaFile*>* pvecFastaFilesPPPResult, CTaxonomicGroup* pTaxonomicGroupSorted, std::vector<CTable*>* pvecOrthoGroups, std::vector<CTable*>* pvecChangedNames, std::vector<CTable*>* pvecTPMFiles, CTable* pTableAllOrthogroups, CTable* pFinalSetOrthogroups)
{
	long lReturn = ERR_NOERROR;

	lReturn = MatchFinalOrthogroupSetToTPM(pTaxonomicGroupSorted, pvecFastaFilesPPPResult, pvecChangedNames, pvecTPMFiles, pFinalSetOrthogroups);
	if (lReturn != ERR_NOERROR)
		return lReturn;

	lReturn = MatchAllOrthoGroupsToTPM(pTaxonomicGroupSorted, pvecOrthoGroups, pvecChangedNames, pvecTPMFiles, pTableAllOrthogroups);
	if (lReturn != ERR_NOERROR)
		return lReturn;

	return lReturn;

}