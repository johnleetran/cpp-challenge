* Book: https://learning.oreilly.com/library/view/the-modern-c/9781788993869/
* Video: https://learning.oreilly.com/videos/the-modern-c/9781838642877
* Solution: https://github.com/PacktPublishing/The-Modern-Cpp-Challenge

## example cmake with vcpkg
```
# to get the -D to pass into cmake

cd /Users/john/Documents/code/cpp/vcpkg
./vcpkg install <some_lib>
./vcpkg integrate install

# genearte build system with vcpkg 
cmake -DCMAKE_TOOLCHAIN_FILE=/Users/john/Documents/code/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake ..
make
```