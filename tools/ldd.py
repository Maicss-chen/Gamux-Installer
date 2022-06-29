#!/bin/python

import subprocess
import sys
import os

result = subprocess.getoutput("ldd "+sys.argv[1])

reslist = result.split("\n")

for entry in reslist:
    so = entry.split(" ")
    if len(so) >= 3:
        print(so[2])
        os.system("cp "+so[2]+" .")
