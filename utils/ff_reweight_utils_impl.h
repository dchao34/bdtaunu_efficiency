#include "ff_reweight_utils.h"

template <typename T>
std::vector<CLHEP::HepLorentzVector> make_lorentz_vector(
    const std::vector<T> &energy, const std::vector<T> &p3mag, 
    const std::vector<T> &costh, const std::vector<T> &phi) {

  size_t n = energy.size();
  if (p3mag.size() != n || 
      costh.size() != n || 
      phi.size() != n) {
    throw std::invalid_argument(
        "make_lorentz_vector(std::vector<>, ...): "
        "vector arguments must have the same sizes. ");
  }

  std::vector<CLHEP::HepLorentzVector> lorentz_vectors; 
  lorentz_vectors.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    lorentz_vectors.push_back(
        make_lorentz_vector(energy[i], p3mag[i], costh[i], phi[i])
    );
  }
  return lorentz_vectors;
}

