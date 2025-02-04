<h1 align="center">
	42 Project - Philosophers
</h1>

<p align="center">
	<b><i> I never thought philosophy would be so deadly </i></b>
</p>

<p align="center">
	<img src="https://raw.githubusercontent.com/ayogun/42-project-badges/refs/heads/main/badges/philosopherse.png" alt="philosophers_logo" />
</p>

---
<p align="center">
	<img src="https://img.shields.io/badge/Score-100-green?style=none&logo=42" alt="Score project : 100"/>
	<img alt="Static Badge" src="https://img.shields.io/badge/Outstanding-0-blue?style=none&logo=42">
	<img alt="GitHub repo size" src="https://img.shields.io/github/repo-size/LeSabreDeDieu/philosopher?style=none&logo=github">
</p>

## Description
Philosopher is a project that implements the Dining Philosophers problem, a classic synchronization problem used to illustrate issues in concurrent programming and resource allocation.

## Installation
Clone this repository and compile the project:
```bash
git clone https://github.com/LeSabreDeDieu/philosopher.git
cd philosopher/philo
make
```

## Usage
To run the program, use the following command:
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
- `<number_of_philosophers>` : The number of philosophers and forks.
- `<time_to_die>` : Time in milliseconds after which a philosopher dies if they haven't started eating.
- `<time_to_eat>` : Time in milliseconds it takes for a philosopher to eat.
- `<time_to_sleep>` : Time in milliseconds a philosopher spends sleeping.
- `[number_of_times_each_philosopher_must_eat]` (optional) : If all philosophers have eaten at least this many times, the simulation ends.

Example :
```bash
./philo 5 800 200 200
```

## Problem Description
In the Dining Philosophers problem, n philosophers sit at a table with n forks. Each philosopher must alternately think, eat and sleep. However, a philosopher can only eat when they have both the left and right forks. The challenge is to design a protocol that ensures no philosopher starves and that the program avoids deadlock and livelock situations.
