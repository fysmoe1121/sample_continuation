from setuptools import setup, Extension
import pybind11
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        'fgt_main',  # Name of the resulting Python module
        ['2d_mvn.cpp'],  # Source file
        include_dirs=[
            pybind11.get_include(),
            '/opt/homebrew/include',
            '/opt/homebrew/opt/boost/include',
            '/opt/homebrew/include/eigen3',
            '/opt/homebrew/Cellar/fgt/0.4.6/include'
        ],
        library_dirs=[
            '/opt/homebrew/opt/boost/lib',
            '/opt/homebrew/Cellar/fgt/0.4.6/lib'
        ],
        libraries=['fgt'],
        language='c++',
        extra_compile_args=[
            '-std=gnu++14',
            '-std=c++11',
            '-fcolor-diagnostics',
            '-fansi-escape-codes',
            '-g'
        ],
        extra_link_args=[
            '-L/opt/homebrew/opt/boost/lib',
            '-L/opt/homebrew/Cellar/fgt/0.4.6/lib',
            '-lfgt'
        ]
    ),
]

setup(
    name='fgt_main',
    ext_modules=ext_modules,
    cmdclass={'build_ext': build_ext},
    zip_safe=False,
)
