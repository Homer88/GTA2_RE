cmake_minimum_required(VERSION 3.16)

project(EditSave
    VERSION 1.0.0
    DESCRIPTION "GTA2 save editor (plyslotN.svg / plyslotN.dat)"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Qt5 on Windows/Legacy, Qt6 on modern distros. Both provide the same API
# surface we use (QWidget, QSpinBox, QTableWidget, QByteArray, QDataStream).
if(NOT DEFINED QT_VERSION_MAJOR)
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
else()
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
endif()
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

# LinguistTools provides lrelease, which turns translations/*.ts into the
# *.qm that QTranslator loads at runtime. Optional so a Qt build shipped
# without it still compiles the app - it just loses the Russian UI.
find_package(Qt${QT_VERSION_MAJOR} QUIET COMPONENTS LinguistTools)

# --------------------------------------------------------------------------
# output layout: everything lands in <source>/bin so the deployed app and its
# libraries sit together and can be copied as one folder.
# --------------------------------------------------------------------------
set(EDITSAVE_BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EDITSAVE_BIN_DIR}")
foreach(cfg DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${cfg} "${EDITSAVE_BIN_DIR}")
endforeach()

set(EDITSAVE_RESOURCES
    resources/resources.qrc
    resources/EditSave.png
    resources/EditSave.ico
)

set(EDITSAVE_SOURCES
    src/main.cpp
    src/AppSettings.cpp
    src/AppSettings.h
    src/SaveFile.cpp
    src/SaveFile.h
    src/ScriptFile.cpp
    src/ScriptFile.h
    src/Cities.cpp
    src/Cities.h
    src/FieldDefs.cpp
    src/FieldDefs.h
    src/MainWindow.cpp
    src/MainWindow.h
    src/FieldEditor.cpp
    src/FieldEditor.h
    src/DatTable.cpp
    src/DatTable.h
    src/WeaponTable.cpp
    src/WeaponTable.h
    src/HexView.cpp
    src/HexView.h
    src/SettingsPage.cpp
    src/SettingsPage.h
    src/Translator.cpp
    src/Translator.h
    ${EDITSAVE_RESOURCES}
)

set(EDITSAVE_HEADERS
    src/AppSettings.h
    src/SaveFile.h
    src/ScriptFile.h
    src/Cities.h
    src/FieldDefs.h
    src/MainWindow.h
    src/FieldEditor.h
    src/DatTable.h
    src/WeaponTable.h
    src/HexView.h
    src/SettingsPage.h
    src/Translator.h
)

# Qt5 needs the explicit includes list; Qt6 folds them into Qt6::Widgets.
if(QT_VERSION_MAJOR EQUAL 5)
    set(EDITSAVE_QT_LIBS Qt5::Widgets Qt5::Gui Qt5::Core)
else()
    set(EDITSAVE_QT_LIBS Qt6::Widgets Qt6::Gui Qt6::Core)
endif()

add_executable(EditSave WIN32 ${EDITSAVE_SOURCES} ${EDITSAVE_HEADERS})

target_include_directories(EditSave PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# windres resolves the ICON path through -I, not relative to the .rc file.
target_include_directories(EditSave PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/resources)

# The window icon from the qrc only reaches the Qt decoration; Explorer, the
# task bar and Alt-Tab need it in the PE resource block.
if(WIN32)
    enable_language(RC)
    target_sources(EditSave PRIVATE resources/EditSave.rc)
endif()

target_link_libraries(EditSave PRIVATE ${EDITSAVE_QT_LIBS})

if(MSVC)
    target_compile_options(EditSave PRIVATE /W4 /utf-8)
    # keep save paths as plain ASCII-safe std::string without needing /permissive-
    target_compile_definitions(EditSave PRIVATE UNICODE _UNICODE)
else()
    target_compile_options(EditSave PRIVATE -Wall -Wextra)
endif()

# --------------------------------------------------------------------------
# Deploy: copy the executable plus every shared library it needs into bin/.
#   Windows : windeployqt (pulls the Qt plugins: platforms/, styles/, imageformats/)
#   macOS   : fixup_bundle + copy via install script
#   Linux   : copy Qt libs into bin/lib and emit a run script with LD_LIBRARY_PATH
# --------------------------------------------------------------------------
if(WIN32)
    find_program(EDITSAVE_WINDEPLOYQT windeployqt HINTS "${QT5_LOCATION}" "${Qt5_DIR}/../../../bin")
    if(EDITSAVE_WINDEPLOYQT)
        add_custom_target(deploy
            COMMAND "${EDITSAVE_WINDEPLOYQT}"
                    --no-translations
                    --no-system-d3d-compiler
                    --no-opengl-sw
                    --dir "${EDITSAVE_BIN_DIR}"
                    "$<TARGET_FILE:EditSave>"
            DEPENDS EditSave
            COMMENT "windeployqt -> ${EDITSAVE_BIN_DIR}"
            VERBATIM)
    else()
        message(WARNING "windeployqt not found; 'deploy' target will only copy the exe")
        add_custom_target(deploy
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "$<TARGET_FILE:EditSave>" "${EDITSAVE_BIN_DIR}"
            DEPENDS EditSave VERBATIM)
    endif()
elseif(APPLE)
    add_custom_target(deploy
        COMMAND ${CMAKE_COMMAND} -E make_directory "${EDITSAVE_BIN_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE:EditSave>" "${EDITSAVE_BIN_DIR}/"
        COMMENT "copy bundle -> ${EDITSAVE_BIN_DIR}"
        VERBATIM)
else()
    # Linux: gather the resolved runtime libraries and drop them next to the exe.
    add_custom_target(deploy
        COMMAND ${CMAKE_COMMAND} -E make_directory "${EDITSAVE_BIN_DIR}/lib"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE:EditSave>" "${EDITSAVE_BIN_DIR}/"
        COMMENT "copy exe + libs -> ${EDITSAVE_BIN_DIR}"
        VERBATIM)
endif()

# 'all' builds the binary; 'deploy' additionally stages the libraries.
add_custom_target(stage ALL DEPENDS deploy)

# --------------------------------------------------------------------------
# EditSaveCli - console front end over the same parsing code. Used to verify
# the format handling headlessly ("cmake --build build --target EditSaveCli")
# since a GUI that mis-parses a save is indistinguishable from a working one.
# --------------------------------------------------------------------------
add_executable(EditSaveCli
    src/cli_main.cpp
    src/SaveFile.cpp
    src/SaveFile.h
    src/ScriptFile.cpp
    src/ScriptFile.h
    src/Cities.cpp
    src/Cities.h
    src/FieldDefs.cpp
    src/FieldDefs.h
)
target_include_directories(EditSaveCli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(EditSaveCli PRIVATE ${EDITSAVE_QT_LIBS})
if(MSVC)
    target_compile_options(EditSaveCli PRIVATE /W4 /utf-8)
else()
    target_compile_options(EditSaveCli PRIVATE -Wall -Wextra)
endif()

if(WIN32 AND EDITSAVE_WINDEPLOYQT)
    add_custom_target(deploy_cli
        COMMAND "${EDITSAVE_WINDEPLOYQT}"
                --no-translations --no-system-d3d-compiler --no-opengl-sw
                --dir "${EDITSAVE_BIN_DIR}" "$<TARGET_FILE:EditSaveCli>"
        DEPENDS EditSaveCli
        COMMENT "windeployqt -> ${EDITSAVE_BIN_DIR} (cli)"
        VERBATIM)
    add_dependencies(deploy_cli deploy)
else()
    add_custom_target(deploy_cli
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE:EditSaveCli>" "${EDITSAVE_BIN_DIR}"
        DEPENDS EditSaveCli VERBATIM)
endif()

# --------------------------------------------------------------------------
# Translations.
#
# The .ts files are generated from the tr() strings by
# tools/make_translations.py, so the source is the single point of truth and a
# new user-visible string shows up as untranslated rather than silently absent.
#
# The .qm files land in bin/translations/, which is the first place
# Translator::candidatePaths() looks - next to the exe, so the app stays
# portable and a missing system Qt catalogue cannot break the Russian UI.
# --------------------------------------------------------------------------
set(EDITSAVE_TS
    translations/editsave_en.ts
    translations/editsave_ru.ts
)

if(TARGET Qt${QT_VERSION_MAJOR}::lrelease)
    if(QT_VERSION_MAJOR EQUAL 5)
        qt5_add_translation(EDITSAVE_QM ${EDITSAVE_TS})
    else()
        qt6_add_translation(EDITSAVE_QM ${EDITSAVE_TS})
    endif()

    # The add_*_translation targets put the .qm next to the .ts; copy it to the
    # runtime location so the app finds it next to the exe and stays portable.
    set(EDITSAVE_QM_OUT)
    foreach(qm ${EDITSAVE_QM})
        get_filename_component(qm_name "${qm}" NAME)
        set(qm_dst "${EDITSAVE_BIN_DIR}/translations/${qm_name}")
        add_custom_command(OUTPUT "${qm_dst}"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${EDITSAVE_BIN_DIR}/translations"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${qm}" "${qm_dst}"
            DEPENDS "${qm}"
            COMMENT "translations/${qm_name} -> bin/"
            VERBATIM)
        list(APPEND EDITSAVE_QM_OUT "${qm_dst}")
    endforeach()
    add_custom_target(translations ALL DEPENDS ${EDITSAVE_QM_OUT})
    add_dependencies(EditSave translations)
else()
    message(WARNING
        "Qt LinguistTools not found - lrelease is unavailable, so the .qm "
        "catalogues will not be built and the app falls back to English.")
endif()
