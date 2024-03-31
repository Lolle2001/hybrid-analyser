# Hybrid Processor

## Description

This code is extensible data processing code for heavy ion collision simulation software. Currently it processes data from **AMPT** and the hybrid framework **IPGlasma**+**MUSIC**+**iSS**.

Both AMPT and iSS output their data in a format that includes an event with a list of particles and their properties like momentum and mass. This allows for a similar way of data processing, hence this software that allows to process both. The structure of the code however allows for extension to non-similar data output. Data will eventually always be put into histograms.

Currently the framework is setup to generate histograms for yield, transverse momentum spectra, (pseudo)rapidity spectra, anisotropic flow, average transverse momentum and the nuclear modification factor. All histograms are binned as function of centrality, transverse momentum and rapidity. It is easy to change the binning of histograms to a desired format.

Currently there are multiple types of histograms: 1D, 2D, 3D and Map3D.

- 1D Histogram: used for event specific statistics, like the average impact parameter per bin, number of participant nucleons and binary collisions.
- 2D Histogram: currently not used.
- 3D Histogram: used for particle specific statistics, like the spectra, anisotropic flow etc. This can be used to be more precise on how a histogram is filled, for example by allowing both $\pi^+$ and $\pi^-$ to contribute to it, such that a summed spectrum is obtained.
- 3D Histogram Map: used for single particle statistics. This currently only is used for fitting.

## Use

To use the program it is desirable to compile the code with openmp. By calling the `make -j $numberofavailblecores` command when in the main directory. This will create an executable called `hybridp`.

The code currently assumes that the data is outputted in a certain way:

- For AMPT that is, the data of a simulation is stored in a directory with a number, inside the directory there are subdirectories with the format `$runnumber_$index`. These folder will then contain a folder `ana` that has the file `ampt.dat` inside it. It is mandatory to have a log file with the format `$runnumber_$index.log` inside the subdirectory, which contains the output of AMPT. Inside this the number of binary collisions is listed, which is important. To get this correct straight away it is recommended to used the multiprocessing code for AMPT in my other repositery.
- For the hydro framework the data for iSS must be inside a folder with the same structure as AMPT. But the subdirectories will directly contain a folder called `particle_samples.bin`. Make sure that the corresponding IPGlasma parameter files are available, with the correct index label. This file will contain the number of participant nucleons and binary collisions of the event.
- There is a parameter file `ProcessParameters.par` in which the data directories of AMPT, iSS and IPGlasma can be specified.

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
