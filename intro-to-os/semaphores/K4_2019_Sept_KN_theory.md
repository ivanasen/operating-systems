[Problems link](http://skelet.ludost.net/OS/problems/K4_2019_Sept_KN_theory.pdf)

```python
# Initial
sem = Semaphore(0)
mutex = Semaphore(1)
count = 0

# P
p_1
mutex.wait()
    count = count + 1
    if count == 3: sem.signal()
mutex.signal()
p_2

# Q
q_1
sem.wait()
sem.signal()
q_2
```