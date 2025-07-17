#include "Management.h"

long CManagement::ErrorChecker(long lError) const
{
	if (lError != ERR_NOERROR)
	{

#ifdef _WINDOWS
		printf_s("Error %i detected: %s \n", lError, GetErrorDescription(lError));
#elif _LINUX
		printf("Error %i detected: %s \r\n", lError, GetErrorDescription(lError));
#endif

		return lError;
	}
	else
		return ERR_NOERROR;

}

const char* CManagement::GetErrorDescription(long lError)const
{
	switch (lError)
	{
	case ERR_NOERROR:
		return "Error ERR_NOERROR, No Error Occured.";
	case PARSE_COMMAND_LINE:
		return "Error PARSE_COMMAND_LINE, could not parse the command line.";
	case PARSE_COMMAND_LINE_MAN:
		return "Please restart the program with the right parameters.";
	case DIRLIST_FAIL:
		return "Error DIRLIST_FAIL, failed to obtain files with the chosen directory.";
	case ERR_SPLIT_STRING_SEPARATE_SUBS:
		return "Error ERR_SPLIT_STRING_SEPARATE_SUBS, failed to split the columns split char not found.";
	case PARSECOMMANDLINE_COLUMNNUMBER_GPDS:
		return "Error PARSECOMMANDLINE_COLUMNNUMBER_GPDS, was not able to set the column number of the blast output file";
	case PARSECOMMANDLINE_BLASTEXTENSION_GPDS:
		return "Error PARSECOMMANDLINE_BLASTEXTENSION_GPDS, was not able to set the file extension of the blast output file";
	case PARSECOMMANDLINE_FASTAQUERY_GPDS:
		return "Error PARSECOMMANDLINE_FASTAQUERY_GPDS, was not able to set the path of the Query.fa file";
	case PARSECOMMANDLINE_GENESPATH_GPDS:
		return "Error PARSECOMMANDLINE_GENESPATH_GPDS, was not able to set the genes.txt file";
	case PARSECOMMANDLINE_BLASTFILE_GPDS:
		return "Error PARSECOMMANDLINE_BLASTFILE_GPDS, was not able to set the path of the blast file.";
	case PARSECOMMANDLINE_OUTPUTPATH_GPDS:
		return "Error PARSECOMMANDLINE_OUTPUTPATH_GPDS, Was not able to set the output folder.";
	case PARSECOMMANDLINE_STRAINNAME_GPDS:
		return "Error PARSECOMMANDLINE_STRAINNAME_GPDS, was not able to set the strain name.";
	case PARSECOMMANDLINE_DECONTAMINATIONLIST_GPDS:
		return "Error PARSECOMMANDLINE_DECONTAMINATIONLIST_GPDS, was not able to set the Decontamination list.";
	case PARSECOMMANDLINE_STRICTDECONTAMINATION_GPDS:
		return "Error PARSECOMMANDLINE_STRICTDECONTAMINATION_GPDS, was not able to set the decontamination filter to strict.";
	case PARSECOMMANDLINE_KEGGMATRIX_GPDS:
		return "Error PARSECOMMANDLINE_KEGGMATRIX_GPDS, was not able to set the path Kegg Matrix tsv.";
	case PARSECOMMANDLINE_KEGGBOOL_GPDS:
		return "Error PARSECOMMANDLINE_KEGGBOOL_GPDS, was not able to set the if the user want to get the Kegg matrix parsed.";
	case PARSECOMMANDLINE_GENEMAPSPATH_GPDS:
		return "Error PARSECOMMANDLINE_GENEMAPSPATH_GPDS, was not able to set the path to the gene maps.";
	case PARSECOMMANDLINE_GENEMAPSBOOL_GPDS:
		return "PARSECOMMANDLINE_GENEMAPSBOOL_GPDS, was not able to set the if the user want the gene maps parsed or not.";
	case PARSECOMMANDLINE_FASTADIR_OSG: //Command Line OSG
		return "Error PARSECOMMANDLINE_FASTADIR_OSG, was not able to set the path to the fasta files for OSG. Do you have permission?";
	case PARSECOMMANDLINE_ORTHOGROUPDIR_OSG:
		return "Error PARSECOMMANDLINE_ORTHOGROUPDIR_OSG, was not able to set the path to the Orthogroup files in tsv format, Do you have permission?";
	case PARSECOMMANDLINE_OUTPUTDIR_OSG:
		return "Error PARSECOMMANDLINE_OUTPUTDIR_OSG, was not able to set the path to the Output path.";
	case PARSECOMMANDLINE_TAXONOMICGROUPFILE_OSG:
		return "Error PARSECOMMANDLINE_TAXONOMICGROUPFILE_OSG. Was not able to set the full path to the Taxonomic Group file.";
	case PARSECOMMANDLINE_TAXONOMICTHRESHOLD_OSG:
		return "Error PARSECOMMANDLINE_TAXONOMICTHRESHOLD_OSG, was not able to set the threshold value for the taxonomic groups. Be sure it's a value lower than 9,223,372,036,854,775,807, without the commas";
	case PARSECOMMANDLINE_TAXONOMICTHRESHOLD_TOOLOW_OSG:
		return "Error PARSECOMMANDLINE_TAXONOMICTHRESHOLD_TOOLOW_OSG you can not do the filtering step with a negative number or 0. The minimum value is '1' for this program";
	case PARSECOMMANDLINE_PHYLOPYPRUNERFORMAT_OSG:
		return "Error PARSECOMMANDLINE_PHYLOPYPRUNERFORMAT_OSG, could not set the program to format the output to PhyloPyPruner aka SpeciesName@GeneID e.g. Umutabilis@1";
	case PARSECOMMANDLINE_SUMMARYPATH_OSG:
		return "Error PARSECOMMANDLINE_SUMMARYPATH_OSG, Could not set the path for the summary file.";
	case PARSECOMMANDLINE_BOOLSUMMARY_OSG:
		return "Error PARSECOMMANDLINE_BOOLSUMMARY_OSG, could not set if the user want a summary file or not.";
	case PARSECOMMANDLINE_BOOLSKIPTAXONOMICHEADER_OSG:
		return "Error PARSECOMMANDLINE_BOOLSKIPTAXONOMICHEADER_OSG, could not set if the user want to skip the files missing taxonomic headers in the taxonomic group file.";
	case PARSECOMMANDLINE_BOOLTAXGROUPFILTER_OSG:
		return "Error PARSECOMMANDLINE_BOOLTAXGROUPFILTER_OSG, could not set the boolean if the user wants to skip taxonomic group filtering.";
	case PARSECOMMANDLINE_BOOLCONCATENATE_HOGS_OSG:
		return "Error PARSECOMMANDLINE_BOOLCONCATENATE_HOGS_OSG, could not set the boolean if the user want to concatenate the HOGS into one OG.";
	case PARSECOMMANDLINE_BOOLSTRAINONLY_SCPT:
		return "Error PARSECOMMANDLINE_BOOLSTRAINONLY_SCPT, could not set if the user have only strains in their headers or not.";
	case PARSECOMMANDLINE_TREEFORMAT_APPPF:
		return "Error PARSECOMMANDLINE_TREEFORMAT_APPPF, could not set the file extension for the tree Files.";
	case PARSECOMMANDLINE_TREEDIR_APPPF:
		return "Error PARSECOMMANDLINE_TREEDIR_APPPF, could not set the path to the tree files.";
	case PARSECOMMANDLINE_TAXONOMICGROUPFILE_APPPF:
		return "Error PARSECOMMANDLINE_TAXONOMICGROUPFILE_APPPF, could not set the path to the taxonomic group file.";
	case PARSECOMMANDLINE_OUTPUTFOLDER_APPPF:
		return "Error PARSECOMMANDLINE_OUTPUTFOLDER_APPPF, could not set the path to the output folder.";
	case PARSECOMMANDLINE_BOOLMOVEMAFFTFILE_APPPF:
		return "Error PARSECOMMANDLINE_BOOLMOVEMAFFTFILE_APPPF, could not set the bool if Mafft files have to be moved.";
	case PARSECOMMANDLINE_MOVEMAFFTFIELPATH_APPPF:
		return "Error PARSECOMMANDLINE_MOVEMAFFTFIELPATH_APPPF, could not set the path to the directory where the mafft files are located.";
	case PARSECOMMANDLINE_FASTADIR_FPPPR: //Command Line FPPPR
		return "Error PARSECOMMANDLINE_FASTADIR_FPPPR, was not able to set the path to the fasta files for FPPPR. Do you have permission?";
	case PARSECOMMANDLINE_OUTPUTDIR_FPPPR:
		return "Error PARSECOMMANDLINE_OUTPUTDIR_FPPPR, was not able to set the path to the Output path.";
	case PARSECOMMANDLINE_TAXONOMICGROUPFILE_FPPPR:
		return "Error PARSECOMMANDLINE_TAXONOMICGROUPFILE_FPPPR. Was not able to set the full path to the Taxonomic Group file.";
	case PARSECOMMANDLINE_TAXONOMICTHRESHOLD_FPPPR:
		return "Error PARSECOMMANDLINE_TAXONOMICTHRESHOLD_FPPPR, was not able to set the threshold value for the taxonomic groups. Be sure it's a value lower than 9,223,372,036,854,775,807, without the commas";
	case PARSECOMMANDLINE_TAXONOMICTHRESHOLD_TOOLOW_FPPPR:
		return "Error PARSECOMMANDLINE_TAXONOMICTHRESHOLD_TOOLOW_FPPPR you can not do the filtering step with a negative number or 0. The minimum value is '1' for this program";
	case PARSECOMMANDLINE_SUMMARYPATH_FPPPR:
		return "Error PARSECOMMANDLINE_SUMMARYPATH_FPPPR, Could not set the path for the summary file.";
	case PARSECOMMANDLINE_BOOLSUMMARY_FPPPR:
		return "Error PARSECOMMANDLINE_BOOLSUMMARY_FPPPR, could not set if the user want a summary file or not.";
	case PARSECOMMANDLINE_BOOLNOGAP_FPPPR:
		return "Error PARSECOMMANDLINE_BOOLNOGAP_FPPPR, could not set if hte user wants the gaps removed out of the sequences or not.";
	case PARSECOMMANDLINE_FASTADIR_RFBS:
		return "Error PARSECOMMANDLINE_FASTADIR_RFBS, could not set the path to the Fasta files.";
	case PARSECOMMANDLINE_BOOLNOHEADER_FPPPR:
		return "Error PARSECOMMANDLINE_BOOLNOHEADER_FPPPR, could not set the if the user want to have full Gene IDS in the file or not.";
	case PARSECOMMANDLINE_HEADERFILE_RFBS:
		return "Error PARSECOMMANDLINE_HEADERFILE_RFBS, could not set the path to the header file.";
	case PARSECOMMANDLINE_OUTPUTDIR_RFBS:
		return "Error PARSECOMMANDLINE_OUTPUTDIR_RFBS, could not set the path to the output directory.";
	case PARSECOMMANDLINE_BOOLPHYLOPYPRUNERFORMAT_RFBS:
		return "Error PARSECOMMANDLINE_BOOLPHYLOPYPRUNERFORMAT_RFBS, could not set if the user want to reformat the fasta files to the PhylopyPrunerFormat or not.";
	case PARSECOMMANDLINE_INPUTFOLDER_RASFAF: //RASFAF
		return "Error PARSECOMMANDLINE_INPUTFOLDER_RASFAF, could not set the input folder where the scripts are located";
	case PARSECOMMANDLINE_OUTPUTFOLDER_RASFAF:
		return "Error PARSECOMMANDLINE_OUTPUTFOLDER_RASFAF, could not set the output folder where the scripts are located.";
	case PARSECOMMANDLINE_JOBNUMBER_TOO_LOW_RASFAF:
		return "Error PARSECOMMANDLINE_JOBNUMBER_TOO_LOW, the job limitation must be at least 1.";
	case PARSECOMMANDLINE_JOBNUMBER_INCORRECT_RASFAF:
		return "Error PARSECOMMANDLINE_JOBNUMBER_INCORRECT, the job limitation number is incorrect.";
	case PARSECOMMANDLINE_JOBWAITINGTIME_TOO_LOW_RASFAF:
		return "Error PARSECOMMANDLINE_JOBWAITINGTIME_TOO_LOW_RASFAF, the waiting time between jobs must be at least 1.";
	case PARSECOMMANDLINE_JOBWAITINGTIME_INCORRECT_RASFAF:
		return "Error PARSECOMMANDLINE_JOBWAITINGTIME_INCORRECT_RASFAF, the waiting time between jobs is invorrect.";
	case PARSECOMMANDLINE_BOOLISSLURM_RASFAF:
		return "Error PARSECOMMANDLINE_BOOLISSLURM_RASFAF, could not set if the scripts should be parsed as a slurm job or locally.";
	case PARSECOMMANDLINE_BOOLISCONDOR_RASFAF:
		return "Error PARSECOMMANDLINE_BOOLISCondor_RASFAF, could not set if the scripts should be parsed as a condor job or locally.";
	case PARSECOMMANDLINE_BOOLISSINGLECORE_RASFAF:
		return "Error PARSECOMMANDLINE_BOOLISSINGLECORE_RASFAF, could not set if the program should be running in single or multi core.";
	case PARSECOMMANDLINE_JOBLIMIT_RASFAF:
		return "Error PARSECOMMANDLINE_JOBLIMIT_RASFAF, could not set the time limitation for a job.";
	case PARSECOMMANDLINE_FASTAFILE_ONE_COGS: //Parse command line COGS
		return "Error PARSECOMMANDLINE_FASTAFILE_ONE_COGS, could not set the First Fasta File set Path.";
	case PARSECOMMANDLINE_FASTAFILE_TWO_COGS:
		return "Error PARSECOMMANDLINE_FASTAFILE_TWO_COGS, could not set the Second Fasta File set Path.";
	case PARSECOMMANDLINE_FASTAFILE_BASE_COGS:
		return "Error PARSECOMMANDLINE_FASTAFILE_BASE_COGS, could not set the base fasta file set Path.";
	case PARSECOMMANDLINE_ORTHOGROUPDIR_COGS:
		return "Error PARSECOMMANDLINE_ORTHOGROUPDIR_COGS, could not set the OrthoGroup dir Path.";
	case PARSECOMMANDLINE_OUTPUTDIR_COGS:
		return "Error PARSECOMMANDLINE_OUTPUTDIR_COGS, could not set the output dir path.";
	case PARSECOMMANDLINE_PHYLOPYPRUNER_FORMAT_COGS:
		return "Error PARSECOMMANDLINE_PHYLOPYPRUNER_FORMAT_COGS, could not set if the user want to set the output in phylopypruner format.";
	case PARSECOMMANDLINE_PPPINPUTGRAB_COGS:
		return "Error PARSECOMMANDLINE_PPPINPUTGRAB_COGS, could not set if the user wants to use the Phylopypruner input as source instead of the Orthofinder output";
	case PARSECOMMANDLINE_PPPINPUTDIRONE_COGS:
		return "Error PARSECOMMANDLINE_PPPINPUTDIRONE_COGS, could not set the Phylopypruner input folder for set one";
	case PARSECOMMANDLINE_PPPINPUTDIRTWO_COGS:
		return "Error PARSECOMMANDLINE_PPPINPUTDIRTWO_COGS, could not set the Phylopypruner input folder for set Two";
	case PARSECOMMANDLINE_FASTA_TRINITY_DEMC: //DEMC
		return "Error PARSECOMMANDLINE_FASTA_TRINITY_DEMC, could not set the file path to the trinity assembly file.";
	case PARSECOMMANDLINE_FASTA_PROTEIN_DEMC:
		return "Error PARSECOMMANDLINE_FASTA_PROTEIN_DEMC, could not set the file path to the protein file.";
	case PARSECOMMANDLINE_TRINOTATE_REPORT_DEMC:
		return "Error PARSECOMMANDLINE_TRINOTATE_REPORT_DEMC, could not set the file path to the trinotate report file.";
	case PARSECOMMANDLINE_DIFFERENTIAL_MATRIX_DEMC:
		return "Error PARSECOMMANDLINE_DIFFERENTIAL_MATRIX_DEMC, could not set the file path to the differential matrix.";
	case PARSECOMMANDLINE_INFERNAL_DEMC:
		return "Error PARSECOMMANDLINE_INFERNAL_DEMC, could not set the file path to the infernal output file.";
	case PARSECOMMANDLINE_COLUMNS_TO_PARSE_DEMC:
		return "Error PARSECOMMANDLINE_COLUMNS_TO_PARSE_DEMC, could not set the column names for interpretation of the DE matrix.";
	case PARSECOMMANDLINE_OUTPUT_FOLDER_DEMC:
		return "Error PARSECOMMANDLINE_OUTPUT_FOLDER_DEMC, could not set the output folder.";
	case PARSECOMMANDLINE_BOOL_COLUMNS_DEMC:
		return "Error PARSECOMMANDLINE_BOOL_COLUMNS_DEMC, could not set if the user wants to filter the DE matrix or not.";
	case PARSECOMMANDLINE_BOOL_FASTA_FILTER_DEMC:
		return "Error PARSECOMMANDLINE_BOOL_FASTA_FILTER_DEMC could not set if the user wants to filter based on the peptide fasta file or not.";
	case PARSECOMMANDLINE_PREFIX_DEMC:
		return "Error PARSECOMMANDLINE_PREFIX_DEMC, could not set the prefix for the output files.";
	case PARSECOMMANDLINE_KEGGMATRIX_KEGGCOUNTER: //KEGGCounter
		return "Error PARSECOMMANDLINE_KEGGMATRIX_KEGGCOUNTER, could not set the path to the KEGG Matrix";
	case PARSECOMMANDLINE_KEGGDESCRIPTION_KEGGCOUNTER:
		return "Error PARSECOMMANDLINE_KEGGDESCRIPTION_KEGGCOUNTER, could not set the path to the Kegg Description file";
	case PARSECOMMANDLINE_BOOL_PREFIXTAG_KEGGCOUNTER:
		return "Error PARSECOMMANDLINE_BOOL_PREFIXTAG_KEGGCOUNTER, could not set the boolean for the prefix tag for the KEGG matrix";
	case PARSECOMMANDLINE_PREFIXTAG_KEGGCOUNTER:
		return "Error PARSECOMMANDLINE_PREFIXTAG_KEGGCOUNTER could not set the prefix tag for the KEGG matrix";
	case PARSECOMMANDLINE_THRESHOLD_DE_KEGGCOUNTER:
		return "Error PARSECOMMANDLINE_THRESHOLD_KEGGCOUNTER, could not set the threshold for the minimum amount log2fold the user wants.";
	case PARSECOMMANDLINE_OUTPUT_FOLDER_KEGGCOUNTER:
		return "Error PARSECOMMANDLINE_OUTPUT_FOLDER_KEGGCOUNTER, could not set the Output folder path, for the output files.";
	case PARSECOMMANDLINE_THRESHOLD_HITS:
		return "Error PARSECOMMANDLINE_THRESHOLD_HITS, could not set the minimum amount of Kegg hits the user wants";
	case PARSECOMMANDLINE_THRESHOLD_SETSAVAILABLE:
		return "Error PARSECOMMANDLINE_THRESHOLD_SETSAVAILABLE, could not set the threshold for minimum amount of biological sets the user wants.";
	case PARSECOMMANDLINE_OUTPUT_PREFIX_KEGGCOUNTER:
		return "Error PARSECOMMANDLINE_OUTPUT_PREFIX_KEGGCOUNTER, could not set the output prefix for the output file.";
	case PARSECOMMANDLINE_FASTAPATH_BAVA: //BAVA
		return "Error PARSECOMMANDLINE_FASTAPATH_BAVA, could not set the fasta path to the database file.";
	case PARSECOMMANDLINE_BLASTDIR_BAVA:
		return "Error PARSECOMMANDLINE_BLASTDIR_BAVA, could not set the path to the directory containing all blast output files.";
	case PARSECOMMANDLINE_OUTPUTDIR_BAVA:
		return "Error PARSECOMMANDLINE_OUTPUTDIR_BAVA, could not set the path to the output direcotry.";
	case PARSECOMMANDLINE_OUTPUTPREFIX_BAVA:
		return "Error PARSECOMMANDLINE_OUTPUTPREFIX_BAVA, could not set the output prefix.";
	case PARSECOMMANDLINE_EVALUETHRESHOLD_BAVA:
		return "Error PARSECOMMANDLINE_EVALUETHRESHOLD_BAVA, could not set the threshold for the E-value";
	case PARSECOMMANDLINE_PERCENTAGETHRESHOLD_BAVA:
		return "Error PARSECOMMANDLINE_PERCENTAGETHRESHOLD_BAVA, could not set the threshold for the identical percentage in the blast output file.";
	case PARSECOMANDLINE_STRAINAMECONVERSION_BAVA:
		return "Error PARSECOMANDLINE_STRAINAMECONVERSION_BAVA, could not set the path to the Strain conversion file.";
	case PARSECOMMANDLINE_BOOL_MMSEQS_BAVA:
		return "Error PARSECOMMANDLINE_BOOL_MMSEQS_BAVA, could not set the boolean for MMSEQS being used to true";
	case PARSECOMMANDLINE_PARTITIONFILE_CLCHECK:
		return "Error PARSECOMMANDLINE_PARTITIONFILE_CLCHECK, could not set the path to the partition file (output of Phyx)";
	case PARSECOMMANDLINE_CLIPKITFILE_CLCHECK:
		return "Error PARSECOMMANDLINE_CLIPKITFILE_CLCHECK, could not set the path to the clipkit log file";
	case PARSECOMMANDLINE_OUTPUTDIR_CLCHECK:
		return "Error PARSECOMMANDLINE_OUTPUTDIR_CLCHECK, could not set the path to output directory";
	case PARSECOMMANDLINE_INPUTFOLDER_MIAF:
		return "Error PARSECOMMANDLINE_INPUTFOLDER_MIAF, could not set the input directory";
	case PARSECOMMANDLINE_OUTPUTFOLDER_MIAF:
		return "Error PARSECOMMANDLINE_OUTPUTFOLDER_MIAF, could not set the output directory";
	case PARSECOMMANDLINE_MAFFTPATH_MIAF:
		return "Error PARSECOMMANDLINE_MAFFTPATH_MIAF, could not set the path to the mafft program.";
	case PARSECOMMANDLINE_IQTREEPATH_MIAF:
		return "Error PARSECOMMANDLINE_IQTREEPATH_MIAF, could not set the path to the IQTree program.";
	case PARSECOMMANDLINE_SCRIPTPATH_MIAF:
		return "Error PARSECOMMANDLINE_SCRIPTPATH_MIAF, coul dnot set the path the original script.";
	case PARSECOMMANDLINE_SYSTEMTYPE_MIAF:
		return "Error PARSECOMMANDLINE_SYSTEMTYPE_MIAF, could not set the type of the system MIAF is being run on. Either use -s s (for slurm) and -s n for running it locally";
	case PARSECOMMANDLINE_CPULIMIT_MIAF:
		return "Error PARSECOMMANDLINE_CPULIMIT_MIAF, could not set the cpu limit";
	case PARSECOMMANDLINE_IQTHREADLIMIT_MIAF:
		return "Error PARSECOMMANDLINE_IQTHREADLIMIT_MIAF, could not set the IQThread limit";
	case PARSECOMMANDLINE_JOBTIMELIMIT_MIAF:
		return "Error PARSECOMMANDLINE_JOBTIMELIMIT_MIAF, could not set the Time limitation of the job";
	case PARSECOMMANDLINE_BOOLPREQUAL_MIAF:
		return "Error PARSECOMMANDLINE_BOOLPREQUAL_MIAF, could not set if the user want to run mafft/iqtree or PREQUAL/MAFFT/CLIPKIT";
	case PARSECOMMANDLINE_INPUTFOLDER_FFRBOL:
		return "Error PARSECOMMANDLINE_INPUTFOLDER_FFRBOL, could not set the input directory";
	case PARSECOMMANDLINE_OUTPUTFOLDER_FFRBOL:
		return "Error PARSECOMMANDLINE_OUTPUTFOLDER_FFRBOL, could not set the output directory";
	case PARSECOMMANDLINE_MINLENGHT_FFRBOL:
		return "Error PARSECOMMANDLINE_MINLENGHT_FFRBOL, could not set the minimal length";
	case PARSECOMMANDLINE_MAXLENGTH_FFRBOL:
		return "Error PARSECOMMANDLINE_MAXLENGTH_FFRBOL, could not set the maximal read length";
	case PARSECOMMANDLINE_PROTEINNAME_CHANGE_GTVO: //Parse Command line GTVO
		return "Error PARSECOMMANDLINE_PROTEINNAME_CHANGE_GTVO, could not set the path to the folder containing all the changed protein names.";
	case PARSECOMMANDLINE_COGS_PPP_GTVO:
		return "Error PARSECOMMANDLINE_COGS_PPP_GTVO, could not set the path to the COGS, Phylopypruner output folder.";
	case PARSECOMMANDLINE_COGS_FPPP_GTVO:
		return "Error PARSECOMMANDLINE_COGS_FPPP_GTVO, could not set the path to the COGS, Filter PPP Output folder";
	case PARSECOMMANDLINE_ORTHOGROUP_GTVO:
		return "Error PARSECOMMANDLINE_ORTHOGROUP_GTVO, could not set the path to the orthogroup tsv files (output of Orthofinder).";
	case PARSECOMMANDLINE_OUTPUTFOLDER_GTVO:
		return "Error PARSECOMMANDLINE_OUTPUTFOLDER_GTVO, could not set the output folder path for the result of GTVO.";
	case PARSECOMMANDLINE_TAXONOMICGROUP_GTVO:
		return "Error PARSECOMMANDLINE_TAXONOMICGROUP_GTVO, could not set the taxonomic group file path.";
	case PARSECOMMANDLINE_PREFIX_OUTPUT_GTVO:
		return "Error PARSECOMMANDLINE_PREFIX_OUTPUT_GTVO, could not set the Prefix value for the output files.";
	case PARSECOMMANDLINE_BOOL_PREFIX_GTVO:
		return "Error PARSECOMMANDLINE_BOOL_PREFIX_GTVO, could not set the boolean if the Prefix is set.";
	case PARSECOMMANDLINE_TPM_FOLDER_GTVO:
		return "Error PARSECOMMANDLINE_TPM_FOLDER_GTVO, could not set the folder containing all the tpm files (Kallisto output, containing sub folders which included abundance.tsv files etc).";
	case PROPERTYBAG_GETCOLUMNNUMBER_GPDS: //Propertybag GPDS
		return "Error PROPERTYBAG_GETCOLUMNNUMBER_GPDS, was not able to obtain the column number from the propertybag";
	case PROPERTYBAG_GETBLASTEXTENSION_GPDS:
		return "Error PROPERTYBAG_GETBLASTEXTENSION_GPDS, was not able to obtain the right file extension from the propertybag";
	case PROPERTYBAG_GETFASTAQUERY_GPDS:
		return "Error PROPERTYBAG_GETFASTAQUERY_GPDS, was not able to get the path of the Query.fa file.";
	case PROPERTYBAG_GETGENESPATH_GPDS:
		return "Error PROPERTYBAG_GETGENESPATH_GPDS, was not able to get the genes.txt path";
	case PROPERTYBAG_GETBLASTFILE_GPDS:
		return "Error PROPERTYBAG_GETBLASTFILE_GPDS, was not able to get the path of the blast output file";
	case PROPERTYBAG_GETOUTPUTPATH_GPDS:
		return "Error PROPERTYBAG_GETOUTPUTPATH_GPDS, was not able to get the path of the output folder";
	case PROPERTYBAG_GETSTRAIN_NAME_GPDS:
		return "Error PROPERTYBAG_GETSTRAIN_NAME_GPDS, was not able to the strain name from the propertybag object.";
	case PROPERTYBAG_GETSTRICTDECONTAMINATION_GPDS:
		return "Error PROPERTYBAG_GETSTRICTDECONTAMINATION_GPDS, was not able to get the boolean to set the decontamination filter to strict or not.";
	case PROPERTYBAG_GETKEGGMATRIX_GPDS:
		return "Error PROPERTYBAG_GETKEGGMATRIX_GPDS, was not able to obtain the path to the KEGG matrix.";
	case PROPERTYBAG_GETKEGGBOOL_GPDS:
		return "Error PROEPRTYBAG_GETKEGGBOOL_GPDS, was not able to obtain if the user want the KEGG matrix parsed or not.";
	case PROPERTYBAG_GETGENEMAPPATH_GPDS:
		return "Error PROPERTYBAG_GETGENEMAPPATH_GPDS, was not able to obtain to get the path to the gene maps.";
	case PROPERTYBAG_GENEMAPSBOOL_GPDS:
		return "Error PROPERTYBAG_GENEMAPSBOOL_GPDS, was not able to obtain fi the user wants the Gene Maps parsed or not.";
	case PROPERTYBAG_GETFASTADIR_OSG: // PropertyBag OSG
		return "Error PROPERTYBAG_GETFASTADIR_OSG, could not obtain the path to the fasta files, are you sure it was set as a parameter?";
	case PROPERTYBAG_ORTHOGROUPDIR_OSG:
		return "Error PROPERTYBAG_ORTHOGROUPDIR_OSG, Could not set the path to the orthogroup files. Are you sure it was set?";
	case PROPERTYBAG_OUTPUTDIR_OSG:
		return "Error PROPERTYBAG_OUTPUTDIR_OSG, could not obtain the path to the output directory. Are you sure it was set?";
	case PROPERTYBAG_TAXONOMICGROUPFILE_OSG:
		return "Error PROPERTYBAG_TAXONOMICGROUPFILE_OSG, could not obtain the path to the Taxonomic Group file. Are you sure it was set?";
	case PROPERTYBAG_TAXONOMICTHRESHOLD_OSG:
		return "Error PROPERTYBAG_TAXONOMICTHRESHOLD, could not obtain the Taxonomic group threshold. Are you sure it was set?";
	case PROPERTYBAG_PHYLOPYPRUNERFORMAT_OSG:
		return "Error PROPERTYBAG_PHYLOPYPRUNERFORMAT_OSG, could not obtain if the user want to set the output files with or without the Phylopypruner format.";
	case PROPERTYBAG_SETTAXONOMICGROUPSIZE_VECTOR_OSG:
		return "Error PROPERTYBAG_SETTAXONOMICGROUPSIZE_VECTOR, could not set the size of the taxonomic group vector object. Size incorrect.";
	case PROPERTYBAG_GETTAXONOMICGROUPSIZE_VECTOR_OSG:
		return "Error PROPERTYBAG_GETTAXONOMICGROUPSIZE_VECTOR, could not obtain the size of the taxonomic group vector object. size incorrect.";
	case PROPERTYBAG_GET_SUMMARYPATH_OSG:
		return "Error PROPERTYBAG_GET_SUMMARYPATH_OSG, Could not obtain the path to the directory the user want to write the Summary file to.";
	case PROPERTYBAG_GET_BOOLSUMMARY_OSG:
		return "Error PROPERTYBAG_GET_BOOLSUMMARY_OSG, Could not obtain the boolean if the user want to write an output file or not.";
	case PROPERTYBAG_GET_BOOLTAXONOMICSKIP_OSG:
		return "Error PROPERTYBAG_GET_BOOLTAXONOMICSKIP_OSG, could not obtain the boolean if the user want to skip not findable taxonomic headers.";
	case PROPERTYBAG_GET_BOOLTAXGROUPFILTER_OSG:
		return "Error PROPERTYBAG_GET_BOOLTAXGROUPFILTER_OSG, could not obtain the boolean if the user want to skip taxonomic gorup filtering.";
	case PROPERTYBAG_GET_BOOLCONCATENATE_HOGS_OSG:
		return "Error PROPERTYBAG_GET_BOOLCONCATENATE_HOGS_OSG, could not obtain the boolean if hte user want to concatenate the HOGS into a single OG.";
	case PROPERTYBAG_GETBOOLSTRAINONLY_SCPT:
		return "Error PROPERTYBAG_GET_BOOLSTRAINONLY_SCPT, could not obtain the if the user have strain only or not.";
	case PROPERTYBAG_GETTREEFORMAT_APPPF: //PropertyBag APPPF
		return "Error PROPERTYBAG_GETTREEFORMAT_APPPF, could not obtain the tree format from the propertybag.";
	case PROPERTYBAG_SETTREEFORMAT_APPPF:
		return "Error PROPERTYBAG_SETTREEFORMAT_APPPF, could not set the Tree format through the propertybag.";
	case PROPERTYBAG_GETTREEDIRPATH_APPPF:
		return "Error PROPERTYBAG_GETTREEDIRPATH_APPPF, could not obain the path from the propertybag to the directory where the trees are located.";
	case PROPERTYBAG_GETTAXONOMICGROUPFILE_APPPF:
		return "Error PROPERTYBAG_GETTAXONOMICGROUPFILE_APPPF, could not obtain the Taxonomic Group File path from the propertybag.";
	case PROPERTYBAG_GETOUTPUTDIR_APPPF:
		return "Error PROPERTYBAG_GETOUTPUTDIR_APPPF, could not obtain the output directory from the propertybag.";
	case PROPERTYBAG_GET_BOOLMOVEMAFFTFILE_APPPF:
		return "Error PROPERTYBAG_GET_BOOLMOVEMAFFTFILE_APPPF, could not obtain the boolean, if the user wants to move the MSA (Mafft) files.";
	case PROPERTYBAG_GETMOVEMAFFTFILEPATH_APPPF:
		return "ERror PROPERTYBAG_GETMOVEMAFFTFILEPATH_APPPF, could not obtain the path to the directory to the MSA (MAFFT) files.";
	case PROPERTYBAG_GETFASTADIR_FPPPR: // PropertyBag FPPPR
		return "Error PROPERTYBAG_GETFASTADIR_FPPPR, could not obtain the path to the fasta files, are you sure it was set as a parameter?";
	case PROPERTYBAG_OUTPUTDIR_FPPPR:
		return "Error PROPERTYBAG_OUTPUTDIR_FPPPR, could not obtain the path to the output directory. Are you sure it was set?";
	case PROPERTYBAG_TAXONOMICGROUPFILE_FPPPR:
		return "Error PROPERTYBAG_TAXONOMICGROUPFILE_FPPPR, could not obtain the path to the Taxonomic Group file. Are you sure it was set?";
	case PROPERTYBAG_TAXONOMICTHRESHOLD_FPPPR:
		return "Error PROPERTYBAG_TAXONOMICTHRESHOLD, could not obtain the Taxonomic group threshold. Are you sure it was set?";
	case PROPERTYBAG_SETTAXONOMICGROUPSIZE_VECTOR_FPPPR:
		return "Error PROPERTYBAG_SETTAXONOMICGROUPSIZE_VECTOR, could not set the size of the taxonomic group vector object. Size incorrect.";
	case PROPERTYBAG_GETTAXONOMICGROUPSIZE_VECTOR_FPPPR:
		return "Error PROPERTYBAG_GETTAXONOMICGROUPSIZE_VECTOR, could not obtain the size of the taxonomic group vector object. size incorrect.";
	case PROPERTYBAG_GET_SUMMARYPATH_FPPPR:
		return "Error PROPERTYBAG_GET_SUMMARYPATH_FPPPR, Could not obtain the path to the directory the user want to write the Summary file to.";
	case PROPERTYBAG_GET_BOOLSUMMARY_FPPPR:
		return "Error PROPERTYBAG_GET_BOOLSUMMARY_FPPPR, Could not obtain the boolean if the user want to write an output file or not.";
	case PROPERTYBAG_GET_BOOLNOHEADER_FPPPR:
		return "Error PROPERTYBAG_GET_BOOLNOHEADER_FPPPR, could not obtain the boolean if the user want to have gene ids in the fasta files or not.";
	case PROPERTYBAG_GET_BOOLNOGAPS_FPPPR:
		return "Error PROPERTYBAG_GET_BOOLNOGAPS_FPPPR, could not obtain the boolean if the user want to have the gaps removed out of the sequences or not.";
	case PROPERTYBAG_GETFASTADIR_RFBS: //Propertybag RFBS
		return "Error PROPERTYBAG_GETFASTADIR_RFBS, could not obtain the directory where the fasta files are located.";
	case PROPERTYBAG_GETHEADERFILE_RFBS:
		return "Error PROPERTYBAG_GETHEADERFILE_RFBS, could not obtain the path to the Header file.";
	case PROPERTYBAG_GETOUTPUTDIR_RFBS:
		return "Error PROPERTYBAG_GETOUTPUTDIR_RFBS, could not obtani the path to the output directory.";
	case PROPERTYBAG_GETBOOLPHYLOPYPRUNERFORMAT_RFBS:
		return "Error PROPERTYBAG_GETBOOLPHYLOPYPRUNERFORMAT_RFBS, could not obtain if the bool, if the user want to reformat the fasta files into the Phylopypruner format.";
	case PROPERTYBAG_GETINPUTFOLDERSCRIPT_RASFAF: //Propertybag RASFAF
		return "ERROR PROPERTYBAG_GETINPUTFOLDERSCRIPT_RASFAF, could not get the Input folder from the propertybag.";
	case PROPERTYBAG_GETOUTPUTFOLDERSCRIPT_RASFAF:
		return "ERROR PROPERTYBAG_GETOUTPUTFOLDERSCRIPT_RASFAF, could not get the output folder from the propertybag.";
	case PROPERTYBAG_GETJOBLIMITNUMBER_RASFAF:
		return "ERROR PROPERTYBAG_GETJOBLIMITNUMBER_RASFAF, could not get the job limit number from the propertybag.";
	case PROPERTYBAG_GETJOBWAITING_TIME_RASFAF:
		return "Error PROPERTYBAG_GETJOBWAITING_TIME, could not get the job waiting time from the propertybag.";
	case PROPERTYBAG_GETBOOLSLURM_RASFAF:
		return "Error PROPERTYBAG_GETBOOLSLURM_RASFAF, could not get if the system command should be on the slurm system or local.";
	case PROPERTYBAG_GETBOOLCONDOR_RASFAF:
		return "Error PROPERTYBAG_GETBOOLCONDOR_RASFAF, could not get if the system command should be on the condor system or local.";
	case PROPERTYBAG_GETBOOLSINGLECORE_RASFAF:
		return "Error PROPERTYBAG_GETBOOLSINGLECORE_RASFAF, could not get if you want to run it in single or multi core use.";
	case PROPERTYBAG_GETJOBTIMELIMIT_RASFAF:
		return "Error PROPERTYBAG_GETJOBTIMELIMIT_RASFAF, could not get the time job limitation.";
	case PROPERTYBAG_FASTAFILE_ONE_COGS: //COGS
		return "Error PROPERTYBAG_FASTAFILE_ONE_COGS, could not get the path for the first fasta file set.";
	case PROPERTYBAG_FASTAFILE_TWO_COGS:
		return "Error PROPERTYBAG_FASTAFILE_TWO_COGS, could not get the path for the second fasta file set.";
	case PROPERTYBAG_FASTAFILE_BASE_COGS:
		return "Error PROPERTYBAG_FASTAFILE_BASE_COGS, could not get the path for the base fasta files.";
	case PROPERTYBAG_ORTHOGROUPDIR_COGS:
		return "Error PROPERTYBAG_ORTHOGROUPDIR_COGS, could not get the path for the orthogroups.";
	case PROPERTYBAG_OUTPUTDIR_COGS:
		return "Error PROPERTYBAG_OUTPUTDIR_COGS, could not get the output dir path.";
	case PROPERTYBAG_PHYLOPYPRUNER_FORMAT_COGS:
		return "Error PROPERTYBAG_PHYLOPYPRUNER_FORMAT_COGS, could not get if the user wants the output in phylopypruner format or not.";
	case PROPERTYBAG_PPPINPUTGRAB_COGS:
		return "Error PROPERTYBAG_PPPINPUTGRAB_COGS, could not get the phylopypruner input as source option.";
	case PROPERTYBAG_PPPINPUTDIRONE_COGS:
		return "Error PROPERTYBAG_PPPINPUTDIRONE_COGS, could not get the Phylopypruner input folder for set one";
	case PROPERTYBAG_PPPINPUTDIRTWO_COGS:
		return "Error PROPERTYBAG_PPPINPUTDIRTWO_COGS, could not get the Phylopypruner input folder for set two";
	case PROPERTYBAG_FASTA_TRINITY_DEMC: //DEMC
		return "Error PROPERTYBAG_FASTA_TRINITY_DEMC, could not get the path to the trinity output file from the propertybag.";
	case PROPERTYBAG_FASTA_PROTEIN_DEMC:
		return "Error PROPERTYBAG_FASTA_PROTEIN_DEMC, could not get the path to the protein file from the propertybag.";
	case PROTERTYBAG_TRINOTATE_REPORT_DEMC:
		return "Error PROTERTYBAG_TRINOTATE_REPORT_DEMC, could not get the path to the trinotate report from the propertybag.";
	case PROPERTYBAG_DIFFERENTIAL_MATRIX_DEMC:
		return "Error PROPERTYBAG_DIFFERENTIAL_MATRIX_DEMC, could not get the path to the differential matrix from the propertybag.";
	case PROPTERYBAG_INFERNAL_DEMC:
		return "Error PROPTERYBAG_INFERNAL_DEMC, could not get path to the infernal output file from the propertybag.";
	case PROPERTYBAG_COLUMNS_TO_PARSE_DEMC:
		return "Error PROPERTYBAG_COLUMNS_TO_PARSE_DEMC, could not get the column names you want to extract from the DE matrix from the Propertybag.";
	case PROPERTYBAG_BOOL_COLUMNS_DEMC:
		return "Error PROPERTYBAG_COLUMNS_TO_PARSE_DEMC, could not get if the user wants to filter the DE matrix or not based on the column input.";
	case PROPERTYBAG_OUTPUTFOLDER_DEMC:
		return "Error PROPERTYBAG_OUTPUTFOLDER_DEMC, could not get the path to the output folder from the propertybag.";
	case PROPERTYBAG_PREFIX_DEMC:
		return "Error PROPERTYBAG_PREFIX_DEMC, could not get the prefix from the propertybag.";
	case PROPERTYBAG_BOOL_FASTA_FILTER_DEMC:
		return "Error PROPERTYBAG_BOOL_FASTA_FILTER_DEMC, could not get the bool for filtering on fasta peptide file.";
	case PROPERTYBAG_KEGGMATRIX_KEGGCOUNTER: //KEGGCOUNTER
		return "Error PROPERTYBAG_KEGGMATRIX_KEGGCOUNTER, could not get the Path to the KEGG Matrix.";
	case PROPERTYBAG_KEGGDESCRIPTION_KEGGCOUNTER:
		return "Error PROPERTYBAG_KEGGDESCRIPTION_KEGGCOUNTER, could not get the path to the KEGG description file.";
	case PROPERTYBAG_BOOL_PREFIXTAG_KEGGCOUNTER:
		return "Error PROPERTYBAG_BOOL_PREFIXTAG_KEGGCOUNTER, could not get the boolean for the KEGG Prefix tag.";
	case PROPERTYBAG_PREFIXTAG_KEGGCOUNTER:
		return "Error PROPERTYBAG_PREFIXTAG_KEGGCOUNTER, could not get the Prefix tag.";
	case PROPERTYBAG_THRESHOLD_DE_KEGGCOUNTER:
		return "Error PROPERTYBAG_THRESHOLD_KEGGCOUNTER, could not get the Threshold for the DE minimum.";
	case PROPERTYBAG_THRESHOLD_HITS_KEGGCOUNTER:
		return "Error PROPERTYBAG_THRESHOLD_HITS, could not get the Threshold for the minimum amount of hits per KEGG.";
	case PROPERTYBAG_THRESHOLD_SETSAVAILABLE_KEGGCOUNTER:
		return "Error PROPERTYBAG_THRESHOLD_SETSAVAILABLE, could not get the Threshold for the minimum amount of Sets need to be present.";
	case PROPERTYBAG_OUTPUT_FOLDER_KEGGCOUNTER:
		return "Error PROPERTYBAG_OUTPUT_FOLDER_KEGGCOUNTER, could not get the Output Folder, for the output files.";
	case PROPERTYBAG_FASTAPATH_BAVA:
		return "Error PROPERTYBAG_FASTAPATH_BAVA, could not get the path to the fasta database file.";
	case PROPERTYBAG_BLASTDIR_BAVA:
		return "Error PROPERTYBAG_BLASTDIR_BAVA, could not get the path to the Blast output files directory.";
	case PROPERTYBAG_OUTPUTDIR_BAVA:
		return "Error PROPERTYBAG_OUTPUTDIR_BAVA, could not get the path to the output directory.";
	case PROPERTYBAG_OUTPUTPREFIX_BAVA:
		return "Error PROPERTYBAG_OUTPUTPREFIX_BAVA, could not get the output prefix.";
	case PROPERTYBAG_EVALUETHRESHOLD_BAVA:
		return "Error PROPERTYBAG_EVALUETHRESHOLD_BAVA, could not get the e-value threshold.";
	case PROPERTYBAG_PERCENTAGETHRESHOLD_BAVA:
		return "Error PROPERTYBAG_PERCENTAGETHRESHOLD_BAVA, could not get the identical percentage value for the blast output files.";
	case PROPERTYBAG_STRAINAMECONVERSION_BAVA:
		return "Error PROPERTYBAG_STRAINAMECONVERSION_BAVA, could not get the path to the Strain Name conversion file.";
	case PROPERTYBAG_BOOL_MMSEQS_BAVA:
		return "Error PROPERTYBAG_BOOL_MMSEQS_BAVA, could not get the boolean if the MMSEQS output was used into a boolean object.";
	case PROPERTYBAG_PARTITIONFILE_CLCHECK:
		return "Error PROPERTYBAG_PARTITIONFILE_CLCHECK, could not obtain the path to the partition file.";
	case PROPERTYBAG_CLIPKITFILE_CLCHECK:
		return "Error PROPERTYBAG_CLIPKITFILE_CLCHECK, could not get the path to the clipkit log file.";
	case PROPERTYBAG_OUTPUTDIR_CLCHECK:
		return "Error PROPERTYBAG_OUTPUTDIR_CLCHECK, could not get the path to the output directory.";
	case PROPERTYBAG_GETINPUTFOLDER_MIAF:
		return "Error PROPERTYBAG_GETINPUTFOLDER_MIAF, could not get the path to the input directory";
	case PROPERTYBAG_GETOUTPUTFOLDER_MIAF:
		return "Error PROPERTYBAG_GETOUTPUTFOLDER_MIAF, could not get the path to the output directory";
	case PROPERTYBAG_GETMAFFTPATH_MIAF:
		return "Error PROPERTYBAG_GETMAFFTPATH_MIAF, could not get the path to the MAFFT program";
	case PROPERTYBAG_GETIQTREEPATH_MIAF:
		return "Error PROPERTYBAG_GETIQTREEPATH_MIAF, could not get the path to the IQTree program";
	case PROPERTYBAG_GETSCRIPTPATH_MIAF:
		return "Error PROPERTYBAG_GETSCRIPTPATH_MIAF, could not get the path to the original script";
	case PROPERTYBAG_GETSYSTEMTYPE_MIAF:
		return "Error PROPERTYBAG_GETSYSTEMTYPE_MIAF, could not get the system type on which this program is running on e.g. slurm or norma (running it locally)";
	case PROPERTYBAG_GETCPUTLIMIT_MIAF:
		return "Error PROPERTYBAG_GETCPUTLIMIT_MIAF, could not get the maximum amount of cpu this program is allowed to run, default is used which is two";
	case PROPERTYBAG_GETIQTHREADLIMIT_MIAF:
		return "Error PROPERTYBAG_GETIQTHREADLIMIT_MIAF, could not get the maximum amount of threads per IQTree job, default is used which is 1";
	case PROPERTYBAG_GETJOBTIMELIMIT_MIAF:
		return "Error PROPERTYBAG_GETJOBTIMELIMIT_MIAF, could not get the maximum amount this job can run";
	case PROPERTYBAG_BOOLPREQUAL_MIAF:
		return "Error PROPERTYBAG_BOOLPREQUAL_MIAF, could not get the propertybag object if the user wants to run MAFFT/IQTree or Prequal/MAFFT/clipkit";
	case PROPERTYBAG_PROTEINNAME_CHANGE_GTVO:
		return "Error PROPERTYBAG_PROTEINNAME_CHANGE_GTVO, could not get propertybag object containing the path to the changed protein name files.";
	case PROPERTYBAG_COGS_PPP_GTVO:
		return "Error PROPERTYBAG_COGS_PPP_GTVO, could not get the propertybag object containing the path to the COGS PPP Output folder.";
	case PROPERTYBAG_COGS_FPPP_GTVO:
		return "Error PROPERTYBAG_COGS_FPPP_GTVO, could not get the propertybag object containing the path to the COGS Filtered PPP Output folder.";
	case PROPERTYBAG_ORTHOGROUP_GTVO:
		return "Error PROPERTYBAG_ORTHOGROUP_GTVO, could not get the propertybag object containing the path the orthogroup tsv output files.";
	case PROPERTYBAG_OUTPUTFOLDER_GTVO:
		return "Error PROPERTYBAG_OUTPUTFOLDER_GTVO, could not get the propertybag object containing the path to the output folder.";
	case PROPERTYBAG_TAXONOMICGROUP_GTVO:
		return "Error PROPERTYBAG_TAXONOMICGROUP_GTVO, could not get the propertybag object containing the path to the taxonomic group file.";
	case PROPERTYBAG_TPM_FOLDER_GTVO:
		return "Error PROPERTYBAG_TPM_FOLDER_GTVO, could not get the propertybag object containing the path to the TPM folder (Kallisto output sub folders).";
	case PROPERTYBAG_PREFIX_OUTPUT_GTVO:
		return "Error PROPERTYBAG_PREFIX_OUTPUT_GTVO, could not get the property object containing the prefix for the output files.";
	case PROPERTYBAG_BOOL_PREFIX_GTVO:
		return "Error PROPERTYBAG_BOOL_PREFIX_GTVO, could not get the propertybag object containing the boolean value if the prefix is set.";
	case FASTA_PUSBACKBLOCK_ADD_VECTOR: //Fasta Files
		return "Error FASTA_PUSBACKBLOCK, could not add the Fasta Block to the FastaFile Vector, since the object is empty.";
	case FASTABLOCK_SETBLOCK_NOFASTAFORMAT:
		return "Error FASTABLOCK_SETBLOCK_NOFASTAFORMAT, this Fastablock does not have a fasta format, which should start with a '>', check your fasta file again.";
	case FASTABLOCK_SETFASTAHEADER:
		return "Error FASTABLOCK_SETFASTAHEADER, Could not set the fasta header in the fasta block.";
	case FASTABLOCK_SETFASTAHEADERADDON:
		return "Error FASTABLOCK_SETFASTAHEADERADDON, could not set the fasta header add in the fasta block.";
	case FASTABLOCK_SETFASTAHEADER_POINTERDIFFERENCE:
		return "Error FASTABLOCK_SETFASTAHEADER_POINTERDIFFERENCE, the difference between the pointers is not correct. The fasta file is not correctly formatted.";
	case FASTABLOCK_SETFASTAHEADERSTRAIN_POINTERDIFFERENCE:
		return "Error FASTABLOCK_SETFASTAHEADERSTRAIN_POINTERDIFFERENCE, the difference beween the pointers is not correct. THe fasta file is not correclty formatted.";
	case FASTABLOCK_SETFASTAHEADERADDON_POINTERDIFFERENCE:
		return "Error FASTABLOCK_SETFASTAHEADERADDON_POINTERDIFFERENCE, the difference between the pointers is not correct. Is the genemap file correctly formatted?";
	case FASTABLOCK_SETHEADERSTRAIN_NODATA:
		return "Error FASTABLOCK_SETHEADERSTRAIN_NODATA, the input object to set the Header Strain is empty.";
	case FASTABLOCK_SETFASTAHREST_POITNERDIFFERENCE:
		return "Error FASTABLOCK_SETFASTAHREST_POITNERDIFFERENCE, the difference between the pointers is not the correct. the fasta file is not correctly formatted.";
	case FASTABLOCK_SETHEADERREST_NODATA:
		return "Error FASTABLOCK_SETHEADERREST_NODATA, the input object to set the Rest part of the header is empty.";
	case FASTABLOCK_GETFASTAHEADER:
		return "Error FASTABLOCK_GETFASTAHEADER, could not get the fasta sequence from the fasta block object.";
	case FASTABLOCK_SETFASTASEQUENCE:
		return "Error FASTABLOCK_SETFASTASEQUENCE, Could not set the fasta sequence in the fasta block.";
	case FASTABLOCK_SETFASTASEQUENCE_POINTERDIFFERENCE:
		return "Error FASTABLOCK_SETFASTASEQUENCE_POINTERDIFFERENCE, the difference between the pointers is not correct. The fasta file is not correctly formatted.";
	case FASTABLOCK_GETFASTASEQUENCE:
		return "Error FASTABLOCK_GETFASTASEQUENCE, could not get the fasta sequence from the fasta block object.";
	case FASTABLOCK_GETFASTAHEADERADDON:
		return "Error FASTABLOCK_GETFASTAHEADERADDON, could not get the fasta header add on variable form the fasta block object.";
	case FASTABLOCK_GETHEADERNUMBER:
		return "Error FASTABLOCK_GETHEADERNUMBER, could not get the header number, invalid number.";
	case FASTABLOCK_GETHEADERSTRAIN:
		return "Error FASTABLOCK_GETHEADERSTRAIN, could not get the header strain, invalid header strain object.";
	case FASTABLOCK_GETHEADERREST:
		return "Error FASTABLOCK_GETHEADERREST, could not get the rest of the header, invalid Header rest object.";
	case FASTABLOCK_SETHEADERNUMBER:
		return "Error FASTABLOCK_SETHEADERNUMBER, could not set the header number, invalid number.";
	case FASTABLOCK_GETWRITEFASTABLOCKBOOL:
		return "Error FASTABLOCK_GETWRITEFASTABLOCKBOOL, could not obtain if the FastaBlock has to be written or not.";
	case FASTABLOCK_SETWRITEFASTABLOCKBOOL:
		return "Error FASTABLOCK_SETWRITEFASTABLOCKBOOL, could not define if the setting value for m_bFastaBlockWrite has to be set to true or false.";
	case FASTABLOCK_SETFASTAHEADERADDONBOOL:
		return "Error FASTABLOCK_SETFASTAHEADERADDONBOOL, could not define if the added the Fasta Header add on variable in the Fastablock object.";
	case FASTABLOCK_SETKEGGMATRIXBOOL:
		return "Error FASTABLOCK_SETKEGGMATRIXBOOL, could not define if the KEGG Matrix should be added or not.";
	case FASTABLOCK_GETKEGGMATRIXBOOL:
		return "Error FASTABLOCK_GETKEGGMATRIXBOOL, could not obtain the boolean if the Kegg Matrix was added.";
	case FASTABLOCK_SETKEGGMATRIX:
		return "Error FASTABLOCK_SETKEGGMATRIX, could not set the Kegg matrix, since the input is empty.";
	case FASTABLOCK_GETKEGGMATRIX:
		return "Error FASTABLOCK_GETKEGGMATRIX, could not get the Kegg matrix from the fasta block object. Because the variable is empty.";
	case FASTAFILE_GETFASTAFILEBUFFER:
		return "Error FASTAFILE_GETFASTAFILEBUFFER, could not set file buffer.";
	case FASTAFILE_WRONGFORMAT:
		return "Error FASTAFILE_WRONGFORMAT, Fasta file has the wrong format, doesn't start with >.";
	case FASTAFILE_PARSEFASTABLOCK_WRONGFORMAT:
		return "Error FASTAFILE_PARSEFASTABLOCK_WRONGFORMAT, the fasta block does not have the right format. Are you sure it's a Fasta file starting with '>'.";
	case FASTAFILE_SETFASTAFILENAME_POINTERDIFFERENCE:
		return "Error FASTAFILE_SETFASTAFILENAME_POINTERDIFFERENCE, the difference between the pointers is not correct. The gene file is not correct.";
	case FASTAFILE_GETFASTAFILENAME:
		return "Error FASTAFILE_GETFASTAFILENAME,  could not get the fasta file name from the fasta file object.";
	case FASTAFILE_EMPTY_STRING_FASTAFILENAME:
		return "Error FASTAFILE_EMPTY_STRING_FASTAFILENAME, tried to set the fasta file name, but the string object is empty, does the blast file has entries on column 2?";
	case FASTAFILE_MATCHING_FASTABLOCK_NOT_FOUND:
		return "Error FASTAFILE_MATCHING_FASTABLOCK_NOT_FOUND, could not find the fasta block in the fasta file. Are you sure that the name is exactly matching and exist?";
	case FASTAFILE_MATCHING_FASTABLOCK_NOT_FOUND_BASED_ON_HEADERNUMBER:
		return "Error FASTAFILE_MATCHING_FASTABLOCK_NOT_FOUND_BASED_ON_HEADERNUMBER, could not find the fasta block in the fasta file. This is based on the header numbers in a simplified header format.";
	case FASTAFILE_SETMATCHINGNAME_POINTERDIFFERENCE:
		return "Error FASTAFILE_SETMATCHINGNAME_POINTERDIFFERENCE, the difference between the pointers is not correct. The matching name is not correct.";
	case FASTAFILE_EMPTY_STRING_MATCHINGNAME:
		return "Error FASTAFILE_EMPTY_STRING_MATCHINGNAME, tried to set the fasta file name, but the string object is empty, does the blast file has entries on column 2?";
	case FASTAFILE_GETMATCHINGNAME:
		return "Error FASTAFILE_GETMATCHINGNAME,  could not get the matching file name from the fasta file object.";
	case TABLEROW_SETCOLUMNNAME_HEADER:
		return "Error TABLEROW_SETCOLUMNNAME_HEADER, The header column name does not have the right format.";
	case TABLEROW_SETCOLUMNNAMENEW_HEADER:
		return "Error TABLEROW_SETCOLUMNNAMENEW_HEADER.The header column name to replace the old header name does not have the right format.";
	case TABLEROW_SETCOLUMNNAMENEW_HEADER_POINTER:
		return "Error TABLEROW_SETCOLUMNNAMENEW_HEADER_POINTER, The new header name object parameter does not have any content.";
	case TABLEROW_GETCOLUMNNAME_HEADER:
		return "Error TABLEROW_GETCOLUMNNAME_HEADER, the column name object does not have any content";
	case TABLEROW_GETCOLUMNNAMENEW_HEADER:
		return "Error TABLEROW_GETCOLUMNNAMENEW_HEADER, the column new name that repalces the old column does not have any content.";
	case TABLE_NOTMATCHING_COLUMNNUMBER:
		return "Error ERROR_NOTMATCHING_COLUMNNUMBER, the amount of columns are not matching to one another within this table.";
	case TABLE_NOMATCH_HEADERCOLUMN:
		return "Error TABLE_NOMATCH_HEADERCOLUMN, could not find the column within the table. ";
	case TABLE_NEWNAME_SIZE_FORMAT_WRONG:
		return "Error TABLE_NEWNAME_SIZE_FORMAT_WRONG, could not determine the table name, format wrong.";
	case TABLE_PARSE_ROW_SIZE_TOO_SMALL:
		return "Error TABLE_PARSE_ROW_SIZE_TOO_SMALL, the row for creating this buffer is too small";
	case TABLE_PARSE_ROW_SIZE_TOO_BIG:
		return "Error TABLE_PARSE_ROW_SIZE_TOO_BIG, the row for creating this buffer is too big. This table file probably doesn't have EOL's";
	case TABLE_NEWCOLUMN_SIZE_FORMAT_WRONG:
		return "Error TABLE_NEWCOLUMN_SIZE_FORMAT_WRONG, the file positions to set a new column into the table object is the wrong size.";
	case TABLE_PARSE_ROW_SIZE_FORMAT_WRONG:
		return "Error TABLE_PARSE_ROW_SIZE_FORMAT_WRONG, the row that's trying to be parsed has the wrong format (wrong size)";
	case TABLE_SIZE_HEADER_COLUMN_WRONG:
		return "Error TABLE_SIZE_HEADER_COLUMN_WRONG, This row does not have the right amount of columns, are you sure this table has the right format?";
	case TABLE_FIND_MATCHING_ROW_NAME_DOES_NOT_EXIST:
		return "Error TABLE_FIND_MATCHING_ROW_NAME_DOES_NOT_EXIST, the row you try to find does not exist";
	case TABLE_ROW_MATCHING_NOT_FOUND:
		return "Error TABLE_ROW_MATCHING_NOT_FOUND, Row is not found";
	case TABLE_PARSE_HEADER_FORMAT_WRONG:
		return "Error TABLE_PARSE_HEADER_FORMAT_WRONG, the header row you try to find does not exist";
	case TABLE_HEADER_VECTOR_AND_COLUMN_COUNT_NOT_MATCHING:
		return "Error TABLE_HEADER_VECTOR_AND_COLUMN_COUNT_NOT_MATCHING, the amount of columns does not match with the amount of header columns just added into the Table object. Is it the right format?";
	case TABLE_PARSE_TABLE_FORMAT_WRONG_NO_EOL:
		return "Error TABLE_PARSE_TABLE_FORMAT_WRONG_NO_EOL, the table you try to parse does not have EOLs";
	case TABLE_CREATE_FILE_BUFFER:
		return "Error TABLE_CREATE_FILE_BUFFER, the file buffer for this table could not be created are you sure the file has a content?";
	case TABLE_SET_TABLE_ROW_HEADER:
		return "Error TABLE_SET_TABLE_ROW_HEADER, could not set the table row header.";
	case TABLE_GET_TABLE_ROW_HEADER:
		return "Error TABLE_GET_TABLE_ROW_HEADER, could not get the table row header.";
	case TABLE_NO_TABLE_CONTENT:
		return "Error TABLE_NO_TABLE_CONTENT, this table does not have any content. Just the Header";
	case TABLE_GET_TABLE_NAME:
		return "Error TABLE_GET_TABLE_NAME, could not get the table name.";
	case TABLE_PUSHBACK_ROW_SAFE:
		return "Error TABLE_PUSHBACK_ROW_SAFE, could not push back the row into the table.";
	case TABLE_PUSHBACK_NO_ROWS:
		return "Error TABLE_PUSHBACK_NO_ROWS, there are no rows within this blast output file.";
	case TABLE_POPBACK_NO_ROWS:
		return "Error TABLE_POPBACK_NO_ROWS, there are no rows within this table to pop back.";
	case TABLE_FIND_TABLE_IN_TABLE_VECTOR_DOES_NOT_EXIST:
		return "Error TABLE_FIND_TABLE_IN_TABLE_VECTOR_DOES_NOT_EXIST, could not find the matching the table name. Table doesn't exist in the vector.";
	case TABLE_FIND_TABLE_TABLE_QUERY_VARIABLE_EMPTY:
		return "Error TABLE_FIND_TABLE_TABLE_QUERY_VARIABLE_EMPTY, could not search for the right table in the vector as the search value is empty.";
	case TABLE_STRING_TO_CLEAR_ROW_AND_COLUMN_EMPTY:
		return "Error TABLE_STRING_TO_CLEAR_ROW_AND_COLUMN_EMPTY, can't clear the table columns with an empty string.";
	case TABLE_REPLACE_COLUMN_NEW_COLUMN_EMPTY:
		return "Error TABLE_REPLACE_COLUMN_NEW_COLUMN_EMPTY, new column content is empty can't replace.";
	case TAXONOMIC_GROUP_FIND_SPECIES_SPECIESNAME:
		return "Error TAXONOMIC_GROUP_FIND_SPECIES_SPECIESNAME, could not find the Taxonomic Species from the taxonomic group object. Does the Taxonomic Group file names matches the fasta file names?";
	case TAXONOMIC_GROUP_FIND_SPECIES_HEADERNAME:
		return "Error TAXONOMIC_GROUP_FIND_SPECIES_HEADERNAME, could not find the Taxonomic Species from the taxonomic group object. Does the Taxonomic group file contain the missing species?";
	case INFERNAL_SET_ISOFORMID_SZ:
		return "Error INFERNAL_SET_ISOFORMID_SZ, could not set the Isoform ID in the Infernal object";
	case INFERNAL_SET_ISOFORMID_SIZE:
		return "Error INFERNAL_SET_ISOFORMID_SIZE, could not determine the size of the string of the input. Probably the wrong format.";
	case INFERNAL_SETISOFORMID_POINTERDIFFERENCE:
		return "Error INFERNAL_SETISOFORMID_POINTERDIFFERENCE, pointer difference between pStart and pEnd were illogical, text is probably in the wrong format.";
	case INFERNAL_SET_ACCESSION_SZ:
		return "Error INFERNAL_SET_ACCESSION_SZ, could not set the Accession in the Infernal object";
	case INFERNAL_SET_ACCESSION_SIZE:
		return "Error INFERNAL_SET_ACCESSION_SIZE, could not determine the size of the string of the input. Probably the wrong format.";
	case INFERNAL_SETACCESSION_POINTERDIFFERENCE:
		return "Error INFERNAL_SETACCESSION_POINTERDIFFERENCE, pointer difference between pStart and pEnd were illogical, text is probably in the wrong format.";
	case INFERNAL_SET_DESCRIPTION_SZ:
		return "Error INFERNAL_SET_DESCRIPTION_SZ, could not set the Description in the infernal object";
	case INFERNAL_SET_DESCRIPTION_SIZE:
		return "Error INFERNAL_SET_DESCRIPTION_SIZE,could not determine the size of the string of the input. Probably the wrong format.";
	case INFERNAL_SETDESCRIPTION_POINTERDIFFERENCE:
		return "Error INFERNAL_SETDESCRIPTION_POINTERDIFFERENCE, pointer difference between pStart and pEnd were illogical, text is probably in the wrong format.";
	case INFERNAL_GETISOFORMID:
		return "Error INFERNAL_GETISOFORMID, Could not obtain the Isoform ID from the Infernal object. Since it's not filled.";
	case INFERNAL_GETACCESSION:
		return "Error INFERNAL_GETACCESSION, Could not obtain the Accession from the Infernal object. Since it's not filled.";
	case INFERNAL_GETDESCRIPTION:
		return "Error INFERNAL_GETDESCRIPTION, Could not obtain the Description from the Infernal object. Since it's not filled.";
	case DIFFERENTIALMATRIX_SET_ROW_DEMATRIX_EMPTY:
		return "Error DIFFERENTIALMATRIX_SET_ROW_DEMATRIX_EMPTY, could not set the pointer looking at the Differential Matrix Row. Since it's empty.";
	case DIFFERENTIALMATRIX_SET_ROW_TRINOTATE_EMPTY:
		return "Error DIFFERENTIALMATRIX_SET_ROW_TRINOTATE_EMPTY, could not set the pointer looking at the Trinotate Row. Since it's empty.";
	case DIFFERENTIALMATRIX_SET_TRINITY_EMPTY:
		return "Error DIFFERENTIALMATRIX_SET_TRINITY_EMPTY, could not set the pointer looking at the Trinity Fasta block. since it's empty.";
	case DIFFERENTIALMATRIX_SET_PROTEIN_EMPTY:
		return "Error DIFFERENTIALMATRIX_SET_PROTEIN_EMPTY, could not set the pointer looking at the Protein Fasta block. since it's empty.";
	case DIFFERENTIALMATRIX_SET_INFERNAL_EMPTY:
		return "Error DIFFERENTIALMATRIX_SET_INFERNAL_EMPTY, could not set the pointer looking at the Infernal. since it's empty.";
	case DIFFERENTIALMATRIX_GET_ROW_DEMATRIX_EMPTY:
		return "Error DIFFERENTIALMATRIX_GET_ROW_DEMATRIX_EMPTY, could not obtain the pointer looking at the Differential Matrix. Since it's empty.";
	case DIFFERENTIALMATRIX_GET_ROW_TRINOTATE_EMPTY:
		return "Error DIFFERENTIALMATRIX_GET_ROW_TRINOTATE_EMPTY, could not obtain the pointer looking at the Trinotate Matrix. Since it's empty.";
	case DIFFERENTIALMATRIX_GET_TRINITY_EMPTY:
		return "Error DIFFERENTIALMATRIX_GET_TRINITY_EMPTY, could not obtain the pointer looking at the Trinity Fasta Block. Since it's empty.";
	case DIFFERENTIALMATRIX_GET_PROTEIN_EMPTY:
		return "Error DIFFERENTIALMATRIX_GET_PROTEIN_EMPTY, could not obtain the pointer looking at the Protein Fasta Block. Since it's empty.";
	case DIFFERENTIALMATRIX_GET_INFERNAL_EMPTY:
		return "Error DIFFERENTIALMATRIX_GET_INFERNAL_EMPTY, could not obtain the pointer looking at the Infernal object. Since it's empty.";
	case JOB_SETINPUTFILE_STRING_RASFAF:
		return "Error ERROR_SETINPUTFILE_STRING_RASFAF, could not set the input file path based on whole strings.";
	case JOB_SETINPUTFILE_POSITION_RASFAF:
		return "Error ERROR_SETINPUTFILE_POSITION_RASFAF, could not set hte input file path based on positions.";
	case JOB_GETINPUTFILE_RASFAF:
		return "Error ERROR_GETINPUTFILE_RASFAF, could not get the full input file path, probably not filled.";
	case JOB_SETOUTPUTFILE_STRING_RASFAF:
		return "Error ERROR_SETOUTPUTFILE_STRING_RASFAF, could not set the output file path based on whole strings.";
	case JOB_SETOUTPUTFILE_POSITION_RASFAF:
		return "Error ERROR_SETOUTPUTFILE_POSITION_RASFAF, could not set the output file path based on positions.";
	case JOB_GETOUTPUTFILE_RASFAF:
		return "Error ERROR_GETOUTPUTFILE_RASFAF, could not get the output file path.";
	case JOB_SETSYSTEMCOMMAND_STRING_RASFAF:
		return "Error ERROR_SETSYSTEMCOMMAND_STRING_RASFAF, could not set the command line command based on whole strings.";
	case JOB_SETSYSTEMCOMMAND_POSITION_RASFAF:
		return "Error ERROR_SETSYSTEMCOMMAND_POSITION_RASFAF, could not set the command line command based on positions.";
	case JOB_GETSYSTEMCOMMAND_RASFAF:
		return "Error ERROR_GETSYSTEMCOMMAND_RASFAF, could not get the system command.";
	case JOB_FINDEMPTYSPOT_FORNEWJOB_RASFAF:
		return "Error JOB_FINDEMPTYSPOT_FORNEWJOB_RASFAF, could not find the a spot in the Running job vector.";
	case KEGGSET_KEGGID_DOES_NOT_EXIST: //Class functions CKEGGSet
		return "Error KEGGSET_KEGGID_DOES_NOT_EXIST, KEGG ID while setting is a nullptr.";
	case KEGGSET_KEGGID_NOT_FILLED:
		return "Error KEGGSET_KEGGID_NOT_FILLED, is empty.";
	case KEGGSET_KEGGID_GET_FAIL:
		return "Error KEGGSET_KEGGID_GET_FAIL, Could not optain the KEGGID from the KEGGSet Object, because it's empty";
	case KEGGSET_COUNTERINCREASE_NOT_VALID:
		return "Error KEGGSET_COUNTERINCREASE_NOT_VALID, index to increase is out of bounds.";
	case KEGGSET_KEGGSETTHRESHOLD_NOT_VALID:
		return "Error KEGGSET_KEGGSETTHRESHOLD_NOT_VALID, Sets are not duplicates of 2 (up and down) so there is a missmatch and it can not be used.";
	case KEGGSET_SETKEGGROW_KEGGROW_NOT_VALID:
		return "Error KEGGSET_SETKEGGROW_KEGGROW_NOT_VALID, the pointer looking at the KEGG matrix Row is empty";
	case KEGGSET_KEGGSET_NOT_FOUND_VECTOR:
		return "Error KEGGSET_KEGGSET_NOT_FOUND_VECTOR, Trying to find the KEGGSet object in the vector, but there is no match. Check in the KEGG Description file if it exist, also be sure that the prefix is set (for the KEGG MATRIX) if there is a missmatch in KEGG in the Matrix file and the KEGG Description file.";
	case NAMEDMAPS_SETMAPNAME_POINTERDIFFERENCE: //Named Maps
		return "Error NAMEDMAPS_SETMAPNAME_POINTERDIFFERENCE, the difference between the pointers is not correct. The matching name is not correct";
	case NAMEDMAPS_EMPTY_STRING_MAPNAME:
		return "Error NAMEDMAPS_EMPTY_STRING_MAPNAME, the string object is empty.";
	case NAMEDMAPS_GETMAPNAME:
		return "Error NAMEDMAPS_GETMAPNAME, the object m_szMapName is empty as it isn't set.";
	case NAMEDMAPS_EMPTYMAP:
		return "Error NAMEDMAPS_EMPTYMAP, the map is empty.";
	case NAMEDMAPS_EMPTYKEY:
		return "Error NAMEDMAPS_EMPTYKEY, they key you tried to add is an empty string.";
	case NAMEDMAPS_MATCHING_NAMEDMAPFILE_NOT_FOUND:
		return "Error NAMEDMAPS_MATCHING_NAMEDMAPFILE_NOT_FOUND, could not find a matching Named Map File.";
	case JOB_SETFASTAFILEPATH_POSITION_MIAF:
		return "Error JOB_SETFASTAFILEPATH_POSITION_MIAF, could not set the Fasta File path in the Job object.";
	case JOB_GETFASTAFILEPATH_MIAF:
		return "Error JOB_GETFASTAFILEPATH_MIAF, could not get the Fasta File path from the job object.";
	case JOB_SETINPUTFILENAME_POSITION_MIAF:
		return "Error JOB_SETINPUTFILENAME_POSITION_MIAF, could not set the fasta file name in the Job object.";
	case JOB_GETFASTAFILENAME_MIAF:
		return "Error JOB_GETFASTAFILENAME_MIAF, could not get the Fasta File name in the Job object.";
	case JOB_TIMELIMIT_REACHED:
		return "Error JOB_TIMELIMIT_REACHED, job time limit reached. Restarting the program.";
	case PARSEINPUT_FILE_BLAST_NO_ROWS: //Blast file
		return "Error PARSEINPUT_FILE_BLAST_NO_ROWS, the blast output file does not have any rows for content.";
	case PARSEINPUT_FILE_BLAST_NO_TABLE:
		return "Error PARSEINPUT_FILE_BLAST_NO_TABLE, there is no Blast file in the Blast Vector.";
	case PARSEINPUT_FILE_BLAST_NO_TABLENAME:
		return "Error PARSEINPUT_FILE_BLAST_NO_TABLENAME, there is no path in the blast file.";
	case PARSEINPUT_FILE_SPLIT_FASTA_FILES_NO_FASTABLOCKS:
		return "Error PARSEINPUT_FILE_SPLIT_FASTA_FILES_NO_FASTABLOCKS, the original fasta file does not have any fasta sequences (blocks) in it.";
	case PARSE_INPUT_FILE_TAXONOMICGROUPFILE_TAXONOMICSPECIES_SET_SPECIESNAME: //Own ones - input function / OSG
		return "Error PARSE_INPUT_FILE_TAXONOMICGROUPFILE_TAXONOMICSPECIES_SET_SPECIESNAME, could not parse the species name in the Taxonomic Species object.";
	case PARSE_INPUT_FILE_TAXONOMICGROUPFILE_TAXONOMICSPECIES_SET_SPECIESNAME_SIZETOSMALL:
		return "Error PARSE_INPUT_FILE_TAXONOMICGROUPFILE_TAXONOMICSPECIES_SET_SPECIESNAME_SIZETOSMALL, could not set the species in the taxonomic species object, because the size of the name is incorrect.";
	case PARSE_INPUT_FILE_TAXONOMICGROUPFILE_TAXONOMICSPECIES_GET_SPECIESNAME:
		return "Error PARSE_INPUT_FILE_TAXONOMICGROUPFILE_TAXONOMICSPECIES_GET_SPECIESNAME, could not obtain the species name in the taxonomic species object, since the species name object does not exist within the taxonomic species object.";
	case PARSE_INPUT_FILE_TAXONOMICGROUPFILE_TAXONOMICSPECIES_SET_HEADERNAME:
		return "Error PARSE_INPUT_FILE_TAXONOMICGROUPFILE_TAXONOMICSPECIES_SET_HEADERNAME, could not set the header name witin the taxonomic species object.";
	case PARSE_INPUT_FILE_TAXONOMICGROUPFILE_TAXONOMICSPECIES_SET_HEADERNAME_SIZETOSMALL:
		return "Error PARSE_INPUT_FILE_TAXONOMICGROUPFILE_TAXONOMICSPECIES_SET_HEADERNAME_SIZETOSMALL, could not set the header name within the taxonimic species object, because the size of the name is incorrect.";
	case PARSE_INPUT_FILE_TAXONOMICGROUPFILE_TAXONOMICSPECIES_GET_HEADERNAME:
		return "Error PARSE_INPUT_FILE_TAXONOMICGROUPFILE_TAXONOMICSPECIES_GET_HEADERNAME, could not obtain the header name in the taxonomic species object, since the Header Name object does not exist within the Taxonomic Species object.";
	case PARSE_INPUT_FILE_TAXONOMICGROUPFILE_TAXONOMICGROUP_PUSHBACK_TAXONOMIC_SPECIES:
		return "Error PARSE_INPUT_FILE_TAXONOMICGROUPFILE_TAXONOMICGROUP_PUSHBACK_TAXONOMIC_SPECIES, could not push back a taxonimic species object within the taxonomic group object since there is no Taxonomic Species object to be pushed back.";
	case PARSE_INPUT_FILE_TAXONOMICGROUPFILE_WRONG_FORMAT:
		return "Error PARSE_INPUT_FILE_TAXONOMICGROUPFILE_WRONG_FORMAT, Taxonomic group file has the wrong format. The format should be 'SpeciesName1(HeaderName1),SpeciesName2(HeaderName2),etc,SpeciesNameN(HeaderNameN) ";
	case PARSE_INPUT_FILE_HEADERFILE_SETFILEBUFFER_RFBS: //Own ones - input function / RFBS
		return "Error PARSE_INPUT_FILE_HEADERFILE_SETFILEBUFFER, could not set the file buffer for the Header File.";
	case PARSE_INPUT_FILE_HEADERFILE_WRONG_FORMAT_RFBS:
		return "Error PARSE_INPUT_FILE_HEADERFILE_WRONG_FORMAT_RFBS, the header file does not have the right format. The right format is [HeaderToFind][TAB][+/-] e.g. + = Strain only, - is Full Header e.g. Aagrestis_BONN	+Aagrestis_OXF@17242	-";
	case MATCHING_FASTAFILE_NOT_FOUND:
		return "Error MATCHING_FASTAFILE_NOT_FOUND, could not find the matching Fasta File.";
	case MATCHING_SPLIT_HEADERNAME_AND_NUMBER_TOO_SMALL:
		return "Error MATCHING_SPLIT_HEADERNAME_AND_NUMBER_TOO_SMALL, the header of a fasta block is not properly formatted it should be [HeaderName]-[HeaderNumber]. Total size at least 3";
	case MATCHING_FASTAFILE_FILENAME_NOT_FOUND:
		return "Error MATCHING_FASTAFILE_FILENAME_NOT_FOUND, Fasta file was not found based on the fasta file name. Are you use the fasta file matches the orthofinder output?";
	case MATCHING_FASTAFILE_MATCHINGNAME_NOT_FOUND:
		return "Error MATCHING_FASTAFILE_MATCHINGNAME_NOT_FOUND, Fasta file was not found based on Matching file name. Are you sure the fasta file matches the orthofinder output?";
	case MATCHING_FASTAFILE_DOES_NOT_EXIST_RFBS:
		return "Error MATCHING_FASTAFILE_DOES_NOT_EXIST_RFBS, The fasta file withint he vector does not contain any data.";
	case MATCHING_HEADERNAME_DOES_NOT_EXIST_RFBS:
		return "Error MATCHING_HEADERNAME_DOES_NOT_EXIST_RFBS, the header object within the vector does not contain any information.";
	case MATCHING_HEADERNAME_HEADERORSTRAIN_DOES_NOT_EXIST_RFBS:
		return "Error MATCHING_HEADERNAME_HEADERORSTRAIN_DOES_NOT_EXIST_RFBS, the information if the header is a strain or complete header object does not contain any information.";
	case MATCHING_HEADERNAME_WRONG_FORMAT:
		return "Error MATCHING_HEADERNAME_WRONG_FORMAT, the header file is not in the right format. The right format is [HeaderToFind][TAB][+/-] e.g. + = Strain only, - is Full Header e.g. Aagrestis_BONN	+Aagrestis_OXF@17242	-";
	case DEMC_MATCHING_INFERNAL_NOT_FOUND:
		return "Error DEMC_MATCHING_INFERNAL_NOT_FOUND, Matching infernal object not found.";
	case DEMC_SPLIT_DE_NAMES_EMPTY_COLUMN_NAME:
		return "Error DEMC_SPLIT_DE_NAMES_EMPTY_COLUMN_NAME, splitting names column is empty";
	case DEMC_SPLIT_DE_NAMES_COLUMN_NOT_FOUND:
		return "Error DEMC_SPLIT_DE_NAMES_COLUMN_NOT_FOUND, split Differential Expressned names column not found.";
	case DEMC_PROTEIN_DESCRIPTION_NOT_FOUND:
		return "Error DEMC_PROTEIN_DESCRIPTION_NOT_FOUND, protein description not found.";
	case PARSE_INPUT_FILE_PARTITION_FILE_ALIGNMENT_SIZE_NOT_THE_SAME_CLCHECK:
		return "Error PARSE_INPUT_FILE_PARTITION_FILE_ALIGNMENT_SIZE_NOT_THE_SAME_CLCHECK, the alignment size of the partition file and the clipkit output file aren't the same.";
	case PARSE_INPUT_FILE_PARTITION_FILE_PARSEDPARITIONFILE_VECTOR_NOT_SAME_ALIGNMENT_SIZE_CLCHECK:
		return "Error PARSE_INPUT_FILE_PARTITION_FILE_PARSEDPARITIONFILE_VECTOR_NOT_SAME_ALIGNMENT_SIZE_CLCHECK, the size of the parsed Partition Vector is not the same as the Clipkit output size.";
	case JOB_ALREADYFINISHED_RASFAF:
		return "Error JOB_ALREADYFINISHED, the job is already finished, but not filled yet! This is no error.";
	case JOB_EMPTYJOBOBJECT:
		return "Error JOB_EMPTYJOBOBJECT, this job object has no data.";
	case JOB_NOTFINISHEDYET_RASFAF:
		return "Error JOB_NOTFINISHEDYET_RASFAF, Job not finished yet can not be replaced.";
	case JOB_NOEMPTYSPOTFOUND_RASFAF:
		return "Error JOB_NOEMPTYSPOTFOUND_RASFAF, Could not find an empty spot in the vector.";
	case GTVO_HEADER_CREATION_SPECIES_NAME_EMPTY:
		return "Error GTVO_HEADER_CREATION_SPECIES_NAME_EMPTY, the species name is empty.";

	case WRITE_OUTPUT_FILE_ERROR_FOPEN:
		return "Error WRITE_OUTPUT_FILE_ERROR_FOPEN, could not write the output file. Be sure to have permissions in the output folder and/or to check if the same file does not exist already with locked permissions";
	case WRITE_OUTPUT_FILE_SUMMARY_DECONTAMINATION:
		return "Error WRITE_OUTPUT_FILE_SUMMARY_DECONTAMINATION, could not write the Summary Decontamination output file. Be sure to have permissions in the output folder and/or to check if the same file does not exist already with locked permissions";
	case REPLACE_STRING_FOR_SZOBJECT_ZERO_STRING_SIZE:
		return "Error REPLACE_STRING_FOR_SZOBJECT_ZERO_STRING_SIZE, the base string is empty so no file buffer is created.";
	case DUPLICATE_ZERO_TERMINATED_STRING_SIZE_ZERO:
		return "Error DUPLICATE_ZERO_TERMINATED_STRING_SIZE_ZERO, the base string to duplicate is enmpty so no file bufer can be created.";
	case WRITE_OUTPUT_ORTHOGROUP_FASTAOBJECT:
		return "Error WRITE_OUTPUT_ORTHOGROUP_FASTAOBJECT, The orthogroup fasta file object does not cotain any information.";
	case WRITE_OUTPUT_FILE_SUMMARY_OSG:
		return "Eror WRITE_OUTPUT_FILE_SUMMARY_OSG, could not write the summary file for OrthoGroup Sequence Grabber.";
	case FILTERED_DIR_LIST:
		return "Error FILTERED_DIR_LIST, failed to execute the function GetFilteredDirList";
	case FILTERED_DIR_LIST_NO_ITEMS:
		return "Error FILTERED_DIR_LIST_NO_ITEMS, there are no items within the filtered dir list";
	default:
		return "ERROR UNKOWN, no error number, unknown error.";
	}
	return "ERROR UNKNOWN ERROR occured";
}