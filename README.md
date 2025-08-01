# Delta Hedging

This repository demonstrates delta hedging strategies used in quantitative finance to reduce the directional risk of holding options. The project includes stock price simulations, option pricing using the Black-Scholes-Merton (BSM) model, delta-hedging portfolio construction, and performance analysis using given market data.

## Features

Simulates 1000 stock price paths using the stock_simulation class, utilizing Boost’s normal distribution.

Implements the BSM model in the BSM class for option pricing, delta calculation, and implied volatility estimation.

Constructs delta-hedging portfolios with the delta_hedge class and analyzes cumulative hedging errors.

Validates methods with real market data and includes unit tests to verify model accuracy.

## Usage

- Stock Price Simulation

`stock_simulation` generates 1000 price paths of length 101 using input parameters like S0, T, μ, σ, and N.

Results are saved in `stock_path.csv`, each row represents one path.

- Option Pricing (BSM)

The `BSM` class handles European option pricing with volatility inputs or infers implied volatility from market prices.

Includes functions `BSM_price()`, `BSM_delta()`, `BSM_iv()`.

Generates `option_path.csv` of simulated call option price paths.

- Delta Hedging

The `delta_hedge` class records BSM parameters and calculates cumulative hedging error using `hedge_error()`.

Output is saved in `hedging_error.csv`.

- Real Market Data Validation

Import interest, stock, and option data from CSV files.

Calculate implied volatility, delta, hedging error, PNL, and export results to `result.csv`.

- Unit Testing

Tests `BSM_price`, `BSM_delta`, and `BSM_iv` using known values.

Passes if absolute difference is ≤ 0.001.
