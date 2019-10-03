import matplotlib.pyplot as gph
import matplotlib.lines as lin
import numpy as np
import time
from drawnow import drawnow

fig = gph.figure()

fourx = np.linspace(-40, -1, 25)
foury = np.sqrt(1600-(fourx*fourx))
fourt = np.arctan(foury/fourx)*np.pi/180
fourr = (fourx**2 + foury**2)**(1/2)
#fourt = 2*np.pi*fourr

def grafica():
	#gph.axis((-160, 160, 0, 160))
	#gph.axes().set_aspect('equal', 'datalim')
	gph.title('Radar')
	gph.polar(fourt,fourr)


time.sleep(2)

def main():
	while 1:
		drawnow(grafica)
		time.sleep(0.0001)

if __name__ == "__main__":
	main()
