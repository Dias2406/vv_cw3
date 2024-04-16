# Infer Verification on ChatGPT LeetCode Solutions

## Overview
This GitHub repository is dedicated to evaluating the effectiveness of the Infer static analysis tool on code completions generated by ChatGPT for 15 LeetCode problems. The repository includes all LeetCode problem solutions provided by ChatGPT, categorized into specific folders, and logs of Infer's analysis outputs on these solutions.

## Folder Structure
The repository consists of the following directories:

- **leetcode_completions**: This folder contains files for each LeetCode problem completed by ChatGPT. Each file is named according to the LeetCode problem number and title.

- **infer-outputs**: This directory stores the output logs from the Infer static analysis tool. The logs are named corresponding to the LeetCode problem numbers, providing a direct way to inspect the output from Infer for each specific problem.

## Infer Usage
### Installation

Before running Infer, ensure it is installed on your system. To install Infer, follow the [Getting Started Guide](https://fbinfer.com/docs/getting-started/) on Infer's official site.

It is recommended to run Infer on Linux system. If you do not have Linux System, using Github Codespaces is recommended. You can run the following command to install Infer:
```
cd vv_cw3

./install_infer.sh
```
## Running Infer
To run Infer on a LeetCode problem completion:

1. Open your terminal.
2. Change to the directory where the repository is cloned.
3. To analyze a specific LeetCode problem solution using Infer, use the `run_infer.sh` script followed by the problem file you want to test:
```
./run_infer.sh <path_to_leetcode_completion>
```

For example:
```
./run_infer.sh ./leetcode_completions/14.Valid_Number.c
```