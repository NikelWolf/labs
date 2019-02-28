from dataclasses import dataclass
from pprint import pprint
from random import choice, randint, shuffle
from string import ascii_lowercase
from typing import List, Tuple
import math


@dataclass(order=True)
class Student:
    ID: int
    full_name: str
    notes: List[int]
    active: bool = True

    @property
    def average_score(self):
        return sum(self.notes) / len(self.notes)

    @staticmethod
    def generate_name():
        return " ".join(
            (
                "".join(
                    choice(ascii_lowercase) for _ in range(randint(5, 10))
                ).capitalize(),
                "".join(
                    choice(ascii_lowercase) for _ in range(randint(5, 10))
                ).capitalize(),
            )
        )

    @staticmethod
    def generate_notes():
        return [randint(3, 5) for i in range(15, 30)]


def _read_id(message: str):
    while True:
        try:
            return int(input(message))
        except ValueError:
            print("enter valid ID (integer)")


def linear_search(target_id: int, students: List[Student]) -> Tuple[int, int, bool]:
    index = counter = 0
    while True:
        counter += 1
        if index >= len(students):
            break

        counter += 1
        if students[index].ID == target_id:
            break

        index += 1
    return index, counter, index != len(students)


def barrier_search(target_id: int, students: List[Student]) -> Tuple[int, int, bool]:
    students = students[:]
    students.append(Student(ID=target_id, full_name="", notes=[], active=False))

    index = counter = 0
    while True:
        counter += 1
        if students[index].ID == target_id:
            break

        index += 1

    return index, counter, students[index].active


def golden_ratio_index_search(target_id: int, students: List[Student], a: int, b: int) -> int:
    gr = (math.sqrt(5) + 1) / 2
    x1 = int(b - (b - a) / gr)
    x2 = int(a + (b - 1) / gr)

    if target_id == students[x1].ID:
        return x1
    elif target_id == students[a].ID:
        return a
    elif target_id == students[b].ID:
        return b
    elif target_id == students[x2].ID:
        return x2
    elif target_id < students[x1].ID:
        return golden_ratio_index_search(target_id, students, a, x1)
    elif students[x1].ID < target_id < students[x2].ID:
        return golden_ratio_index_search(target_id, students, x1, x2)
    elif target_id > students[x2].ID:
        return golden_ratio_index_search(target_id, students, x2, b)
    else:
        return -1

def binary_search(
    target_id: int, students: List[Student]
) -> Tuple[int, int, bool]:
    index = counter = 0
    left, right = 0, len(students) - 1
    found = False
    while True:
        counter += 1
        if left > right:
            break

        counter += 1
        if found:
            break

        index = int((left + right) //2)
        s = students[index]

        counter += 1
        if s.ID == target_id:
            found = True
            continue

        counter += 1
        if s.ID < target_id:
            left = index + 1
            continue

        counter += 1
        if s.ID > target_id:
            right = index - 1
            continue

    return index, counter, found


def print_search_results(
    index: int, found: bool, target_id: int, students: List[Student]
):
    if not found:
        print(f"no student with ID {target_id} found")
    else:
        print(f"student with ID {target_id}: {students[index]}")


def main():
    search_id: int = _read_id("enter student's ID for search: ")
    students: List[Student] = [
        Student(ID=i, full_name=Student.generate_name(), notes=Student.generate_notes())
        for i in range(1, 1000)
    ]
    pprint({"students": students})
    print()

    # task 1
    index, task_1_counter, found = linear_search(search_id, students)
    print_search_results(index, found, search_id, students)

    # task 2
    index, task_2_counter, found = barrier_search(search_id, students)
    print_search_results(index, found, search_id, students)

    # task 4
    index, task_4_counter, found = binary_search(search_id, students)
    print_search_results(index, found, search_id, students)

    # task 5
    print(golden_ratio_index_search(search_id, students, 0, len(students) - 1))

    # task 3, 6
    print(
        "",
        f"first task operations counter: {task_1_counter}",
        f"second task operations counter: {task_2_counter}",
        f"forth task operations counter: {task_4_counter}",
        sep="\n",
    )


if __name__ == "__main__":
    main()
