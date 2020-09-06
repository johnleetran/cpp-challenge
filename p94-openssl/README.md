```
mkdir -p build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=/Users/john/Documents/code/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake -DOPENSSL_ROOT_DIR=/usr/local/bin -DOPENSSL_INCLUDE_DIR=/usr/local/include ..
```
ubuntu
```
cmake -DOPENSSL_ROOT_DIR=/usr/bin -DOPENSSL_INCLUDE_DIR=/usr/lib/ssl ..
```

sign
```
./main --sign --private-key /Users/john/Documents/code/cpp/cpp-challenge/p94/private.key --data /Users/john/Documents/code/cpp/cpp-challenge/p94/main.cpp 
```
verify
```
./main --verify --public-key /Users/john/Documents/code/cpp/cpp-challenge/p94/public.crt --data /Users/john/Documents/code/cpp/cpp-challenge/p94/main.cpp --signature signature.txt
```

source - https://eclipsesource.com/blogs/2016/09/07/tutorial-code-signing-and-verification-with-openssl/