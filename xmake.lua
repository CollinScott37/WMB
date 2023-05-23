add_rules("mode.debug", "mode.release")
--add_requires("glm")
set_policy("build.warning", true) -- show warnings
set_warnings("all") -- warn about many things

target("WMB")
    set_kind("static")
    set_languages("cxx17")
    -- Copy assets
    after_build(function (target)
        cprint("Copying assets")
        os.cp("$(projectdir)/assets", path.directory(target:targetfile()))
    end)
    --add_packages("glm") 
    -- Declare our engine's header path.
    -- This allows targets that depend on the engine to #include them.
    add_includedirs("src", {public = true})
    add_includedirs("bitmap", {public = true})
    -- Add all .cpp files in the `src` directory.
    add_files("src/*.cpp")
    add_files("bitmap/*.cpp")

target("helloworld")
    set_kind("binary")
    set_languages("cxx17")
    add_deps("WMB")
    add_files("demo/helloworld.cpp")