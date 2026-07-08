# C Build Notes

## What This Project Uses

- Root CMake entry: `CMakeLists.txt`
- Presets: `CMakePresets.json`
- Example targets: `examples/CMakeLists.txt` and `examples/algebra/CMakeLists.txt`
- Core C library target: `algebra_core`

## Target Structure

1. `algebra_core`
- Source: `src/c/algebra/vector.c`
- Public include root: `src/c/include`

2. `vector_example`
- Source: `examples/algebra/vector_example.c`
- Links to: `algebra_core`

3. `dot_product_example`
- Source: `examples/algebra/dot_product_example.c`
- Standalone example target

## Presets

- `debug`
- Generator: Unix Makefiles
- Build dir: `build/debug`
- Build type: Debug

- `release`
- Generator: Unix Makefiles
- Build dir: `build/release`
- Build type: Release

## Daily Commands

Run from repo root (`/home/matt/dev/machine-learning-c`):

1. Configure debug

```bash
cmake --preset debug
```

2. Build all

```bash
cmake --build --preset debug
```

3. Build one example target

```bash
cmake --build --preset debug --target vector_example
cmake --build --preset debug --target dot_product_example
```

4. Run binaries

```bash
./build/debug/examples/algebra/vector_example
./build/debug/examples/algebra/dot_product_example
```

## Build From Any Directory

```bash
cmake --build /home/matt/dev/machine-learning-c/build/debug --target vector_example
```

## VS Code Task Note

`/.vscode/tasks.json` builds the currently open C file with:

- `-g -O0 -Wall -Wextra`
- `-I${workspaceFolder}/src/c/include`

This is convenient for quick single-file builds. For project targets and linking, prefer CMake.

## Troubleshooting

1. `Could not read presets`
- You are not in repo root when running `--preset`.

2. `fatal error: algebra/vector.h: No such file or directory`
- Missing include path to `src/c/include`.

3. `undefined reference` linker errors
- The source/library providing symbols was not linked (use CMake target or include `src/c/algebra/vector.c` in manual compile).
