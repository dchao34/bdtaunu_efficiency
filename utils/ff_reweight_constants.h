#ifndef __FF_REWEIGHT_CONSTANTS_H__
#define __FF_REWEIGHT_CONSTANTS_H__

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>

constexpr double twoPI = 6.2831853071795864769;
constexpr double PI = 3.1415926535897932384;
constexpr int Upsilon4SLund = 70553;
constexpr int B0Lund = 511;
constexpr int BpLund = 521;
constexpr int DstarpLund = 413;
constexpr int Dstar0Lund = 423;
constexpr int DpLund = 411;
constexpr int D0Lund = 421;
constexpr int KpLund = 321;
constexpr int K0Lund = 311;
constexpr int pi0Lund = 111;
constexpr int pipLund = 211;
constexpr int a1pLund = 20213;
constexpr int rhopLund = 213;
constexpr int eLund = 11;
constexpr int muLund = 13;
constexpr int tauLund = 15;
constexpr int nueLund = 12;
constexpr int numuLund = 14;
constexpr int nutauLund = 16;
constexpr int gammaLund = 22;

constexpr int D1pLund = 10413;
constexpr int D10Lund = 10423;
constexpr int D2pLund = 415;
constexpr int D20Lund = 425;
constexpr int D1primepLund = 20413;
constexpr int D1prime0Lund = 20423;
constexpr int D0sspLund = 10411;
constexpr int D0ss0Lund = 10421;

constexpr int DspLund = 431;
constexpr int DsstarpLund = 433;
constexpr int Ds1pLund = 10433;

constexpr double mBp = 5.2792;
constexpr double mB0 = 5.2795;
constexpr double mDp = 1.8696;
constexpr double mD0 = 1.8648;
constexpr double mDps = 2.01025;
constexpr double mD0s = 2.00696;

constexpr double mD0ss0 = 2.308;
constexpr double mD0ssp = 2.308;
constexpr double mD1prime0 = 2.461;
constexpr double mD1primep = 2.461;
constexpr double mD1p = 2.427;
constexpr double mD10 = 2.4222;
constexpr double mD2p = 2.459;
constexpr double mD20 = 2.4589;

constexpr double mTau = 1.7768;
constexpr double mMu  = 0.10566;
constexpr double mE   = 0.000511;
constexpr double Vcb  = 0.03912;
constexpr double V11  = 1.0816;
constexpr double GF   = 0.000011664;
constexpr double hbar = 6.582119e-25;
constexpr double mb_quark = 4.20;  // [GeV] in the MSbar scheme, evaluated at mb.
constexpr double mc_quark = 0.901; // From Xing, Zhang, Zhou (2008)

inline bool is_bmeson(int lund) {
  int abslund = abs(lund);
  return (abslund == B0Lund || abslund == BpLund) ? true : false; 
}

inline bool is_chargedB(int lund) { return abs(lund) == BpLund ? true : false ; }
inline bool is_neutralB(int lund) { return abs(lund) == B0Lund ? true : false ; }
inline bool is_chargedD(int lund) { return abs(lund) == DpLund ? true : false ; }
inline bool is_neutralD(int lund) { return abs(lund) == D0Lund ? true : false ; }
inline bool is_chargedDstar(int lund) { return abs(lund) == DstarpLund ? true : false ; }
inline bool is_neutralDstar(int lund) { return abs(lund) == Dstar0Lund ? true : false ; }

inline bool is_positive_lepton(int lund) { 
  return (lund == eLund || lund == muLund || lund == tauLund) ? true : false;
}

inline bool is_dstar(int lund) {
  int abslund = abs(lund);
  return (abslund == DstarpLund || abslund == Dstar0Lund) ? true : false; 
}

inline bool is_dmeson(int lund) {
  int abslund = abs(lund);
  return (abslund == DpLund || abslund == D0Lund) ? true : false; 
}

inline bool is_lepton(int lund) {
  int abslund = abs(lund);
  return (abslund == eLund || abslund == muLund || abslund == tauLund) ? true : false; 
}

inline bool is_neutrino(int lund) {
  int abslund = abs(lund);
  return (abslund == nueLund || abslund == numuLund || abslund == nutauLund) ? true : false; 
}

inline bool is_dstar_softdau(int lund) {
  int abslund = abs(lund);
  return (abslund == gammaLund || abslund == pipLund || abslund == pi0Lund) ? true : false; 
}

inline bool is_gamma(int lund) {
  return lund == gammaLund;
}

inline bool is_pion(int lund) {
  int abslund = abs(lund);
  return (abslund == pipLund || abslund == pi0Lund) ? true : false; 
}

inline bool is_e(int lund) { return abs(lund) == eLund; }
inline bool is_mu(int lund) { return abs(lund) == muLund; }
inline bool is_tau(int lund) { return abs(lund) == tauLund; }

inline bool is_D1(int lund) {
  int abslund = abs(lund);
  return (abslund == D1pLund || abslund == D10Lund) ? true : false;
}

inline bool is_D2(int lund) {
  int abslund = abs(lund);
  return (abslund == D2pLund || abslund == D20Lund) ? true : false;
}

inline bool is_D1prime(int lund) {
  int abslund = abs(lund);
  return (abslund == D1primepLund || abslund == D1prime0Lund) ? true : false;
}

inline bool is_Dss0(int lund) {
  int abslund = abs(lund);
  return (abslund == D0sspLund || abslund == D0ss0Lund) ? true : false;
}

inline bool is_dsstar(int lund) {
  return is_D1(lund) || is_D2(lund) || is_D1prime(lund) || is_Dss0(lund);
}

#endif
