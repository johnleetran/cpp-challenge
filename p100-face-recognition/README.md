Build
```
#!/bin/bash

mkdir -p build
cd build 
cmake -DCMAKE_TOOLCHAIN_FILE=/Users/john/Documents/code/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake ..
make
```