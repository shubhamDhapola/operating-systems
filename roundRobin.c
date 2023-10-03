while (completed != n)
{
    idx = getFront();  // Get the front element of the queue
    pop();             // Remove the front element from the queue

    // Check if the process is starting for the first time
    if (burst_remaining[idx] == p[idx].burst_time)
    {
        // Set the start time of the process
        p[idx].start_time = (current_time > p[idx].arrival_time) ? current_time : p[idx].arrival_time;

        // Update total idle time
        total_idle_time += p[idx].start_time - current_time;

        // Update the current time
        current_time = p[idx].start_time;
    }

    // Check if the remaining burst time is greater than the time quantum
    if (burst_remaining[idx] - tq > 0)
    {
        // Process is preempted, update burst time and current time
        burst_remaining[idx] -= tq;
        current_time += tq;
    }
    else
    {
        // Process completes its execution
        current_time += burst_remaining[idx];
        burst_remaining[idx] = 0;
        completed++;

        // Update completion time, turnaround time, and waiting time
        p[idx].completion_time = current_time;
        p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
        p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

        // Update total turnaround time and total waiting time
        total_turnaround_time += p[idx].turnaround_time;
        total_waiting_time += p[idx].waiting_time;
    }

    // Enqueue processes that have arrived and not marked yet
    for (int i = 1; i < n; i++)
    {
        if (burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0)
        {
            push(i);   // Enqueue the process
            mark[i] = 1;  // Mark the process as enqueued
        }
    }

    // If the current process still has burst time left, enqueue it again
    if (burst_remaining[idx] > 0)
    {
        push(idx);
    }

    // If the queue is empty, enqueue the first available process
    if (isEmpty())
    {
        for (int i = 1; i < n; i++)
        {
            if (burst_remaining[i] > 0)
            {
                push(i);
                mark[i] = 1;
                break;
            }
        }
    }
}
