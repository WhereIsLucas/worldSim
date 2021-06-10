import os.path
import matplotlib.animation as animation
import matplotlib.pyplot as plt

import numpy as np

# from plyer import notification


types = ['float', 'float', 'float', 'float']
domainTypes = ['float', 'float', 'int']
preysData = []
predatorsData = []
foodData = []

# Set up the codec for the video file
Writer = animation.writers['ffmpeg']
writer = Writer(fps=25, metadata=dict(artist='Lucas H'), bitrate=1800)
# import the world parameters
world = np.genfromtxt('./cmake-build-debug/results/world.txt',
                      delimiter=',',
                      dtype=domainTypes,
                      names=['x', 'y', 'stepPerDay'])

start = 0 * world['stepPerDay']
end = 1000 * world['stepPerDay']

fig = plt.figure(figsize=(7, 7))

# this counts the number of frames
path1 = "./cmake-build-debug/results/preys/"
num_files = len([f for f in os.listdir(path1) if os.path.isfile(os.path.join(path1, f))])

totalFrames = end - start
skip = 200

j = 0
for i in range(start, end):
    fileName = path1 + "prey" + str(i) + ".txt"
    if os.path.exists(fileName):
        if i % skip == 0:
            preysData.insert(j, np.genfromtxt(fileName,
                                              delimiter=',',
                                              dtype=types,
                                              names=['x', 'y', 'E', 'speed']))
            j = j + 1

# showingFrame = 146
showingFrame = 0
preysHistGraph = plt.hist(preysData[showingFrame]['speed'])

plt.title('World Simulation')
plt.legend()
plt.xlim(left=0.8, right=1.5)

plt.savefig('exports/test2.png')


def update(frame_number):
    plt.cla()
    plt.xlim(left=0.8, right=1.5)
    plt.ylim(top=50)
    plt.hist(preysData[frame_number]['speed'], bins=np.arange(0.8, 1.5 + 0.01, 0.01))


animation = animation.FuncAnimation(fig, update, interval=40, frames=j)
# plt.show()
animation.save('exports/im2.mp4', writer=writer)

title = 'worldSim'
message = 'Video is ready'

# notification.notify(title=title,
#                   message=message,
#                   app_icon=None,
#                   timeout=10,
#                   toast=False)
