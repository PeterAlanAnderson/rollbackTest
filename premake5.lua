workspace "RollbackTest"
    language "C++"
    cppdialect "C++17"
    configurations {"Debug", "Release"}
    platforms {"LinuxX64", "LinuxX86", "LinuxARM", "WindowsARM", "WindowsX86", "WindowsX64"}
    startproject "RollbackTest"

    flags {"MultiProcessorCompile"}
    buildoptions {"-pipe", "-Wall"}
    defines {}

    links {"glfw3"}
    includedirs {"%{wks.location}/include/", "C:/SDK/websocketpp/"}

    filter "action:vs*"
        buildoptions {"/W4"}
        toolset "msc"
        includedirs {"C:/local/boost_1_75_0/", "C:/SDK/GLFW/include/"}
        libdirs {"C:/local/boost_1_75_0/lib64-msvc-14.2", "C:/SDK/GLFW/lib-vc2019/"}

    filter "action:not vs*"
        toolset "gcc"

    filter {"action:not vs*", "files:not glad.c"}
        buildoptions {"-Wpedantic", "-Wextra", "-Wnon-virtual-dtor", "-Winline", "-Wunreachable-code", "-Wshadow", "-Wconversion", "-Wno-switch", "-Wno-unused-variable", "-Wold-style-cast",
        	      "-Wcast-align", "-Wunused", "-Woverloaded-virtual", "-Wsign-conversion", "-Wduplicated-cond", "-Wduplicated-branches", "-Wlogical-op", "-Wnull-dereference", "-Wuseless-cast",
        	      "-Wdouble-promotion"}

    filter "platforms:Linux*"
        system "linux"
    filter "platforms:Windows*"
        system "windows"

    filter "platforms:*ARM"
        architecture "ARM"
    filter "platforms:*X86"
        architecture "x86"
    filter "platforms:*X64"
        architecture "x86_64"

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    project "RollbackTest"
        kind "ConsoleApp"
        location "%{wks.location}"
        targetdir "%{prj.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"

        files {"%{prj.location}/src/**.cpp", "%{prj.location}/src/**.c", "%{prj.location}/include/**.hpp", "%{prj.location}/include/**.h", "%{prj.location}/premake5.lua"}


