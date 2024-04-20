import math
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

fig, (f1, f2, f3, f4) = plt.subplots(1,4,figsize=(20,5))

x,y = np.loadtxt("uni1.dat", usecols=(0,1), unpack='true')
f1.plot(x,y,label='N=1',marker=".",color="crimson")
leg = f1.legend(fontsize=15);
f1.tick_params(axis='both', which='major', labelsize=14.5)
f1.grid(True)

y= np.loadtxt("uni2.dat", usecols=(1), unpack='true')
f2.plot(x,y, marker=".",label='N=2',color="salmon")
leg = f2.legend(fontsize=15);
f2.tick_params(axis='both', which='major', labelsize=14.5)
f2.grid(True)

y= np.loadtxt("uni10.dat", usecols=(1), unpack='true')
f3.plot(x,y,marker=".",label='N=10',color="orangered")
leg = f3.legend(fontsize=15);
f3.tick_params(axis='both', which='major', labelsize=14.5)
f3.grid(True)

def func(x, a, mu, sigma):
     return (a/(pow(2*math.pi,2)*sigma))* np.exp(-((x-mu)**2)/(2*sigma)) 

y= np.loadtxt("uni100.dat", usecols=(1), unpack='true')
f4.plot(x,y,marker=".",label='N=100',color="red")
leg = f4.legend(fontsize=15);
f4.tick_params(axis='both', which='major', labelsize=11.5)
f4.grid(True)
    
popt, pcov = curve_fit(func, x, y)
y_fit = func(x,popt[0],popt[1],popt[2])
print(popt)

plt.plot(x, y_fit,color="yellow")

plt.savefig("uni.jpeg")