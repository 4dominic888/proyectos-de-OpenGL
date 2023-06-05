import subprocess
import os
import shutil

file_name = "Ruta3D"

cpp_dir = "dependencias/include/extra"

include_dir = "dependencias/include"
lib_dir = "dependencias/lib"
lib = "-lglfw3 -lglew32s -lglew32 -lopengl32 -lgdi32"
object_dir = "objects"
dll_dir = "dlls"

def compilar():
    for cpp_file in os.listdir(cpp_dir):
        if cpp_file.endswith(".cpp"):
            cpp_path = os.path.join(cpp_dir, cpp_file)
            base_name = os.path.splitext(cpp_file)[0]
            object_file = os.path.join(object_dir, base_name + ".o")
            subprocess.call(["g++", "-c", cpp_path, "-I", include_dir, "-o", object_file])


def main():
    compilar();
    object_file = os.path.join(object_dir, "main.o")
    subprocess.call(f"g++ -c main.cpp -I {include_dir} -o {object_file}")
    subprocess.call(f"g++ {object_dir}/*.o -o {file_name} -L {lib_dir} {lib} -Wl,-rpath,'$ORIGIN/{dll_dir}'")
    

if "__main__" == __name__:
    main()