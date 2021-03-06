"""
Read and write interactions to and from ROOT files.
"""
from types import MethodType
from typing import Any, Dict, List, Tuple

import numpy as np
import uproot

import apricot
import pandas as pd


def to_file(
    filename: str,
    interactions: List[List[apricot.Interaction]],
    parameters: Dict[str, Any],
) -> None:
    """
    Write a collection of interaction tree lists to a ROOT file.

    This writes a flattened ROOT array where interactions from multiple
    events are joined together. In order to maintain the connection
    between each interaction, a sub-index is created for each event
    that starts at 0 for each event.

    Parameters
    ----------
    filename: str
        The filename to write the interactions to.
    interactions: List[List[Interaction]]
        A jagged list of apricot Interactions.
    parameters: Dict[str, Any]
        A dict of simulation parameters to write to the fle.

    Returns
    -------
    None

    Raises
    ------
    FileNotFoundError
        If the output file can not be found.
    """

    # remove any empty interactions
    interactions = [i for i in interactions if i]

    # get the total number of events
    N = sum([len(I) for I in interactions])

    # arrays to store general interaction properties
    subindex = np.zeros(N, dtype=np.int16)
    pdgid = np.zeros(N, dtype=np.int32)
    energy = np.zeros(N, dtype=np.float64)
    itype = np.zeros(N, dtype=np.int32)
    weight = np.zeros(N, dtype=np.float64)
    altitude = np.zeros(N, dtype=np.float64)

    # arrays to store the locations and directions
    location = np.zeros((N, 3), dtype=np.float64)
    direction = np.zeros((N, 3), dtype=np.float64)

    # the index that we are currently write to
    i = 0

    # we now fill in the arrays from the lists
    for j in range(len(interactions)):

        # loop over the interactions in this event
        for k, event in enumerate(interactions[i]):

            # fill in the arrays
            subindex[i] = k
            pdgid[i] = event.pdgid
            energy[i] = event.energy
            itype[i] = event.type
            location[i, :] = event.location
            direction[i, :] = event.direction
            weight[i] = event.weight
            altitude[i] = event.altitude

            # and increment our array index
            i += 1

    # open the output file and write the data
    with uproot.recreate(filename) as f:

        # create the branches
        branches = {
            "subindex": np.int16,
            "pdgid": np.int32,
            "energy": np.float64,
            "itype": np.int32,
            "location.x": np.float64,
            "location.y": np.float64,
            "location.z": np.float64,
            "direction.x": np.float64,
            "direction.y": np.float64,
            "direction.z": np.float64,
            "weight": np.float64,
            "altitude": np.float64,
        }

        # create the tree
        f["interactions"] = uproot.newtree(branches, title="interactions")

        # and write the data to the tree
        f["interactions"].extend(
            {
                "subindex": subindex,
                "pdgid": pdgid,
                "energy": energy,
                "itype": itype,
                "location.x": location[:, 0],
                "location.y": location[:, 1],
                "location.z": location[:, 2],
                "direction.x": direction[:, 0],
                "direction.y": direction[:, 1],
                "direction.z": direction[:, 2],
                "weight": weight,
                "altitude": altitude,
            }
        )

        # sanitize the parameters
        parameters = _sanitize_parameters(parameters)

        # create the branches for the parameter tree
        param_branches = {k: type(v[0]) for k, v in parameters.items()}

        # create the parmaeter tree
        f["parameters"] = uproot.newtree(param_branches, title="parameters")

        # and write the data to the three
        f["parameters"].extend(parameters)

    # and we are done


def from_file(filename: str, **kwargs) -> Tuple[pd.DataFrame, pd.DataFrame]:
    """
    Load a apricot ROOT file as a Pandas dataframe.

    This creates a Pandas dataframe with a multi-level index
    ('events' and 'interactions') to preserve the stack-like
    structure of the interaction file.

    Parameters
    ----------
    filename: str
        The filename of the ROOT file to load.
    **kwargs: Dict[Any]
        All other args are passed through to uproot.pandas.df

    Raises
    ------
    KeyError
       If the "interactions" tree cannot be found in the file.
    """

    # open the given file
    with uproot.open(filename) as f:

        # extract the given tree - this raises an exception
        # if the tree cannot be found
        tree = f["interactions"]

        # create the corresponding Pandas dataframe
        df = tree.pandas.df(**kwargs)

        # and create the multi-level index (inplace)
        df.set_index([df.index, "subindex"], inplace=True)

        # and set some better names
        df.index.names = ["event", "interaction"]

        # add a method to get the (N, 3) locations of this dataframe
        df.locations = MethodType(
            lambda self: np.vstack(
                (self["location.x"], self["location.y"], self["location.z"])
            ).T,
            df,
        )

        # add a method to get the (N, 3) directions of this dataframe
        df.directions = MethodType(
            lambda self: np.vstack(
                (self["direction.x"], self["direction.y"], self["direction.z"])
            ).T,
            df,
        )

        # also load the parameters
        parameters = f["parameters"].pandas.df()

        # and return the dataframe
        return df, parameters


def _sanitize_parameters(parameters: Dict[str, Any]) -> Dict[str, Any]:
    """
    Sanitize `parameters` so that we can write it to
    a ROOT file.

    Parameters
    ----------
    parameters: Dict[str, Any]
        The parameters to write to the file.

    Returns
    -------
    parameters: Dict[str, Any]
        The writeable parameters.
    """

    # fix the energy
    for energy in ["min_energy", "max_energy", "fixed_energy"]:

        # make the energy zero if it's not provided
        if parameters[energy] == None:
            parameters[energy] = 0.0

    # and convert every element to a list
    sanitized = {k: [v] for k, v in parameters.items()}

    # and return the sanitized energy
    return sanitized
