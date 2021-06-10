import os.path
import matplotlib.animation as animation
import matplotlib.pyplot as plt

import numpy as np


# from plyer import notification

def plotting_fig(x, y, label):
    creatureScatGraph = plt.plot(x, y, label=label)
    showingFrame = 0
    plt.ylim(bottom=0)
    plt.title('Creatures')
    # plt.legend()
    plt.xlabel('days')
    plt.ylabel(label)
    plt.savefig('exports/' + label + '_graph.png')
    plt.clf()


types = ['float', 'float', 'float', 'float', 'float', 'float']
domainTypes = ['float', 'float']
creaturesData = []
foodData = []

fig = plt.figure(figsize=(7, 7))

# this counts the number of frames
path = "./cmake-build-debug/results/creatureCount.txt"
creaturesData = np.genfromtxt(path,
                              delimiter=',',
                              dtype=types,
                              names=['x', 'y', 'energy', 'meanSpeed', 'preys', "'predators'"])

showingFrame = 0

speedScatGraph = plt.plot(creaturesData['x'], creaturesData['meanSpeed'], label='Creature meanSpeed')
plt.ylim(bottom=0)
plt.title("mean speed evolution")
plt.legend()
plt.savefig('exports/speed_graph.png')

plt.clf()

plt.stackplot(creaturesData['x'], creaturesData['predators'], creaturesData['preys'])
plt.ylim(bottom=0)
plt.title("population evolution")
plt.legend()
plt.savefig('exports/population_graph.png')
#
# plt.clf()
#
energyScatGraph = plt.plot(creaturesData['x'], creaturesData['energy'] / creaturesData['y'], label='Creature energy')
plt.ylim(bottom=0)
plt.title("energy_graph")
plt.legend()
plt.savefig('exports/energy_graph.png')
#
plt.clf()


plt.plot(creaturesData['preys'], creaturesData['predators'], "r-")
plt.ylim(bottom=0)
plt.title("population evolution")
plt.legend()
plt.savefig('exports/population_cycles.png')



'''oscillation = [[]]
for i in range(5):
    prey_mean = 0
    predator_mean = 0
    path = "./cmake-build-debug/results/creatureCount"+str(i)+".txt"
    creaturesData = np.genfromtxt(path,
                                  delimiter=',',
                                  dtype=types,
                                  names=['x', 'y', 'energy', 'meanSpeed', 'preys', "'predators'"])
    for j in range(creaturesData.shape[0]):
        prey_mean += creaturesData['preys'].iloc[j]
        predator_mean += creaturesData['predators'].iloc[j]
    
    prey_mean /= creaturesData.shape[0] # mean number of preys throughout the simulation
    predator_mean /= creaturesData.shape[0]
    
    oscillation.append([prey_mean,predator_mean])

abscissa = np.arange(5)
oscillationT = np.transpose(oscillation)
plt.scatter(abscissa, oscillationT[0])
plt.scatter(abscissa, oscillationT[1])
plt.legend(["Preys", "Predators"])
plt.ylim(bottom=0)
plt.show()'''

title = 'worldSim'
message = 'Graphs are ready'

# notification.notify(title=title,
#                    message=message,
#                    app_icon=None,
#                    timeout=10,
#                    toast=False)
