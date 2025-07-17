#include "GlobalHelper.h"

long CheckReturnValue(long lReturn, std::vector<CFastaFile*> * pvecFastaFilesPPPResult, std::vector<CTable*> * pvecOrthoGroups, std::vector<CTaxonomicGroup*> *pvecTaxonomicGroups, std::vector<CTable*> * pvecChangedNames, std::vector<CTable*> * pvecTPMFiles)
{
    if (lReturn != ERR_NOERROR)
    {
        ClearVector(pvecFastaFilesPPPResult);
		ClearVector(pvecOrthoGroups); //CTable object and rows get deleted
        ClearVector(pvecTaxonomicGroups);
        ClearVector(pvecChangedNames);
        ClearVector(pvecTPMFiles);
       
    }

    return lReturn;

}