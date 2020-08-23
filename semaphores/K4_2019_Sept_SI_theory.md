[Problems link](http://skelet.ludost.net/OS/problems/K4_2019_Sept_SI_theory.pdf)

```bash
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
sem.wait()
sem.signal()
p_2
```