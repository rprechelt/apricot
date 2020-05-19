"""
Provide various geometry related functions for apricot data.
"""
from typing import Any, Union

import numpy as np
import pandas as pd

import _apricot
import _apricot.geometry
from _apricot.geometry import (
    propagate_to_sphere,
    random_cap_point,
    random_spherical_point,
    reflect_below,
    spherical_cap_area,
)


def latlon(
    events: pd.DataFrame, inplace: bool = False
) -> Union[np.ndarray, pd.DataFrame]:
    """
    Calculate the latitude and longitude of each event.

    Parameters
    ----------
    events: pd.DataFrame
        The loaded apricot events.
    inplace: bool
        If True, add the columns to the DataFrame.

    Returns
    -------
    latlon: np.ndarray
        A (N, 2) array containing latitude and longitude [degrees].
    """

    # compute the radius of these events
    radius = np.linalg.norm(get_locations(events), axis=1)

    # and the longitude
    longitude = np.degrees(np.arctan2(events["location.y"], events["location.x"]))

    # and compute the polar theta
    theta = np.arccos(events["location.z"] / radius)

    # and convert this into a latitude
    latitude = np.degrees(np.pi / 2.0 - theta)

    # if we want this in-place, we add the columns
    if inplace:
        events["latitude"] = latitude
        events["longitude"] = longitude
        return events

    # otherwise, return the stack
    return np.vstack((latitude, longitude)).T


def payload_elevation(
    events: pd.DataFrame,
    parameters: pd.DataFrame,
    inplace: bool = False,
    reflected=False,
    **kwargs: Any
) -> Union[np.ndarray, pd.DataFrame]:
    """
    Calculate the payload elevation angle of various interactions.

    This returns the angle in degrees w.r.t the payload horizon
    of the interaction location as seen from the payload. Positive
    is above the payload horizontal, negative below.

    Parameters
    ----------
    events: pd.DataFrame
        apricot interactions stored in a DataFrame
    parameters: pd.DataFrame
        Apricot parameters stored in a pandas DataFrame
    inplace: bool
        If True, add elevation angles to DataFrame.

    Returns
    -------
    elevation_angle: np.ndarray
        Payload elevation angles [degrees].
    """

    # construct the payload from the parameters
    payload = get_payload(parameters)

    # if these are reflected events, propagate them to the surface first
    if reflected:
        locations = _apricot.geometry.propagate_to_sphere(
            get_locations(events), get_directions(events), parameters.Re[0]
        )
    else:
        locations = get_locations(events)

    # get the vector from the payload to the interaction
    view = locations - payload

    # normalize the view vector
    view /= np.linalg.norm(view, axis=1).reshape((-1, 1))

    # and compute the dot product between view and payload
    dot = np.einsum("ij,ij->i", payload / np.linalg.norm(payload, axis=1), view)

    # and convert this into an angle in degrees and map
    # so that the horizon is at 0 degrees
    angle = np.degrees(np.pi / 2.0 - np.arccos(dot))

    # we now calculate the off-axis view angles
    # for each of these events
    offaxis = view_angle(events, parameters)

    # if the offaxis is greater than 90 degrees, we need to
    # reflect the elevation angles above the horizon
    # since they are events that developed PAST anita.

    # these are the events we need to invert above the horizon
    backward = offaxis > 90.0

    # so invert/reflect over the horizon
    angle[backward] = -angle[backward]

    # if we have inplace, add it to the DataFrame
    if inplace:
        events["elevation"] = angle
        events["backwards"] = backward

    # otherwise, just return the angle's
    return angle


def reflected_view_angle(
    events: pd.DataFrame,
    parameters: pd.DataFrame,
    inplace: bool = False,
) -> Union[np.ndarray, pd.DataFrame]:
    """
    Calculate the view angle for reflected interactions.

    This returns the angle in degrees w.r.t the payload horizon
    of the interaction location as seen from the payload. Positive
    is above the payload horizontal, negative below.

    Parameters
    ----------
    events: pd.DataFrame
        apricot interactions stored in a DataFrame
    parameters: pd.DataFrame
        Apricot parameters stored in a pandas DataFrame
    inplace: bool
        If True, add elevation angles to DataFrame.


    Returns
    -------
    elevation_angle: np.ndarray
        Payload elevation angles [degrees].
    """

    # get the (N, 3) location of these events
    locations = get_locations(events)

    # and the (N, 3) direction of these events
    directions = get_directions(events)

    # construct the payload from the parameters
    payload = get_payload(parameters)

    # propagate to the surface
    surface = propagate_to_sphere(locations, directions, parameters.Re[0])

    # construct the normal vector at the surface
    normal = surface / np.linalg.norm(surface, axis=1).reshape((-1, 1))

    # compute the view vector of the payload from the surface
    surface_view = payload - surface

    # reflect this vector below the surface
    reflected = reflect_below(surface_view, normal)

    # compute the reflected location of the payload
    reflected_payload = surface + reflected

    # the vector from the interaction point to the payload
    view = reflected_payload - locations

    # normalize the view vector
    view /= np.linalg.norm(view, axis=1).reshape((-1, 1))

    # and compute the angle w.r.t to the shower axis
    offaxis = np.degrees(np.arccos(np.einsum("ij,ij->i", view, directions)))

    # if we have inplace, add it to the DataFrame
    if inplace:
        events["view"] = offaxis

    # otherwise, just return it
    return offaxis


def view_angle(
    events: pd.DataFrame, parameters: pd.DataFrame, inplace: bool = False
) -> Union[np.ndarray, pd.DataFrame]:
    """
    Calculate the view angle from shower max to the payload

    This returns the view angle (degrees) of the payload as seen
    from the interaction location looking along the shower axis.

    Parameters
    ----------
    events: pd.DataFrame
        Apricot interactions stored in a pandas DataFrame
    parameters: pd.DataFrame
        Apricot parameters stored in a pandas DataFrame
    inplace: bool
        If True, add the view angles to the DataFrame.

    Returns
    -------
    view_angle: np.ndarray
        Cosmic ray view angles [degrees].
    """

    # construct the payload from the parameters
    payload = get_payload(parameters)

    # get the vector from the interaction to the payload
    view = payload - get_locations(events)

    # normalize the view vector
    view /= np.linalg.norm(view, axis=1).reshape((-1, 1))

    # and compute the dot product between view and the shower axis
    dot = np.einsum("ij,ij->i", get_directions(events), view)

    # and convert this to an angle in degrees.
    angles = np.degrees(np.arccos(dot))

    # if we have inplace, add it to the DataFrame
    if inplace:
        events["view"] = angles

    # otherwise, just return the angle's
    return angles


def get_locations(events: pd.DataFrame) -> np.ndarray:
    """
    Get the (N, 3) location of each event.

    Parameters
    ----------
    events: pd.DataFrame
        Apricot events loaded in a DatFrame.

    Returns
    -------
    locations: np.ndarray
        A (N, 3) NumPy array containing event locations.
    """

    return np.vstack(
        [events["location.x"], events["location.y"], events["location.z"]]
    ).T


def get_directions(events: pd.DataFrame) -> np.ndarray:
    """
    Get the (N, 3) location of each event.

    Parameters
    ----------
    events: pd.DataFrame
        Apricot events loaded in a DatFrame.

    Returns
    -------
    directions: np.ndarray
        A (N, 3) NumPy array containing event directions.
    """

    return np.vstack(
        [events["direction.x"], events["direction.y"], events["direction.z"]]
    ).T


def get_payload(parameters: pd.DataFrame) -> np.ndarray:
    """
    Get the (N, 3) location the payload

    Parameters
    ----------
    parameters: pd.DataFrame
        Apricot simulation parameters loaded in a DatFrame.

    Returns
    -------
    payload: np.ndarray
        A (1, 3) NumPy array containing the paload location
    """

    return np.asarray([[0.0, 0.0, -(parameters.Re[0] + parameters.altitude[0])]])
