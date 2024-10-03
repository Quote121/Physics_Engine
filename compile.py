## Ability to cross compile code
import os
import subprocess
import shutil
import argparse

EXECNAME = "physicsMain.exe"
BUILDDIR = "build"
WINDOWS: bool
LINUX: bool

## My overrided print
def write(msg: str) -> None:
    ## Get just the filename from the whole file path
    pos = __file__.rfind('\\')
    filename = __file__[pos+1:len(__file__)]
    print(f"{filename} : [" + msg + ']')


## Will print error message and terminate process
def error(errorMsg: str) -> None:
    write("Error: '", errorMsg, "'")
    quit()


## Helper method, will print if verbose mode active
def verbose(msg: str) -> None:
    if (args.verbose):
        write(msg)


## Will remove directory and all contents provided by dir
def clean(dir: str) -> None:

    verbose(f"Cleaning directory: {dir}")

    if not (os.path.exists(dir)):
        write("Clean() dir not found")
        return

    shutil.rmtree(dir)


def main(parser: argparse.ArgumentParser) -> None:
    global args
    args = parser.parse_args()

    if (args.run and args.gdb):
        write("Cannot use 'run' and 'run gdb' at the same time.")
        quit()

    ## Clean
    if (args.clean):
        clean(BUILDDIR)

    ## Determine if there is a build folder, if not create it
    if not (os.path.exists(f"./{BUILDDIR}/")):
        verbose("Build dir not found, creating.")
        os.mkdir(f"./{BUILDDIR}/")
        
    else:
        verbose("Build dir found.")
        
    ## cd build
    os.chdir(f"./{BUILDDIR}/")
    verbose("Entered build dir.")

    if WINDOWS:
        cmakeArgs = ""

        if (args.debug):
            cmakeArgs += "-DCMAKE_BUILD_TYPE=debug"

        ## CMake create
        verbose("Running cmake script.")
        subprocess.run(["cmake", "-G", "MinGW Makefiles", "-DCMAKE_C_COMPILER=gcc", "-DCMAKE_CXX_COMPILER=g++", cmakeArgs, ".."])

        ## Make
        verbose("Running make.")
        subprocess.run(["mingw32-make.exe"])

    elif LINUX:
        error("Not implemented.")

    ## Run program if specified
    if (args.run):
        verbose(f"Running application {EXECNAME}")
        subprocess.run([f"./src/{EXECNAME}"])

    if (args.gdb):
        verbose(f"Running gdb on {EXECNAME}")
        subprocess.run(["gdb", f"./src/{EXECNAME}"])

    ## Leave the build dir
    verbose(f"Exiting {BUILDDIR}")
    os.chdir("../")
    


if __name__ == "__main__":
    
    ## Determine what OS we are on
    ## 'nt', 'posix'
    if (os.name == 'nt'):
        WINDOWS = True
    elif (os.name == 'posix'):
        LINUX = True
        error("Error, unsupported system: LINUX")
    else:
        WINDOWS = False
        LINUX = False
        error("Error, unsupported system: unknown/macos")

    ## Add parcer arguments
    parser = argparse.ArgumentParser(
        prog="Project compile script",
        description="Supply various compilation options"
    )
    parser.add_argument('-r', '--run', help="Will run the executable after compilation", action='store_true') 
    parser.add_argument('-c', '--clean', help="Will clean the project and compile from scratch", action='store_true')
    parser.add_argument('-v', '--verbose', help="Print out detailed information", action='store_true')
    parser.add_argument('-d', '--debug', help="Enable debugging symbols", action='store_true')
    parser.add_argument('-g', '--gdb', help="Enable gdb", action='store_true')

    main(parser)