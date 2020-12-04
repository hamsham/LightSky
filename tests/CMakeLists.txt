
# -------------------------------------
# Project Setup
# -------------------------------------
project(ls_tests CXX)



# -------------------------------------
# 3rd-party libraries
# -------------------------------------
include(SDL2Config.cmake)



# -------------------------------------
# Source Paths
# -------------------------------------
set(LS_TEST_SOURCES
    Context.h
    Context.cpp

    ControlState.h
    ControlState.cpp

    Display.h
    Display.cpp

    HelloPropertyState.h
    HelloPropertyState.cpp

    HelloMeshState.h
    HelloMeshState.cpp

    HelloPrimState.h
    HelloPrimState.cpp

    HelloTextState.h
    HelloTextState.cpp

    MainState.h
    MainState.cpp
)

set(LS_TEST_SOURCES_HELLOWORLD
    main.cpp
    ${LS_TEST_SOURCES}
    ${LS_TEST_HEADERS}
)



# -------------------------------------
# Misc Files
# -------------------------------------
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/testdata)

configure_file(testdata/testfont.ttf testdata/testfont.ttf COPYONLY)
configure_file(testdata/lorem_ipsum.txt testdata/lorem_ipsum.txt COPYONLY)

configure_file(testdata/altair/ACboots_n.tga  testdata/altair/ACboots_n.tga COPYONLY)
configure_file(testdata/altair/ACboots.tga    testdata/altair/ACboots.tga COPYONLY)
configure_file(testdata/altair/ACgloves_n.tga testdata/altair/ACgloves_n.tga COPYONLY)
configure_file(testdata/altair/ACgloves.tga   testdata/altair/ACgloves.tga COPYONLY)
configure_file(testdata/altair/AChood_n.tga   testdata/altair/AChood_n.tga COPYONLY)
configure_file(testdata/altair/AChood.tga     testdata/altair/AChood.tga COPYONLY)
configure_file(testdata/altair/ACRobePa_n.tga testdata/altair/ACRobePa_n.tga COPYONLY)
configure_file(testdata/altair/ACRobePa.tga   testdata/altair/ACRobePa.tga COPYONLY)
configure_file(testdata/altair/ACRobeSh_n.tga testdata/altair/ACRobeSh_n.tga COPYONLY)
configure_file(testdata/altair/ACRobeSh.tga   testdata/altair/ACRobeSh.tga COPYONLY)
configure_file(testdata/altair/ACshorts_n.tga testdata/altair/ACshorts_n.tga COPYONLY)
configure_file(testdata/altair/ACshorts.tga   testdata/altair/ACshorts.tga COPYONLY)
configure_file(testdata/altair/ACswords_n.tga testdata/altair/ACswords_n.tga COPYONLY)
configure_file(testdata/altair/ACswords.tga   testdata/altair/ACswords.tga COPYONLY)
configure_file(testdata/altair/altair.3ds     testdata/altair/altair.3ds COPYONLY)
configure_file(testdata/altair/mata.tga       testdata/altair/mata.tga COPYONLY)
configure_file(testdata/altair/rai_NRM.tga    testdata/altair/rai_NRM.tga COPYONLY)
configure_file(testdata/altair/rai.tga        testdata/altair/rai.tga COPYONLY)

configure_file(testdata/rover/MSL_dirty.blend      testdata/rover/MSL_dirty.blend COPYONLY)
configure_file(testdata/rover/MSL_Shadow2.png.meta testdata/rover/MSL_Shadow2.png.meta COPYONLY)
configure_file(testdata/rover/MSL_Shadow.png.meta  testdata/rover/MSL_Shadow.png.meta COPYONLY)
configure_file(testdata/rover/parts_AO.png         testdata/rover/parts_AO.png COPYONLY)
configure_file(testdata/rover/parts_AO.png.meta    testdata/rover/parts_AO.png.meta COPYONLY)
configure_file(testdata/rover/testmesh.dae         testdata/rover/testmesh.dae COPYONLY)
configure_file(testdata/rover/tex_01.png           testdata/rover/tex_01.png COPYONLY)
configure_file(testdata/rover/tex_01.png.meta      testdata/rover/tex_01.png.meta COPYONLY)
configure_file(testdata/rover/tex_02.png           testdata/rover/tex_02.png COPYONLY)
configure_file(testdata/rover/tex_02.png.meta      testdata/rover/tex_02.png.meta COPYONLY)
configure_file(testdata/rover/tex_03_n.png         testdata/rover/tex_03_n.png COPYONLY)
configure_file(testdata/rover/tex_03_n.png.meta    testdata/rover/tex_03_n.png.meta COPYONLY)
configure_file(testdata/rover/tex_03.png           testdata/rover/tex_03.png COPYONLY)
configure_file(testdata/rover/tex_03.png.meta      testdata/rover/tex_03.png.meta COPYONLY)
configure_file(testdata/rover/tex_03_s.png         testdata/rover/tex_03_s.png COPYONLY)
configure_file(testdata/rover/tex_03_s.png.meta    testdata/rover/tex_03_s.png.meta COPYONLY)
configure_file(testdata/rover/tex_04.png           testdata/rover/tex_04.png COPYONLY)
configure_file(testdata/rover/tex_04.png.meta      testdata/rover/tex_04.png.meta COPYONLY)
configure_file(testdata/rover/tex_05.png           testdata/rover/tex_05.png COPYONLY)
configure_file(testdata/rover/tex_05.png.meta      testdata/rover/tex_05.png.meta COPYONLY)

configure_file(testdata/sibenik/copyright.txt      testdata/sibenik/copyright.txt COPYONLY)
configure_file(testdata/sibenik/kamen-bump.png     testdata/sibenik/kamen-bump.png COPYONLY)
configure_file(testdata/sibenik/kamen.png          testdata/sibenik/kamen.png COPYONLY)
configure_file(testdata/sibenik/KAMEN-stup.png     testdata/sibenik/KAMEN-stup.png COPYONLY)
configure_file(testdata/sibenik/mramor6x6-bump.png testdata/sibenik/mramor6x6-bump.png COPYONLY)
configure_file(testdata/sibenik/mramor6x6.png      testdata/sibenik/mramor6x6.png COPYONLY)
configure_file(testdata/sibenik/sibenik.mtl        testdata/sibenik/sibenik.mtl COPYONLY)
configure_file(testdata/sibenik/sibenik.obj        testdata/sibenik/sibenik.obj COPYONLY)




# -------------------------------------
# Building and Linking Targets
# -------------------------------------
function(LS_TEST_ADD_TARGET trg srcs)
    add_executable(${trg} ${srcs})
    target_include_directories(${trg} PUBLIC .)
    target_link_libraries(${trg}
        LightSky::Game
        LightSky::Draw
        LightSky::Utils
        LightSky::Math
        LightSky::Setup
        ${SDL2_LIBRARIES}
    )
endfunction()

LS_TEST_ADD_TARGET(hello_ls_game "${LS_TEST_SOURCES_HELLOWORLD}")
