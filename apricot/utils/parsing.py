"""
This module provides some basic parsing help.
"""
from typing import Any, Optional, Union

import apricot


def create_flux(
    particle: str,
    min_energy: Optional[float],
    max_energy: Optional[float],
    fixed_energy: Optional[float],
) -> apricot.Flux:
    """
    Create a Flux model from config arguments.

    If `fixed_energy` is not None, return a fixed
    energy sampler at that energy. Otherwise, return
    a UniformParticleFlux between `min_energy`` and `max_energy`.


    Parameters
    ----------
    particle: str
        The particle to sample.
    min_energy: Optional[float]
        The minimum energy to sample [log10(eV)].
    max_energy: Optional[float]
        The maximum energy to sample [log10(eV)].
    fixed_energy: Optional[float]
        If provided, the fixed energy to sample [log10(eV)].

    Returns
    -------
    flux: apricot.Flux
        An apricot Flux model.

    Raises
    ------
    ValueError
        If we are unable to parse the args into a valid flux model.
    """

    # convert the particle species into upper-case first
    particle = particle.capitalize()

    # if we got given a fixed energy, create a fixed sample
    if fixed_energy is not None:

        # get the appropriate flux sampler
        flux = getattr(apricot, f"Fixed{particle}Flux")

        # and create it at the right energy:
        return flux(fixed_energy)

    elif min_energy is not None and max_energy is not None:
        # we create a uniform sampler
        flux = getattr(apricot, f"Uniform{particle}Flux")

        # and create it at the right energy:
        return flux(min_energy, max_energy)

    else:  # otherwise, raise a ValueError
        msg = (
            "Unable to create a Flux model from: \n"
            f"particle:     {particle}\n"
            f"min_energy:   {min_energy}\n"
            f"max_energy:   {max_energy}\n"
            f"fixed_energy: {fixed_energy}\n"
        )
        raise ValueError(msg)


def create_earth(
    earth_model: str, earth_radius: Union[str, float], **kwargs
) -> apricot.Earth:
    """
    Create an Earth model from config arguments.

    Parameters
    ----------
    earth_model: str
        The Earth model to use.
    earth_radius: Union[str, float]
        The radius type to use ("polar", "equatorial") or a fixed radius.

    Returns
    -------
    earth: apricot.Earth
        An apricot Earth model.

    Raises
    ------
    ValueError
        If an unknown `earth_model` was provided.
    """

    # we model a spherical Earth
    if earth_model == "spherical":

        # parse the earth radius into a float
        radius = parse_earth_radius(earth_radius)

        # and create the corresponding Earth model
        return apricot.SphericalEarth(radius)

    else:  # catch any other Earth models, just in case
        raise ValueError(f"{earth_model} is not a currently supported Earth model.")


def parse_earth_radius(earth_radius: Union[str, float]) -> float:
    """
    Parse an `earth_radius` into a radius in km.

    Parameters
    ----------
    earth_radius: Union[str, float]
        The radius type to use ("polar", "equatorial") or a fixed radius.

    Returns
    -------
    radius: float
        The radius in km.

    Raises
    ------
    ValueError
        If `earth_radius` cannot be parsed.
    """

    # if we already have a floating point radius
    if isfloat(earth_radius):
        return float(earth_radius)
    else:  # this should be an identifying string "polar" etc.

        # if it's not a string, then just give up
        if not isinstance(earth_radius, str):
            raise ValueError(f"{earth_radius} is not a valid radius specifier.")

        # check that this is currently included in apricot
        try:
            return getattr(apricot.SphericalEarth, earth_radius.lower())
        except Exception as _:  # noqa
            raise ValueError(f"'{earth_radius}' is not recognized by apricot.")


def isfloat(value: Any) -> bool:
    """
    Check if a value is convertible to float.

    Parameters
    ----------
    value: Any
        An unknown value

    Returns
    -------
    isfloat: bool
        True if convertible to float.
    """
    try:
        float(value)
        return True
    except ValueError:
        return False
