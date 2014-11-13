from setuptools import setup
import os


import shutil

def run_command(cmd):
    print ">>>", cmd
    returncode = os.system(cmd)
    if returncode:
        exit("Error while running command '"+cmd+"'")

shutil.copy("/Applications/BornAgain.app/Contents/lib/BornAgain-0.9/libBornAgainCore.so","./bornagain/.")
#run_command("install_name_tool -add_rpath /Users/pospelov/anaconda/lib bornagain/libBornAgainCore.so")
run_command("install_name_tool -add_rpath /Applications/BornAgain.app/Contents bornagain/libBornAgainCore.so")


setup(name='bornagain',
      version='0.9',
      description='The funniest joke in the world',
      url='www.bornagainproject.org',
      author='Flying Circus',
      author_email='flyingcircus@example.com',
      license='GPL',
      packages=['bornagain'],
      include_package_data=True,
      zip_safe=False)

