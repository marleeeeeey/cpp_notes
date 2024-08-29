import subprocess
import sys


def main():
    if len(sys.argv) < 2:
        print("Usage: python infinite_runner.py <application>")
        sys.exit(1)

    application = sys.argv[1:]

    while True:
        process = subprocess.Popen(application, stdout=sys.stdout, stderr=sys.stderr)
        process.wait()

        success = process.returncode == 0
        if not success:
            print(f"Process {application[0]} exited with code {process.returncode}. STOP")
            break

        print(f"Process {application[0]} exited with code {process.returncode}. Restarting...")


if __name__ == "__main__":
    main()
