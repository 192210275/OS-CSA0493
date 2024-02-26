#include <stdio.h>
#include <stdlib.h>

// Process structure to store process details
struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingBurstTime;
};

// Function to perform Preemptive Priority Scheduling
void preemptivePriorityScheduling(struct Process processes[], int n) {
    int currentTime = 0;  // Current time
    int totalWaitingTime = 0;  // Total waiting time for all processes
    int totalTurnaroundTime = 0;  // Total turnaround time for all processes

    // Calculate total burst time for processes
    int totalBurstTime = 0;
    for (int i = 0; i < n; i++) {
        totalBurstTime += processes[i].burstTime;
        processes[i].remainingBurstTime = processes[i].burstTime;
    }

    // Perform Preemptive Priority Scheduling
    while (currentTime < totalBurstTime) {
        int highestPriority = -1;
        int selectedProcess = -1;

        // Find the process with the highest priority at the current time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingBurstTime > 0) {
                if (highestPriority == -1 || processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    selectedProcess = i;
                }
            }
        }

        // Update waiting time for the selected process
        if (selectedProcess != -1) {
            processes[selectedProcess].remainingBurstTime--;
            totalWaitingTime += currentTime - processes[selectedProcess].arrivalTime;
        }

        // Move to the next time unit
        currentTime++;
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        processes[i].remainingBurstTime = processes[i].burstTime;  // Reset remaining burst time
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    // Display results
    printf("Process\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].priority, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    // Calculate and display average waiting and turnaround times
    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

int main() {
    // Number of processes
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    // Perform Preemptive Priority Scheduling
    preemptivePriorityScheduling(processes, n);

    return 0;
}

