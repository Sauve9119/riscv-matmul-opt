# RISC-V Matrix Multiplication Optimization (LFX Mentorship Challenge)

This project implements optimized matrix multiplication for square matrices using:

- ✅ **Naive Approach**
- ✅ **Cache-Aware Tiling (Loop Blocking)**
- ✅ **Performance Benchmarking**
- ✅ **Bonus:** Vectorization using compiler flags (`-march=native`, `-O3`)

---

##  Compilation

### On Native Machine (e.g., x86_64 with GCC):
```bash
g++ -O2 -o matmul matmul.cpp                           # Basic optimization
g++ -O3 -march=native -ftree-vectorize -o matmul matmul.cpp   # With vectorization
