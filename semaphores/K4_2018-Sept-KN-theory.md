[Problems link](http://skelet.ludost.net/OS/problems/K4_2018-Sept-KN-theory.pdf)

```python
# Initial
sem_1 = Semaphore(0)
sem_2 = Semaphore(1)

# P
sem_2.wait()
p_1
sem_1.signal()
sem_2.wait()
p_2
sem_1.signal()
sem_2.wait()
p_3
sem_1.signal()

# Q
sem_1.wait()
q_1
sem_2.signal()
sem_1.wait()
q_2
sem_2.signal()
sem_1.wait()
q_3
sem_2.signal()
```