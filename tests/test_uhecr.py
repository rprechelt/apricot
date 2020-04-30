"""
Perform various checks on the UHECR hierarchy.
"""
import os.path as op
import apricot
import numpy as np
import matplotlib.pyplot as plt


def test_create_uhecr():
    """
    Check that I can create all the UHECR's
    """

    # check that I can create perotons
    for E in np.linspace(18.0, 21.0, 10):
        _ = apricot.Proton(E)
        _ = apricot.Helium(E)
        _ = apricot.Nitrogen(E)
        _ = apricot.Iron(E)
        _ = apricot.MixedUHECR(E)


def test_plot_shower_max():
    """
    Plot the grammage at shower max for the UHECR's.
    """

    # the energies we evaluate it at
    energies = np.linspace(18., 20., 100)

    # the directory containing our calibration data
    calib_dir = op.abspath(op.join(op.dirname(__file__), op.pardir, "data", "calibration", "Xmax"))

    # create the plot
    fig, ax = plt.subplots()

    # and plot the various grammages
    ax.plot(energies, apricot.Proton.get_Xmax(energies), label="Proton", c="r")
    ax.plot(energies, apricot.Helium.get_Xmax(energies), label="Helium", c="m")
    ax.plot(energies, apricot.Nitrogen.get_Xmax(energies), label="Nitrogen", c="orange")
    ax.plot(energies, apricot.Iron.get_Xmax(energies), label="Iron", c="blue")
    ax.plot(energies, apricot.MixedUHECR.get_Xmax(energies), label="TA (Measured)", c="k")

    # and plot it against the data that it was fit to
    data = np.loadtxt(f"{calib_dir}/telescope_array_xmax.dat")
    ax.scatter(data[:, 0], data[:, 1], marker="+", c="k")

    # some axis labels
    ax.set_xlabel(r"Energy [log10(eV)]")
    ax.set_ylabel(r"X$_{\mathrm{max}}$ [g cm$^{-2}$]")

    # and some limits
    ax.set_ylim([630, 830])

    # add a legend
    plt.legend()

    # and save the plot
    fig.savefig(f"{op.dirname(__file__)}/figures/uhecr_xmax.pdf")
