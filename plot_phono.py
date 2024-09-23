# import packages
import mdapy as mp
from mdapy.potential import LammpsPotential

mp.init()

# provide phonon path and labels, find in in seekpath website.
pair_parameter = """
pair_style nep
pair_coeff * * example/C_2024_NEP4.txt C
"""
elements_list = ["C"]
path = "0.0 0.0 0.0 0.3333333333 0.3333333333 0.0 0.5 0.0 0.0 0.0 0.0 0.0"
labels = "$\Gamma$ K M $\Gamma$"
potential = LammpsPotential(pair_parameter)

# Load graphene file and do cell optimization
gra = mp.System("example/gra.xyz")
relax_gra = gra.cell_opt(pair_parameter, elements_list)

# compute and plot phonon dispersion
relax_gra.cal_phono_dispersion(path, labels, potential, elements_list)
fig, ax, _ = relax_gra.Phon.plot_dispersion()

# One can save the picture
# fig.savefig('example/phono.png', bbox_inches='tight', dpi=300)
