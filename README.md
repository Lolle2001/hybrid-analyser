# Hybrid Processor

> [!IMPORTANT]
> If you use/fork this code, please use the following citation:<br><br>
> L. J. Huisman, _Data analyser for AMPT and IP-Glasma+MUSIC+iSS_, thesis database UU (2024). https://link

## Description

This code is for data analysis of heavy ion collision simulations. Currently it processes data from **[AMPT](https://myweb.ecu.edu/linz/ampt/)**[^1] and the hybrid framework **[IPGlasma](https://github.com/chunshen1987/ipglasma)**+**[MUSIC](https://github.com/MUSIC-fluid/MUSIC)**+**[iSS](https://github.com/chunshen1987/iSS)**[^2][^3][^4].

Both AMPT and iSS output their data in a format that includes an event with a list of particles and their properties like momentum and mass. This allows for a similar way of data analysis, hence this software that allows to process both. The structure of the code however allows for extension to non-similar data output. Data will eventually always be put into histograms.

Currently the framework is setup to generate histograms for yield, transverse momentum spectra, (pseudo)rapidity spectra, anisotropic flow, average transverse momentum and the nuclear modification factor. All histograms are binned as function of centrality, transverse momentum and rapidity. It is easy to change the binning of histograms to a desired format.

Currently there are multiple types of histograms: 1D, 2D, 3D and Map3D.

- 1D Histogram: used for event statistics, like the average impact parameter per bin, number of participant nucleons and binary collisions, but also the average transverse momentum.
- 2D Histogram: used mainly to obtain observables as function of centrality and transverse momentum or rapidity.
- 3D Histogram: used for particle specific statistics, like the spectra, anisotropic flow etc. This can be used to be more precise on how a histogram is filled, for example by allowing both $\pi^+$ and $\pi^-$ to contribute to it, such that a summed spectrum is obtained.
- 3D Histogram Map: used for single particle statistics. This currently only is used for fitting.

## Structure

The main part of the program is to process the final state data from AMPT and iSS (using IPGlasma+MUSIC). The program is called `analyser`. Both output a format in terms of a list of particles, with their monte carlo ID, position, momentum and mass. The main part source code can be found directly in the directory `src`.

To investigate evolution dynamics of AMPT and MUSIC two sub programs have been developed to process data which can for example be used for animations. The programs are called `evo-ampt` and `evo-music` respectively. The source code for these programs can be found in `src/evolution-ampt` and `src/evolution-music`.

Another program that was created is `fitter`. This program was intended to fit the (spherical/elliptical) Boltzmann-Gibbs blast wave model and Tsallis blast wave model to the invariant transverse momentum differential (i.e. the transverse momentum spectrum). Development of this code was stopped after trying numerous attempts to fit the functions without having numeric problems and useless fit paramaters. Another reason was that it is redundant in the case that the low transverse momentum part of the spectrum fits experimental data well. Experimental data has already been thrown against these models in many articles.

## Compilation

To compile the programs several makefiles have been made, which can be found in the directory `make`. Helper scripts have been made for easy compilation and begin with `compile`. To compile `analyser` one can use `bash compile.sh`, and similar for the other options. The object files are stored in the directory `build`. Keep in mind that compilation is done with the use of `12` cores. To change this the files can be edited. A future improvement would be to use `cmake` which handles a lot of aspects automatically. Having that in mind, it should be noted that several libraries such as `ROOT`, `nlohmann`, `GSL`, `fmt`, `argparse` and `omp` are needed. The makefiles are very simple and therefore might require modifications to include the libraries and make the compilation work for your system.

## Usage

### Datastructure

To use the programs one first has to make sure the data structure has the right format and that the parameter files have been modified correctly. The data structure is not to difficult. For AMPT it is needed that all runs are stored in a datafolder (desirably the same). Currently it is needed that this is a number. Each folder needs a subfolder which has a postfix denoting the data from a single thread. This folder needs to contain a similarly formatted `.log` file with the output of the program `ampt` (see AMPT Processor page for further details). This file contains the number of binary collisions and the program will not work without this. In the subfolder `ana` the general output is stored, in `ana1` the animation files will be stored (see AMPT Processor page for further details).

Similarly for iSS, a datafolder contains a folder named with a number. It contains a sub folder for every hydro event. The subfolder contains the output of iSS. It is important that the `usedParameters` file of IPGlasma can be read, this contains the number of binary collisions and number of participants, as wel as the impact parameter. Without this the program cannot run.

The assumed structure in which data is stored is as follows:

```
AMPT/iSS
|
|-- data
|     |-- run-1
|           |-- run-1-1
|           |-- run-1-2
|           |-- run-1-...
```

### Running

To parse iSS data use `./analyser iss`, to parse AMPT data use `./analyser ampt`. There are several required options:

- `-i` specifies the name of the directory in which the data is stored (e.g. `run-1`).
- `-o` specifies the name of the directory in which you want to output the analysed data (e.g. `run-1/processed`).
- `-col` specifies the centrality classification that must be used.

Default parameter values are read from the `analyser.par` file (such as default directories, which makes it easier to use).

# Hybrid Analyser

## Description

## Installation

### Dependencies

Before compilation first make sure that all dependencies are installed.

- [**GSL**](https://github.com/ampl/gsl)
- [**ROOT**](https://github.com/root-project/root)
- [**json**](https://github.com/nlohmann/json)
- [**fmt**](https://github.com/fmtlib/fmt)
- [**argparse**](https://github.com/p-ranav/argparse)
- [**omp**](https://github.com/open-mpi/ompi)

### Compilation

> [!WARNING]
> The program has been tested on linux and MacOS. Depending on your system you might need to modify the makefiles. Currently there is no CMake support.

## Usage

### Required data structure

For the usage of _analyser_ it is assumed that the files have a certain name and that the data is sorted in a subfolders. In the following cases, the `-i` argument is given `{NAME}` as input. `{N}` is the event/batch number and is automatically determined.

**IPGlasma**

- `{NAME}/usedParameters{N}.dat`

**MUSIC**

- `{NAME}/{NAME}-{N}/evolution_for_movie_xyeta.dat`

**iSS**

- `{NAME}/{NAME}-{N}/particle_samples.bin`

**AMPT**

- `{NAME}/{NAME}-{N}//ana/ampt.dat`
- `{NAME}/{NAME}-{N}//ampt.log`
- `{NAME}/{NAME}-{N}//ana1/h-animate.dat`
- `{NAME}/{NAME}-{N}//ana1/p-animate.dat`
- `{NAME}/{NAME}-{N}//ana1/p-finalft.dat`

### Running _analyser_ with command line arguments

Running with command line arguments allows to use all features of the program.

### Running _analyser_ with a configuration file

Running with a configuration file allows to setup jobs quickly when the data is stored in the same folders.

### Running _evo-ampt_

### Running _evo-music_

### Running _fitter_

### Adding function to _fitter_

Define a function in the form

```[c++]
double function(double * x, double * par)
```

## Future improvements

- [ ] Add option to write animation histograms into .npy files, for fast loading in python.
- [ ] Improve commandline parser for analyser.
- [ ] Add more options for analyser to be read from .par files.
- [ ] Add subparsers for consistent and more controlable dataprocessing and less errors.
- [x] Rename the repository to "hybrid-analyser" and executable to "analyser" and use subparsers to acces animation analysis and fitting.
- [ ] Switch to JSON/HDF5
- [ ] Add CMake support.

[^1]: Z. W. Lin, C. M. Ko, B. A. Li, B. Zhang and S. Pal, _A Multi-phase transport model for relativistic heavy ion collisions_. Phys. Rev. C 72, 064901 (2005). https://doi.org/10.1103/PhysRevC.72.064901
[^2]: Schenke, S. Jeon, C. Gale. _3+1D hydrodynamic simulation of relativistic heavy-ion collisions_. Phys.Rev.C 82, 014903 (2010) [arXiv:1004.1408](https://arxiv.org/abs/1004.1408)
[^3]: Schenke, S. Jeon, C. Gale. _Elliptic and triangular flow in event-by-event (3+1)D viscous hydrodynamics_. Phys.Rev.Lett. 106, 042301 (2011). [arXiv:1009.3244](https://arxiv.org/abs/1009.3244)
[^4]: J.-F. Paquet, C. Shen, G. S. Denicol, M. Luzum, B. Schenke, S. Jeon, and C. Gale. _Production of photons in relativistic heavy-ion collisions_. Phys. Rev. C 93, 044906 (2016). [arXiv:1509.06738](https://arxiv.org/abs/1509.06738)
