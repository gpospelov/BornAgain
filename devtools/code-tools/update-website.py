#!/usr/bin/env python3
"""
To update examples on website:

1) Run in your build directory
ctest -R PyExamples
This will run all existing examples and generate intensity images for web site.

2) Run this script
python update-examples.py <website-source-dir> <BornAgain-source-dir> <BornAgain-build-dir>
"""

import argparse, os, shutil

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


def copy_files(source_list, destination_list):
    """
    Every file in destination_list will be replaced by the file with the same
    basename found in source_list
    """
    missed_files = []
    updated_files = []
    for f in destination_list:
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


def update_example_scripts(website_dir, bornagain_source):
    """
    Copies example scripts from BornAgain to website.
    """
    website = os.path.join(website_dir, "static/files/python")
    source = os.path.join(bornagain_source, "Examples/Python")
    website_files = get_files(website, ".py")
    source_files = get_files(source, ".py")

    print(f'Update {len(website_files)} scripts ...')

    if verbose:
        print(website_files)

    copy_files(source_files, website_files)


def update_example_images(website_dir, example_images):
    """
    Copies example images from BornAgain build directory to website.
    """
    print("Update images ...")

    website = os.path.join(website_dir, "content/documentation/examples")
    source = example_images
    website_files = get_files(website, ".png")
    source_files = get_files(source, ".png")

    copy_files(source_files, website_files)


def update_website(website_source_dir, ba_source_dir, ba_build_dir):
    """
    Updates example scripts and images on website.
    """
    user_website_dir = os.path.expanduser(website_source_dir)
    user_source_dir = os.path.expanduser(ba_source_dir)
    user_build_dir = os.path.expanduser(ba_build_dir)
    user_image_dir = os.path.join(user_build_dir, "test_output/Functional/PyExamples")

    if verbose:
        print("Directories:")
        print("  website_dir    : '{}'".format(user_website_dir))
        print("  source_dir     : '{}'".format(user_source_dir))
        print("  build_dir      : '{}'".format(user_build_dir))
        print("  image_dir      : '{}'".format(user_image_dir))

    update_example_scripts(user_website_dir, user_source_dir)
    update_example_images(user_website_dir, user_image_dir)


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--verbose", action="store_true")
    parser.add_argument("website_source_dir", type=str)
    parser.add_argument("ba_source_dir", type=str)
    parser.add_argument("ba_build_dir", type=str)
    args = parser.parse_args()

    verbose = args.verbose

    update_website(args.website_source_dir, args.ba_source_dir, args.ba_build_dir)
