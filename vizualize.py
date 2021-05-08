import os.path
import matplotlib.animation as animation
import matplotlib.pyplot as plt
import numpy as np

types = ['float', 'float']
domainTypes = ['float', 'float']
agentsData = []
foodData = []

# Set up the codec for the video file
Writer = animation.writers['ffmpeg']
writer = Writer(fps=25, metadata=dict(artist='Lucas H'), bitrate=1800)
fig = plt.figure(figsize=(7, 7))

# this counts the number of frames
path = "./cmake-build-debug/results/agents/"
num_files = len([f for f in os.listdir(path) if os.path.isfile(os.path.join(path, f))])
print(num_files)
totalFrames = num_files - 1
for i in range(0, totalFrames):
    fileName = path + "agent" + str(i) + ".txt"
    agentsData.insert(i, np.genfromtxt(fileName,
                                 delimiter=',',
                                 dtype=types,
                                 names=['x', 'y']))
showingFrame = 0
agentScatGraph = plt.scatter(agentsData[showingFrame]["x"], agentsData[showingFrame]['y'], alpha=0.5, s=20, c='red', label='Agent')
#red are agents
#blue is food

path2 = "./cmake-build-debug/results/food/"
for i in range(0, totalFrames):
    fileName = path2 + "food" + str(i) + ".txt"
    foodData.insert(i, np.genfromtxt(fileName,
                                 delimiter=',',
                                 dtype=types,
                                 names=['x', 'y']))
showingFrame = 0
foodScatGraph = plt.scatter(foodData[showingFrame]["x"], foodData[showingFrame]['y'],marker='*', alpha=0.5, s=20, c='blue',label='Food')

plt.title('Scatter plot test')
plt.legend()
# plt.gca().set_aspect('equal', adjustable='box')
plt.axis("equal")

plt.xlim(-5, 105)
plt.ylim(-5, 105)
# plt.xlabel('x')
# plt.ylabel('y')

plt.savefig('exports/test.png')

def update(frame_number):
    agentScatGraph.set_offsets(np.c_[agentsData[frame_number]["x"], agentsData[frame_number]["y"]])
    foodScatGraph.set_offsets(np.c_[foodData[frame_number]["x"], foodData[frame_number]["y"]])


animation = animation.FuncAnimation(fig, update, interval=40, frames=totalFrames)
# plt.show()
animation.save('exports/im.mp4', writer=writer)
