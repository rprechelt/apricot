import apricot
import apricot.geometry
import numpy as np


def test_propagate_to_sphere_origin():
    """
    Generate a set of random vectors within the unit sphere centered
    at the origin and propagate them to a sphere of random radius
    between 1 and 100.

    We then verify that the rays are all at the surface, that the
    initial direction and normal point in the same direction (only
    valid for rays from the origin), and that the forward solution
    was chosen.
    """

    # the number of vectors to generate per trial
    N = 100

    # this test only uses vectors starting at the origin
    start = np.zeros((N, 3))

    # let's try 10 different trials
    for i in np.arange(20):

        # pick a set of random cartesian vectors
        directions = np.random.random((N, 3))

        # we have to normalize the directions
        directions /= np.linalg.norm(directions, axis=1).reshape((-1, 1))

        # pick a random radius for this trial
        radius = np.random.uniform(1.0, 100.0)

        # check that the original direction vector
        # and surface vector are colinear
        for j in np.arange(directions.shape[0]):

            # propagate the rays to the sphere
            surface = apricot.geometry.propagate_to_sphere(
                start[j, :], directions[j, :], radius
            )

            # check that all the radii are correct
            np.testing.assert_allclose(np.linalg.norm(surface), radius)

            # compute the normalized direction to the surface
            to_surface = surface / np.linalg.norm(surface)

            # and check that everything matches
            np.testing.assert_allclose(np.dot(to_surface, directions[j, :]), 1.0)

            # and check that the the new surface vectors have
            # the same sign as the initial directions - this
            # checks that we are picking the *forward* solution
            # along the raypath.
            np.testing.assert_allclose(np.sign(directions[j, :]), np.sign(surface))


def test_propagate_to_sphere():
    """
    Generate a set of random vectors within the unit sphere centered
    at a different random point within the unit sphere and propagate
    them to a sphere of random radius between 1 and 100.

    We then verify that the rays are all at the surface,
    and that the forward solution was chosen.
    """

    # the number of vectors to generate per trial
    N = 100

    # let's try 100 different trials
    for i in np.arange(10):

        # pick a set of random cartesian vectors
        start = np.random.random((N, 3))

        # pick a set of random cartesian vectors
        directions = np.random.random((N, 3))

        # we have to normalize the directions
        directions /= np.linalg.norm(directions, axis=1).reshape((-1, 1))

        # pick a random radius for this trial
        radius = np.random.uniform(1.0, 100.0)

        # loop over every vector
        for j in np.arange(N):

            # propagate the rays to the sphere
            surface = apricot.geometry.propagate_to_sphere(
                start[j, :], directions[j, :], radius
            )

            # check that all the radii are correct
            np.testing.assert_allclose(np.linalg.norm(surface), radius)

            # check that the line from the origin to the surface
            # is along the forward direction
            assert (np.dot(surface - start[j, :], directions[j, :]) > 0.0).all()


def test_propagate_to_sphere_from_outside():
    """
    Generate a set of random vectors *outside* the unit sphere centered
    at a different random point within the unit sphere and propagate
    them to a sphere of random radius between 1 and 100.

    We then verify that the rays are all at the surface,
    and that the forward solution was chosen.
    """

    # the number of radial vectors we try
    N = 200

    # generate N starting locations
    start = 100.0 * np.random.random((N, 3))

    # the directions are the inverses of the starting locations
    directions = -np.copy(start)

    # and make sure directions are normalized
    directions /= np.linalg.norm(directions, axis=1).reshape((-1, 1))

    # loop over every vector
    for j in np.arange(N):

        # propagate them to a surface at radius 1.
        surface = apricot.geometry.propagate_to_sphere(
            start[j, :], directions[j, :], 1.0
        )

        # and check that they are at the surface of the sphere
        # and in the right location.
        np.testing.assert_allclose(
            surface, start[j, :] / np.linalg.norm(start[j, :])
        )
