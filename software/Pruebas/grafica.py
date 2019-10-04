import matplotlib.pyplot as gph
import matplotlib.lines as lin
import numpy as np
import time
from drawnow import drawnow


fourx = np.linspace(-40, 40, 40)
foury = np.sqrt(1600-(fourx*fourx))
fourt = np.arctan2(foury,fourx)
fourr = (fourx**2 + foury**2)**(0.5)

angles=[]
for n in range(1,34):
	angles.append(-136+n*8)

radii=[]
for n in range(1,9):
	radii.append(n*10)

#for n in range(1,100):
#	print "r: %d; ang: %f" %(fourr[n],fourt[n])
#	print "x: %d, y: %d" %(fourx[n], foury[n])

def grafica():
	#gph.axis((-160, 160, 0, 160))
	#gph.axes().set_aspect('equal', 'datalim')
	#gph.rgrids(2, labels=None, angle=22.5, fmt=None)
	ax = gph.subplot(111, projection='polar')
	ax.plot(fourt, fourr,'ro')
	ax.set_theta_offset(np.pi/2)
	ax.set_thetalim(thetamin=-135,thetamax=135)
	ax.set_thetagrids(angles)
	ax.set_rgrids(radii)

	

time.sleep(2)

def main():
	while 1:
		drawnow(grafica)
		time.sleep(0.0001)

if __name__ == "__main__":
	main()
