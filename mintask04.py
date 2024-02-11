import sys
import os

path = sys.argv[1]
first_hash = sys.argv[2]
second_hash = sys.argv[3]
command = sys.argv[4]

os.chdir(path)
stream = os.popen("git log " + first_hash + " " + second_hash + " --oneline")
logs = [log.split()[0] for log in stream.read().split('\n')[:-1]]

left = 0
right = len(logs) - 1

while left + 1 < right:
    pivot = (right + left) // 2
    os.popen("git checkout " + logs[pivot] + " -q")
    os.popen(command)
    stream = os.popen("echo $?")
    code = int(stream.read())
    if code == 0:
        left = pivot
    else:
        right = pivot
print("First bad commit: ", logs[left])
