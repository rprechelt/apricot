import os
import apricot
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as mticker


def test_create_exponential_atmosphere():
    """
    Test that we can create an exponential atmosphere.
    """

    # defaults
    _ = apricot.ExponentialAtmosphere()

    # one override
    _ = apricot.ExponentialAtmosphere(1.233e-3)

    # two overrides
    _ = apricot.ExponentialAtmosphere(1.233e-3, 300)

    # and by keywords
    _ = apricot.ExponentialAtmosphere(rho0=1.233e-3, T=300)


def test_plot_exponential_atmosphere():
    """
    Create a test plot of the exponential atmosphere.
    """

    # the altitudes we sample at
    altitudes = np.linspace(0, 100, 2000)

    # create the atmosphere model
    atmosphere = apricot.ExponentialAtmosphere()

    # and sample the densities
    density = atmosphere.density(altitudes)

    # the density should always be less than 1 g/cm^3
    np.testing.assert_array_less(density, 1.0)

    # and there should be no negative densities.
    assert np.all(density >= 0.0)

    # create the figure
    fig, ax = plt.subplots()

    # create the pelot
    ax.plot(altitudes, density)

    # make it xlog
    ax.set_xscale("log")
    ax.set_yscale("log")

    # and some labels
    ax.set_xlabel(r"Altitude [km]")
    ax.set_ylabel(r"Density [g/cm$^3$]")

    # remove scientific notation on x-axis
    ax.xaxis.set_major_formatter(mticker.ScalarFormatter())

    # and save it
    fig.savefig(f"{os.path.dirname(__file__)}/figures/exponential_atmosphere.pdf")

def test_add_earth():
    """
    Test that I can add atmosphere models to Earth models.
    """

    # create an Earth model
    earth = apricot.SphericalEarth()

    # construct an atmosphere
    atmosphere = apricot.ExponentialAtmosphere()

    # and add an ExponentialAtmosphere
    earth.add(atmosphere)

    # get the radius of the current Earth model at the pole
    Re = earth.radius(np.asarray([0, 0, -1.0]))

    # the altitudes at which we evaluate our model [km]
    altitudes = np.linspace(0, 5., 100)

    # make sure that the density above the surface is non-zero
    radii = Re + altitudes

    # build the locations that we evaluate the density at
    locations = np.zeros((altitudes.shape[0], 3))
    locations[:, 2] = radii

    # get the density at each of these locations using the Earth
    earth_density = earth.density(locations)

    # get the density at each of these locations using the atmosphere
    atmosphere_density = atmosphere.density(altitudes)

    # check that they agree
    np.testing.assert_allclose(earth_density, atmosphere_density)
