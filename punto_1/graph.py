import matplotlib.pyplot as plt
import corner
import numpy as np

data = np.loadtxt('sismo.dat')

corner.corner(data,labels=[r"$x$", r"$y$"],show_titles=True)
plt.savefig('graph.pdf',format='pdf',transparent=True)
plt.close()
