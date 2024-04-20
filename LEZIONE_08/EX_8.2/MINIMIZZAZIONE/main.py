# uso mu, sigma = 0.8, 0.65

import matplotlib
import matplotlib.pyplot as plt
import numpy as np

N = 150
x = np.arange(N)+1      # uso l'ordinamento da 1 a N

plt.figure(figsize = (12,8))

pos, ave, err = np.loadtxt("energia.dat", usecols=(0,1,2), delimiter=' ', unpack='true')
plt.errorbar(x, ave, yerr = err, label = r"$\langle H\rangle_T$ - 150 stp/blk") 

plt.ylabel('Energy', fontsize = 15)
plt.xlabel('Block number', fontsize = 15)
plt.grid(True)
#plt.ylim(-0.525,-0.375)
#plt.axhline(y=-0.46, color = 'r', linestyle = '-')
plt.title('Progressive average $\hat{H}$', fontsize = 20, fontweight = "bold")
plt.legend()

plt.savefig("energia.jpeg")

#---------------------------------------

plt.figure(figsize = (12,8))

histofill_blk = 1000                  # numero di posizioni salvate per blocco (cfr input.dat)
x = np.linspace(-2,2,150)      # uso l'ordinamento da 1 a N

mu = 0.8
sgm = 0.6
def f(x):
   return np.exp(-pow(x-mu,2)/pow(sgm,2))+np.exp(-pow(x+mu,2)/pow(sgm,2))+2.*np.exp(-(pow(x,2)+pow(mu,2))/pow(sgm,2))
norm = 2*(3.14**(1/2))*sgm*(1.0+np.exp(-pow(mu,2)/pow(sgm,2)))

pos = np.loadtxt("funzione_onda.dat", usecols=(0), delimiter=' ', unpack='true')
plt.hist(pos, 150, density = "true", label = "Sampled positions")
plt.plot(x,f(x)/norm, label = "$\psi^2$", marker = ".")
plt.ylabel('Occurrences', fontsize = 15)
plt.xlabel('Position', fontsize = 15)
plt.title("Sampled particle positions", fontsize = 20, fontweight = "bold")
plt.grid(True)
plt.legend()

plt.savefig("funzione_onda.jpeg")