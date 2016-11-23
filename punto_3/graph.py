import numpy as np
import matplotlib.pyplot as plt
import corner

data = np.loadtxt('diff.dat')
print(data.shape)
corner.corner(data[60000:,:],labels=[r"$\alpha$",r"$\beta$",r"$\gamma$",r"$\delta$"],show_titles=True)
plt.savefig('graph.pdf',format='pdf',transparent=True)
plt.close()
