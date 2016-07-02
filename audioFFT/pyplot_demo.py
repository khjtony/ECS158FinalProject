import numpy as np
import matplotlib.pyplot as plt
import signal
import sys

def signal_handler(signal, frame):
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

plt.axis([0, 10, 0, 1])
plt.ion()

for i in range(10):
    y = np.random.random()
    plt.scatter(i, y)
    plt.pause(0.1)

while True:
    plt.pause(5)
    sys.exit(0)