## Ability to cross compile code
import os
import subprocess
import shutil
import argparse
import traceback

EXECNAME = "physicsMain.exe"
BUILDDIR = "build"
EXECPATH = f"./{BUILDDIR}/src/{EXECNAME}"
MAKEAPP = "mingw32-make.exe"
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
    write("Error: '" + errorMsg + "'")
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
    try:
        global args
        args = parser.parse_args()
        current_dir = os.getcwd()

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
            cmakeArgs = []
            
            ## Debug is needed if we are using gdb too
            if (args.debug or args.gdb):
                cmakeArgs.append("-DCMAKE_BUILD_TYPE=debug")
            ## Output log to the console
            if (args.log):
                cmakeArgs.append("-DCONSOLE_LOG_OUTPUT=1")
            else:
                cmakeArgs.append("-DCONSOLE_LOG_OUTPUT=0")

            ## Install path argument (location of this script is CMAKE_SOURCE_DIR)
            verbose(f"Setting install prefix to: {current_dir}")
            cmakeArgs.append(f"-DCMAKE_INSTALL_PREFIX={current_dir}")

            if (len(cmakeArgs) > 0):
                verbose("Using cmake arguments: " + str(cmakeArgs))

            ## CMake create
            verbose("Running cmake script.")

            command = ["cmake", "-G", "MinGW Makefiles", "-DCMAKE_C_COMPILER=gcc", "-DCMAKE_CXX_COMPILER=g++"] + cmakeArgs + [".."]
            verbose("Running command: " + str(command))
            subprocess.run(command)

            ## Make
            verbose("Running make.")
            subprocess.run([MAKEAPP, "install"])

        elif LINUX:
            error("Not implemented.")
        
        ## Leave the build dir
        verbose(f"Exiting {BUILDDIR}/")
        os.chdir("../")

        ## Run program if specified
        if (args.run):
            verbose(f"Running application {EXECNAME}")
            subprocess.run([f"./{EXECPATH}"])

        if (args.gdb):
            verbose(f"Running gdb on {EXECNAME}")
            subprocess.run(["gdb", f"./{EXECPATH}"])
    
    except KeyboardInterrupt:
        error("Keyboard interrupt.")
    except Exception as e:
        trace = traceback.format_exc()
        error(("Exception: " + str(e) + trace))


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
    parser.add_argument('-l', '--log', help="Write the log output to console", action='store_true')

    main(parser)
