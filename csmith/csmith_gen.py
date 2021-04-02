import os
import sys
import subprocess
import time
import random
import copy

MAX_RUN_DURATION = 3

def get_csmith_include():
    """
    Finds relative path based on `CSMITH_PATH` environment variable value.
    
    CSmith output can be compiled with `gcc <cfile> -I$CSMITH_PATH` but
    AST library does not support `-I` option. This is solved by replacing:

    `#include "csmith.h"`

    with 

    `include "[REL_PATH]/csmith.h"`
    """
    assert os.environ['CSMITH_PATH'] is not None, 'Please set "CSMITH_PATH" environment variable value!'
    csmith_abs_path = os.environ['CSMITH_PATH']
    script_abs_path = os.path.abspath('.')
    csmith_include_file = 'csmith.h'
    
    csmith_relative_path = os.path.relpath(csmith_abs_path, script_abs_path)
    csmith_include = f'{csmith_relative_path}/{csmith_include_file}'
    return csmith_include

def run_csmith():
    """
    Generates random C file using CSmith tool.

    This script takes same arguments as CSmith tool (it's just a wrapper)
    """
    args = sys.argv[1:]

    # If no seed is chosen with `-s` option then random seed is generated
    try:
        seed_index = args.index('-s')
        assert len(args) > seed_index, 'Missing seed number after "-o" option!'
        seed = int(args[seed_index])
    except ValueError:
        seed = random.randrange(sys.maxsize)
        args.append('-s')
        args.append(str(seed))

    # if no output filename is chosen with `-o` option then name is same as seed number
    try:
        output_filename_index = args.index('-o')+1
        assert len(args) > output_filename_index, 'Missing output file name after "-o" option!'
        output_filename = args[output_filename_index]
    except ValueError:
        output_filename = f'{seed}.c'
        args.append('-o')
        args.append(output_filename)

    # Creating random C program
    args_line = ' '.join(args)
    command = f'csmith {args_line}'
    subprocess.run(command, shell=True)

    return output_filename, seed

def replace_csmith_include(output_filename, csmith_include):
    """
    Replacing `#include "csmith.h"` with `include "[csmith_include]"` in output_filename.
    Check `get_csmith_include()` function.
    """
    result_lines = []

    # Copying all lines except include csmith line
    with open(output_filename, 'r') as f:
        lines = f.readlines()
        for line in lines:
            if line.strip() == '#include "csmith.h"':
                result_lines.append(f'#include "{csmith_include}"')
            else:
                result_lines.append(line)

    with open(output_filename, 'w') as f:
        f.write('\n'.join(result_lines))

def test_generated_c_code(output_filename):
    """
    CSmith can generate C programs with infinite loop.
    All files that need more than [MAX_RUN_DURATION] to finish are dumped.

    In `[seed].c` is program.
    In `[seed].checksum.txt` is program output.
    """
    compiled_file_name = 'csmith.out'
    # Option '-w' disables all warnings
    compile_command = f'gcc {output_filename} -o {compiled_file_name} -w'
    subprocess.run(compile_command, shell=True)

    run_commad = f'./{compiled_file_name}'

    filename = output_filename[:-2]
    warn_filename = filename + '.warn.txt'
    checksum_filename = filename + '.checksum.txt'
    with open(checksum_filename, 'w') as checksum_file: 
        poll = subprocess.Popen(run_commad, shell=True, stdout=checksum_file)

        time.sleep(MAX_RUN_DURATION)
        if poll is None:
            poll.kill()

            # Removing files from dumped program
            os.remove(output_filename)
            os.remove(warn_filename)
            return False

        # cleanup
        os.remove(compiled_file_name)
        return True

def run():
    passed_test = False

    seed = None
    while not passed_test:
        csmith_include = get_csmith_include()
        output_filename, seed = run_csmith()
        replace_csmith_include(output_filename, csmith_include)
        passed_test = test_generated_c_code(output_filename)

    return seed

if __name__ == '__main__':
    run()
    