from serial import Serial
import pygame
from time import sleep
from pygame.locals import *


pygame.init()

DISPLAYSURF = pygame.display.set_mode((300,300))
pygame.display.set_caption('Stepper Debugger')

#ser = Serial('/dev/cu.usbmodem1411', 9600, timeout=2)
arduino = Serial('/dev/cu.usbmodem1421', 115200, timeout=2)

#print("connected to: " + ser.portstr)
print("connected to: " + arduino.portstr)

print(arduino.readline())


aDown = False
dDown = False
wDown = False
sDown = False
fDown = False
hDown = False
tDown = False
gDown = False

while True:

	# get all the user events
	for event in pygame.event.get():
		#if the user wants to quit
		if event.type == QUIT:
			print("Stopping")
			pygame.quit()
			arduino.close()
		elif event.type == KEYUP:
			if event.key == K_a:
				aDown = False
			elif event.key == K_d:
				dDown = False
			elif event.key == K_w:
				wDown = False
			elif event.key == K_s:
				sDown = False
			elif event.key == K_f:
				fDown = False
			elif event.key == K_h:
				hDown = False
			elif event.key == K_t:
				tDown = False
			elif event.key == K_g:
				gDown = False
		# 	arduino.write('r'.encode('utf-8'))
		elif event.type == KEYDOWN:
			if event.key == K_r:
				arduino.write('r'.encode('utf-8'))
			elif event.key == K_a:
				aDown = True
			elif event.key == K_d:
				dDown = True
			elif event.key == K_w:
				wDown = True
			elif event.key == K_s:
				sDown = True
			elif event.key == K_f:
				fDown = True
			elif event.key == K_h:
				hDown = True
			elif event.key == K_t:
				tDown = True
			elif event.key == K_g:
				gDown = True

	if aDown:
		arduino.write('a'.encode('utf-8'))
	if dDown:
		arduino.write('d'.encode('utf-8'))
	if wDown:
		arduino.write('w'.encode('utf-8'))
	if sDown:
		arduino.write('s'.encode('utf-8'))
	if fDown:
		arduino.write('f'.encode('utf-8'))
	if hDown:
		arduino.write('h'.encode('utf-8'))
	if tDown:
		arduino.write('t'.encode('utf-8'))
	if gDown:
		arduino.write('g'.encode('utf-8'))


	sleep(0.01)

	# pygame.display.update()

	# line = ser.readline()
	# if line:
	# 	words = str(line).split(' ')
	# 	if 'width' in str(line):
	# 		x_pos = words[7]
	# 		y_pos = words[9]
	# 		print('x: ' + x_pos + '; y: ' + y_pos)
	# else :
	# 	print('YOU LOSE')







