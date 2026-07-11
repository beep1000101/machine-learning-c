# C Build Notes

## What This Project Uses

- Root CMake entry: `CMakeLists.txt`
- Presets: `CMakePresets.json`
- Example targets: `examples/CMakeLists.txt` and `examples/algebra/CMakeLists.txt`
- Core C library target: `algebra_core`
- VS Code debug launcher: `.vscode/launch.json` using CMake Tools launch target path
- VS Code build tasks: `.vscode/tasks.json` using CMake preset configure/build pipeline

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

`/.vscode/tasks.json` runs a CMake-first pipeline:

- `CMake configure (debug)` -> `cmake --preset debug`
- `CMake build (debug)` -> `cmake --build --preset debug`
- `CMake configure + build (debug)` chains both tasks

`/.vscode/launch.json` uses one launch config:

- `program`: `${command:cmake.launchTargetPath}`
- `cwd`: `${command:cmake.launchTargetDirectory}`
- `preLaunchTask`: `CMake configure + build (debug)`

This gives a single F5 workflow: configure, build, link dependencies, then debug selected launch target.

`/.vscode/settings.json` controls default launch target behavior:

- `cmake.defaultLaunchTarget` can pin F5 to one executable (for example `dot_product_example`).
- If omitted, F5 uses the currently selected CMake launch/debug target.

## Adding New Examples

Will it discover other examples automatically?

- Partly.
- CMake and CMake Tools only discover executables that are declared as CMake targets.

Required steps for a new example:

1. Add the new source file (for example `examples/algebra/new_example.c`).
2. Register it in `examples/algebra/CMakeLists.txt` with `add_executable(new_example new_example.c)`.
3. Link dependencies if needed, for example `target_link_libraries(new_example PRIVATE algebra_core)`.
4. Reconfigure/build (`cmake --preset debug`, `cmake --build --preset debug`) or press F5.

After that, CMake Tools can launch/debug the new target.

## Discovery Model (Why It Works)

Target discovery is based on the CMakeLists hierarchy, not on scanning files:

1. `CMakeLists.txt` includes `examples/` via `add_subdirectory(examples)`.
2. `examples/CMakeLists.txt` includes `examples/algebra/` via `add_subdirectory(algebra)`.
3. `examples/algebra/CMakeLists.txt` declares launchable executables with `add_executable(...)`.

Only targets declared this way are visible to CMake Tools as launch/debug targets.

## Troubleshooting

1. `Could not read presets`
- You are not in repo root when running `--preset`.

2. `fatal error: algebra/vector.h: No such file or directory`
- Missing include path to `src/c/include`.

3. `undefined reference` linker errors
- The source/library providing symbols was not linked (use CMake target or include `src/c/algebra/vector.c` in manual compile).

4. F5 always launches the same executable
- Check `cmake.defaultLaunchTarget` in `/.vscode/settings.json`.
- Remove it if you want F5 to follow your currently selected CMake launch target.
