# Exact Diagonalization for t-J Model and RIXS Spectra

This repository provides a C++ implementation for the Exact Diagonalization (ED) of the t-J model on finite clusters. It is specifically designed to compute Resonant Inelastic X-ray Scattering (RIXS) cross-sections using the Ultrashort Core-hole Lifetime (UCL) expansion.

## Overview

The code performs many-body calculations for the t-J Hamiltonian and evaluates dynamical correlation functions. It supports different orders of the UCL expansion to approximate RIXS intensities, which are crucial for studying excitations in strongly correlated electronic systems.

### Key Features
- **Model:** t-J model with no-double-occupancy constraint.
- **Method:** Exact Diagonalization using Lanczos-like approaches or full diagonalization via Eigen/MKL.
- **RIXS:** UCL expansion up to second order (UCL0, UCL1, UCL2).
- **Parallelization:** Integrated with OpenMP and Intel MKL for high-performance linear algebra.
- **Data Format:** Outputs results in HDF5 and plain text for easy analysis.

---

## Mathematical Model

### The t-J Hamiltonian
The Hamiltonian implemented in this code is:
$$H = - \sum_{\langle ij \rangle, \sigma} t_{ij} (\tilde{c}^\dagger_{i\sigma} \tilde{c}_{j\sigma} + \text{h.c.}) + \sum_{\langle ij \rangle} J_{ij} \left( \mathbf{S}_i \cdot \mathbf{S}_j - \frac{1}{4} n_i n_j \right)$$
where $\tilde{c}_{i\sigma}$ are the Gutzwiller-projected electron operators (no double occupancy).

### RIXS Cross-Section
The RIXS intensity is calculated from the Kramers–Heisenberg formula and expanded in the UCL series:
- **UCL0 (Zeroth order):** Corresponds to the local density or spin response.
- **UCL1 (First order):** Includes corrections due to nearest-neighbor hopping during the core-hole lifetime.
- **UCL2 (Second order):** Accounts for two-step virtual processes.

---

## Code Structure

- `t-J/`: Core implementation of the t-J model.
    - `Hamiltonian/`: Contains `Hamiltonian.hpp` (diagonal terms) and `hopping.hpp` (off-diagonal terms).
    - `input/`: Handling of basis formation, input parameters, and output printing.
    - `Operator_NSC/`: Implementation of RIXS operators for different UCL orders.
- `Data/`: Scripts and headers for processing and consolidating the output data.
- `CMakeLists.txt`: Build configuration for the project.
- `U_O.cpp`: Main entry point for computing eigenspectra and RIXS operators.
- `D.cpp`: Utility for consolidating results.

---

## Tutorial: How to Use

### 1. Prerequisites
Ensure you have the following installed:
- C++20 compatible compiler (e.g., GCC 10+)
- [CMake](https://cmake.org/) (3.16+)
- [HDF5](https://www.hdfgroup.org/solutions/hdf5/) libraries
- [Intel oneAPI MKL](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl.html) (optional but recommended for performance)

### 2. Building the Code
We use CMake to manage the build process.

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

If you are using Intel MKL, ensure your environment is sourced:
```bash
source /opt/intel/oneapi/setvars.sh
```

### 3. Running a Calculation
You can run a basic calculation using the `run_desk.sh` script or by calling the binary directly.

**Example command:**
```bash
./build/s1 <index> <N> <nup> <ndown> <order>
```
- `<index>`: Identifier for the run.
- `<N>`: Total number of sites (cluster size).
- `<nup>`: Number of spin-up electrons.
- `<ndown>`: Number of spin-down electrons.
- `<order>`: UCL expansion order (0, 1, or 2).

### 4. Consolidating Data
After running the calculations for various momenta or parameters, use the `D` utility to gather results:
```bash
./build/D <N> <nup> <ndown> <t1> <t2> <J1> <J2> <mode>
```

---

## Applications and Results

This code can be used to reproduce results similar to those found in [arXiv:2505.23208](https://arxiv.org/abs/2505.23208), "Emergent Quasiparticles & Field-Tuned RIXS Spectra in a Trimerized Spin-1/2 Chain".

### Example Computation
The code can compute:
- **Static Structure Factors:** $\langle g | S^z_i S^z_j | g \rangle$
- **Dynamic RIXS Spectra:** Frequency-dependent intensity $I(\omega, q)$ for trimerized chains.

As shown in the referenced paper, RIXS can reveal:
- **Emergent gapless modes** governed by trimer periodicity.
- **Composite quasiparticles** arising from one- and two-trimer excitations.
- **Spectral signatures** of fractionalized spinons.

### Representative Figures
Below are some figures extracted from the paper [arXiv:2505.23208](https://arxiv.org/abs/2505.23208) demonstrating the capabilities of this code:

| Description | Figure |
|-------------|--------|
| **Lattice Structure and Magnetization:** Visualization of the trimerized chain and its magnetic properties. | ![Lattice](https://ar5iv.labs.arxiv.org/html/2505.23208/assets/Fig1_f.png) |
| **RIXS Spectra:** Computed RIXS intensity $I(\omega, q)$ showing various excitation branches. | ![RIXS Spectra](https://ar5iv.labs.arxiv.org/html/2505.23208/assets/P2.png) |
| **Trimer Excitations:** Detailed view of excitations within the trimerized unit cell. | ![Trimer](https://ar5iv.labs.arxiv.org/html/2505.23208/assets/P3c.png) |
| **Field-Tuned Spectra:** Evolution of the RIXS signal under an external magnetic field. | ![Field-Tuned](https://ar5iv.labs.arxiv.org/html/2505.23208/assets/P4c.png) |

---

## Citation

If you use this code in your research, please cite this software as follows:

```bibtex
@software{pal_ed_tJ_rixs,
  author = {Subhajyoti Pal and Pradeep Thakur and Ashis Kumar Nandy and Anamitra Mukherjee},
  title = {Exact Diagonalization for t-J Model and RIXS Spectra},
  url = {https://github.com/your-username/your-repo-name},
  version = {1.0.0},
  year = {2025}
}
```

Additionally, please cite the associated research paper:

```bibtex
@misc{pal2025emergent,
      title={Emergent Quasiparticles \& Field-Tuned RIXS Spectra in a Trimerized Spin-1/2 Chain},
      author={Subhajyoti Pal and Pradeep Thakur and Ashis Kumar Nandy and Anamitra Mukherjee},
      year={2025},
      eprint={2505.23208},
      archivePrefix={arXiv},
      primaryClass={cond-mat.str-el},
      url={https://arxiv.org/abs/2505.23208},
}
```

---

## Third-party dependencies
This project vendors the following open-source libraries:
- **HighFive** (BSD-3-Clause)
- **Eigen** (MPL 2.0)
