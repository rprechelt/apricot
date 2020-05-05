"""
Provide various geometry related functions for apricot data.
"""
from typing import Union

import numpy as np
import pandas as pd

import _apricot
from _apricot.geometry import *


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
    radius = np.linalg.norm(events.locations(), axis=1)

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
    events: pd.DataFrame, payload: np.ndarray, inplace: bool = False
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
    payload: np.ndarray
        A (1, 3) array containing the location of the payload.
    inplace: bool
        If True, add elevation angles to DataFrame.

    Returns
    -------
    elevation_angle: np.ndarray
        Payload elevation angles [degrees].
    """

    # get the vector from the payload to the interaction
    view = events.locations() - payload

    # normalize the view vector
    view /= np.linalg.norm(view, axis=1).reshape((-1, 1))

    # and compute the dot product between view and payload
    dot = np.einsum("ij,ij->i", payload / np.linalg.norm(payload, axis=1), view)

    # and convert this into an angle in degrees and map
    # so that the horizon is at 0 degrees
    angle = np.degrees(np.pi / 2.0 - np.arccos(dot))

    # we now calculate the off-axis view angles
    # for each of these events
    offaxis = view_angle(events, payload)

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


def view_angle(
    events: pd.DataFrame, payload: np.ndarray, inplace: bool = False
) -> Union[np.ndarray, pd.DataFrame]:
    """
    Calculate the view angle from shower max to the payload

    This returns the view angle (degrees) of the payload as seen
    from the interaction location looking along the shower axis.

    Parameters
    ----------
    events: pd.DataFrame
        apricot interactions stored in a pandas DataFrame
    payload: np.ndarray
        A (1, 3) array containing the location of the payload.
    inplace: bool
        If True, add the view angles to the DataFrame.

    Returns
    -------
    view_angle: np.ndarray
        Cosmic ray view angles [degrees].
    """

    # get the vector from the interaction to the payload
    view = payload - events.locations()

    # normalize the view vector
    view /= np.linalg.norm(view, axis=1).reshape((-1, 1))

    # and compute the dot product between view and the shower axis
    dot = np.einsum("ij,ij->i", events.directions(), view)

    # and convert this to an angle in degrees.
    angles = np.degrees(np.arccos(dot))

    # if we have inplace, add it to the DataFrame
    if inplace:
        events["view"] = angles

    # otherwise, just return the angle's
    return angles
