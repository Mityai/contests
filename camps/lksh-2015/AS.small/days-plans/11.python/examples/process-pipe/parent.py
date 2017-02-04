import subprocess
import sys

s = "test"
p = subprocess.Popen([sys.executable, "child.py"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
out, _ = p.communicate(s.encode())
print(out.decode())
