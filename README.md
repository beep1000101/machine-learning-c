# machine-learning-c

Hybrid C and Python workspace for numerical experiments.

## Layout

- src/c/: C implementation sources and public headers
- src/python/: Python package and wrappers
- examples/: C example executables
- tests/: test code (C and Python)
- scripts/: developer bootstrap and utility scripts

## Quick Start

1. Create Python environment:
   ./scripts/bootstrap.sh
2. Build C examples:
   cmake --preset debug
   cmake --build --preset debug

## Example Targets

- Example target definitions live in examples/CMakeLists.txt and examples/algebra/CMakeLists.txt.
- Build a specific example target:
  cmake --build --preset debug --target vector_example
  cmake --build --preset debug --target dot_product_example
