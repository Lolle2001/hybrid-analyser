# Hybrid Analyser

> [!IMPORTANT]
> This code was developed for my thesis. If you use/fork this code, please use the following citation in your work:<br><br>
> L. J. Huisman, _Data analyser for AMPT and IP-Glasma+MUSIC+iSS_, version 1.0.0 (2024). https://github.com/Lolle2001/HybridProcessor

## :rocket: About

This program is for the data analysis of heavy ion collision simulations. Currently it analyses data generated with **[AMPT](https://myweb.ecu.edu/linz/ampt/)**[^1] and the hybrid framework **[IPGlasma](https://github.com/chunshen1987/ipglasma)**+**[MUSIC](https://github.com/MUSIC-fluid/MUSIC)**+**[iSS](https://github.com/chunshen1987/iSS)**[^2][^3][^4].
This program (`analyser`) uses the similarity of the AMPT and iSS data output. The form of the data is in essence a list of particles and their properties for multiple events. The raw data is parsed by this program and processed into histograms. Currently the histograms are hard coded and the framework is setup to generate histograms for yield, transverse momentum spectra, (pseudo)rapidity spectra, anisotropic flow, average transverse momentum and the nuclear modification factor. All histograms are binned as function of centrality, transverse momentum and rapidity. It is easy to change the binning of histograms to a desired format. In addition subprograms exist (`evo-music` and `evo-ampt`) to parse evolution data into a format that can be used for animations. There also is a subprogram (`fitter`) that is able to fit blast wave models to (experimental) data of heavy ion collisions. Currently only simultaneous fitting of the transverse momentum spectrum is supported.

## :wrench: Installation

### Dependencies

Before compilation first make sure that all dependencies are installed.

- [**ROOT**](https://github.com/root-project/root) - Used for simultaneous fitting.
- [**json**](https://github.com/nlohmann/json) - Used for reading and writing JSON files.
- [**fmt**](https://github.com/fmtlib/fmt) - Used for formatting of streams.
- [**argparse**](https://github.com/p-ranav/argparse) - Used for parsing command line arguments.
- [**omp**](https://github.com/open-mpi/ompi) -Used for multi-threading.

### Compilation

Compilation is done by running the following code,

```shell
# Main program: analyser
bash compile.sh

# Animation subprograms: evo-ampt & evo-music
bash compile-evo.sh

# Fitter subprogram: fitter
bash compile-fitter.sh
```

> [!WARNING]
> The program has been tested on linux and MacOS. Depending on your system you might need to modify the makefiles. Currently there is no CMake support.

## :books: Documentation

### Required data structure

For the usage of _analyser_, _evo-music_ and _evo-ampt_ it is assumed that the files have a certain name and that the data is sorted in a subfolders. In the following cases, the `-i` argument is given `{NAME}` as input. `{N}` is the event/batch number and is automatically determined. _fitter_ is intended as a framework and uses by default JSON formatted data, the user however can change this to suit their needs.

### File Paths

<table>
  <thead>
    <tr>
      <th>Software</th>
      <th>File Path</th>
      <th>Required for (type)</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>IPGlasma</td>
      <td>{DATA}/{NAME}/usedParameters{N}.dat</td>
      <td>analyser iss (log)</td>
    </tr>
    <tr>
      <td>MUSIC</td>
      <td>{DATA}/{NAME}/{NAME}-{N}/evolution_for_movie_xyeta.dat</td>
      <td>evo-music (data)</td>
    </tr>
    <tr>
      <td>iSS</td>
      <td>{DATA}/{NAME}/{NAME}-{N}/particle_samples.bin</td>
      <td>analyser iss (data)</td>
    </tr>
    <tr>
      <td rowspan="5">AMPT</td>
      <td>{DATA}/{NAME}/{NAME}-{N}/ana/ampt.dat</td>
      <td>analyser ampt (data)</td>
    </tr>
    <tr>
      <td>{DATA}/{NAME}/{NAME}-{N}/ampt.log</td>
      <td>analyser ampt (log)</td>
    </tr>
    <tr>
      <td>{DATA}/{NAME}/{NAME}-{N}/ana1/h-animate.dat</td>
      <td>evo-ampt (data)</td>
    </tr>
    <tr>
      <td>{DATA}/{NAME}/{NAME}-{N}/ana1/p-animate.dat</td>
      <td>evo-ampt (data)</td>
    </tr>
    <tr>
      <td>{DATA}/{NAME}/{NAME}-{N}/ana1/p-finalft.dat</td>
      <td>evo-ampt (data)</td>
    </tr>
  </tbody>
</table>

### Running _analyser_ with command line arguments

Running with command line arguments allows to use all features of the program. It was designed for the above structure, but it should work for more. `analyser` has tow subprograms called `iss` and `ampt` which can be used as follows,

```shell
# AMPT
./analyser \  # Main program.
 -col ${CLASS} \  # Option for centrality class  definitions.
 ampt \  # Subprogram to parse ampt data.
 -i ${NAME1} ${NAME2} ... ${NAMEn} \  # Input folders.
 -id ${DATA} \  # Input folder directory.
 -o ${OUT} \  # Output folder.
 -od ${OUTDIR} \  # Output folder directory.

# IPGlasma & iSS
./analyser \  # Main program.
 -col ${CLASS} \  # Option for centrality class  definitions.
 iss \  # Subprogram to parse ampt data.
 -i ${NAME1} ${NAME2} ... ${NAMEn} \  # Input folders.
 -id ${DATA} \  # Input folder directory.
 -l ${LOG1} ${LOG2} ... ${LOGn} \  # Log folders.
 -ld ${LOGDIR} \  # Log folder directory.
 -o ${OUT} \  # Output folder.
 -od ${OUTDIR} \  # Output folder directory.
```

`${OUTDIR}` could be the same as `${DATA}` and `${OUT}` the same as `${NAME}` if one folder is given as input. It is then recommended to for example write `-o ${NAME}/processed`. In the program the `-id`, `-ld` and `-od` arguments are put in front of the arguments for `-i`, `-l` and `-o` respectively, to define the right paths. It is possible to give the full path to `-i`, `-l` and `-o` if the data is stored in a different folders.

### Running _analyser_ with a configuration file

Running with a configuration file allows to setup jobs quickly when the data is stored in the same folders. If the flag `-p` is used, then the default arguments will be overwritten by those in the configuration file. Only `-col`, `-o`, `-i` and `-l` have to be specified. The use would then look like,

```shell
# By default -pf is analyser.par and -pd ./
# The configuration file specifies -id, -ld and -od and
# assumes that data is put in a subfolder of ${OUT}.

./analyser -p -col ${CLASS} ampt -o ${OUT} \
-i \
${NAME1} \
${NAME1} \
... \
${NAMEn}

```

### Running _evo-ampt_

> [!NOTE]
> This program requires some updates for proper usage.

### Running _evo-music_

> [!NOTE]
> This program requires some updates for proper usage.

### Running _fitter_

> [!NOTE]
> This program requires some updates for proper usage.

<details><summary><b>Instructions</b></summary>
<!-- ### Adding function to _fitter_ -->

Define a function in the form

```cpp
double function(double * x, double * par);
```

Then do

```cpp
void dofit(){
    CFitter::Chi2Function chi2;
    chi2.SetParIndexes(indexmap);
    chi2.SetData(xvals, yvals, xerrs, yerrs);
    chi2.SetSpecies(species);
    chi2.SetFitRange(fitranges);
    chi2.SetFitFunction(function);

    CFitter::MultiFitter fitter;
    fitter.FixPars(fixedpars);
    fitter.LimitPars(limitpars);
    fitter.SetParLimits(parlimits);
    fitter.SetParStepsize(parsteps);
    fitter.SetParNames(parnames);
    fitter.SetParInit(parinit);
    fitter.StepsizePars(stepsizepars);
    fitter.Run(chi2);
    ROOT::Fit::FitResult result = fitter.GetResult();
}
```

</details>

<!-- ## :chart_with_upwards_trend: Future improvements

- [ ] Add option to write animation histograms into .npy files, for fast loading in python.
- [ ] Improve commandline parser for analyser.
- [ ] Add more options for analyser to be read from .par files.
- [ ] Add subparsers for consistent and more controlable dataprocessing and less errors.
- [x] Rename the repository to "hybrid-analyser" and executable to "analyser" and use subparsers to acces animation analysis and fitting.
- [ ] Switch to JSON/HDF5
- [ ] Add CMake support. -->

[^1]: Z. W. Lin, C. M. Ko, B. A. Li, B. Zhang and S. Pal, _A Multi-phase transport model for relativistic heavy ion collisions_. Phys. Rev. C 72, 064901 (2005). https://doi.org/10.1103/PhysRevC.72.064901
[^2]: Schenke, S. Jeon, C. Gale. _3+1D hydrodynamic simulation of relativistic heavy-ion collisions_. Phys.Rev.C 82, 014903 (2010) [arXiv:1004.1408](https://arxiv.org/abs/1004.1408)
[^3]: Schenke, S. Jeon, C. Gale. _Elliptic and triangular flow in event-by-event (3+1)D viscous hydrodynamics_. Phys.Rev.Lett. 106, 042301 (2011). [arXiv:1009.3244](https://arxiv.org/abs/1009.3244)
[^4]: J.-F. Paquet, C. Shen, G. S. Denicol, M. Luzum, B. Schenke, S. Jeon, and C. Gale. _Production of photons in relativistic heavy-ion collisions_. Phys. Rev. C 93, 044906 (2016). [arXiv:1509.06738](https://arxiv.org/abs/1509.06738)
