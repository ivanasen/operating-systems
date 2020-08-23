[Problems link](http://skelet.ludost.net/OS/problems/OS_K1_2018_theory.pdf)

## KN1

```python
# Inital
barrier_a = Semaphore(0)
sem_b = Semaphore(0)

# P
p_1
barrier_a.signal()
p_2
sem_b.wait()
p_3

# Q
q_1
barrier_a.wait()
barrier_a.signal()
q_2
q_3

# R
r_1
barrier_a.wait()
barrier_a.signal()
r_2
sem_b.signal()
r_3
```

## KN2

```python
# Initial
sem_a = Semaphore(0)
sem_b = Semaphore(0)
sem_c = Semaphore(0)
sem_dp = Semaphore(0)
sem_dq = Semaphore(0)

# P
p_1
sem_a.signal()
sem_c.wait()
p_2
sem_dp.signal()
p_3

# Q
q_1
sem_b.signal()
sem_a.wait()
q_2
sem_dq.signal()
q_3

# R
r_1
sem_c.signal()
sem_b.wait()
r_w
sem_dp.wait()
sem_dq.wait()
r_3
```

## SI

```python
#initial
sem_a = Semaphore(0)
sem_b = Semaphore(1)

# P
p_1
sem_b.wait()
p_2
sem_a.signal()
p_3

# Q
q_1
sem_b.wait()
q_2
sem_a.signal()
q_3

# R
r_1
sem_a.wait()
r_2
sem_b.signal()
r_3
```