# Hybrid Processor

## Description

This code is extensible data processing code for heavy ion collision simulation software. Currently it processes data from **AMPT** and the hybrid framework **IPGlasma**+**MUSIC**+**iSS**.

Both AMPT and iSS output their data in a format that includes an event with a list of particles and their properties like momentum and mass. This allows for a similar way of data processing, hence this software that allows to process both. The structure of the code however allows for extension to non-similar data output. Data will eventually always be put into histograms.

Currently the framework is setup to generate histograms for yield, transverse momentum spectra, (pseudo)rapidity spectra, anisotropic flow, average transverse momentum and the nuclear modification factor. All histograms are binned as function of centrality, transverse momentum and rapidity. It is easy to change the binning of histograms to a desired format.

Currently there are multiple types of histograms: 1D, 2D, 3D and Map3D.

- 1D Histogram: used for event statistics, like the average impact parameter per bin, number of participant nucleons and binary collisions, but also the average transverse momentum.
- 2D Histogram: used mainly to obtain observables as function of centrality and transverse momentum or rapidity.
- 3D Histogram: used for particle specific statistics, like the spectra, anisotropic flow etc. This can be used to be more precise on how a histogram is filled, for example by allowing both $\pi^+$ and $\pi^-$ to contribute to it, such that a summed spectrum is obtained.
- 3D Histogram Map: used for single particle statistics. This currently only is used for fitting.

## Structure

The main part of the program is to process the final state data from AMPT and iSS (using IPGlasma+MUSIC). The program is called `hybridp`. Both output a format in terms of a list of particles, with their monte carlo ID, position, momentum and mass. The main part source code can be found directly in the directory `src`.

To investigate evolution dynamics of AMPT and MUSIC two sub programs have been developed to process data which can for example be used for animations. The programs are called `evo-ampt` and `evo-music` respectively. The source code for these programs can be found in `src/evolution-ampt` and `src/evolution-music`.

Another program that was created is `fitter`. This program was intended to fit the (spherical/elliptical) Boltzmann-Gibbs blast wave model and Tsallis blast wave model to the invariant transverse momentum differential (i.e. the transverse momentum spectrum). Development of this code was stopped after trying numerous attempts to fit the functions without having numeric problems and useless fit paramaters. Another reason was that it is redundant in the case that the low transverse momentum part of the spectrum fits experimental data well. Experimental data has already been thrown against these models in many articles.

## Compilation

To compile the programs several makefiles have been made, which can be found in the directory `make`. Helper scripts have been made for easy compilation and begin with `compile`. To compile `hybridp` one can use `bash compile.sh`, and similar for the other options. The object files are stored in the directory `build`. Keep in mind that compilation is done with the use of `12` cores. To change this the files can be edited. A future improvement would be to use `cmake` which handles a lot of aspects automatically. Having that in mind, it should be noted that several libraries such as `ROOT`, `nlohmann`, `GSL` and `omp` are needed. The makefiles are very simple and therefore might require modifications to include the libraries and make the compilation work for your system.

## Usage

### Datastructure

To use the programs one first has to make sure the data structure has the right format and that the parameter files have been modified correctly. The data structure is not to difficult. For AMPT it is needed that all runs are stored in a datafolder (desirably the same). Currently it is needed that this is a number. Each folder needs a subfolder which has a postfix denoting the data from a single thread. This folder needs to contain a similarly formatted `.log` file with the output of the program `ampt` (see AMPT Processor page for further details). This file contains the number of binary collisions and the program will not work without this. In the subfolder `ana` the general output is stored, in `ana1` the animation files will be stored (see AMPT Processor page for further details).

Similarly for iSS, a datafolder contains a folder named with a number. It contains a sub folder for every hydro event. The subfolder contains the output of iSS. It is important that the `usedParameters` file of IPGlasma can be read, this contains the number of binary collisions and number of participants, as wel as the impact parameter. Without this the program cannot run.

### Running

To use the program it is desirable to compile the code with openmp. By calling the `bash compile.sh` command when in the main directory. This will create an executable called `hybridp`.

The code currently assumes that the data is outputted in a certain way:

- For AMPT that is, the data of a simulation is stored in a directory with a number, inside the directory there are subdirectories with the format `$runnumber_$index`. These folder will then contain a folder `ana` that has the file `ampt.dat` inside it. It is mandatory to have a log file with the format `$runnumber_$index.log` inside the subdirectory, which contains the output of AMPT. Inside this the number of binary collisions is listed, which is important. To get this correct straight away it is recommended to used the multiprocessing code for AMPT in my other repositery.
- For the hydro framework the data for iSS must be inside a folder with the same structure as AMPT. But the subdirectories will directly contain a folder called `particle_samples.bin`. Make sure that the corresponding IPGlasma parameter files are available, with the correct index label. This file will contain the number of participant nucleons and binary collisions of the event.
- There is a parameter file `hybridp.par` in which the data directories of AMPT, iSS and IPGlasma can be specified. A JSON format is used, to allow for easy modification of the code.

When using the hydro framework one can call:

```
./hybridp hydro $runnumber
```

or

```
./hybridp hydro -nr $runnumber -nrip $ipglasmarunnumber -ne $numberofevents -col $centralitybinningoption -par $directoryofparameterfile
```

For AMPT one can call:

```
./hybridp transport $runnumber
```

or

```
./hybridp transport -nr $runnumber -nb $endindexofbatch -nbmin $startindexofbatch -col $centralitybinningoption -par $directoryofparameterfile
```

It is possible to combine multiple runs, by passing a list of runnumbers to `-nr` and/or `-nrip`. The option `-col 4` will use centrality binning from my thesis.

## Future improvements

- [ ] Add option to write animation histograms into .npy files, for fast loading in python.
- [ ] Improve commandline parser for hybridp.
- [ ] Add more options for hybridp to be read from .par files.
- [ ]
