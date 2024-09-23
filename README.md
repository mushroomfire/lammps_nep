# Lammps_nep
This package aims to provide a simple way to install [lammps](https://www.lammps.org/) python interface with [NEP](https://gpumd.org/potentials/nep.html) support. It is helpful for directly calling lammps in [mdapy](https://github.com/mushroomfire/mdapy), which can be used to do cell optimization and phonon dispersion calculation.

# Package version

- lammps version: 29 Aug 2024
- NEP_CPU version: v1.3

# Prerequirement

- Make sure you have a C++ compiler and python env. We test for MSVC in windows, gcc in Ubuntu and clang in Mac OS.
- Use virtual python env is better. For conda user, activate the env before the installation.
- In windows, install cmake and use git bash to run the script.

# Installation

- git clone https://github.com/mushroomfire/lammps_nep.git && cd lammps_nep
- bash build.sh

# Validation

- After installation, check it in python cmd by typing:

``` python
import lammps
lmp = lammps.lammps()
```

The output should be like below:

``` bash
LAMMPS (29 Aug 2024 - Development)
```

# Example

Now one can calculate the phonon dispersion entirely in python scripts.

- pip install mdapy -U
- conda install -c conda-forge phonopy

``` python
# import packages
import mdapy as mp
from mdapy.potential import LammpsPotential
mp.init()

# provide phonon path and labels, find in in seekpath website.
pair_parameter = """
pair_style nep
pair_coeff * * example/C_2024_NEP4.txt C
"""
elements_list = ['C']
path = '0.0 0.0 0.0 0.3333333333 0.3333333333 0.0 0.5 0.0 0.0 0.0 0.0 0.0'
labels = '$\Gamma$ K M $\Gamma$'
potential = LammpsPotential(pair_parameter)

# Load graphene file and do cell optimization
gra = mp.System('example/gra.xyz')
relax_gra = gra.cell_opt(pair_parameter, elements_list)

# compute and plot phonon dispersion
relax_gra.cal_phono_dispersion(path, labels, potential, elements_list)
fig, ax, _ = relax_gra.Phon.plot_dispersion()

# One can save the picture
fig.savefig('example/phono.png', bbox_inches='tight', dpi=300)
```

If everything runs okay, the output is:

<img src=./example/phono.png  width="500px" />

# Note

- Only compile serial version for lammps.
- For reducing package size, we have removed unnecessary folder in original lammps, only keep the src, lib, python and cmake folders.
- We have modified the install.py in lammps/python folder, make it compatible with python 3.8.
