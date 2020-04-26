import os
import apricot
import numpy as np
import matplotlib.pyplot as plt


def test_create_spherical_earth():
    """
    Test the creation of Earth instances.
    """

    _ = apricot.SphericalEarth()
    _ = apricot.SphericalEarth(6367.755)


def test_spherical_cap_area():
    """
    Some basic tests of SphericalEarth::cap_area
    """

    # use a known value of Re
    Re = 6400

    # create a spherical earth model
    earth = apricot.SphericalEarth(Re)

    # create a center location
    center = np.asarray([0, 0, 0])

    # a spherical cap of theta=0 has zero area
    np.testing.assert_array_equal(earth.cap_area(center, 0.0), 0.0)

    # and a cap with theta=pi is a full-sphere
    np.testing.assert_allclose(earth.cap_area(center, np.pi), 4 * np.pi * Re * Re)

    # and a cap with theta=pi/2. is a half-sphere
    np.testing.assert_allclose(earth.cap_area(center, np.pi / 2.0), 2 * np.pi * Re * Re)


def test_spherical_earth_radii():
    """
    Test the creation of Earth instances.
    """

    # create a spherical Earth at the polar radius
    earth = apricot.SphericalEarth(6356.755)

    # test that I can evaluate at a single location
    earth.radius(np.asarray([0, 0, 0]))

    # and test that I can evaluate at a vector of locations
    locations = np.zeros((100, 3))
    radii = earth.radius(locations)

    # and check that they are the same
    for i in np.arange(locations.shape[0]):
        np.testing.assert_allclose(radii[i], earth.radius(locations[i, :]))


def test_spherical_earth_density():
    """
    Test and validate earth.density.
    """

    # the radii that we evaluate at
    locations = np.zeros((10_000, 3))

    # and fill in the radii
    locations[:, 2] = np.linspace(0.0, 6360.0, 10_000)

    # create the non-BEDMAP2 and BEDMAP2 Earth's
    earth = apricot.SphericalEarth()

    # and the corresponding densities
    density = earth.density(locations)

    # loop over the radii and check that they are the same
    for i in np.arange(locations.shape[0]):

        # and evaluate the density using each model
        np.testing.assert_allclose(density[i], earth.density(locations[i, :]))

    # we now have the density as a function of radius.

    # we create the plot
    fig, ax = plt.subplots()

    # and make the pelots
    ax.plot(np.linalg.norm(locations, axis=1), density, label="Spherical Earth")

    # and some labels
    ax.set_xlabel("Radius [km]")
    ax.set_ylabel(r"Density [g/cm$^3$]")

    # and save the plot
    fig.savefig(f"{os.path.dirname(__file__)}/figures/earth_density.pdf")
