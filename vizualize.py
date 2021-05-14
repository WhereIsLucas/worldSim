import os.path
import matplotlib.animation as animation
import matplotlib.pyplot as plt

import numpy as np
#from plyer import notification

types = ['float', 'float']
domainTypes = ['float', 'float']
preysData = []
predatorsData = []
foodData = []

# Set up the codec for the video file
Writer = animation.writers['ffmpeg']
writer = Writer(fps=25, metadata=dict(artist='Lucas H'), bitrate=1800)

fig = plt.figure(figsize=(7, 7))

# this counts the number of frames
path = "./cmake-build-debug/results/creatures/"
num_files = len([f for f in os.listdir(path) if os.path.isfile(os.path.join(path, f))])
totalFrames = min(num_files - 1, 1500)
for i in range(0, totalFrames):
    fileName = path + "prey" + str(i) + ".txt"
    preysData.insert(i, np.genfromtxt(fileName,
                                      delimiter=',',
                                      dtype=types,
                                      names=['x', 'y']))
    fileName = path + "predator" + str(i) + ".txt"
    predatorsData.insert(i, np.genfromtxt(fileName,
                                          delimiter=',',
                                          dtype=types,
                                          names=['x','y']))
    
showingFrame = 0
preysScatGraph = plt.scatter(preysData[showingFrame]["x"], preysData[showingFrame]['y'], alpha=0.5, s=20,
                             c='red', label='prey')
predatorsScatGraph = plt.scatter(predatorsData[showingFrame]["x"], predatorsData[showingFrame]['y'], alpha=0.5, s=20, 
                                 c='magenta', label='predator')
# red are preys
# magenta are predators
# blue is food

path2 = "./cmake-build-debug/results/food/"
for i in range(0, totalFrames):
    fileName = path2 + "food" + str(i) + ".txt"
    foodData.insert(i, np.genfromtxt(fileName,
                                     delimiter=',',
                                     dtype=types,
                                     names=['x', 'y']))
showingFrame = 0
foodScatGraph = plt.scatter(foodData[showingFrame]["x"], foodData[showingFrame]['y'], marker='*', alpha=0.5, s=20,
                            c='blue', label='Food')

plt.title('World Simulation')
plt.legend()
# plt.gca().set_aspect('equal', adjustable='box')
plt.axis("equal")

# import the world parameters
world = np.genfromtxt('./cmake-build-debug/results/world.txt',
                      delimiter=',',
                      dtype=types,
                      names=['x', 'y'])

plt.xlim(-world['x'] * 0.55, world['x'] * 0.55)
plt.ylim(-world['y'] * 0.55, world['y'] * 0.55)

plt.savefig('exports/test.png')


def update(frame_number):
    preysScatGraph.set_offsets(np.c_[preysData[frame_number]["x"], preysData[frame_number]["y"]])
    predatorsScatGraph.set_offsets(np.c_[predatorsData[frame_number]["x"], predatorsData[frame_number]["y"]])
    foodScatGraph.set_offsets(np.c_[foodData[frame_number]["x"], foodData[frame_number]["y"]])


animation = animation.FuncAnimation(fig, update, interval=40, frames=totalFrames)
# plt.show()
animation.save('exports/im.mp4', writer=writer)

title = 'worldSim'
message = 'Video is ready'

#notification.notify(title=title,
#                   message=message,
#                   app_icon=None,
#                   timeout=10,
#                   toast=False)
