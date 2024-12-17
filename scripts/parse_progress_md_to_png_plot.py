import matplotlib.pyplot as plt
import re
from datetime import datetime

def main():

    # Reading the content of the file
    with open("../PROGRESS.md", "r") as file:
        data = file.read()

    # Extracting dates, DONE and TODO values from the file
    dates = re.findall(r"### (\d{4}-\d{2}-\d{2})", data)
    done_values = [int(x) for x in re.findall(r'"DONE" : (\d+)', data)]
    todo_values = [int(x) for x in re.findall(r'"TODO" : (\d+)', data)]

    # Converting dates to datetime objects
    dates = [datetime.strptime(date, "%Y-%m-%d") for date in dates]

    # Drawing graph
    plt.figure(figsize=(10, 5))
    plt.plot(dates, done_values, label="DONE", marker="o")
    plt.plot(dates, todo_values, label="TODO", marker="o")

    # Setting labels and title
    plt.xlabel("Date")
    plt.ylabel("Count")
    plt.title("My Learning Progress Over Time")
    plt.xticks(rotation=45)
    plt.legend()
    plt.grid()

    # Saving the plot
    plt.savefig("PROGRESS_OVER_TIME.png", bbox_inches="tight")


if __name__ == "__main__":
    main()