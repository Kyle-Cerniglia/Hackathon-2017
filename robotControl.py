import serial
port = serial.Serial("/dev/ttyAMA0",bauimdrate=9600,timeout=3.0)

def onPoseEdge(pose, edge):
	print("onPoseEdge: "+pose+", "+edge)
	if(pose=="waveRight" and edge=='on'):
		port.write("R")
	if(pose=="waveLeft and edge=='on'):
		port.write("L")
	if(pose=='fist' and edge=='on'):
		port.write("H")
	if(pose='fingerSpread' and edge=='on'):
		port.write("F")



myo.onWear(arm,xdirection)=onPoseEdge(myo.getPoseSide(), myo.getEdge())
