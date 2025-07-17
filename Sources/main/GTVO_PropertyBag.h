#pragma once

#include "stdafx.h"
#include "Management.h"

class CGTVOPropertyBag : CPropertyBag
{
protected:
	char m_szGetTPMValuesOrthogroupsErrMessage[255];
public:
	CGTVOPropertyBag() {};
	~CGTVOPropertyBag() {};
	const char* GetGTPMValuesOrthogroupsErrorMessage() { return m_szGetTPMValuesOrthogroupsErrMessage; }

/*
Changed Protein Names Folder x
COGS PPP Output Folder x
COGS FilteredPPP Folder x
OrthoGroup Dir x
TPM Files Folder
Output Directory x
Taxonomic Group File x
*/
	long SetProteinNameChangedFolder(const char* szProteinNameChangedFolderPath)
	{
		std::string strProteinNameChangedFolderPath = szProteinNameChangedFolderPath;
		AppendSlash(&strProteinNameChangedFolderPath); //This is to make sure the path ends with a /
		return SetValueString("Paths", "ProteinNameChangedFolder", strProteinNameChangedFolderPath.c_str());
	}

	long GetProteinNameChangedFolderPath(std::string* pstrProteinNameChangedFolderPath)
	{
		return GetValueString("Paths", "ProteinNameChangedFolder", pstrProteinNameChangedFolderPath);
	}

	long SetCOGSPPPFolderPath(const char* szCOGSPPPFolderPath)
	{
		std::string strCOGSPPPFolderPath = szCOGSPPPFolderPath;
		AppendSlash(&strCOGSPPPFolderPath); //This is to make sure the path ends with a /
		return SetValueString("Paths", "COGSPPPFolder", strCOGSPPPFolderPath.c_str());
	}

	long GetCOGSPPPFolderPath(std::string* pstrCOGSPPPFolderPath)
	{
		return GetValueString("Paths", "COGSPPPFolder", pstrCOGSPPPFolderPath);
	}

	long SetCOGSFilterPPPFolderPath(const char* szCOGSPPPFolderPath)
	{
		std::string strCOGSFilterPPPFolderPath = szCOGSPPPFolderPath;
		AppendSlash(&strCOGSFilterPPPFolderPath); //This is to make sure the path ends with a /
		return SetValueString("Paths", "COGSFilterPPPFolder", strCOGSFilterPPPFolderPath.c_str());
	}

	long GetCOGSFilterPPPFolderPath(std::string* pstrCOGSFilterPPPFolderPath)
	{
		return GetValueString("Paths", "COGSFilterPPPFolder", pstrCOGSFilterPPPFolderPath);
	}

	long SetOrthoGroupDirPath(const char* szOGDirPath)
	{
		std::string strOGPath = szOGDirPath;
		AppendSlash(&strOGPath);
		return SetValueString("Paths", "OrthoGroups", strOGPath.c_str());
	}

	long GetOrthoGroupDirPath(std::string* pstrOrthoGroupsPath)
	{
		return GetValueString("Paths", "OrthoGroups", pstrOrthoGroupsPath);
	}

	long SetOutputFolderPath(const char* szOutputPath)
	{
		std::string strOutputPath = szOutputPath;
		AppendSlash(&strOutputPath);
		return SetValueString("Paths", "Output", strOutputPath.c_str());
	}

	long GetOutputFolderPath(std::string* pstrOutputPath)
	{
		return GetValueString("Paths", "Output", pstrOutputPath);
	}


	long SetTaxonomicGroupFilePath(const char* szTaxonomicGroupFile)
	{
		return SetValueString("Paths", "TaxonomicGroupFile", szTaxonomicGroupFile);
	}

	long GetTaxonomicGroupFilePath(std::string* pstrTaxonomicGroupFile)
	{
		return GetValueString("Paths", "TaxonomicGroupFile", pstrTaxonomicGroupFile);
	}

	long SetTPMFolderPath(const char* szTPMFolderPath)
	{
		return SetValueString("Paths", "TPM", szTPMFolderPath);
	}

	long GetTPMFolderPath(std::string* pstrTPMFolderPath)
	{
		return GetValueString("Paths", "TPM", pstrTPMFolderPath);
	}

	long SetPrefixFiles(const char* szPrefixFiles)
	{
		return SetValueString("Variable", "Prefix", szPrefixFiles);
	}

	long GetPrefixFiles(std::string* pstrPrefixFiles)
	{
		return GetValueString("Variable", "Prefix", pstrPrefixFiles);
	}


	long SetBoolPrefix(bool bSetPrefix = true)
	{
		return SetValueBool("Bool", "Prefix", bSetPrefix);
	}

	long GetBoolPrefix(bool* pBGetPrefix)
	{
		long lReturn = ERR_NOERROR;
		lReturn = GetValueBool("Bool", "Prefix", pBGetPrefix, false);
		if (lReturn == PROP_ERR_SECTION_NOT_FOUND_DEFAULT_USED)
		{
			printf_s("%s %s","Prefix Bool Not Found: Default No Prefix is used",EOL);
			return ERR_NOERROR;
		}
		return lReturn;
	}

};