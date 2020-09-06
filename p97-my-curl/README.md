```
gunzip -c curl-7.72.0.tar.gz | tar xvz
mv curl-7.72.0 curl
mkdir -p build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=/Users/john/Documents/code/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake  -DOPENSSL_ROOT_DIR=/usr/local/bin -DOPENSSL_INCLUDE_DIR=/usr/local/include -DBUILD_CURL_EXE=OFF ..
```