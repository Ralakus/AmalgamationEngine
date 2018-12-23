-- Tup build file

local debug, release = 0, 1
local linux, windows, other = 0, 1, 2

operating_system = linux

build_mode = debug

output     = "Amalgamation"

build_dir  = "build/"
obj_dir    = build_dir .. "obj/"
bin_dir    = build_dir .. "bin/"

src            = {
    "src/main.cpp",
    "lib/glad/src/glad.c"
}
include_dirs   = {
    "lib/cxxopts/include",
    "lib/glad/include",
    "lib/glm",
    "src",
}
lib_paths      = {
}
link_libraries = {
    "glfw",
}

defines = {
    "AE_64_BIT"
}

compiler = "clang++"
linker   = "clang++"

compile_args = " -std=c++17 -m64 "
link_args    = " -std=c++17 -m64 "

if build_mode == release then

    compile_args = compile_args .. " -O3 -flto "
    link_args    = link_args    .. " -O3 -flto "

    defines[#defines + 1] = "AE_BUILD_RELEASE"

elseif build_mode == debug then

    compile_args = compile_args .. " -O0 -g3 -Wall "
    link_args    = link_args    .. " -O0 -g3 -Wall "

    defines[#defines + 1] = "AE_BUILD_DEBUG"

end

if operating_system == linux then

    link_libraries[#link_libraries + 1] = "GL"
    link_libraries[#link_libraries + 1] = "dl"

elseif operating_system == windows then 

    link_libraries[#link_libraries + 1] = "opengl32"

end



-- Magic happens below this comment



build_include_dir_str = ""
for i = 1, #include_dirs do
    build_include_dir_str = build_include_dir_str .. " -I" .. include_dirs[i]
end

build_defines_str = ""
for i = 1, #defines do
    build_defines_str = build_defines_str .. " -D" .. defines[i]
end

link_link_paths_str = ""
for i = 1, #lib_paths do 
    link_link_paths_str = link_link_paths_str .. " -L".. lib_paths[i] 
end

link_link_libs_str = ""
for i = 1, #link_libraries do 
    link_link_libs_str = link_link_libs_str .. " -l".. link_libraries[i] 
end

build_command = compiler .. " -c " .. compile_args.. build_include_dir_str .. build_defines_str .. " -o %o %f"
link_command  = linker   .. link_args .. link_link_paths_str   .. link_link_libs_str .. " -o %o %f"

objects = tup.foreach_rule(
    src,
    build_command,
    { obj_dir .. "%B.o" }
)

tup.rule(objects, link_command, { bin_dir .. output })
