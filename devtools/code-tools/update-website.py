#!/usr/bin/env python3
"""
To update examples on website:

1) Run in your build directory
ctest -R PyExamples
This will run all existing examples and generate intensity images for web site.

2) Run this script
python update-examples.py <website-source-dir> <BornAgain-source-dir> <BornAgain-build-dir>
"""

import argparse, datetime, os, shutil

def log(msg):
    flog.write(msg+"\n")

def log2(msg):
    print(msg)
    log(msg)

def find_files(dir_name):
    """
    Return recursive list of files in given dir_name
    """
    for subdir, dirs, files in os.walk(dir_name):
        for filename in files:
            yield subdir, filename


def get_files(dir_name, extension):
    """
    Return list of all files in subdirectories of dir_name with given extension
    """
    result = []
    for subdir, filename in find_files(dir_name):
            name, ext = os.path.splitext(filename)
            if ext in extension:
                result.append(os.sep.join([subdir, filename]))
    return result


def find_files_with_same_name(filename_list, name_to_find):
    same_names = []
    for filename in filename_list:
        if os.path.basename(filename) == name_to_find:
            same_names.append(filename)

    return same_names


def update_all_files_of_one_type(source, destination, extension):
    """
    Every file in dest_list will be replaced by the file with the same
    basename found in source_list
    """

    source_list = get_files(source, extension)
    dest_list = get_files(destination, extension)

    log2(f'Update {len(dest_list)} {extension} files')
    log2(f'  from {source}')
    log2(f'    to {destination}')
    log(f'  {dest_list}')

    missed_files = []
    updated_files = []
    for f in dest_list:
        found_source = find_files_with_same_name(source_list, os.path.basename(f))
        if len(found_source) == 1:
            updated_files.append(f)
            shutil.copyfile(found_source[0], f)
        else:
            print(len(found_source), "Problem with ", f)
            missed_files.append(f)

    print("Following files have been updated on website:")
    for f in updated_files:
        print(f)

    if len(missed_files):
        print("Following files exist on website but not in source dir:")
        for f in missed_files:
            print(f)


def update_website(website_source_dir, ba_source_dir, ba_build_dir):
    """
    Updates example scripts and images on website.
    """

    # Start logging
    website_dirpath = os.path.expanduser(website_source_dir)
    log_path = os.path.join(website_dirpath, "update.examples.log")
    global flog
    flog = open(log_path, "a")
    print(f'Appending log to {log_path}')
    log(f'\n===\n{datetime.datetime.now().strftime("%d%b%y %H:%M:%S")}')

    update_all_files_of_one_type(
        os.path.join(ba_source_dir, "Examples/Python"),
        os.path.join(website_dirpath, "static/files/python"),
        '.py')

    update_all_files_of_one_type(
        os.path.join(website_dirpath, "content/documentation/examples"),
        os.path.join(ba_build_dir, "test_output/Functional/PyExamples"),
        '.png')


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument("website_source_dir", type=str)
    parser.add_argument("ba_source_dir", type=str)
    parser.add_argument("ba_build_dir", type=str)
    args = parser.parse_args()

    update_website(args.website_source_dir, args.ba_source_dir, args.ba_build_dir)
