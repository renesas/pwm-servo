# Servo

This is software module to help users control RC Servo motors.

## Needed Tools
- C build tools (build-essential package on Debian/Ubuntu)
- Meson build framework

## How to run
```sh
# This sets up the bld directory. Only needs to be run once
meson setup bld -Dunity:extension_fixture=true
# Compile all of the code using the bld directory
meson compile -C bld
# Run the test executables through meson verbosely
meson test -C bld -v
```

The Makefile has these commands already, so you can do
```sh
make # Run when there's no build directory
make test # Build + run tests
make clean # Get everything back to what it was before
```

## Pre-commit

This repository uses [pre-commit](pre-commit.com) to perform checks and run [uncrustify](https://github.com/uncrustify/uncrustify) before every commit.

The pre-commit rules are configured to run these steps on all staged files:
- Ensure that staged files don't have trailing whitespace.
- Ensure that files end with a newline.
- Prevent large files from being committed to the repo.
- Run uncrustify on all staged files.

If any of the pre-commit lints fail, your staged files will be modified and you must stage them again.

To install pre-commit into this project, follow the steps below.

### Install pre-commit using a python project manager like uv (recommended)

```bash
uv sync
uv run pre-commit install
```

### Install pre-commit with pip + venv

```bash
# Create a virtual environment in the directory .venv
python -m venv .venv

# Install dev dependency inside venv
.venv/bin/pip install --group dev

# Activate venv, install pre-commit, deactivate venv
. .venv/bin/activate
pre-commit install
deactivate
```

## Pack Generation

The [pack-creator](http://pbgitap01.rea.renesas.com/jordan.stein.yh/pack-creator/-/tree/edit?ref_type=heads) project makes it easy to build FSP pack creators in a very flexible way.

After installing the package, run `pack-creator -f pack-creator.xml`. Your packfile will be placed in a directory with the same name as the version number specified in the XML file. If necessary, you can also pass in the -o argument to change the output directory.

Additionally, `make pack` will use the pack-creator tool to make a .pack file in the ./pack/out/ directory.

## Generating Documentation

It is possible to run `doxygen` to generate documentation. An HTML page can be found in ./doxy_out/html/index.html

## Directory Structure

- [src](./src/): Source code files
- [include](./include): Headers needed for everything to work
- [pack](./pack/): Code+files related to pack file generation
- [tests](./tests): Unit tests
- [tests/mocks](./tests/mocks): Mock FSP modules with associated tests
- [tests/runners](./tests/runners): Test runners for unit tests
- [documentation](./documentation): Needed for doxygen html generation
