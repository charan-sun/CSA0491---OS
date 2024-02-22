#include <stdio.h>
struct process {
    int pid; 
    int burst_time;
    int waiting_time; 
    int turnaround_time; 
};


void swap(struct process *a, struct process *b) {
    struct process temp = *a;
    *a = *b;
    *b = temp;
}

void sjfScheduling(struct process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].burst_time > proc[j + 1].burst_time) {
                swap(&proc[j], &proc[j + 1]);
            }
        }
    }

    proc[0].waiting_time = 0;
    proc[0].turnaround_time = proc[0].burst_time;
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

void displayProcesses(struct process proc[], int n) {
    printf("PID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
    }
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
    }

    sjfScheduling(proc, n);


    displayProcesses(proc, n);

    return 0;
}

