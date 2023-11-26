import serial
import numpy as np
import matplotlib.pyplot as plt

arduino = serial.Serial(port='COM8', baudrate=115200, timeout=.1)

row_size = 30
col_size = 30

rows = np.full((row_size, col_size), 255, dtype=float)

row1 = []
row2 = []
read = True
data = []
count = 0

while read:
    line = arduino.readline().decode('utf-8')
    if(len(line)>0):
        data = line.split('/')
        print(data)
        for x in data:
            if (len(x) > 0):                
                row1.append(float(x.split('*')[0]))
                row2.append(float(x.split('*')[1]))

            if len(row1) == col_size and len(row2) == col_size:
                # print(row1)
                # print(row2)
                if count%4 == 0:
                    rows[count, :] = row1
                    rows[count+1, :] = row2
                else:
                    rows[count, :] = list(reversed(row1))
                    rows[count+1, :] = list(reversed(row2))
                    
                count = count + 2
                row1 = []
                row2 = []

    if count >= 29:
        read = False

print(rows)
#temparr = [[180, 120, 100, 230], [3, 4, 2, 1], [9, 8, 7, 6], [5, 9, 10, 14]]

def greyscale(arr):
    arr[arr>20] = 255
    arr[arr<5] = 0
    result = np.interp(arr, [5, 20], [0, 255])
    return result
# row1 = greyscale(np.array(row1))
# row2 = greyscale(np.array(row2))

# rows = greyscale(rows)
np.savetxt("hifive.csv", rows, delimiter=",");
pixel_plot = plt.figure()

pixel_plot.add_subplot()
  
# customizing plot
plt.title("pixel_plot")
pixel_plot = plt.imshow(
   rows, cmap='gray', vmax= 255, vmin = 0, interpolation='nearest', aspect= 'auto')
  
plt.colorbar(pixel_plot)
  
# save a plot
plt.savefig('pixel_plot.png')
  
# show plot
plt.show()