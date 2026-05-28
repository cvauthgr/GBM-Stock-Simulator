# GBM Stock Simulator

A C++23 simulation of a one-year stock price path using **Geometric Brownian Motion (GBM)** with **stochastic volatility**. This project generates realistic stock price trajectories by modeling price movements with time-varying volatility, making it useful for quantitative finance research, risk analysis, and derivative pricing.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Theory](#theory)
  - [Geometric Brownian Motion](#geometric-brownian-motion)
  - [Stochastic Volatility](#stochastic-volatility)
  - [Mathematical Formula](#mathematical-formula)
- [Use Cases](#use-cases)
- [Requirements](#requirements)
- [Installation & Build](#installation--build)
- [Usage](#usage)
  - [Basic Usage](#basic-usage)
  - [Configuration Parameters](#configuration-parameters)
  - [Output](#output)
- [Project Structure](#project-structure)
- [Examples](#examples)
  - [Example 1: Standard Stock Simulation](#example-1-standard-stock-simulation)
  - [Example 2: Customizing Parameters](#example-2-customizing-parameters)
- [Technical Details](#technical-details)
  - [Random Number Generation](#random-number-generation)
  - [Drift Rate Calculation](#drift-rate-calculation)
  - [Volatility Movement Model](#volatility-movement-model)
- [Visualizing Results](#visualizing-results)
- [License](#license)

---

## Overview

This simulator generates realistic stock price paths by combining:

1. **Geometric Brownian Motion** - A standard mathematical model for stock price dynamics
2. **Stochastic Volatility** - Volatility that changes over time, reflecting real market behavior (e.g., volatility clustering)

The simulator produces a 252-day trading year simulation with daily price points, capturing both expected drift and random market shocks.

---

## Features

✨ **Core Features:**

- **GBM with Stochastic Volatility** - Models realistic stock price movements with time-varying volatility
- **C++23 Implementation** - Modern C++ features with optimized performance
- **Configurable Parameters** - Easy to adjust number of trading days, starting price, and initial volatility
- **Random Number Generation** - Thread-safe MT19937-64 for high-quality randomness
- **Data Export** - Output simulation results to files for analysis
- **Real-time Output** - Console display of simulated price paths
- **Visualization Ready** - Gnuplot integration for generating price path charts
- **Multi-threaded Compatible** - Thread-local random generation prevents race conditions

---

## Theory

### Geometric Brownian Motion

**What is GBM?**

Geometric Brownian Motion is a stochastic differential equation commonly used in quantitative finance to model stock prices. Unlike simple random walks, GBM ensures prices never go negative and exhibits realistic log-normal distribution of returns.

**The GBM Equation:**

```
dS = μS dt + σS dW
```

Where:
- **S** = Stock price
- **μ** = Drift rate (expected return)
- **σ** = Volatility (standard deviation of returns)
- **dt** = Small time increment
- **dW** = Wiener process (random shock)

**Discrete Solution (Euler Scheme):**

The continuous equation is discretized for simulation:

```
S(t+Δt) = S(t) × exp[(μ × Δt) + (σ × √Δt × ε)]
```

Where:
- **ε** = Standard normal random variable N(0,1)
- **Δt** = Time step (1/252 for daily data in annual simulation)

**Key Properties:**
- Prices are always positive (log-normal distribution)
- Returns follow a normal distribution
- Mean-reverting under certain parameters
- Captures geometric growth patterns

### Stochastic Volatility

**What is Stochastic Volatility?**

Standard GBM assumes constant volatility, but real markets exhibit **volatility clustering** - periods of high volatility followed by low volatility, and vice versa. Stochastic volatility models this phenomenon by allowing volatility to change over time.

**The Volatility Model (This Implementation):**

The simulator implements a probabilistic volatility jump model:

```
1. Generate random probability P ∈ [0, 1]
2. Calculate shock magnitude: Shock = σ × √(Δt)
3. Apply volatility adjustment:
   - If P ≤ 0.68: σ → σ + 1 × Shock × fairChance()
   - If P ≤ 0.95: σ → σ + 2 × Shock × fairChance()
   - If P ≤ 0.99: σ → σ + 3 × Shock × fairChance()
   - If P > 0.99: σ → σ + 4 × Shock × fairChance()
```

Where `fairChance()` returns either +Shock or -Shock with equal probability.

**Why This Matters:**
- Captures volatility clustering observed in real markets
- Produces more realistic price paths than constant volatility
- Useful for pricing exotic derivatives and risk management

### Mathematical Formula

**Combined Price Update Formula Used:**

```
σ(t+Δt) = σ(t) + ε₁ × √(Δt)  [Volatility evolution]

S(t+Δt) = S(t) × e^[(μ × Δt) + (σ(t) × √(Δt) × ε₂)]  [Price update]
```

Where:
- **ε₁** = Random shock to volatility (with probability weighting)
- **ε₂** = Standard normal random variable for price shock
- Both are independent random processes

**Drift Rate:**

The drift rate (μ) is randomly sampled from a normal distribution:
```
μ ~ N(0.1, 0.05²)
```
This represents an expected annual return of approximately 10% with realistic variation.

---

## Use Cases

### 1. **Quantitative Finance Research**
   - Validate pricing models for derivatives
   - Backtest trading strategies
   - Study market behavior under different volatility regimes

### 2. **Risk Management**
   - Value-at-Risk (VaR) estimation
   - Stress testing portfolios
   - Calculate optimal portfolio allocation

### 3. **Options Pricing**
   - Generate paths for Monte Carlo methods (European/American options)
   - Estimate implied volatility surfaces
   - Study volatility smile effects

### 4. **Portfolio Analysis**
   - Multi-asset simulations (extend for multiple stocks)
   - Correlation analysis between price movements
   - Performance attribution analysis

### 5. **Academic Research**
   - Study stochastic processes
   - Validate financial models
   - Develop new pricing methodologies

---

## Requirements

- **C++23** compiler support
- **Windows OS** (Gnuplot plotting features use Windows-specific APIs)
- **Gnuplot** (optional, for visualization)
- **CMake** 3.20+ (recommended for building)

**Compiler Support:**
- MSVC 2022 or later
- GCC 13+ (with C++23 support)
- Clang 16+ (with C++23 support)

---

## Installation & Build

### 1. Clone the Repository

```bash
git clone https://github.com/cvauthgr/GBM-Stock-Simulator.git
cd GBM-Stock-Simulator
```

### 2. Build the Project

**Using a compiler with C++23 support:**

```bash
# MSVC (Windows)
cl /std:c++latest /EHsc src/main.cpp /Fe:GBMSimulator.exe

# GCC (Linux/MinGW)
g++ -std=c++23 -O3 src/main.cpp -o GBMSimulator

# Clang
clang++ -std=c++23 -O3 src/main.cpp -o GBMSimulator
```

**Using CMake (if CMakeLists.txt is provided):**

```bash
mkdir build
cd build
cmake .. -DCMAKE_CXX_STANDARD=23
cmake --build . --config Release
```

### 3. Optional: Install Gnuplot

For visualization support:
```bash
# Windows (using choco or download from gnuplot.info)
choco install gnuplot

# Linux
sudo apt-get install gnuplot

# macOS
brew install gnuplot
```

---

## Usage

### Basic Usage

The simulator is designed for easy configuration. Modify parameters in `src/main.cpp`:

```cpp
auto simulationObject = createSimulationObject(
    252,      // Number of trading days (1 year)
    100.0,    // Starting stock price ($100)
    0.35      // Initial volatility (35% annualized)
);

simulationObject.executeSimulation();           // Run simulation
simulationObject.printStockPriceAndTimeIndex(); // Print to console
simulationObject.writeStockDataToFile();        // Save to file
```

### Configuration Parameters

| Parameter | Type | Range | Description |
|-----------|------|-------|-------------|
| `numberOfDays` | `int` | 1-1000+ | Number of trading days to simulate |
| `startingPrice` | `double` | >0 | Initial stock price |
| `initialVolatility` | `double` | 0.01-2.0 | Starting volatility (0.35 = 35%) |

### Output

**Console Output:**
```
Price : 101.245 , index : 1
Price : 100.856 , index : 2
Price : 102.134 , index : 3
...
```

**File Output:**
`SimulatedStockSnapshot.txt` - Contains one price per line, formatted for Gnuplot visualization.

---

## Project Structure

```
GBM-Stock-Simulator/
├── src/
│   └── main.cpp                    # Main program entry point
├── header files/
│   ├── stockSimulation.h           # GBM simulator class
│   └── RandomGeneration.h          # Random number generation utilities
├── README.md                       # This file
├── LICENSE                         # MIT License
└── SimulatedStockSnapshot.txt      # Generated output (after running)
```

**File Descriptions:**

- **main.cpp** - Entry point that creates simulation object, executes simulation, and handles Gnuplot visualization
- **stockSimulation.h** - Core `stockPriceSimulator` class implementing GBM with stochastic volatility
- **RandomGeneration.h** - Thread-safe random number generation utilities using MT19937-64

---

## Examples

### Example 1: Standard Stock Simulation

**Scenario:** Simulate Apple stock over 252 trading days starting at $150 with 25% volatility.

**Code:**
```cpp
#include "stockSimulation.h"

int main() {
    // Create simulation object
    auto apple_sim = createSimulationObject(
        252,      // 1 year of trading days
        150.0,    // Starting price: $150
        0.25      // Starting volatility: 25%
    );
    
    // Execute the simulation
    apple_sim.executeSimulation();
    
    // Print results to console
    apple_sim.printStockPriceAndTimeIndex();
    
    // Save to file for analysis
    apple_sim.writeStockDataToFile();
    
    return 0;
}
```

**Expected Output:**
```
Price : 150.234 , index : 1
Price : 151.567 , index : 2
Price : 149.876 , index : 3
...
Price : 152.432 , index : 252
```

**Analysis:**
- Starting price: $150
- Expected final price range: $135-$175 (based on normal GBM statistics)
- Volatility will fluctuate around 25%, creating realistic price clustering

---

### Example 2: Customizing Parameters for High Volatility

**Scenario:** Model a volatile penny stock with high initial volatility.

**Code:**
```cpp
#include "stockSimulation.h"

int main() {
    // Penny stock simulation
    auto penny_stock = createSimulationObject(
        252,      // 1 year
        5.0,      // Starting price: $5.00
        0.75      // High volatility: 75%
    );
    
    penny_stock.executeSimulation();
    penny_stock.writeStockDataToFile();
    
    // Process and analyze results
    auto prices = penny_stock.getStockValues();
    double min_price = prices[0].first;
    double max_price = prices[0].first;
    
    for (auto [price, day] : prices) {
        min_price = std::min(min_price, price);
        max_price = std::max(max_price, price);
    }
    
    std::cout << "Min Price: $" << min_price << '\n';
    std::cout << "Max Price: $" << max_price << '\n';
    std::cout << "Range: $" << (max_price - min_price) << '\n';
    
    return 0;
}
```

**Expected Output:**
```
Min Price: $2.145
Max Price: $8.234
Range: $6.089
```

---

## Technical Details

### Random Number Generation

The simulator uses **MT19937-64** (Mersenne Twister) for high-quality random number generation:

```cpp
// From RandomGeneration.h
thread_local std::mt19937_64 mt { generate() };

// Thread-safe seeding with 7 sources of entropy
std::seed_seq ss { rd(), rd(), rd(), rd(), rd(), rd(), rd() };
```

**Why MT19937-64?**
- Period of 2^19937-1 (extremely long, no repetition in practice)
- Fast generation of 64-bit random numbers
- Better statistical properties than simpler RNGs
- Thread-local ensures different random sequences per thread

### Drift Rate Calculation

The drift rate is sampled from a normal distribution at the start of each simulation:

```cpp
std::normal_distribution<double> driftRateDist(0.1, 0.05);
m_driftRate = driftRateDist(random::mt);
```

**Parameters:**
- **Mean (μ)** = 0.1 (10% expected annual return)
- **Std Dev (σ)** = 0.05 (5% variation)

This models realistic equity returns with variation across different market conditions.

### Volatility Movement Model

The stochastic volatility mechanism uses probability-weighted jumps:

```cpp
void volatilityMovement() {
    double randomChance = random::getReal(0.0, 1.0);
    double suddenVolatilityMovement = m_volatility * std::sqrt(m_dt);
    
    if (m_volatility < 1 && m_volatility > 0) {
        if (randomChance <= 0.68)
            m_volatility += 1 * random::fairChance(suddenVolatilityMovement);
        else if (randomChance <= 0.95)
            m_volatility += 2 * random::fairChance(suddenVolatilityMovement);
        else if (randomChance <= 0.99)
            m_volatility += 3 * random::fairChance(suddenVolatilityMovement);
        else
            m_volatility += 4 * random::fairChance(suddenVolatilityMovement);
    }
}
```

**Interpretation:**
- 68% of the time: Small volatility change (±1σ)
- 27% of the time: Medium change (±2σ)
- 4% of the time: Large change (±3σ)
- 1% of the time: Very large change (±4σ)

This distribution mirrors real-world volatility clustering with rare extreme events.

---

## Visualizing Results

### Using Gnuplot (Windows)

The program includes Gnuplot integration. Uncomment the visualization code:

```cpp
// In main.cpp, change from:
#define EXTERNALREQUEST

// To:
// #define EXTERNALREQUEST
```

Then run the program:
```bash
GBMSimulator.exe
```

This will launch a Gnuplot window showing the simulated stock price path with:
- Black background and red price line
- White axes and labels
- 800x600 resolution

### Manual Visualization

Alternatively, use Gnuplot directly:

```bash
gnuplot> set terminal png
gnuplot> set output "stock_path.png"
gnuplot> plot "SimulatedStockSnapshot.txt" with lines title "Stock Price Path"
gnuplot> exit
```

Or with Python/Matplotlib:

```python
import matplotlib.pyplot as plt

prices = [float(line.strip()) for line in open("SimulatedStockSnapshot.txt")]
days = range(1, len(prices) + 1)

plt.figure(figsize=(12, 6))
plt.plot(days, prices, linewidth=1.5, color='blue')
plt.xlabel("Trading Day")
plt.ylabel("Stock Price ($)")
plt.title("Simulated Stock Price Path (GBM with Stochastic Volatility)")
plt.grid(True, alpha=0.3)
plt.savefig("stock_simulation.png", dpi=150)
plt.show()
```

---

## Performance Characteristics

| Metric | Value |
|--------|-------|
| Time Step Size | 1/252 (daily) |
| Number of Pricing Updates | Configurable (typically 252) |
| Random Numbers per Day | 2 (volatility shock, price shock) |
| Memory Usage (252 days) | ~4 KB (pairs of price + index) |
| Typical Execution Time | <1ms on modern CPU |

---

## Extending the Simulator

### Multi-Asset Simulation

To simulate multiple correlated stocks:

```cpp
class portfolioSimulator {
    std::vector<stockPriceSimulator> stocks;
    
    void simulateWithCorrelation(double correlation) {
        // Correlate shocks between assets
    }
};
```

### Different Volatility Models

Replace `volatilityMovement()` with:
- **ARCH/GARCH Models** - More sophisticated volatility clustering
- **Heston Model** - Volatility mean-reverting process
- **Jump-Diffusion** - Sudden price jumps with volatility

### Variance Reduction Techniques

Implement for faster convergence:
- **Antithetic Variates** - Reduce variance by pairing paths
- **Control Variates** - Use known analytical solutions as reference
- **Stratified Sampling** - Ensure uniform coverage of probability space

---

## Troubleshooting

### Issue: "C++23 not supported by compiler"
**Solution:** Update your compiler or use `-std=c++2b` for experimental support.

### Issue: "Cannot find windows.h"
**Solution:** This is Windows-specific. For cross-platform builds, wrap in `#ifdef _WIN32`.

### Issue: Gnuplot window doesn't appear
**Solution:** Ensure Gnuplot is installed and in PATH. Manually run Gnuplot visualization commands.

### Issue: Random results are identical across runs
**Solution:** The random seed is derived from `std::random_device`. Try adding time-based seeding.

---

## References & Further Reading

### Academic Papers
- **Black, F., & Scholes, M. (1973).** "The Pricing of Options and Corporate Liabilities." *Journal of Political Economy*
- **Hull, J. C. (2018).** "Options, Futures, and Other Derivatives" (10th ed.)
- **Heston, S. L. (1993).** "A Closed-Form Solution for Options with Stochastic Volatility"

### Related Concepts
- Brownian Motion and Stochastic Calculus
- Itô's Lemma
- Risk-neutral pricing
- Monte Carlo methods
- Volatility smile and surface

### Online Resources
- [Investopedia: Geometric Brownian Motion](https://www.investopedia.com/)
- [Wikipedia: Brownian Motion](https://en.wikipedia.org/wiki/Brownian_motion)
- [QuantPie: GBM Simulation](https://en.wikipedia.org/wiki/Geometric_Brownian_motion)

---

## Contributing

Contributions are welcome! Areas for enhancement:
- [ ] Multi-asset portfolio simulation
- [ ] Alternative volatility models (Heston, SABR)
- [ ] Output to financial data formats (CSV, JSON)
- [ ] Performance optimization with SIMD
- [ ] GUI for parameter configuration
- [ ] Cross-platform Gnuplot support

To contribute:
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit changes (`git commit -m 'Add amazing feature'`)
4. Push to branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

---

## License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

MIT License permits:
- ✅ Commercial use
- ✅ Modification
- ✅ Distribution
- ✅ Private use

With conditions:
- ℹ️ License and copyright notice required

---

## Disclaimer

This simulator is for **educational and research purposes only**. While based on established financial models, real market behavior is far more complex. Do not use this for actual trading or investment decisions without:

1. Professional validation
2. Proper risk management
3. Regulatory compliance
4. Realistic parameter calibration to market data

**Past simulations do not guarantee future results.**

---

## Contact & Support

For questions, issues, or suggestions:
- Open an issue on GitHub
- Contact the maintainer: [@cvauthgr](https://github.com/cvauthgr)

---

**Last Updated:** May 2026

**Version:** 1.0.0
