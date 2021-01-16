import os
import shutil
import signal
import sys
import subprocess

BUILD_DIR = "_build"

def default():
    if not os.path.exists(BUILD_DIR):
        os.mkdir(BUILD_DIR)

    subprocess.run("cmake ..", cwd=BUILD_DIR, shell=True)
    subprocess.run("make", cwd=BUILD_DIR, shell=True)
    result = subprocess.run("program/program", cwd=BUILD_DIR, shell=True)
    if result.returncode == 0:
        print("Program executed successfully!")
    else:
        print(f"Program received {signal.Signals(-result.returncode).name} signal")

def test():
    if not os.path.exists(BUILD_DIR):
        os.mkdir(BUILD_DIR)

    subprocess.run("cmake ..", cwd=BUILD_DIR, shell=True)
    subprocess.run("make", cwd=BUILD_DIR, shell=True)
    subprocess.run("testrunner/testrunner", cwd=BUILD_DIR, shell=True)

    print("Done!")

def clean():
    if os.path.isdir(BUILD_DIR):
        shutil.rmtree(BUILD_DIR)

    print("Done!")

if len(sys.argv) == 1:
    default()
else:
    locals()[sys.argv[1]](*sys.argv[2:])
