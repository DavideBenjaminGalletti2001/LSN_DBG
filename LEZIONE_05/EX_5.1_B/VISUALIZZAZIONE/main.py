import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

X, Y, Z= np.loadtxt("orbitale1s.dat", usecols=(0,1,2), delimiter=' ', unpack='true')

fig = plt.figure()
ax = fig.add_subplot(projection = '3d')
ax.scatter(X, Y, Z, c=Z, marker='.')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
print("        Nube elettronica: orbitale 1s")
ax.view_init(0, 30)
plt.savefig("orbitale1s.jpeg")

X, Y, Z= np.loadtxt("orbitale2p.dat", usecols=(0,1,2), delimiter=' ', unpack='true')

fig = plt.figure()
ax = fig.add_subplot(projection = '3d')
ax.scatter(X, Y, Z, c=Z, marker='.')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
print("        Nube elettronica: orbitale 2p")
ax.view_init(0, 30)
plt.savefig("orbitale2p.jpeg")

plt.figure()

x, f, error = np.loadtxt("mt1.dat", usecols=(0,1,2), delimiter=' ', unpack='true')
plt.errorbar(x,f,yerr=error)
plt.xlabel('$N$', fontsize=12)
plt.ylabel('$<r>$ ', fontsize=12)
plt.title('Distanza media (1s): T(x|y) uniforme', fontsize=12)
plt.grid(True)


s=np.linspace(0,100,1000)
t=1.5*(s/s)
plt.plot(s,t, color="black")
plt.savefig("ray1s.jpeg")

plt.figure()

x, f, error = np.loadtxt("mt2.dat", usecols=(0,1,2), delimiter=' ', unpack='true')
plt.errorbar(x,f,yerr=error)
plt.xlabel('$N$', fontsize=12)
plt.ylabel('$<r>$ ', fontsize=12)
plt.title('Distanza media (1s): T(x|y) uniforme', fontsize=12)
plt.grid(True)


s=np.linspace(0,100,1000)
t=5.0*(s/s)
plt.plot(s,t, color="black")
plt.savefig("ray2p.jpeg")