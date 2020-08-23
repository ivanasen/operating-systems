[Problems link](http://skelet.ludost.net/OS/problems/OS_2019_KN_SI_theory.pdf)

## Problem 4, SI:

```python
# Initial
sem_1 = Semaphore(0)
sem_2 = Semaphore(0)

# P
p_1
sem_1.signal()
sem_2.wait()
p_2
sem_1.signal()
sem_2.wait()
p_3

# Q
q_1
sem_2.signal()
sem_1.wait()
q_2
sem_2.signal()
sem_1.wait()
q_3
```

## Problem 4, KN1:

```python
# Initial
sem_1 = Semaphore(0)
sem_2q = Semaphore(0)
sem_2r = Semaphore(0)

# P
sem_1.signal()
p_1
p_2
sem_2q.wait()
sem_2r.wait()
p_3

# Q
q_1
sem_1.wait()
sem_1.signal()
q_2
sem_2q.signal()
q_3

# R
r_1
sem_1.wait()
sem_1.signal()
r_2
sem_2r.signal()
r_3
```

## Problem 4, KN2:

```python
# Initial
sem_1 = Semaphore(1)
sem_2 = Semaphore(0)
sem_3 = Semaphore(0)

# P
sem_1.wait()
p_1
sem_2.signal()
sem_1.wait()
p_2
sem_2.signal()

# Q
sem_2.wait()
q_1
sem_3.signal()
sem_2.wait()
q_2
sem_3.signal()

# R
sem_3.wait()
r_1
sem_1.signal()
sem_3.wait()
r_2
sem_1.signal()
```