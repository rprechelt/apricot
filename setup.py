from os import path
from setuptools import setup, find_packages
from cmake import CMakeExtension, CMakeBuild

# the apricot version
__version__ = "0.1.0"

# get the absolute path of this project
here = path.abspath(path.dirname(__file__))

# Get the long description from the README file
with open(path.join(here, "README.md"), encoding="utf-8") as f:
    long_description = f.read()

# the standard setup info
setup(
    name="apricot",
    version=__version__,
    description=(
        "Propagate ultra-high-energy particles through the Earth"
        " to Antarctica and beyond!"
    ),
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/rprechelt/apricot",
    author="Remy L. Prechelt",
    author_email="prechelt@hawaii.edu",
    classifiers=[
        "Development Status :: 3 - Alpha",
        "License :: OSI Approved :: MIT License",
        "Intended Audience :: Science/Research",
        "Topic :: Scientific/Engineering :: Physics",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
    ],
    keywords=[
        "anita",
        "science",
        "neutrino",
        "point",
        "source",
        "antarctica",
        "cosmic ray",
    ],
    packages=["apricot"],
    python_requires=">=3.6*, <4",
    install_requires=["configargparse", "numpy"],
    extras_require={
        "test": [
            "matplotlib",
            "uproot",
            "isort",
            "mypy",
            "black",
            "flake8",
            "pytest",
            "coverage",
        ],
        "root": ["uproot", "pandas"],
    },
    scripts=["scripts/apricot"],
    project_urls={
        "NuTauSim": "https://github.com/harmscho/NuTauSim",
        "ANITA Github": "https://github.com/anitaNeutrino",
    },
    include_package_data=True,
    # call into CMake to build our module
    ext_modules=[CMakeExtension("_apricot")],
    cmdclass={"build_ext": CMakeBuild},
    zip_safe=False,
)
