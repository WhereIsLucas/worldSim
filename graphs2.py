import os.path
import matplotlib.animation as animation
import matplotlib.pyplot as plt

import numpy as np

types = ['float', 'float', 'float', 'float', 'float', 'float']
domainTypes = ['float', 'float']
creaturesData = []
foodData = []

fig = plt.figure(figsize=(7, 7))

# this counts the number of frames

showingFrame = 0

for a in range(-5, 11):
    plt.clf()
    path = "./cmake-build-debug/results/creatureCount" + str(a) + ".txt"
    creaturesData = np.genfromtxt(path,
                                  delimiter=',',
                                  dtype=types,
                                  names=['x', 'y', 'energy', 'meanSpeed', 'preys', "'predators'"])

    plt.stackplot(creaturesData['x'], creaturesData['predators'], creaturesData['preys'])
    plt.ylim(bottom=0)
    plt.title("population evolution")
    plt.legend()
    plt.savefig('exports/population_graph' + str(a) + '.png')
