#!/usr/bin/python3

import os
import subprocess
from pathlib import Path
import difflib

#RUN FROM ./minishell, not ./minishell/testing
#python3 ./testing/run.py

MINISHELL = "./minishell"
BASH = "/bin/bash"
TEST_DIR = "./testing"
RESULTS_FILE = os.path.join(TEST_DIR, "results.log")

class Colors:
	RED = "\033[0;31m"
	GREEN = "\033[0;32m"
	CYAN = "\033[0;36m"
	RESET = "\033[0m"

def run_shell(shell_path, input_file):
	with open(input_file, "r") as f:
		input_data = f.read()

	process = subprocess.Popen(
		shell_path, 
		stdin=subprocess.PIPE, 
		stdout=subprocess.PIPE, 
		stderr=subprocess.STDOUT,
		text=True
	)
	output, _ = process.communicate(input_data + "\nexit\n")
	return output

def generate_diff(output1, output2):
	diff = difflib.unified_diff(
		output1.splitlines(), 
		output2.splitlines(), 
		lineterm="",
		fromfile="minishell",
		tofile="bash"
	)
	return "\n".join(diff)

def main():
#	subprocess.run(["make"], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
	os.system(f"make re MS_CUTE=0 MS_DEBUG=0")
	with open(RESULTS_FILE, "w") as f:
		f.write(f"Test Results - {os.linesep}")
	test_cases = sorted(file for file in Path(TEST_DIR).iterdir()
	if file.name.startswith("input") and file.is_file() and file.suffix == ".txt")

	for input_file in test_cases:
		test_case = input_file.stem.replace("input", "")
		print(f"Running test case {test_case}...")
		minishell_output = run_shell(MINISHELL, input_file)
		bash_output = run_shell(BASH, input_file)

		if minishell_output == bash_output:
			print(f"Test case {test_case}: {Colors.GREEN}PASSED{Colors.RESET}")
			result = f"Test case {test_case}: PASSED\n"
		else:
			print(f"Test case {test_case}: {Colors.RED}FAILED{Colors.RESET}")
			diff = generate_diff(minishell_output, bash_output)
			print(f"{Colors.CYAN}Diff:\n{diff}{Colors.RESET}")
			result = f"Test case {test_case}: FAILED\n"
			result += "Minishell Output:\n" + minishell_output + "\n"
			result += "Bash Output:\n" + bash_output + "\n"
			#result += "Diff:\n" + diff + "\n"

		with open(RESULTS_FILE, "a") as f:
			f.write(result)

	print(f"\nResults saved to {RESULTS_FILE}")
	print(f"{Colors.RED}THINK ABOUT:{Colors.RESET}")
	print("-cute exit status+prompt\n-debugging info\n-manually test redirs and cat|cat|ls")

if __name__ == "__main__":
	main()

