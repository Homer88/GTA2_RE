project(gbh LANGUAGES CXX)

add_library(gbh STATIC gbh.cpp)
target_compile_definitions(gbh PRIVATE _CRT_SECURE_NO_WARNINGS)
# Temp buildsrc verified: RE exe links D3DDLL.lib; static symbols give single GBH state.
# Guarded by env GTA2_TEXT_GBH_STATIC=1 at runtime.
target_compile_definitions(gbh PRIVATE GTA2_TEXT_GBH_LINK_STATIC)
