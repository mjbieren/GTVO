#include "GlobalHelper.h"
CGlobal glb;

long ParseCommandLine(int argc, char* argv[], char* envp[]);
long CheckReturnValue(long lReturn, std::vector<CFastaFile*>* pvecFastaFilesPPPResult, std::vector<CTable*>* pvecOrthoGroups, std::vector<CTaxonomicGroup*>* pvecTaxonomicGroups, std::vector<CTable*>* pvecChangedNames, std::vector<CTable*>* pvecTPMFiles);
long ParseInputFiles(std::vector<CFastaFile*>* pvecFastaFilesPPPResult, std::vector<CTable*>* pvecOrthogroups, std::vector<CTable*>* pvecChangedNames, std::vector<CTable*>* pvecTPMFiles, std::vector<CTaxonomicGroup*>* pvecTaxonomicGroups, CTaxonomicGroup* pTaxonomicGroupSorted);
long MatchOrthogroupsWithTPMValues(std::vector<CFastaFile*>* pvecFastaFilesPPPResult, CTaxonomicGroup* pTaxonomicGroupSorted, std::vector<CTable*>* pvecOrthoGroups, std::vector<CTable*>* pvecChangedNames, std::vector<CTable*>* pvecTPMFiles, CTable* pTableAllOrthogroups, CTable* pFinalSetOrthogroups);
long WriteOutputFiles(CTable* pTableAllOrthogroups, CTable* pTableFinalSetOrthogroups);

/*
OVERVIEW OF THE STEPS FOR THIS PROGRAM
Step 1 parse command line
	1) Folder with tsv files of changed protein names.
	2) COGS PPP Output
	3) COGS Filter PPP Output
	4) N0.tsv file
	5) TPM Files
	6) TaxonomicGroup File
	7) Result

	-f COGS PPP Output
	-p COGS Filter
	-c Changed Names
	-t TPM Value folder
	-r Result output folder
	-g Taxonomic group file path
	-o Orthofinder Output Folder


Step 2 parse input files
	Parse COGS PPP Output fasta files (All fasta files headers)
	COGS Filter PPP Output (Only need the header names).
	N0.tsv file
	Vector of tables of the TPM Files
	Vector of tables of protein name changes.
	Get Taxonomic group file and order alphabetically. (This will be the header order for  the tables). With Header position. (Add a variable that indicate order for header).
	
	
Step 3 Match TPM
	Create Table (Final result only)
	Set Header row
	Get HOG names from COGS Filter PPP Output.
		LOOP
			Get Fasta File with file name from HOG
				Create new row and set everything to N/A
				Loop over Fasta Headers
					Get Fasta Header name and check what the gene name was called by comparing it to protein name change files.
						If file does not excist TPM will be set to 0.
					Get TPM value from TPM gene file corresponding to the header name
					Replace N/A for the TPM Value.
					
					
	Create Table (All HOGS).
	Set Header Row
	Go step by step over the N0.tsv file
	If it's empy skip it, if it's filled, take the data
		There can be 0,1 or more proteins in there, So for each protein we have to find the original name form the protein name change files. If file does not excist (Species name), it will be set to 0 (for all proteins).
		Get TPM value from TPM gene file corresponding to the Header name.
		Replace N/A wit hthe TPM Value(s).
		

Step 4 Write output file:

rough overview

xx		Species 1	Species 2	Species N
HOG1
HOG2
HOG3
HOGN
				


*/

int main(int argc, char* argv[], char* envp[])
{

	 long lReturn = ERR_NOERROR;

    //STEP ONE
    printf_s("Step one: Parsing the command line %s", EOL);
    lReturn = ParseCommandLine(argc, argv, envp);
    CHECK_RETURNVALUE(lReturn);
    printf_s("Done with parsing the command line %s", EOL);


	//Set the Variables
	std::vector<CFastaFile*> vecFastaFilesPPPResult;
	std::vector<CTable*> vecOrthogroups; //Multiple files = multiple table files.
	std::vector<CTable*> vecChangedNames;
	std::vector<CTable*> vecTPMFiles;
	std::vector<CTaxonomicGroup*> vecTaxonomicGroups; //Taxonomic Group file split in different groups. The amount of objects in the vectors = how many taxonomic group sthere is in total. Do not confuse that with how many there need to be.
	

	//Create an object for the taxonomic Group but then sorted, for easy search during the matching.
    CTaxonomicGroup* pTaxonomicGroupSorted = new CTaxonomicGroup;
    //Set the boolean to delete the vector objects to false, since the objects exist in the vecTaxonomicGroups vector and we can't delete an object twice!
    pTaxonomicGroupSorted->SetDeleteTaxonomicSpecies(false);
    //Set a Smart pointer for the object so that we do not have to keep trace of deleting it, it will be deleted automatically :)
    CSmartPtr<CTaxonomicGroup> pAutoDeleteTaxonomicGroup = pTaxonomicGroupSorted;


	//STEP TWO
    printf_s("Step Two: Parsing the input files %s", EOL);
	lReturn = ParseInputFiles(&vecFastaFilesPPPResult, &vecOrthogroups, &vecChangedNames, &vecTPMFiles, &vecTaxonomicGroups, pTaxonomicGroupSorted);
	CheckReturnValue(lReturn, &vecFastaFilesPPPResult, &vecOrthogroups, &vecTaxonomicGroups, &vecChangedNames, &vecTPMFiles);
	CHECK_RETURNVALUE(lReturn);

	printf_s("Done with printing the input files%s", EOL);


	//STEP THREE
	CTable TableAllOrthogroups;
	CTable TableFinalSetOrthogroups;

	printf_s("Step Three: Time to match the Orthogroups with the TPM Values %s", EOL);
	lReturn = MatchOrthogroupsWithTPMValues(&vecFastaFilesPPPResult, pTaxonomicGroupSorted, &vecOrthogroups, &vecChangedNames, &vecTPMFiles, &TableAllOrthogroups, &TableFinalSetOrthogroups);
	CheckReturnValue(lReturn, &vecFastaFilesPPPResult, &vecOrthogroups, &vecTaxonomicGroups, &vecChangedNames, &vecTPMFiles);
	CHECK_RETURNVALUE(lReturn);
	printf_s("Done with matching %s", EOL);


	printf_s("Step Four: Write Output File %s", EOL);
	lReturn = WriteOutputFiles(&TableAllOrthogroups, &TableFinalSetOrthogroups);
	CheckReturnValue(lReturn, &vecFastaFilesPPPResult, &vecOrthogroups, &vecTaxonomicGroups, &vecChangedNames, &vecTPMFiles);
	CHECK_RETURNVALUE(lReturn);
	printf_s("Done with Writing the output files %s", EOL);


	ClearVector(&vecFastaFilesPPPResult);
	ClearVector(&vecOrthogroups); //CTable object and rows get deleted
    ClearVector(&vecTaxonomicGroups);
    ClearVector(&vecChangedNames);
    ClearVector(&vecTPMFiles);

    return 0;
}