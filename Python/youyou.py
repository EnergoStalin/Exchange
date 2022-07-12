from tasklib import TaskManager, TaskWithFile
import re

class t1(TaskWithFile):
    def __init__(self, file: str) -> None:
        super().__init__(file)

    def is_consonant(self, e):
        return not e in ['a','e','i','u','o']

    def solve(self):
        data = self.readFile(True)
        return data


if __name__ == "__main__":
    print(TaskManager().addTasks([
        t1("input.txt")
    ]).execute())