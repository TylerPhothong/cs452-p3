## Objective
The objective of this analysis is to examine the performance of a multi-threaded merge sort algorithm by measuring the sorting time as the number of threads increases. By analyzing these results, we aim to identify the optimal thread count for sorting efficiency and understand the performance trends of our system.

## System Overview
The merge sort algorithm was modified to support multi-threading. Each thread handles a separate segment of the array, and the results are merged sequentially after sorting. This approach aims to reduce sorting time by leveraging multiple cores.

# Observations

## Optimal Thread Count:
The minimum recorded time for sorting occurred when the number of threads was around 28. With 28 threads, the sorting time reached approximately 116.38 ms, which appears to be the optimal performance for this dataset and system configuration.
Other near-optimal times occurred at 15 threads (117.24 ms) and 31 threads (116.90 ms), indicating some consistency in performance improvement in the 15–32 thread range.

## Performance Trends:
From the graph, I observed a general trend where the sorting time initially decreases as the number of threads increases, reaching an optimal range around 15–32 threads.
However, the sorting time fluctuates significantly with certain thread counts. For example, 12 and 10 threads have higher times (146.80 ms and 143.87 ms, respectively), showing that performance does not always scale linearly with an increase in threads.
This fluctuation could be due to system overheads, such as context switching or increased CPU load, which diminish the benefits of additional threads.

## Anomalies and Inconsistencies:
The sorting time increases at specific points (e.g., at 5, 6, 10, 12, and 20 threads), likely due to overhead associated with managing too many or inefficiently assigned threads.
The irregular pattern suggests that as more threads are introduced, contention for resources such as CPU caches, memory, and bandwidth could impact performance negatively.

## Comparisons with Single-Threaded Performance:
The single-threaded performance, measured at 178.38 ms, is considerably slower than most multi-threaded results.
This confirms that multi-threading provides a substantial speedup, especially in the 15–32 thread range, reducing sorting time by over 35% compared to the single-threaded version.
Conclusion
The analysis shows that the multi-threaded merge sort achieves optimal performance with around 28 threads on this system. Beyond this thread count, the gains in sorting time are minimal or inconsistent due to system overhead. The system architecture is an Inspiron i7-3000 series and its handling of multi-threading may account for why the optimal count is higher compared to other systems, such as M1 Macs, which may reach optimum performance with fewer threads due to their different architecture and threading efficiencies.

# Analysis
Were you able to generate something close to what the example showed? Why or why not.

The graph was similar just a lot more zoomed in then the expected result, but the overall data of the graph wasn't even close to the expected result. In the example, the optimal thread count was around 9 or 10, with a clear decrease in sorting time as thread count increased up to that point, followed by a gradual increase in sorting time with additional threads. In my case, however, the optimal thread count was significantly higher (around 28 threads), and the graph showed more fluctuation in sorting times as thread count increased. The difference is likely due to hardware variations. The example was run on an M1 Mac, which has a different architecture and may handle multi-threading more efficiently with fewer threads. In contrast, my machine (an Inspiron with an Intel i7 processor) benefits from more threads, likely because of its specific core and hyper-threading structure, which allows it to handle a larger number of threads before reaching its peak performance.

Did you see a slow down at some point why or why not?

Yes, there were slowdowns at several points, particularly around 5, 6, 10, 12, and 20 threads. These slowdowns are likely due to the overhead associated with managing multiple threads. 


Did your program run faster and faster when you added more threads? Why or why not?

No, the program did not continue to run faster with each additional thread. Initially, increasing the thread count led to faster sorting times, but after reaching an optimal range (around 15-32 threads), the performance gains became inconsistent, with some thread counts even showing increased sorting times.


What was the optimum number of threads for your machine?

The optimal number of threads for this machine was 28 threads, which yielded the lowest sorting time of approximately 116.38 ms.


What was the slowest number of threads for your machine?


The slowest sorting time occurred with 1 thread, at approximately 178.38 ms. This is expected, as a single-threaded merge sort lacks the parallelism to take advantage of the system’s multiple cores, resulting in the longest execution time.


## Graph
You can find the graph in my report summary or the file "student_plot.png" as I wasn't able to put a picture into this file.
