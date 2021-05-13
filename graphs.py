import os.path
import matplotlib.animation as animation
import matplotlib.pyplot as plt

import numpy as np
from plyer import notification

def plotting_fig(x,y, label):
    creatureScatGraph = plt.plot(x, y, label=label)
    showingFrame = 0
    plt.ylim(bottom=0)
    plt.title('Creatures')
    plt.legend()
    plt.savefig('exports/'+label+'_graphs.png')
    plt.clf()

    

types = ['float', 'float', 'float','float']
domainTypes = ['float', 'float']
creaturesData = []
foodData = []

fig = plt.figure(figsize=(7, 7))

# this counts the number of frames
path = "./cmake-build-debug/results/creatureCount.txt"
creaturesData = np.genfromtxt(path,
                              delimiter=',',
                              dtype=types,
                              names=['x', 'y', 'energy','meanSpeed'])


plotting_fig(creaturesData['x'],creaturesData['y'], 'Population')
plotting_fig(creaturesData['x'],creaturesData['meanSpeed'], 'MeanSpeed')
plotting_fig(creaturesData['x'],creaturesData['energy'], 'Energy')

# plt.gca().set_aspect('equal', adjustable='box')



# plt.xlabel('x')
# plt.ylabel('y')


title = 'worldSim'
message = 'Graph is ready'

notification.notify(title=title,
                    message=message,
                    app_icon=None,
                    timeout=10,
                    toast=False)
