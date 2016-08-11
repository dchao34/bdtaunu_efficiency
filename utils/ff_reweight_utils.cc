#include <vector>
#include <stdexcept>

#include "ff_reweight_utils.h"

CLHEP::HepLorentzVector make_lorentz_vector(
  double energy, double p3mag, double costh, double phi) {

  double th = acos(costh);
  double x = p3mag*sin(th)*cos(phi); 
  double y = p3mag*sin(th)*sin(phi); 
  double z = p3mag*costh;
  return CLHEP::HepLorentzVector(energy, CLHEP::Hep3Vector(x, y, z));

}
