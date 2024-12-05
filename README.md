# Serpent

- A mod that lets you make simple GD mods using Python.
- Built using [pybind11](https://github.com/pybind/pybind11)!

- Please check [Serpent Documentation Site](https://yellowcat98.github.io/serpent-docs) for documentation.

# Credits
- Alphalaneous: Python button sprite

**Note!**
- In order to keep this mod's size manageable, Serpent uses `pybind11` which requires python 3.9.13 (the exact version) to be installed, you can install python at https://python.org.
- Serpent is in beta! please report any issues you encounter in the [Discord server](https://discord.gg/qnPgmUVZsV)

# Known Issues
- Missing DLL or dependency error:
- Make sure you have python 3.9.13 installed.
- If you do, make sure that it's in the PATH.
- (you can check by running `python --version` in the console)

# Compiling & Contributing
## Compiling:
- First, just go to https://docs.geode-sdk.org if you don't know how to setup geode.
- Then run `geode build`.
- Normally if you compile locally, you should be able to run serpent on GD fine.
- If you compiled through GitHub Actions and got a "Serpent couldn't load its binary" error, try checking the GitHub Runner python version, and try switching to that one on your local machine.
## Contributing:
- You can contribute by opening a pull request.