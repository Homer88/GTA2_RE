cmake -S . -B build  -A Win32 "-DCMAKE_POLICY_VERSION_MINIMUM=3.5" 
cmake --build  ./build  --target GTA2
pause
