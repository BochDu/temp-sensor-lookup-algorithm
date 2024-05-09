import csv
import matplotlib.pyplot as plt

# 打开CSV文件
with open('temp.csv', newline='') as csvfile:
    reader = csv.reader(csvfile)
    data = list(reader)

# 默认列名
header = ['Temperature', 'Rmax', 'Rave', 'Rmin']

# 获取不同温度下的电阻值
temperature_index = 0
resistance1_index = 1
resistance2_index = 2
resistance3_index = 3

temperatures = []
resistance1_values = []
resistance2_values = []
resistance3_values = []

for row in data:
    temperatures.append(float(row[temperature_index]))
    resistance1_values.append(float(row[resistance1_index]))
    resistance2_values.append(float(row[resistance2_index]))
    resistance3_values.append(float(row[resistance3_index]))

plt.figure(figsize=(10, 6))

# 绘制折线图
plt.plot(temperatures, resistance1_values, color='blue', label='Rmax')
plt.plot(temperatures, resistance2_values, color='red', label='Rave')
plt.plot(temperatures, resistance3_values, color='green', label='Rmin')

plt.xlabel('Temperature (Celsius)')
plt.ylabel('Resistance (kOhm)')
plt.title('Resistance vs Temperature')
plt.legend()
plt.grid(True)
plt.show()





