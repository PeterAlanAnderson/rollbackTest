workspace "RollbackTest"
    language "C++"
    cppdialect "C++17"
    configurations {"Debug", "Release"}
    platforms {"LinuxARM", "LinuxX86", "LinuxX64", "WindowsARM", "WindowsX86", "WindowsX64"}
    startproject "RollbackTest"

    flags {"MultiProcessorCompile"}
    buildoptions {"-pipe", "-Wall"}
    defines {}

    links {"glfw3"}
    includedirs {"%{wks.location}/include/", "C:/SDK/websocketpp/"}

    filter "action:vs*"
        toolset "msc"
        includedirs {"C:/local/boost_1_75_0/", "C:/SDK/GLFW/include/"}
        libdirs {"C:/local/boost_1_75_0/stage/lib/", "C:/SDK/GLFW/lib-vc2019/"}

    filter "action:not vs*"
        toolset "gcc"
        buildoptions {"-Wextra", "-Wnon-virtual-dtor", "-Winline", "-Wunreachable-code", "-Wshadow", "-Wconversion", "-Wno-switch", "-Wno-unused-variable"}

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
        buildoptions {"-pg", "-fsanitize=address", "-fsanitize=leak", "-static-libasan"}
        linkoptions {"-pg", "-fsanitize=address", "-fsanitize=leak", "-static-libasan"}

    filter "configurations:Release"
        optimize "On"

    project "RollbackTest"
        kind "ConsoleApp"
        location "%{wks.location}"
        targetdir "%{prj.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"

        filter "action:not vs*"
		    pchheader "RollbackTestpch.hpp"
        filter {}

        files {"%{prj.location}/src/**.cpp", "%{prj.location}/src/**.c", "%{prj.location}/include/**.hpp", "%{prj.location}/include/**.h", "%{prj.location}/premake5.lua"}


