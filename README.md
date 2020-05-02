# Antarctic Propagator for Neutrino and Cosmic Ray Observatories (APRICOT)

![GitHub](https://img.shields.io/github/license/rprechelt/apricot?logoColor=brightgreen)
[![C++: 17](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
![Python](https://img.shields.io/badge/python-3.6%20%7C%203.7%20%7C%203.8-blue)
[![Code style: black](https://img.shields.io/badge/code%20style-black-000000.svg)](https://github.com/psf/black)


APRICOT (**A**ntarctic **P**ropagator for Neut**ri**no and **C**osmic Ray
**O**bserva**t**ories) is a general purpose framework for propagating
*ultra-high energy particles* (typically greater than 1 EeV) through the *Earth*
(in 3D) to a user-specified *detection* volume.

While initially constructed to simulate neutrino propagation in Antarctica for
the **AN**tarctic **I**mpulsive **T**ransient **A**ntenna (ANITA), `apricot` has
been designed to be extremely flexible and can be used to propagate custom
particles from user-specified source particle distributions to user-specified
detection volumes using fast parametrizations of ultra-high-energy (UHE)
neutrino and lepton physics.

`apricot` is written in modern C++ (17) for performance reasons but a complete Python
wrapper is provided that allows configuration, execution, and analysis to be
performed solely from Python. However, the C++ backend is still feature-complete
and can be used independent of the Python interface.

`apricot` currently supports:

* Spherical (with custom radius) and Ellipsoidal (WGS84) Earth models with the
  PREM500 earth density dataset.
* Ultra-high energy (> 1 EeV) neutrino and anti-neutrino propagation with several
  charged current and neutral neutrino cross section models as well as different
  models for the neutrino-nucleon Y-factor.
* Propagation of UHE muons and tau-leptons including tau-lepton decays
  (implemented using TAUOLA) as well as several fast continuous models for
  UHE lepton energy loss processes.
* Several Antarctic ice models including fast exponential parameterizations as
  well as the full BEDMAP2 dataset.
* Various particle sampling methods including fixed energy, uniform log-space or
  linear-space energies, or sampling from a standard text-based flux file
  format. 
* Various particle source classes to model isotropic and point source fluxes.
* Basic ultra-high-energy cosmic ray (UHECR) propagation to calculate the
  location of shower max for different UHECR primaries. This is useful for
  generating cosmic ray trial events that can then be passed to other dedicated
  shower simulation codes.

All aspects of `apricot` are extensible in C++ (and most in Python) so the simulation
framework can be easily adapted for a particular simulation.

`apricot` is exclusively designed for **ultra-high energy** particle propagation
(with a key focus on neutrino propagation). We use parametrizations exclusively
designed for this regime and make several assumptions that will start to fail at
lower energies. Typical applications of `apricot` are for source particle
energies greater than 100 PeV and up to 1 ZeV (1,000,000 PeV).

## Installation

`apricot` has the following dependencies:

- GCC >= 7.x 
- CMake 3
- Eigen3
- Python >= 3.6 (optional for the Python bindings)

All of these dependencies are available in most Linux package managers and
Homebrew for MacOS.

If you only want to use `apricot` without modification, then the project can be
directly installed using `pip` (most users will probably want to install
`apricot` in *development mode*).

To install directly from `git`,

``` shell
pip install git+git://github.com/rprechelt/apricot.git#egg=apricot
```

### Development Mode
If you wish to develop the package (and therefore have access to the C++ and
Python source), you should clone this repository directly and install using `pip`.

``` shell
git clone --recursive https://github.com/rprechelt/apricot
cd apricot
pip install --user -e .
```

