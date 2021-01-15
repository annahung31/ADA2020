import collections

# Import Python wrapper for or-tools CP-SAT solver.
from ortools.sat.python import cp_model


def MinimalJobshopSat(jobs_data, same_job, n_jobs, n_tasks, machines_count):
    """Minimal jobshop problem."""
    # Create the model.
    model = cp_model.CpModel()


    task_machine_id = [['' for i in range(n_tasks)] for j in range(n_jobs)]
    

    for i_job, job in enumerate(jobs_data):
        print(i_job)
        for j_task, task in enumerate(job):
            print(j_task)
            task_machine_id[i_job][j_task] += str(task[0]+1)
            

    
    all_machines = range(machines_count)

    # Computes horizon dynamically as the sum of all durations.
    horizon = sum(task[1] for job in jobs_data for task in job)

    # Named tuple to store information about created variables.
    task_type = collections.namedtuple('task_type', 'start end interval')
    # Named tuple to manipulate solution information.
    assigned_task_type = collections.namedtuple('assigned_task_type',
                                                'start job index duration')

    # Creates job intervals and add to the corresponding machine lists.
    all_tasks = {}
    machine_to_intervals = collections.defaultdict(list)

    for job_id, job in enumerate(jobs_data):
        for task_id, task in enumerate(job):
            machine = task[0]
            duration = task[1]
            suffix = '_%i_%i' % (job_id, task_id)
            start_var = model.NewIntVar(0, horizon, 'start' + suffix)
            end_var = model.NewIntVar(0, horizon, 'end' + suffix)
            interval_var = model.NewIntervalVar(start_var, duration, end_var,
                                                'interval' + suffix)
            all_tasks[job_id, task_id] = task_type(
                start=start_var, end=end_var, interval=interval_var)
            machine_to_intervals[machine].append(interval_var)

    # Create and add disjunctive constraints.
    for machine in all_machines:
        model.AddNoOverlap(machine_to_intervals[machine])

    # Precedences inside a job.
    for job_id, job in enumerate(jobs_data):
        for task_id in range(len(job)):
            dependency = jobs_data[job_id][task_id][2]
            if (dependency != -1):
                model.Add(all_tasks[job_id, task_id].start >= all_tasks[job_id, dependency].end)
    

    # same operation needs two machine -> needs to be start at the same time

    for a_set in same_job:
        idx = 0
        while idx+1 != len(a_set):
            model.Add(all_tasks[a_set[idx][0], a_set[idx][1]].start == all_tasks[a_set[idx+1][0], a_set[idx+1][1]].start)
            idx += 1

    # Makespan objective.
    obj_var = model.NewIntVar(0, horizon, 'makespan')
    model.AddMaxEquality(obj_var, [
        all_tasks[job_id, len(job) - 1].end
        for job_id, job in enumerate(jobs_data)
    ])
    model.Minimize(obj_var)

    # Solve model.
    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    if status == cp_model.OPTIMAL:
        # Create one list of assigned tasks per machine.
        assigned_jobs = collections.defaultdict(list)
        for job_id, job in enumerate(jobs_data):
            for task_id, task in enumerate(job):
                machine = task[0]
                assigned_jobs[machine].append(
                    assigned_task_type(
                        start=solver.Value(all_tasks[job_id, task_id].start),
                        job=job_id,
                        index=task_id,
                        duration=task[1]))


        # Create per machine output lines.
        output = ''

        n_tasks = 3
        n_jobs = 3
        task_st = [[0 for i in range(n_tasks)] for j in range(n_jobs)]
        
        for machine in all_machines:
            # Sort by starting time.
            assigned_jobs[machine].sort()
            sol_line_tasks = 'Machine ' + str(machine) + ': '
            sol_line = '           '

            for assigned_task in assigned_jobs[machine]:
                name = 'job_%i_%i' % (assigned_task.job, assigned_task.index)


                # Add spaces to output to align columns.
                sol_line_tasks += '%-10s' % name

                start = assigned_task.start
                task_st[assigned_task.job][assigned_task.index] = int(start)

                duration = assigned_task.duration
                sol_tmp = '[%i,%i]' % (start, start + duration)
                # Add spaces to output to align columns.
                sol_line += '%-10s' % sol_tmp

            sol_line += '\n'
            sol_line_tasks += '\n'
            output += sol_line_tasks
            output += sol_line

        # Finally print the solution found.
        # print('Optimal Schedule Length: %i' % solver.ObjectiveValue())
        # print(output)


        for i in range(n_jobs):
            for j in range(n_tasks):
                if (task_machine_id[i][j] != ''):
                    print(str(task_st[i][j]) + " " + task_machine_id[i][j])
            
        with open("00.out", "w") as f:
            for i in range(n_jobs):
                for j in range(n_tasks):
                    if (task_machine_id[i][j] != ''):
                        f.writelines(str(task_st[i][j]) + " " + task_machine_id[i][j]+ "\n")



if __name__ == "__main__":

    n_jobs = 3
    n_tasks = 3
    machines_count = 3
    jobs_data = [  # task = (machine_id, processing_time, dependency, op_id).
            [(0, 10,-1), (0, 5, 0), (2, 7, 0)],  # Job0
            [(1, 5, -1), (2, 5, -1)],  # Job1
            [(2, 7, -1)]  # Job2
        ]
    same_job = [[(1,0),(1,1)]]


           
    MinimalJobshopSat(jobs_data, same_job, n_jobs, n_tasks, machines_count)