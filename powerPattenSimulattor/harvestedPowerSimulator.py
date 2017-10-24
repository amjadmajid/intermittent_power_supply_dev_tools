#! /usr/bin/python

"""
Harvested power simulator 
Author: Amjad Y. Majid
Date  : Oct, 16th 2017
"""

import random
import matplotlib.pyplot as plt
import numpy as np


def LowFreqGen(sr, freq):
    """
        sine wave signal generator
    """

    # sample rate 
    fs = sr
    # the frequency of the signal
    f = freq

    # compute the value ( amplitude) of the sin wave at the for each sample
    y = np.array([ np.sin(2*np.pi*f * (i/float(fs) )) for i in np.arange(fs)]) 
    # replace the negative values with zeros
    return (y)


def noise(sr, lowBound, upperBound):
    noiseSig = []
    for i in range(sr):
        noiseSig.append( random.randint(lowBound,upperBound) )
    return (np.array(noiseSig))



CapSize =  0    # the  device ON time when a perfect cap is considered and zero charing rate during computation is:
                #onTime / (MCU clock frequency) 


f = 16
sampRate = 200
ampVals = [1, 10000] # amplifier values
NoiseLowBound = -500
NoiseUpperBound = 5000

PowerPattens=[]

basicNoisyPwrPat = noise(sampRate,NoiseLowBound,NoiseUpperBound )

for ampVal in ampVals:
    assert( ampVal != 0), "zero is not an allowed value for amplification"
    y =  LowFreqGen(sampRate,f)
    y [y <0] = 0
    PowerPattens.append ( (basicNoisyPwrPat + CapSize +y * ampVal).astype(int)) 

temp_PP = []
for i in np.arange(0,200, 1):
    temp_PP.append((basicNoisyPwrPat[i] + CapSize +i**2).astype(int)) 

PowerPattens.append(temp_PP)

print('Noisy Fixed Pattern')
print(','.join(map(str,PowerPattens[0])) )
print('Camel Pattern')
print(','.join(map(str,PowerPattens[1])) )
print('Towards Pattern')
print(','.join(map(str,PowerPattens[2])) )



# Three subplots sharing both x/y axes
f, (ax1, ax2, ax3) = plt.subplots(3, sharex=True)
ax1.plot(PowerPattens[0])
ax1.set_title('Noisy Fixed Pattern')
ax2.plot(PowerPattens[1])
ax2.set_title('Camel Pattern')
ax3.plot(PowerPattens[2])
ax3.set_title('Towards Reader Pattern')


# Fine-tune figure; make subplots close to each other and hide x ticks for
# all but bottom plot.
# f.subplots_adjust(hspace=0)
plt.setp([a.get_xticklabels() for a in f.axes[:-1]], visible=False)


plt.show()
    