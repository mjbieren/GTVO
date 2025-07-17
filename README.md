# 🧬 Get TPM Values for Orthogroups (GTVO)

**GTVO** is a C++ tool developed to match and organize **TPM values** across orthogroups (HOGs) derived from the PhyloRSeq++ pipeline. It correlates processed protein names, transcript expression (TPM) values, and orthogroup structure from **OrthoFinder** and **Phylopypruner** outputs.

This tool was developed for the Coleochaetophyceae phylogenomics project and helps summarize gene expression across orthogroups, with special consideration for renamed proteins and taxonomic structure.

---

## ⚙️ Overview of GTVO Workflow

1. **Parse Command-Line Inputs**
2. **Read and Match Input Data**
3. **Integrate TPM Values Across Orthogroups**
4. **Generate Final Summary Tables**

---

## 🗂️ Input Requirements

| Argument | Description |
|----------|-------------|
| `-f`     | Path to COGS PPP output (fasta files) |
| `-p`     | Path to COGS FilterPPP output (filtered headers only) |
| `-c`     | Folder containing renamed protein headers (TSV format) |
| `-t`     | Folder containing TPM value tables (1 per species) |
| `-r`     | Output folder for results |
| `-g`     | Taxonomic group file (used for header ordering) |
| `-o`     | OrthoFinder output folder (for N0.tsv file) |
| `-x`     | Prefix for the output files |

---

## 📥 Step-by-Step Process

### 🧾 Step 1 – Command-Line Argument Parsing

GTVO expects 7 inputs:

- Filtered and unfiltered orthogroup data (In- and Output of FPPPResult)
- N0.tsv from OrthoFinder (Phylogenetic_Hierarchical_Orthogroups)
- TPM expression values per sample/species
- Protein header renaming files (It's common practice to use simplified names for orthofinder for easy lookup)
- A taxonomic group reference (used for consistent column ordering)


---

### 🧬 Step 2 – Parse Input Files

- All Fasta files from both the COGS PPP output and C
- Renaming tables are used to match standardized protein names to original IDs
- TPM values are extracted per species/sample
- The **taxonomic group file** is used to sort species for consistent header ordering alphabetically

---

### 🔍 Step 3 – Match TPM Values to Orthogroups

GTVO produces **two tables**:

#### 1. Filtered HOGs Table

For each HOG that passed PPP filtering:
- Uses only the relevant HOGs (from FilterPPP output)
- Loops over each protein in the fasta file
- Matches renamed headers to original names
- Extracts TPM from species-specific tables
- Sets **`N/A`** if TPM data is missing or to `0` when the species has no represented member for this gene family.

#### 2. All HOGs Table (based on N0.tsv)

- Reads all orthogroups from N0.tsv
- Handles multiple proteins per species
- Fallbacks to `0` or `N/A` when TPM is missing (0) or renaming files (N/A) don’t exist 
- Includes expression for every protein instance (can be redundant)

---

### 💾 Step 4 – Output

Two output tables are written to the result folder:

- **Filtered TPM Summary Table**

```
Orthogroup     Species_1     Species_2     Species_N
HOG0001           0.00          1.25           N/A
HOG0002           N/A           N/A            3.45
...
```

- **All TPM Summary Table (from N0.tsv)**

Each table is organized according to the taxonomic group file. Expression values are numeric (TPM), `0` if present but no expression, and `N/A` if missing.

---

## 📁 Folder Structure Example

```
project/
├── ChangedNames/              # Renamed protein headers (TSV)
├── COGS_PPP/                  # Full COGS PPP output (fasta)
├── COGS_FilterPPP/            # Filtered fasta headers
├── TPM_Tables/                # TPMs per species (TSV)
├── Orthofinder_Output/        # Includes N0.tsv
├── TaxonomicGroups.txt        # Taxonomic group definitions
└── Results/                   # Output files from GTVO
```

See [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.16044005.svg)](https://doi.org/10.5281/zenodo.16044005) for the example set.

For an example script see [GTVO_Example.sh](https://github.com/mjbieren/GTVO/blob/main/GTVO_Example.sh)

---

## ⚙️ Executables

Precompiled static executables available:  

- Debian 12: [GTVO_Static_Debian.out](https://github.com/mjbieren/GTVO/blob/main/Sources/Executables/GTVO_Static_Debian.out)  
- Rocky Linux 8: [GTVO_Static_HPC.out](https://github.com/mjbieren/GTVO/blob/main/Sources/Executables/GTVO_Static_HPC.out)  

Or compile from source. (Boost library 1.88, visual studio 2019, gcc compiler)

---

## 📧 Contact

**Maaike Jacobine Bierenbroodspot**  
📧 maaikejacobine.bierenbroodspot@uni-goettingen.de

---

## 🧪 Notes

- This tool assumes consistent naming conventions across the pipeline.
- Species names must match exactly between TPM files name and taxonomic group taxa.
- The more complete your renaming and TPM files are, the more accurate the summary will be.
