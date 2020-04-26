# Antarctic Particle Propagator (APRICOT)

[![Actions Status](https://github.com/rprechelt/apricot/workflows/CI/badge.svg)](https://github.com/rprechelt/apricot/actions)
![GitHub](https://img.shields.io/github/license/rprechelt/apricot?logoColor=brightgreen)
![Python](https://img.shields.io/badge/python-3.6%20%7C%203.7%20%7C%203.8-blue)
[![Code style: black](https://img.shields.io/badge/code%20style-black-000000.svg)](https://github.com/psf/black)

APRICOT (**A**ntarctic **P**a**r**t**ic**le Pr**o**paga**t**or) is a general
purpose framework for propagating ultra-high energy particles (typically greater
than 1 PeV) through the *Earth* (in 3D) to a user-specified *detection* volume.

While initially constructed to only simulate neutrino propagation in Antarctica
for the **AN**tarctic **I**mpulsive **T**ransient **A**ntenna (ANITA), `apricot`
has been designed to be extremely flexible and can be used to propagate custom
particles from user-specified source particle distributions to user-specified
detection volumes using fast parametrizations of ultra-high-energy (UHE)
neutrino and lepton physics.

`apricot` is written in modern C++ (17) for performance reasons but a complete Python
wrapper is provided that allows configuration, execution, and analysis to be
performed solely from Python. However, the C++ backend is still feature-complete
and can be used independent of the Python wrapper.

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

