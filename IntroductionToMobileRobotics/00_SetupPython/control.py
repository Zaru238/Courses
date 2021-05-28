import os
import sys
import subprocess

MAIN_FILE = "main.py"

def default():
    subprocess.run("python " + MAIN_FILE, shell=True)

if len(sys.argv) == 1:
    default()
