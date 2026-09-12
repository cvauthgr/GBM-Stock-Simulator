# GBM Stock Simulator

![C++20](https://img.shields.io/badge/C%2B%2B20-00599C?logo=cplusplus&logoColor=white)
![GCC](https://img.shields.io/badge/GCC-4EAA25?logo=gnu&logoColor=white)
![gnuplot](https://img.shields.io/badge/gnuplot-white?logo=gnuplot&logoColor=black)

A small C++20 stock price simulator inspired by Geometric Brownian Motion.

The simulator generates a sequence of stock prices using a drift rate, volatility and normally distributed random shocks.

## Build and run

Requires GCC, Make and optionally gnuplot for plotting.

```bash
cd <desired-dir>
git clone https://github.com/cvauthgr/GBM-Stock-Simulator
cd GBM-Stock-Simulator
make
./main
```

The current simulation is initialized with:

```cpp
createSimulationObject(252, 100, 0.35);
```

Where the arguments represent:

```text
Number of values
Starting stock price
Starting volatility
```

The generated prices are written to:

```text
SimulatedStockSnapshot.txt
```

## Plotting

After running the simulation (!!!IMPORTANT!!!) : 
Otherwise gnuplot won't be able to find the .txt it
is pointed to and error out .

```bash
make plot
```

This plots the generated stock path from `SimulatedStockSnapshot.txt` using gnuplot.

### Plot examples 

| Low Volatility(0.2) | High Volatility(0.9) |
|---|---|
| <img width="1295" height="924" alt="image" src="https://github.com/user-attachments/assets/3149ede0-0fe2-4487-8b30-9678e6076971" /> | <img width="1295" height="924" alt="image" src="https://github.com/user-attachments/assets/7b9e74a4-1bcb-42b9-8cf0-018ab729d654" /> |

## Example

```text
Price : 98.9836 , index : 1
Price : 99.3271 , index : 2
Price : 100.041 , index : 3
...


````
