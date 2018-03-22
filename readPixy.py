from serial import Serial
ser = Serial('/dev/cu.usbmodem1411', 9600, timeout=2)

print("connected to: " + ser.portstr)

while True:
  line = ser.readline()
  if line:
    words = str(line).split(' ')
    if 'width' in str(line):
      x_pos = words[7]
      y_pos = words[9]
      print('x: ' + x_pos + '; y: ' + y_pos)
  else :
    print('YOU LOSE')
ser.close()