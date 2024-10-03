## Ability to cross compile code
import os
import subprocess
import argparse

EXECNAME = "physicsMain.exe"
BUILDDIR = "build"
WINDOWS: bool
LINUX: bool
global args


## Will print error message and terminate process
def error(errorMsg: str) -> None:
    print("Error: '", errorMsg, "'")
    quit()


## Helper method, will print if verbose mode active
def verbose(msg: str) -> None:
    if (args.verbose):
        print(msg)


## Will remove directory and all contents provided by dir
def clean(dir: str) -> None:
    verbose(f"Cleaning directory: {dir}")

    if WINDOWS:
        ## CMD built in, powershell will fail
        subprocess.run(["rmdir", "/s", "/q", f"./{dir}/"])
    elif LINUX:
        subprocess.run(["rm", "-rf", f"./{dir}/"])


def main(parser: argparse.ArgumentParser) -> None:
    args = parser.parse_args()

    ## Determine if there is a build folder, if not create it
    if not (os.path.exists(f"./{BUILDDIR}/")):
        verbose("Build dir not found, creating.")
        os.mkdir(f"./{BUILDDIR}/")
        
    else:
        verbose("Build dir found.")
        ## Clean
        if (args.clean):
            clean(BUILDDIR)


    ## cd build
    os.chdir(f"./{BUILDDIR}/")
    verbose("Entered build dir.")

    if WINDOWS:
        cmakeArgs: str

        if (args.debug):
            cmakeArgs += "-DCMAKE_BUILD_TYPE=debug"

        ## CMake create
        verbose("Running cmake script.")
        subprocess.run(["cmake", "-G", "MinGW Makefiles", "-DCMAKE_C_COMPILER=gcc", "-DCMAKE_CXX_COMPILER=g++", cmakeArgs, ".."])

        ## Make
        verbose("Running make.")
        subprocess.run(["mingw32-make.exe"])

    if LINUX:
        error("Not implemented.")


    ## Run program if specified

    if (args.run):
        verbose(f"Running application {EXECNAME}")
        subprocess.run([f"./src/{EXECNAME}"])

    ## Leave the build dir
    verbose(f"Exiting {BUILDDIR}")
    os.chdir("../")
    print("Finished.")
    


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
    parser.add_argument('run', '-r', '--run', help="Will run the executable after compilation", action='store_true') 
    parser.add_argument('clean', '-c', '--clean', help="Will clean the project and compile from scratch", action='store_true')
    parser.add_argument('verbose', '-v', '--verbose', help="Print out detailed information", action='store_true')
    parser.add_argument('debug', '-g', '--debug', help="Enable debugging symbols", action='store_true')

    main(parser)