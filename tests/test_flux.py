import apricot
import numpy as np


def test_create_flux():
    """
    Check that we can create the various flux models.
    """

    _ = apricot.FixedProtonFlux(18.0)


def test_FixedFlux():
    """
    Check the various FixedFlux implementations.
    """

    # the various fixed fluxes that we test
    ftypes = [apricot.FixedProtonFlux, apricot.FixedNitrogenFlux,
             apricot.FixedHeliumFlux, apricot.FixedIronFlux]

    # the associated particle types
    particles = [apricot.Proton, apricot.Nitrogen,
                 apricot.Helium, apricot.Iron]

    # check FixedProtonFlux - try a few times
    # to capture any randomness in the flux sampler.
    for fluxtype, particle in zip(ftypes, particles):

        # create the flux
        flux = fluxtype(18.5)

        # check that the energy is right
        np.testing.assert_allclose(flux.get_particle().energy, 18.5)
        np.testing.assert_allclose(flux.get_particle().energy, 18.5)
        np.testing.assert_allclose(flux.get_particle().energy, 18.5)
        assert isinstance(flux.get_particle(), particle)
        assert isinstance(flux.get_particle(), particle)
        assert isinstance(flux.get_particle(), particle)


def test_UniformFlux():
    """
    Check the various UniformFlux implementations.
    """

    # the various fixed fluxes that we test
    ftypes = [apricot.UniformProtonFlux, apricot.UniformNitrogenFlux,
             apricot.UniformHeliumFlux, apricot.UniformIronFlux]

    # the associated particle types
    particles = [apricot.Proton, apricot.Nitrogen,
                 apricot.Helium, apricot.Iron]

    # check UniformProtonFlux - try a few times
    # to capture any randomness in the flux sampler.
    for fluxtype, particle in zip(ftypes, particles):

        # create the flux
        flux = fluxtype(18.2, 19.9)

        # try 30 times
        for _ in np.arange(30):

            # check that the energy is right
            np.testing.assert_array_less(flux.get_particle().energy, 19.9)
            np.testing.assert_array_less(18.2, flux.get_particle().energy)

            # and check that we always get the same particle
            assert isinstance(flux.get_particle(), particle)
            assert isinstance(flux.get_particle(), particle)
