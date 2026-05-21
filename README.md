# Exact Diagonalization (t-J, RIXS)

Exact diagonalization code for the t-J model to compute RIXS cross sections using the UCL (ultrashort core-hole lifetime) expansion.

## Overview
This C++ code performs exact diagonalization of the t-J Hamiltonian on finite clusters and evaluates RIXS cross sections for different UCL orders. It targets dynamical correlation functions relevant for resonant inelastic x-ray scattering (RIXS).

## RIXS process (schematic)
```
	incident photon (ωi, qi)
				|
				v
	|g>  --(dipole exc.)-->  |n> (core-hole)
				|
				v
	|f>  <--(dipole de-exc)--  emitted photon (ωf, qf)

Energy loss: Ω = ωi - ωf
Momentum transfer: q = qi - qf
```

## RIXS cross section
The RIXS intensity is evaluated from the Kramers–Heisenberg expression and expanded in the UCL series. The code computes the cross section for selected momentum and energy loss, with the expansion truncated at user-specified order.

### UCL orders implemented
- **Zeroth order (UCL0):** local density/spin response only.
- **First order (UCL1):** includes nearest-neighbor hopping corrections.
- **Second order (UCL2):** includes two-step virtual processes.

## Model and Hamiltonian
The t-J Hamiltonian on a finite cluster:
```
H = -t Σ⟨ij⟩,σ ( c†_{iσ} c_{jσ} + h.c. ) + J Σ⟨ij⟩ ( S_i · S_j - 1/4 n_i n_j )
```
with no-double-occupancy constraint.

## Code details
- **Language:** C++
- **Diagonalization:** exact diagonalization of the many-body Hamiltonian.
- **Parallelization:** optional Intel MKL for parallel diagonalization.
- **Output:** RIXS spectra as functions of momentum transfer and energy loss for different UCL orders.

## Build notes
- Use a C++ compiler with BLAS/LAPACK support.
- For parallel diagonalization, link against Intel MKL.

## Usage (high level)
1. Define lattice size, t, J, and filling.
2. Select UCL order (0/1/2).
3. Run ED to obtain eigenstates.
4. Compute RIXS cross section and write spectra.

## Notes
- Finite-size effects are expected; compare trends across cluster sizes where possible.
- Energy broadening can be applied when plotting spectra.

# Third-party dependencies

This project vendors the following open-source libraries:

- HighFive (BSD-3-Clause)
  https://github.com/BlueBrain/HighFive.git

- Eigen (MPL 2.0)
  https://eigen.tuxfamily.org