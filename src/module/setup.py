import os
import sys
import io

from setuptools import setup

package_name = 'opentdf'

version = '0.2.3'

setup(
    name=package_name,
    version=version,
    author='Virtru',
    author_email='developers@virtru.com',
    url='https://developer.virtru.com/',
    license='MIT',
    description='Python Wrapper for openTDF SDK',
    long_description='long description here', #load_readme(),
    long_description_content_type='text/markdown',
    install_requires=[],
          classifiers=[
        'Development Status :: 5 - Production/Stable',
        'Environment :: Console',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Operating System :: MacOS :: MacOS X',
        'Operating System :: Microsoft :: Windows',
        'Operating System :: POSIX',
        'Operating System :: Unix',
        'Programming Language :: Python',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        'Programming Language :: Python :: 3.10',
        'Topic :: Software Development',
        'Topic :: Software Development :: Libraries :: Application Frameworks'
        ],
    py_modules=['opentdf'],
)
