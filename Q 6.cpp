#include<stdio.h>
struct process {
    int pid; 
    int burst_time;
    int priority; 
    int waiting_time; 
    int turnaround_time; 
    int remaining_time;
};


int findHighestPriorityProcess(struct process proc[], int n, int current_time) {
    int highest_priority = -1;
    int selected_process = -1;
    for (int i = 0; i < n; i++) {
        if (proc[i].remaining_time > 0 && proc[i].priority > highest_priority) {
            highest_priority = proc[i].priority;
            selected_process = i;
        }
    }
    return selected_process;
}

void calculateTimes(struct process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

void priorityScheduling(struct process proc[], int n) {
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < n) {
        int selected_process = findHighestPriorityProcess(proc, n, current_time);
        if (selected_process == -1) {
            printf("No process selected at time %d\n", current_time);
            current_time++;
            continue;
        }

        struct process *current_process = &proc[selected_process];
        printf("Processing P%d at time %d\n", current_process->pid, current_time);
        current_process->remaining_time--;

        if (current_process->remaining_time == 0) {
            completed_processes++;
            current_process->turnaround_time = current_time + 1 - current_process->burst_time;
        }

        current_time++;
    }

    calculateTimes(proc, n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process proc[n];

    for (int i = 0; i < n; i++) {
        printf("Enter details for Process %d:\n", i + 1);
        proc[i].pid = i + 1;
        printf("Burst Time: ");
        scanf("%d", &proc[i].burst_time);
        printf("Priority: ");
        scanf("%d", &proc[i].priority);
        proc[i].remaining_time = proc[i].burst_time;
    }

 
    priorityScheduling(proc, n);

    printf("\nPID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].priority, proc[i].waiting_time, proc[i].turnaround_time);
    }

    return 0;
}

