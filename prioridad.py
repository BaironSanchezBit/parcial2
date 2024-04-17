import time

class Process:
    def __init__(self, pid, burst_time, priority=0):
        self.id = pid
        self.burst_time = burst_time
        self.priority = priority

class Queue:
    def __init__(self):
        self.queue = []

    def is_empty(self):
        return len(self.queue) == 0

    def enqueue(self, process):
        self.queue.append(process)

    def dequeue(self):
        if not self.is_empty():
            return self.queue.pop(0)
        return None

def adjust_priority(process):
    if process.burst_time > 10:
        process.priority = (process.priority + 1) % 3
    else:
        process.priority = (process.priority - 1 + 3) % 3

queues = [Queue() for _ in range(3)]
processes = [Process(1, 15), Process(2, 8), Process(3, 12)]

start_time = time.time()

for p in processes:
    queues[p.priority].enqueue(p)

for q in queues:
    while not q.is_empty():
        process = q.dequeue()
        print(f'Ejecutando proceso {process.id} con tiempo de rafaga {process.burst_time} desde la cola {process.priority}')
        adjust_priority(process)
        queues[process.priority].enqueue(process)

end_time = time.time()
print(f"Tiempo de Ejecucion: {end_time - start_time} segundos")