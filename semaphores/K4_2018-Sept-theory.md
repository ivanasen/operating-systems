[Problems link](http://skelet.ludost.net/OS/problems/K4_2018-Sept-theory.pdf)

```python
# Initial
sem_1 = Semaphore(1)
sem_2 = Semaphore(0)
sem_3 = Semaphore(0)

# P
sem_1.wait()
    p_1
sem_2.signal()
p_2
sem_3.wait()
    p_3
sem_1.signal()

# Q
q_1
sem_2.wait()
    q_2
sem_3.signal()
q_3
```