#!/usr/bin/env python3
#
# Copyright 2021-2022 Michael Shafae
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
""" Check student's submission; requires the main file and the
    template file from the original repository. """
# pexpect documentation
#  https://pexpect.readthedocs.io/en/stable/index.html

# ex.
# .action/solution_check_p1.py  part-1 asgt

import difflib
import logging
import io
import os
import os.path
import re
import shutil
import subprocess
import sys
import pexpect
from assessment import csv_solution_check_make, make
from logger import setup_logger


def run_p1(binary):
    """Run part-1"""
    logger = setup_logger()
    status = []
    error_values = (
        ['Empty', "Please provide two arguments, a rectangle's length and width."], # 0 arguments, too few
        ['blue', 'orange', 'There was a problem reading the input numbers.'], # non-existant file
        ['12', 'orange', 'There was a problem reading the input numbers.'], # non-existant file
        ['blue', '34', 'There was a problem reading the input numbers.'], # non-existant file
    )
    values = (
        ['23', '41', '943'],
        ['63', '89', '5607'],
        ['-76', '35', '0'],
        ['53', '-56', '0'],
        ['-3', '-4', '0'],
        ['0', '0', '0'],
    )
    for index, val in enumerate(error_values):
        test_number = index + 1
        logger.info('Test %d - %s', test_number, val)
        rv = _run_p1_error(binary, val)
        if not rv:
            logger.error("Did not receive expected response for test %d.", test_number)
        status.append(rv)

    for index, val in enumerate(values):
        test_number = len(error_values) + index + 1
        logger.info('Test %d - %s', test_number, val)
        rv = _run_p1(binary, val)
        if not rv:
            logger.error("Did not receive expected response for test %d.", test_number)
        status.append(rv)
    return status

def _run_p1_error(binary, values):
    logger = setup_logger()
    status = False
    if values[0] == "Empty":
        proc = pexpect.spawn(binary, timeout=1)
    else:
        proc = pexpect.spawn(binary, timeout=1, args=values[:2])
    # proc.logfile = sys.stdout.buffer
    # values = list(map(str, values))

    with io.BytesIO() as log_stream:
        proc.logfile = log_stream
        try:
            regex = values[-1].replace(' ', '\\s+')
            proc.expect(
                fr'(?i).*{regex}.*'
            )
        except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
            expected_output = values[-1]
            logger.error(f'Expected: "{expected_output}"')
            logger.error('Could not find expected output.')
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            logger.debug("%s", str(exception))
            logger.debug(str(proc))
            return status

        proc.expect(pexpect.EOF)
        proc.close()
        if proc.exitstatus == 0:
            logger.error("Expected: non-zero exit code.")
            logger.error(f'Exit code was {proc.exitstatus}.')
            logger.error("Program returned zero, but non-zero is required")
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            return status
    status = True
    return status    

def _run_p1(binary, values):
    """The actual test with the expected input and output"""
    logger = setup_logger()
    status = False
    proc = pexpect.spawn(binary, timeout=1, args=values[:2])
    # proc.logfile = sys.stdout.buffer
    # values = list(map(str, values))

    with io.BytesIO() as log_stream:
        proc.logfile = log_stream
        try:
            regex = '{}\s*x\s*{}\s*=\s*{}'.format(*values)
            proc.expect(
                fr'(?i)\s*{regex}\s*'
            )
        except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
            expected_output = '{} x {} = {}'.format(*values)
            logger.error(f'Expected: "{expected_output}"')
            logger.error('Could not find expected output.')
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            logger.debug("%s", str(exception))
            logger.debug(str(proc))
            return status

        proc.expect(pexpect.EOF)
        proc.close()
        if proc.exitstatus != 0:
            logger.error("Expected: zero exit code.")
            logger.error(f'Exit code was {proc.exitstatus}.')
            logger.error("Program returned non-zero, but zero is required")
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            return status
    status = True
    return status


def run_p2(binary):
    """Run part-2"""
    logger = setup_logger()
    status = []
    error_values = (
        ['Empty', 'Please specify a county name on the command line. Exiting.'], # 0 arguments, too few
        ['foobar', 'Error: foobar is not in the vector. Please check your spelling.'], # Non-existant county
    )
    values = (
                ['Alameda', '1648556'],
                ['Alpine', '1235'],
                ['Amador', '41259'],
                ['Butte', '208309'],
                ['Calaveras', '46221'],
                ['Colusa', '21917'],
                ['Contra Costa', '1161413'],
                ['Del Norte', '28100'],
                ['El Dorado', '193221'],
                ['Fresno', '1013581'],
                ['Glenn', '28805'],
                ['Humboldt', '136310'],
                ['Imperial', '179851'],
                ['Inyo', '18970'],
                ['Kern', '917673'],
                ['Kings', '153443'],
                ['Lake', '68766'],
                ['Lassen', '33159'],
                ['Los Angeles', '9829544'],
                ['Madera', '159410'],
                ['Marin', '260206'],
                ['Mariposa', '17147'],
                ['Mendocino', '91305'],
                ['Merced', '286461'],
                ['Modoc', '8661'],
                ['Mono', '13247'],
                ['Monterey', '437325'],
                ['Napa', '136207'],
                ['Nevada', '103487'],
                ['Orange', '3167809'],
                ['Placer', '412300'],
                ['Plumas', '19915'],
                ['Riverside', '2458395'],
                ['Sacramento', '1588921'],
                ['San Benito', '66677'],
                ['San Bernardino', '2194710'],
                ['San Diego', '3286069'],
                ['San Francisco', '815201'],
                ['San Joaquin', '789410'],
                ['San Luis Obispo', '283159'],
                ['San Mateo', '737888'],
                ['Santa Barbara', '446475'],
                ['Santa Clara', '1885508'],
                ['Santa Cruz', '267792'],
                ['Shasta', '182139'],
                ['Sierra', '3283'],
                ['Siskiyou', '44118'],
                ['Solano', '451716'],
                ['Sonoma', '485887'],
                ['Stanislaus', '552999'],
                ['Sutter', '99063'],
                ['Tehama', '65498'],
                ['Trinity', '16060'],
                ['Tulare', '477054'],
                ['Tuolumne', '55810'],
                ['Ventura', '839784'],
                ['Yolo', '216986'],
                ['Yuba', '83421'],
            )
    for index, val in enumerate(error_values):
        test_number = index + 1
        logger.info('Test %d - %s', test_number, val)
        rv = _run_p1_error(binary, val)
        if not rv:
            logger.error("Did not receive expected response for test %d.", test_number)
        status.append(rv)

    for index, val in enumerate(values):
        test_number = len(error_values) + index + 1
        logger.info('Test %d - %s', test_number, val)
        rv = _run_p2(binary, val)
        if not rv:
            logger.error("Did not receive expected response for test %d.", test_number)
        status.append(rv)
    return status


def _run_p2(binary, values):
    logger = setup_logger()
    status = False
    proc = pexpect.spawn(binary, timeout=1, args=[values[0]])
    # proc.logfile = sys.stdout.buffer
    # values = list(map(str, values))

    with io.BytesIO() as log_stream:
        proc.logfile = log_stream
        expected_output = "The population of {} County is {}.".format(*values)
        try:
            regex = expected_output.replace(' ', '\\s+')
            proc.expect(
                fr'(?i).*{regex}.*'
            )
        except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
            logger.error(f'Expected: "{expected_output}"')
            logger.error('Could not find expected output.')
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            logger.debug("%s", str(exception))
            logger.debug(str(proc))
            return status

        proc.expect(pexpect.EOF)
        proc.close()
        if proc.exitstatus != 0:
            logger.error("Expected: zero exit code.")
            logger.error(f'Exit code was {proc.exitstatus}.')
            logger.error("Program returned non-zero, but zero is required")
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            return status
    status = True
    return status


def run_p3(binary):
    """Run part-3"""
    logger = setup_logger()
    status = []
    error_values = (
        ['Empty', 'Please provide a path to a file'], # 0 arguments, too few
        ['/foobar', '/foobar is missing the required file extension .png.'], # Missing image format
    )
    values = (
                ['test_output.png', 'sample_images/sample_image.png'],
            )
    for index, val in enumerate(error_values):
        test_number = index + 1
        logger.info('Test %d - %s', test_number, val)
        rv = _run_p1_error(binary, val)
        if not rv:
            logger.error("Did not receive expected response for test %d.", test_number)
        status.append(rv)

    for index, val in enumerate(values):
        test_number = len(error_values) + index + 1
        logger.info('Test %d - %s', test_number, val)
        rv = _run_p3(binary, val)
        if not rv:
            logger.error("Did not receive expected response for test %d.", test_number)
        status.append(rv)
    return status


def _run_p3(binary, values):
    """The actual test with the expected input and output"""
    logger = setup_logger()
    status = True
    proc = pexpect.spawn(binary, timeout=5, args=[values[0]])
    # proc.logfile = sys.stdout.buffer
    # values = list(map(str, values))

    with io.BytesIO() as log_stream:
        proc.logfile = log_stream
        # try:
        #     proc.expect(
        #         fr'(?i).*'
        #     )
        # except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        #     # logger.error(f'Expected: "{expected_output}"')
        #     logger.error('Could not find expected output.')
        #     logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
        #     logger.debug("%s", str(exception))
        #     logger.debug(str(proc))
        #     status = False
        #     return status       

        proc.expect(pexpect.EOF)
                
        proc.close()
        
        if proc.exitstatus != 0:
            logger.error("Expected: zero exit code.")
            logger.error(f'Exit code was {proc.exitstatus}.')
            logger.error("Program returned non-zero, but zero is required")
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            status = False

    if status and shutil.which('gm'):
        if os.path.exists(values[0]) and os.path.exists(values[1]):
            gm_cmd = shutil.which('gm') + ' compare -metric PAE -highlight-style XOR -highlight-color purple -file diff.png {} {}'.format(*values)
            logger.debug(f'Executing {gm_cmd}')
            proc = subprocess.run(
                [gm_cmd],
                capture_output=True,
                shell=True,
                timeout=4,
                check=False,
                text=True,
            )
            regex = r'(?i)(Red|Green|Blue|Total):\s+(\d+\.\d+)\s+(\d+\.\d+)'
            peak_error = {}
            for line in str(proc.stdout).split('\n'):
                match = re.search(regex, line)
                if match:
                    key = match.group(1).lower()
                    peak_error[key] = (float(match.group(2)), float(match.group(3)))
            logger.info('Analyzed difference between "{}" and "{}"'.format(*values))
            if 'total' in peak_error:
                total_error = peak_error['total'][0]
                max_error = 0.0015
                if total_error > max_error:
                    logger.error('❌ Output image has too much error.')
                    status = False
                for key in peak_error.keys():
                    percentage = '{:0.2f}'.format(peak_error[key][0] * 100.0)
                    prefix = '✅ '
                    if peak_error[key][0] > max_error:
                        prefix = '❌ '
                    logger.info(f'{prefix}{key.title()}: {percentage}% error')
            else:
                logger.error('❌ Missing total error measure in analysis.')
                status = False
        else:
            logger.error('❌ Missing output or sample output.')
            status = False

    elif status:
        logger.error('❌ Missing GraphicsMagick; cannot verify output.')
        logger.error('Please install base packages using the command:')
        logger.error('wget -q https://raw.githubusercontent.com/mshafae/tusk/main/quickinstall.sh -O- | sh')
        status = False


    return status


tidy_opts = (
    '-checks="*,-misc-unused-parameters,'
    '-modernize-use-trailing-return-type,-google-build-using-namespace,'
    '-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,'
    '-fuchsia-default-arguments-calls,-clang-analyzer-deadcode.DeadStores,'
    '-bugprone-exception-escape,-llvm-header-guard"'
    ' -config="{CheckOptions: [{key: readability-identifier-naming.ClassCase, value: CamelCase}, '
    '{key: readability-identifier-naming.ClassMemberCase, value: lower_case}, '
    '{key: readability-identifier-naming.ConstexprVariableCase, value: CamelCase}, '
    '{key: readability-identifier-naming.ConstexprVariablePrefix, value: k}, '
    '{key: readability-identifier-naming.EnumCase, value: CamelCase}, '
    '{key: readability-identifier-naming.EnumConstantCase, value: CamelCase}, '
    '{key: readability-identifier-naming.EnumConstantPrefix, value: k}, '
    '{key: readability-identifier-naming.FunctionCase, value: CamelCase}, '
    '{key: readability-identifier-naming.GlobalConstantCase, value: CamelCase}, '
    '{key: readability-identifier-naming.GlobalConstantPrefix, value: k}, '
    '{key: readability-identifier-naming.StaticConstantCase, value: CamelCase}, '
    '{key: readability-identifier-naming.StaticConstantPrefix, value: k}, '
    '{key: readability-identifier-naming.StaticVariableCase, value: lower_case}, '
    '{key: readability-identifier-naming.MacroDefinitionCase, value: UPPER_CASE}, '
    '{key: readability-identifier-naming.MacroDefinitionIgnoredRegexp, value: \'^[A-Z]+(_[A-Z]+)*_$\'}, '
    '{key: readability-identifier-naming.MemberCase, value: lower_case}, '
    '{key: readability-identifier-naming.PrivateMemberSuffix, value: _}, '
    '{key: readability-identifier-naming.PublicMemberSuffix, value: \'\'}, '
    '{key: readability-identifier-naming.NamespaceCase, value: lower_case}, '
    '{key: readability-identifier-naming.ParameterCase, value: lower_case}, '
    '{key: readability-identifier-naming.TypeAliasCase, value: CamelCase}, '
    '{key: readability-identifier-naming.TypedefCase, value: CamelCase}, '
    '{key: readability-identifier-naming.VariableCase, value: lower_case}, '
    '{key: readability-identifier-naming.IgnoreMainLikeFunctions, value: 1}]}"'
)

if __name__ == '__main__':
    cwd = os.getcwd()
    repo_name = os.path.basename(os.path.dirname(cwd))

    if sys.argv[1] == 'part-1':
        csv_solution_check_make(
            csv_key=repo_name,
            target_directory=sys.argv[2],
            program_name=sys.argv[3],
            run=run_p1,
            files=['rectangle_area.cc', 'rectangle_area_functions.cc', 'rectangle_area_functions.h'],
            #do_lint_check=False,
            tidy_options=tidy_opts,
        )
    elif sys.argv[1] == 'part-2':
        csv_solution_check_make(
            csv_key=repo_name,
            target_directory=sys.argv[2],
            program_name=sys.argv[3],
            run=run_p2,
            files=['counties.cc', 'counties_functions.cc', 'counties_functions.h'],
            # do_lint_check=False,
            tidy_options=tidy_opts,
        )
    elif sys.argv[1] == 'part-3':
        csv_solution_check_make(
            csv_key=repo_name,
            target_directory=sys.argv[2],
            program_name=sys.argv[3],
            run=run_p3,
            files=['gradient.cc', 'gradient_functions.cc', 'gradient_functions.h'],
            # do_lint_check=False,
            tidy_options=tidy_opts,
        )
    else:
        print('Error: no match.')
