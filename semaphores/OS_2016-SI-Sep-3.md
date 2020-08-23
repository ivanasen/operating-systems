[Problems link](http://skelet.ludost.net/OS/problems/OS_2016-SI-Sep-3.pdf)

```python
# Initial
sem = Semaphore(0)

# P
p_1
sem.signal()
p_2
p_3

# Q
q_1
sem.wait()
q_2
q_3
sem.signal()

# R
r_1
sem.wait()
r_2
r_3
sem.signal()
```