## Recommended environment

IDE: CLion

Tools / filesystem: WSL

## Preparing for the new contest

* Edit `SolverStubGenerator/SolverStubGenerator/in.txt` file.
* Run `python SolverStubGenerator.py` from `SolverStubGenerator/SolverStubGenerator` folder.
* Add `CMakeLists.txt` to the folder with your new `SolverXXXXA.cpp` files.
* Reference that file in the main `CMakeLists.txt` file.
* Build everything.
* Add a Run configuration in CLion (use solver1837 as an example). Things to double-check:
  * Working directory should be `alexey` folder. Otherwise, fuser won't be able to find inputs.
  * GTest filter flag should be set to something like `--gtest_filter=*1837C*`.
    Otherwise, fuser won't know what to fuse.
