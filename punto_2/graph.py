import numpy as np
import corner
import matplotlib.pyplot as plt

data = np.loadtxt('sun.dat')

corner.corner(data[20000:,:],show_titles=True)
plt.savefig('graph.pdf',format = 'pdf', transparent = True)
plt.close()
