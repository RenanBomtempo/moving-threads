workspace "FSPD"
    architecture "x64"

    configurations 
    {
        "Release",
        "Debug"
    }
    

outputdir = "%{cfg.buildcfg}"

project "build"
    kind "ConsoleApp"
    language "C"

    staticruntime "on"
    targetname "ex1"
    targetdir ("bin/" .. outputdir)
    objdir ("bin-int/" .. outputdir)

    files
    {
        "src/**.h",
        "src/**.c"
    }

    defines 
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        optimize "on"
-- End Project Moxxi
