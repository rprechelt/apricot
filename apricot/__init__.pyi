"""
Since most of apricot's functionality is in the C++ shared library,
and mypy is unable to extract type information from this, we need
to provide typing stubs so we can get MyPy type-checking in the
rest of the codebase.
"""
import numpy as np


class Earth:
    ...


class SphericalEarth(Earth):
    def __init__(self, radius: float):
        ...


class ExponentialAtmosphere:
    ...


class Source:
    ...


class SphericalCapSource(Source):
    def __init__(self, radius: float, theta: float, center: float):
        ...


class Flux:
    ...


class FixedFlux(Flux):
    ...


class UniformFlux(Flux):
    ...


class Detector:
    ...


class OrbitalDetector(Detector):
    def __init__(self, earth: Earth, payload: np.ndarray, maxview: float, mode: str):
        ...


class Propagator:
    ...


class SimplePropagator(Propagator):
    def __init__(self, earth: Earth):
        ...

    def propagate(self, source: Source, flux: Flux, detector: Detector, ntrials: int):
        ...


class Interaction:
    pdgid: int
    energy: float
    type: int
    location: np.ndarray
    direction: np.ndarray
    weight: float
    altitude: float
