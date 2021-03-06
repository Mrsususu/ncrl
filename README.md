# ncrl

使用稳定婚姻算法模拟解决室内可见光环境下多用户多灯组配对问题。

关联条件：灯组和用户各有自身的一套优先级列表（对于用户来说，灯组的优先级列表由收到不同灯组的光强决定；对于灯组来说，用户的优先级列表由特定的公平函数决定，在此不做详细介绍）。一个用户在一个时隙内可以关联多个用户，而一个用户在一个时隙内只能被一个灯组服务。

设计目标：对于理想的用户和灯组服务方案，一个常见的设计目标就是保证系统的容量最大化，也就是最优化用户的效用函数。此外，公平性同样是调度方案中值得考虑的因素。系统的公平性可以从两个角度得到体现：一个是在整个系统服务时间内，用户之间的平均容量差异尽量小；第二个是在服务一个用户时，尽量减少其对周围用户性能影响。
