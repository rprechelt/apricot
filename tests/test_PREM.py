import os
import apricot
import numpy as np
import matplotlib.pyplot as plt


def test_prem_density():
    """
    Test and validate earth.density.
    """

    # the radii that we evaluate at
    radii = np.linspace(0.0, 6360.0, 10_000)

    # and evaluate the density using PREM
    density = apricot.PREM.density(radii)

    # we create the plot
    fig, ax = plt.subplots()

    # and make the pelots
    ax.plot(radii, density, label="PREM")

    # and some labels
    ax.set_xlabel("Radius [km]")
    ax.set_ylabel(r"Density [g/cm$^3$]")

    # and save the plot
    fig.savefig(f"{os.path.dirname(__file__)}/figures/prem_density.pdf")
