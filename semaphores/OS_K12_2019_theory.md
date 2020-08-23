```python
# New solution
# Initial
mutex_p = Semaphore(1)
mutex_q = Semaphore(0)

# P
mutex_p.wait()
p_1
p_2
mutex_q.signal()

# Q
mutex_q.wait()
q_1
q_2
mutex_p.signal()


# Old solution
# Initial
# mutex_p = Semaphore(1)
# mutex_q = Semaphore(1)
# mutex_shared = Semaphore(0)
# flag = True

# # P
# mutex_p.wait()
#     if not flag:
#         mutex_shared.wait()

#     p_1
#     p_2

#     flag = False
#     mutex_shared.signal()
# mutex_p.signal()

# # Q
# mutex_q.wait()
#     if flag:
#         mutex_shared.wait()

#     q_1
#     q_2

#     flag = True
#     mutex_shared.signal()
# mutex_q.signal()
```