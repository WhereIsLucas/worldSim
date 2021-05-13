import os.path
import matplotlib.animation as animation
import matplotlib.pyplot as plt

import numpy as np
from plyer import notification

types = ['float', 'float', 'float']
domainTypes = ['float', 'float']
creaturesData = []
foodData = []

fig = plt.figure(figsize=(7, 7))

# this counts the number of frames
path = "./cmake-build-debug/results/creatureCount.txt"
creaturesData = np.genfromtxt(path,
                              delimiter=',',
                              dtype=types,
                              names=['x', 'y', 'energy'])

showingFrame = 0
creatureScatGraph = plt.plot(creaturesData['x'], creaturesData['y'], label='Creature number')
# energyScatGraph = plt.plot(creaturesData['x'], creaturesData['energy'], label='Creature energy')
plt.title('Creatures')
plt.legend()
# plt.gca().set_aspect('equal', adjustable='box')

plt.ylim(bottom=0)

# plt.xlabel('x')
# plt.ylabel('y')

plt.savefig('exports/population_graphs.png')

title = 'worldSim'
message = 'Graph is ready'

notification.notify(title=title,
                    message=message,
                    app_icon=None,
                    timeout=10,
                    toast=False)
