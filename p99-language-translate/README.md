```
git submodule update --init --recursive
mkdir -p build
cd build
cmake -DBUILD_ONLY="core;translate" -DCMAKE_TOOLCHAIN_FILE=/Users/john/Documents/code/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake ..
make -j
```
