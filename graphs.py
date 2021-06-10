import os.path
import matplotlib.animation as animation
import matplotlib.pyplot as plt

import numpy as np

from plyer import notification


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
foodData = []

fig = plt.figure(figsize=(7, 7))

# this counts the number of frames
path = "./cmake-build-debug/results/creatureCount.txt"
creaturesData = np.genfromtxt(path,
                              delimiter=',',
                              dtype=types,
                              names=['x', 'y', 'energy', 'meanSpeed', 'preys', "'predators'"])
# days = min(creaturesData.size,20)

path = "./cmake-build-debug/results/foodDensity.txt"
foodDensityEvolutionData = np.genfromtxt(path,
                                         delimiter=',',
                                         dtype=[float, float],
                                         names=['x', 'y'])

days = creaturesData.size
# days = min(creaturesData.size, 30)
creaturesData = np.resize(creaturesData, days)

# meanData = np.delete(creaturesData, range(0, 50))
# mean = np.mean(meanData["preys"])
# print(mean)

showingFrame = 0

speedScatGraph = plt.plot(creaturesData['x'], creaturesData['meanSpeed'])
# plt.ylim(bottom=0)
plt.title("Mean Speed Evolution")
plt.xlabel('Days')
plt.ylabel('Mean Speed')
plt.ylim(bottom=0)
plt.xlim(left=0)
plt.savefig('exports/speed_graph.png')

plt.clf()

plt.stackplot(creaturesData['x'], creaturesData['predators'], creaturesData['preys'])
plt.ylim(bottom=0)
plt.xlim(left=0)

plt.title("Population Evolution")
plt.xlabel('Days')
plt.ylabel('Population')
plt.legend()

plt.savefig('exports/population_graph.png')
#
# plt.clf()
#
# energyScatGraph = plt.plot(creaturesData['x'], creaturesData['energy'] / creaturesData['y'], label='Creature energy')
# plt.ylim(bottom=0)
# plt.title("energy_graph")
# plt.legend()
# plt.savefig('exports/energy_graph.png')
#

plt.clf()

plt.scatter(foodDensityEvolutionData['x'], foodDensityEvolutionData['y'])
plt.ylim(bottom=0)
plt.xlim(left=0)
plt.title("foodDensity vs saturation")
plt.xlabel('Food Density')
plt.ylabel('Mean population saturation')
plt.savefig('exports/saturation_density.png')

title = 'worldSim'
message = 'Graphs are ready'

notification.notify(title=title,
                    message=message,
                    app_icon=None,
                    timeout=10,
                    toast=False)
