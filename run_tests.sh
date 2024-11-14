mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCUBEENGINE_BUILD_TESTS=true ..
cmake --build . -j$(nproc)
cd ..
build/tests/CubeEngineTest