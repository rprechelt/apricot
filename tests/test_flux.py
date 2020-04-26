import apricot

def test_create_flux():
    """
    Check that we can create the various flux models.
    """

    _ = apricot.FixedProtonFlux(18.)

def test_FixedFlux():
    """
    Check the various FixedFlux implementations.
    """

    # check FixedProtonFlux - try a few times
    # to capture any randomness in the flux sampler.
    flux = apricot.FixedProtonFlux(18.5)
    assert flux.get_particle().energy == 18.5
    assert flux.get_particle().energy == 18.5
    assert flux.get_particle().energy == 18.5
    assert isinstance(flux.get_particle(), apricot.Proton)
    assert isinstance(flux.get_particle(), apricot.Proton)
    assert isinstance(flux.get_particle(), apricot.Proton)
