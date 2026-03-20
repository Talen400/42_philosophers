# 🍝 Philosophers

> The Dining Philosophers Problem — implemented in C with two concurrency models: threads (mandatory) and processes (bonus).  
> Developed at [42 São Paulo](https://www.42sp.org.br/).

---

## 📋 Table of Contents

- [The Problem](#the-problem)
- [Two Implementations](#two-implementations)
- [Architecture](#architecture)
- [Concurrency Design](#concurrency-design)
- [The ft_usleep Problem](#the-ft_usleep-problem)
- [How to Build & Run](#how-to-build--run)
- [Usage Examples](#usage-examples)
- [Author](#author)

---

## The Problem

The [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) is a classic concurrency challenge: N philosophers sit around a circular table. Between each pair of adjacent philosophers lies a single fork. To eat, a philosopher needs **two forks** — the one on their left and the one on their right.

The challenge is to coordinate access to the forks so that:

- No philosopher **starves** (goes without eating for longer than `time_to_die` ms)
- No **deadlock** occurs (all philosophers waiting for each other forever)
- No **data race** corrupts shared state

```
        [Philo 1]
       /          \
   fork 5        fork 1
     /                \
[Philo 5]          [Philo 2]
     \                /
   fork 4        fork 2
       \          /
        [Philo 4]--fork 3--[Philo 3]
```

---

## Two Implementations

This project includes **two complete and independent implementations**:

| | Mandatory (`philo/`) | Bonus (`philo_bonus/`) |
|---|---|---|
| **Concurrency model** | Threads (`pthread`) | Processes (`fork`) |
| **Forks** | One `pthread_mutex_t` per fork | One named semaphore (`/philo_forks`, value = N) |
| **Shared state** | Shared memory (same process) | Named semaphores |
| **Monitor** | One dedicated thread monitors all philosophers | Each process spawns its own monitor thread |
| **Death signal** | Monitor sets `someone_died` flag, all threads check it | Dying process `exit(1)`, parent `waitpid` kills the rest |
| **Synchronization primitives** | `pthread_mutex_t` | `sem_t` (POSIX named semaphores) |

---

## Architecture

```
philo/
├── src/
│   ├── main.c          # Entry point: spawns threads + monitor, joins all
│   ├── init.c          # Init forks (mutexes), philosophers, global mutexes
│   ├── routine.c       # Philosopher lifecycle: think → eat → sleep
│   ├── monitor.c       # Dedicated monitor thread: checks death & meal count
│   ├── forks.c         # take_forks() / drop_forks()
│   ├── destroy.c       # Cleanup: destroy mutexes and free memory
│   ├── parse.c         # Argument validation and parsing
│   └── utils.c         # ft_gettime(), ft_usleep(), print_status(), print_death()
└── includes/
    └── philo.h

philo_bonus/
├── src/
│   ├── main_bonus.c    # Entry point: fork() per philosopher, waitpid()
│   ├── init_bonus.c    # Init semaphores + philosopher structs
│   ├── process_bonus.c # Philosopher process: spawns monitor thread, runs loop
│   ├── monitor_bonus.c # Monitor thread per process: checks own death
│   ├── semaphores_bonus.c  # sem_open() for all 4 semaphores
│   ├── destroy_bonus.c # sem_close() + sem_unlink() cleanup
│   ├── parse.c         # Same argument validation
│   └── utils_bonus.c   # ft_gettime(), ft_usleep(), print_status(), print_death()
└── includes/
    └── philo_bonus.h
```

---

## Concurrency Design

### Mandatory — Threads + Mutexes

Each philosopher is a **POSIX thread**. Forks are stored as an array of `pthread_mutex_t`, one per fork, and each philosopher holds a pointer to their `left_fork` and `right_fork`:

```c
philos[i].left_fork  = &data->forks[i];
philos[i].right_fork = &data->forks[(i + 1) % data->n_philo];
```

Three global mutexes protect shared state:

| Mutex | Purpose |
|---|---|
| `write_lock` | Serializes all `printf` calls — prevents interleaved output |
| `dead_lock` | Protects `someone_died` and `all_ate_enough` flags |
| `meal_lock` | Protects `last_meal_time` and `meals_eaten` per philosopher |

A dedicated **monitor thread** runs concurrently with all philosopher threads. It polls every 1ms, checking two conditions for every philosopher:

```c
// Death check
time_since_meal = ft_gettime() - philos[i].last_meal_time;
if (time_since_meal > data->die) → print death, set someone_died = TRUE

// Meal completion check (if must_eat is set)
if (all philos have meals_eaten > must_eat) → set all_ate_enough = TRUE
```

Philosopher threads check `should_stop()` at the start of each loop iteration and between actions:

```c
int should_stop(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->dead_lock);
    stop = (philo->data->someone_died || philo->data->all_ate_enough);
    pthread_mutex_unlock(&philo->data->dead_lock);
    return (stop);
}
```

**Deadlock prevention:** even-numbered philosophers wait 1ms before their first action, staggering fork access so odd and even philosophers are never competing for the same pair simultaneously:

```c
if (philo->id % 2 != 1)
    ft_usleep(1);
```

**Edge case — 1 philosopher:** handled explicitly. With only one philosopher there is only one fork — they pick it up, wait `time_to_die` ms, and die. No infinite loop, no deadlock.

---

### Bonus — Processes + Named Semaphores

Each philosopher is a **child process** created with `fork()`. Since processes don't share memory, synchronization uses **named POSIX semaphores** (visible across processes via the filesystem):

| Semaphore | Initial value | Purpose |
|---|---|---|
| `/philo_forks` | N (number of philosophers) | Represents all forks on the table — picking up 2 forks = 2 `sem_wait` |
| `/philo_write` | 1 | Serializes `printf` (binary semaphore) |
| `/philo_dead` | 1 | Protects the death/meal-count flag |
| `/philo_meal` | 1 | Protects `last_meal_time` |

Each philosopher process spawns its **own monitor thread** that watches only itself:

```c
// Inside each child process
pthread_create(&monitor, NULL, monitor_thread, philo);
pthread_detach(monitor);
// monitor_thread: if (time_since_meal > die) → print death, exit(1)
```

The **parent process** calls `waitpid(-1, &status, 0)` in a loop. As soon as any child exits with status `1` (death), the parent sends `SIGKILL` to all remaining children:

```c
if (WEXITSTATUS(status) == 1)
{
    someone_died = TRUE;
    kill_all_processes(philos, data->n_philo);
    break;
}
```

Semaphores are unlinked before creation (`sem_unlink`) to avoid stale state from a previous interrupted run.

---

## The ft_usleep Problem

The standard `usleep()` is **imprecise** — on a loaded system, it can overshoot by several milliseconds. For a philosopher simulation where `time_to_die` might be as low as 60ms, this drift can cause false deaths.

The solution is a **calibrated busy-wait loop** using `gettimeofday`:

```c
void ft_usleep(long ms)
{
    long start = ft_gettime();
    while (1)
    {
        long elapsed   = ft_gettime() - start;
        long remaining = ms - elapsed;
        if (remaining <= 0)
            break;
        else if (remaining > 1)
            usleep(100);   // coarse: ~0.1ms granularity
        else
            usleep(10);    // fine: ~0.01ms granularity for last ms
    }
}
```

This avoids spinning the CPU unnecessarily while still achieving sub-millisecond accuracy. `ft_gettime()` returns UNIX time in **milliseconds**:

```c
long ft_gettime(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
```

---

## How to Build & Run

### Prerequisites

- `gcc` or `cc`
- `make`
- POSIX threads (`-lpthread`)

### Build

```bash
# Mandatory version (threads)
make

# Bonus version (processes + semaphores)
make bonus

# Clean
make clean
make fclean
make re
```

### Run

```bash
# Mandatory
./philo <n_philos> <time_to_die> <time_to_eat> <time_to_sleep> [must_eat_count]

# Bonus
./philo_bonus <n_philos> <time_to_die> <time_to_eat> <time_to_sleep> [must_eat_count]
```

| Argument | Description |
|---|---|
| `n_philos` | Number of philosophers (and forks) |
| `time_to_die` | Milliseconds a philosopher can go without eating before dying |
| `time_to_eat` | Milliseconds it takes to eat |
| `time_to_sleep` | Milliseconds it takes to sleep |
| `must_eat_count` | *(optional)* Simulation stops when all philosophers have eaten this many times |

---

## Usage Examples

```bash
# 5 philosophers — should not die
./philo 5 800 200 200

# Stop after each philosopher eats 7 times
./philo 5 800 200 200 7

# Stress test — tight timing
./philo 4 410 200 200

# Edge case — single philosopher (always dies)
./philo 1 800 200 200

# Bonus version
./philo_bonus 5 800 200 200 7
```

### Expected output format

```
<timestamp_ms> <philo_id> <status>

0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 2 has taken a fork
...
310 3 died
```

No log line should appear more than 10ms after the actual event. Once a philosopher dies, no further output should appear.

---

## Author

| Login | School |
|---|---|
| **tlavared** | 42 São Paulo |

---

*Built as part of the 42 Common Core curriculum — November / December 2025.*