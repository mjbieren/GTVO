#!/bin/bash

PROGRAMPATH=~/Programs/GTVO/GTVO_Static_Debian.out #GTVO_Static_Debian.out Change the path
PPP_OUTPUT=COGSPPP #output_alignment folder of PhyloPyPruner
FPPP_OUTPUT=COGSFPP #Output of filter PhyloPyPruner Result
PROTEIN_CHANGED_NAMES_FOLDER=ChangedProteinNames #Mapped genes names that are used to rename all the fasta headers of the sample files (prior placing them into orthofinder)
TPM_VALUES=TPM
TAXONOMICGROUP_FILE=Coleocheatephyceae_TaxonomicGroupFile_FilterPPP_Set.txt
ORTHOFINDER_OUTPUT_FOLDER=N0 #Folder containing N0.tsv files output of HOG of Orthofinder
OUTPUT_FOLDER=Result_GTVO #Output folder
PREFIX_OUTPUT=Loci2924_New_Orbi_Set

#Filter PPP result based on NUMBER_OF_FILTER_GROUPS
#with gene ids
#$PROGRAMPATH -f $INPUT -t $TAXONOMIC_GROUPFILE -r $OUTPUT -n $NUMBER_OF_FILTER_GROUPS -s $SUMMARY_FILE


#-f <COGS_PPP_Output_Folder> Set the Path to the directory containing the output of PPP with the COGS Set in the form of fasta files: REQUIRED 
#-p <COGS_FPPP_Output_Folder> Set the Path to the directory containing the Orthogroups in TSV format: REQUIRED
#-c <Protein_Changed_Name_Folder> Set the Path the folder containing tsv files with old and simplified fasta header names: REQUIRED 
#-t <TPM _VALUE_FOLDER> Set the Path the folder containg the TPM values for each sample (KAllisto output sub folders): REQUIRED 
#-r <OutputFolderPath> Set the Output Folder Path: REQUIRED 
#-g <TaxonomicGroupFile> Set the Taxonomic Group File path: REQUIRED. 
#-o <Orthofinder Output Folder> Set the Path to the directory containing the Orthogroups in TSV format: REQUIRED
#-x <PREFIX> Set the prefix for the output files: NOT REQUIRED (BUT Recommended) 


$PROGRAMPATH -f $PPP_OUTPUT -p $FPPP_OUTPUT -c $PROTEIN_CHANGED_NAMES_FOLDER -t $TPM_VALUES -g $TAXONOMICGROUP_FILE -o $ORTHOFINDER_OUTPUT_FOLDER -x $PREFIX_OUTPUT -r $OUTPUT_FOLDER
