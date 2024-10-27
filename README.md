**Philosophers**

### Description

The **Philosophers** project is a concurrency-based simulation in C that demonstrates the famous "Dining Philosophers" problem. This classic scenario requires a group of philosophers to alternate between thinking, eating, and sleeping at a shared table where forks are limited, creating a need for synchronized access to resources. The project uses threads and mutexes to prevent data races and ensure that philosophers can “eat” without interference, highlighting fundamental concepts in thread management and synchronization.

### Key Features

- **Simulated Dining**: Each philosopher must pick up two forks (one on each side) to eat, but only one fork is available between each pair of philosophers, leading to potential deadlocks and starvation without proper resource management.
- **Concurrency Management**: Implements threads to represent each philosopher and mutexes to control access to shared resources (forks).
- **Dynamic Timings**: Uses user-defined arguments to adjust the number of philosophers, time to die, time to eat, and time to sleep, creating flexible simulations.
- **Exit Conditions**: The simulation stops when a philosopher dies of starvation or, optionally, when each philosopher has eaten a specified number of times.

### Program Arguments

- **number_of_philosophers**: The number of philosophers (and forks) at the table.
- **time_to_die**: Maximum time (in milliseconds) a philosopher can go without eating before starving.
- **time_to_eat**: Time (in milliseconds) it takes a philosopher to eat, requiring both forks.
- **time_to_sleep**: Duration (in milliseconds) for a philosopher to sleep.
- **[number_of_times_each_philosopher_must_eat]** *(optional)*: Simulation ends when each philosopher has eaten this many times.

### Example Usage

To compile and run the program:

1. **Compile** using the provided `Makefile`:
   ```bash
   make
   ```

2. **Run** the program with arguments:
   ```bash
   ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
   ```

   Example:
   ```bash
   ./philo 5 800 200 200
   ```

### Log Formatting

Each state change of a philosopher is logged in real-time:
- `timestamp_in_ms X has taken a fork`
- `timestamp_in_ms X is eating`
- `timestamp_in_ms X is sleeping`
- `timestamp_in_ms X is thinking`
- `timestamp_in_ms X died`

*(Where `timestamp_in_ms` is the current timestamp, and `X` is the philosopher number)*.
