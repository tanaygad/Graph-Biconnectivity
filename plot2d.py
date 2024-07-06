import matplotlib.pyplot as plt
    
X = [9,30,50,70,99,300,500,700,999,3000,5000,7000,9999,30000,50000,70000,99999,300000,500000,700000]
tarjan = []
tv = []
tvdsu = []
tvnp = []
    
with open('tarjan.txt', 'r') as f:
    for line in f:
        tarjan.append(float(line.split()[0]))
    
with open('tv.txt', 'r') as f:
    for line in f:
        tv.append(float(line.split()[0]))
    
with open('tvdsu.txt', 'r') as f:
    for line in f:
        tvdsu.append(float(line.split()[0]))
    
with open('tvnp.txt', 'r') as f:
    for line in f:
        tvnp.append(float(line.split()[0]))
    
plt.plot(X, tarjan, label='Tarjan')
plt.plot(X, tv, label='TV')
plt.plot(X, tvdsu, label='TVDSU')
plt.plot(X, tvnp, label='TVNP')
    
plt.xlabel('Number of Edges')
plt.ylabel('Time (s)')
plt.title('Execution Time')
plt.legend()
plt.show()
    
plt.plot(X, tarjan, label='Tarjan')
plt.plot(X, tv, label='TV')
plt.plot(X, tvdsu, label='TVDSU')
plt.plot(X, tvnp, label='TVNP')
    
plt.xlabel('Number of Edjes')
plt.ylabel('Time (s)')
plt.xscale('log')
plt.title('Execution Time')
plt.legend()
plt.show()