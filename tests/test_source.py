import apricot
import numpy as np


def test_create_source():
    """
    Test that we can create various sources.
    """

    # a spherical cap source with various options
    _ = apricot.SphericalCapSource()
    _ = apricot.SphericalCapSource(radius=7000.0)
    _ = apricot.SphericalCapSource(theta=np.pi, center=0.0)
    _ = apricot.SphericalCapSource(radius=5000, theta=np.pi, center=0.0)


def test_spherical_cap():
    """
    Perform some tests on the spherical cap source.
    """

    # the radius of the Earth we use
    radius = 6400

    # create a SphericalCapSource
    source = apricot.SphericalCapSource(radius=radius)

    # check that we can ask for a single origin and direction
    origin, direction = source.get_origin()

    # check for dimensions
    assert origin.shape == (3,)
    assert direction.shape == (3,)

    # check that the direction is unit-length
    np.testing.assert_allclose(np.linalg.norm(direction), 1)

    # by default a SphericalCapSource returns points on Antarctica
    # so let's check that.
    np.testing.assert_array_less(origin[2], -5900.0)

    # check that the radius is correct
    np.testing.assert_allclose(np.linalg.norm(origin), radius)


def test_spherical_cap_vectorized():
    """
    Perform some tests on the vectorized spherical cap source.
    """

    # the radius of the Earth we use
    radius = 6400

    # create a SphericalCapSource
    source = apricot.SphericalCapSource(radius=radius)

    # the number of events we sample
    N = 10

    # check that we can ask for a single origin and direction
    origins, directions = source.get_origins(N)

    # check for dimensions
    assert origins.shape == (N, 3)
    assert directions.shape == (N, 3)

    # check that the direction is unit-length
    np.testing.assert_allclose(np.linalg.norm(directions, axis=1.0), 1.0)

    # by default a SphericalCapSource returns points on Antarctica
    # so let's check that.
    np.testing.assert_array_less(origins[:, 2], -5900.0)

    # check that the radius is correct
    np.testing.assert_allclose(np.linalg.norm(origins, axis=1), radius)
