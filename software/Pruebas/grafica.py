from pyqtgraph.Qt import QtGui, QtCore, uic
import matplotlib.pyplot as gph
import matplotlib.lines as lin
import numpy as np
import time
from drawnow import drawnow

n = 0
flag = True

fourx = np.linspace(-40, 40, 40)
foury = np.sqrt(1600-(fourx*fourx))
fourt = np.arctan2(foury,fourx)
fourr = (fourx**2 + foury**2)**(0.5)

#GRIDs
angles=[]
for k in range(1,34):
	angles.append(-136+k*8)

radii=[]
for k in range(1,9):
	radii.append(k*10)

#class MyApp(QtGui.QMainWindow, Ui_MainWindow):
#	def __init__(self):
#		#Inicializar
#		QtGui.QMainWindow.__init__(self)
#		Ui_MainWindow.__init__(self)
#		self.setupUi(self)
	def grafica():
		global n, flag
		#gph.axis((-160, 160, 0, 160))
		#gph.axes().set_aspect('equal', 'datalim')
		#gph.rgrids(2, labels=None, angle=22.5, fmt=None)
		ax = gph.subplot(111, projection='polar')
		ax.plot([n*8*np.pi/180, 0],[80,0],'g',alpha=0.4,drawstyle='steps')
		ax.plot(fourt, fourr,'ro')
		ax.set_theta_offset(np.pi/2)
		ax.set_thetalim(thetamin=-135,thetamax=135)
		ax.set_thetagrids(angles)
		ax.set_rgrids(radii)
		
		if flag:
			n=n+1
			if n>17:
				n=n-2
				flag = False
		else:
			n=n-1
			if n<-17:
				n=n+2
				flag = True
	
	time.sleep(2)
	
	def main():
		while 1:
			drawnow(grafica)
			time.sleep(0.1)
	
if __name__ == "__main__":
	#app = QtGui.QApplication(sys.argv)
	#window = MyApp()
	#window.show()
	#window.main()
	#sys.exit(app.exec_())  
	main()