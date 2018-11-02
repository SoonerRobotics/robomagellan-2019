import glob
from shutil import copy

#TODO: Add some tests to copy files to
dst = ["tests/GPSImuDataPull/"]

for f in glob.glob('*.cpp'):
    for i in range(0, len(dst)):
        copy(f, dst[i])

for f in glob.glob('*.h'):
    for i in range(0, len(dst)):
        copy(f, dst[i])