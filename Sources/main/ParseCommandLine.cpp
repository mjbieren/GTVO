#include "GlobalHelper.h"

#define TOTALREQUIREMENTS 9

long ParseCommandLine(int argc, char* argv[], char* envp[])
{
	long lRet = ERR_NOERROR;

	int aiRequirements[TOTALREQUIREMENTS] = { 0,0,0,0,0,0,0,0,0};
	for (int i = 1; i < argc; i++)
	{

		printf_s("arg %i, %s %s", i, argv[i], EOL);



		if (*argv[i] == '-') //switch detected
		{
			switch (argv[i][1])
			{
			case 'f': //Input COGS PPP output folder path (Used to get the headers of parsed orthogroups.
				lRet = glb.propertyBag.SetCOGSPPPFolderPath(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_COGS_PPP_GTVO;
				aiRequirements[0] = 1;
				break;
			case 'p': //Input COGS FilterPPP output folder path (Used for the fasta files to obtain the right protein names)
				lRet = glb.propertyBag.SetCOGSFilterPPPFolderPath(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return 	PARSECOMMANDLINE_COGS_FPPP_GTVO;
				aiRequirements[1] = 1;
				break;
			case 'r': //Output dir Path
				lRet = glb.propertyBag.SetOutputFolderPath(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_OUTPUTFOLDER_GTVO;
				aiRequirements[2] = 1;
				break;
			case 'g': //Taxonomic Group File Path
				lRet = glb.propertyBag.SetTaxonomicGroupFilePath(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_TAXONOMICGROUP_GTVO;
				aiRequirements[3] = 1;
				break;
			case 't': //TPM Folder path (Kallisto Output
				lRet = glb.propertyBag.SetTPMFolderPath(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_TAXONOMICGROUP_GTVO;
				aiRequirements[4] = 1;
				break;
			case 'c': //Changed name folder
				lRet = glb.propertyBag.SetProteinNameChangedFolder(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_PROTEINNAME_CHANGE_GTVO;
				aiRequirements[5] = 1;
				break;
			case 'o': //Orthofinder output folder (But it is recommended to only use N0.tsv)
				lRet = glb.propertyBag.SetOrthoGroupDirPath(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_ORTHOGROUP_GTVO;
				aiRequirements[6] = 1;
				break;
			case 'x':
				lRet = glb.propertyBag.SetPrefixFiles(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_PREFIX_OUTPUT_GTVO;
				aiRequirements[7] = 1;
				lRet = glb.propertyBag.SetBoolPrefix();
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_BOOL_PREFIX_GTVO;
				aiRequirements[8] = 1;
				break;
			default:
			{
				printf_s("Invalid command line parameter no %i detected: %s %s", i, argv[i], EOL);
				return PARSE_COMMAND_LINE;
			}
			}


		}
		else if (*argv[i] == '?')
		{
			//print arguments: ToDO change it
			printf_s(
				"%s"
				"-f <COGS_PPP_Output_Folder> \t\t Set the Path to the directory containing the output of PPP with the COGS Set in the form of fasta files: REQUIRED %s"
				"-p <COGS_FPPP_Output_Folder> \t\t Set the Path to the directory containing the Orthogroups in TSV format: REQUIRED%s"
				"-c <Protein_Changed_Name_Folder> \t\t Set the Path the folder containing tsv files with old and simplified fasta header names: REQUIRED %s"
				"-t <TPM _VALUE_FOLDER> \t\t Set the Path the folder containg the TPM values for each sample (KAllisto output sub folders): REQUIRED %s"
				"-r <OutputFolderPath> \t\t Set the Output Folder Path: REQUIRED %s"
				"-g <TaxonomicGroupFile> \t\t Set the Taxonomic Group File path: REQUIRED. %s"
				"-o <Orthofinder Output Folder> \t\t Set the Path to the directory containing the Orthogroups in TSV format: REQUIRED%s"
				"-x <PREFIX> \t\t Set the prefix for the output files: NOT REQUIRED (BUT Recommended) %s"
				"%s"
				, EOL, EOL, EOL, EOL,EOL, EOL,EOL,EOL,EOL,EOL,EOL);
			return PARSE_COMMAND_LINE_MAN;
		}
		if (lRet != ERR_NOERROR)
			return lRet;
	}

	if (aiRequirements[7] == 0) //Prefix 
	{
		printf_s("No Prefix is added, a time stamp will be used instead as a prefix %s", EOL);
		aiRequirements[7] = 1;
	}

	if (aiRequirements[8] == 0) //Boolean Prefix
	{
		printf_s("No prefix is added, so a default value is used %s", EOL);
		aiRequirements[8] = 1;
	}
//Check if the other requiprements are met, if not sent a message to the user like if they would use ?. And sent back an error message.
	int iSum = 0;
	size_t idx = 0;
	while (idx < TOTALREQUIREMENTS)
	{
		iSum += aiRequirements[idx];
		idx++;
	}

	if (iSum == TOTALREQUIREMENTS)
		return lRet;
	else
	{
		//print arguments
		printf_s(
				"%s"
				"-f <COGS_PPP_Output_Folder> \t\t Set the Path to the directory containing the output of PPP with the COGS Set in the form of fasta files: REQUIRED %s"
				"-p <COGS_FPPP_Output_Folder> \t\t Set the Path to the directory containing the Orthogroups in TSV format: REQUIRED%s"
				"-c <Protein_Changed_Name_Folder> \t\t Set the Path the folder containing tsv files with old and simplified fasta header names: REQUIRED %s"
				"-t <TPM _VALUE_FOLDER> \t\t Set the Path the folder containg the TPM values for each sample (KAllisto output sub folders): REQUIRED %s"
				"-r <OutputFolderPath> \t\t Set the Output Folder Path: REQUIRED %s"
				"-g <TaxonomicGroupFile> \t\t Set the Taxonomic Group File path: REQUIRED. %s"
				"-o <Orthofinder Output Folder> \t\t Set the Path to the directory containing the Orthogroups in TSV format: REQUIRED%s"
				"-x <PREFIX> \t\t Set the prefix for the output files: NOT REQUIRED (BUT Recommended) %s"
				"%s"
				, EOL, EOL, EOL, EOL,EOL, EOL,EOL,EOL,EOL,EOL,EOL);
			return PARSE_COMMAND_LINE_MAN;
		return PARSE_COMMAND_LINE_MAN;
	}
	
	return lRet;
}