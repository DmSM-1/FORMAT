import matplotlib.pyplot as plt
with open('data.txt') as f:
    arr = [i.split(' ') for i in f]
for i in range(len(arr)):
    arr[i][0] = float(arr[i][0])
    arr[i][1] = float(arr[i][1][:-1])
a = [i[0] for i in arr]
b = [i[1] for i in arr]


plt.plot(a[::2],b[::2])
plt.plot(a[1::2],b[1::2])
plt.savefig(input())
#plt.show()
