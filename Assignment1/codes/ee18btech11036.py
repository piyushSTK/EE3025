#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Feb 23 14:54:25 2021
@author: Piyush Kumar Uttam
Released under GNU-GPl 
"""

import numpy as np
import matplotlib.pyplot as plt
import soundfile as sf
from scipy import signal

#if using termux
import subprocess
import shlex
#end if

def H( z, b, a):
    return np.polyval(b, z**(-1))/np.polyval(a, z**(-1))

def filt( b, a, inputSignal):
    k = np.arange(len(inputSignal))
    w = 2*np.pi*k/len(inputSignal)
    z = np.exp(1j*w)
    Hz = H(z, b, a)
    X = np.fft.fft(inputSignal)
    Y = np.multiply(Hz,X)
    return np.fft.ifft(Y)
    
    
    
    
input_signal, fs = sf.read('Sound_Noise.wav')
sampl_freq = fs
order = 4
cutoff_freq = 4000.0
Wn = 2*cutoff_freq/sampl_freq
b,a = signal.butter(order, Wn, 'low')
output_signal_ori = signal.filtfilt( b, a, input_signal)
output_signal_const = filt(b,a,input_signal)
sf.write('Sound_With_ReducedNoise.wav', output_signal_ori, fs)





plt.figure(1)
plt.figure(figsize=(10,10))
plt.suptitle("Time domain Comparison")
plt.subplot(2,1,1)
plt.plot(output_signal_const)
plt.title('Constructed filter')
plt.grid()

plt.subplot(2,1,2)
plt.plot(output_signal_ori)
plt.title('Scipy Filter')
plt.grid()

plt.savefig('ee18btech11036_1.eps')


plt.figure(2)
plt.figure(figsize=(10,10))
plt.suptitle("Frequency Response Comparison")
plt.subplot(2,1,1)
plt.plot(np.abs(np.fft.fft(output_signal_const)))
plt.title('Constructed filter')
plt.grid()

plt.subplot(2,1,2)
plt.plot(np.abs(np.fft.fft(output_signal_ori)))
plt.title('Scipy Filter')
plt.grid()

plt.savefig('ee18btech11036_2.eps')



#plt.show()

#If using termux
#subprocess.run(shlex.split("termux-open ../figs/ee18btech11036_1.pdf"))
#subprocess.run(shlex.split("termux-open ../figs/ee18btech11036_2.pdf"))
