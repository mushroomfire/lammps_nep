/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   https://www.lammps.org/, Sandia National Laboratories
   LAMMPS development team: developers@lammps.org

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#ifdef PAIR_CLASS
// clang-format off
PairStyle(aip/water/2dm/opt,PairAIPWATER2DMOpt);
// clang-format on
#else

#ifndef LMP_PAIR_AIP_WATER_2DM_OPT_H
#define LMP_PAIR_AIP_WATER_2DM_OPT_H

#include "pair_aip_water_2dm.h"
#include "pair_ilp_graphene_hbn_opt.h"

namespace LAMMPS_NS {

class PairAIPWATER2DMOpt : public PairAIPWATER2DM, public PairILPGrapheneHBNOpt {
 public:
  PairAIPWATER2DMOpt(class LAMMPS *);
  void coeff(int narg, char **args) override;

 protected:
};

}    // namespace LAMMPS_NS
#endif
#endif
