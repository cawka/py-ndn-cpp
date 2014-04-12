# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

VERSION = '0.1.0'
APPNAME = "py-openndn"

from waflib import Logs

def options(opt):
    opt.load(['compiler_cxx', 'python'])
    opt.load(['boost', 'default-compiler-flags'],
             tooldir=['.waf-tools'])

def configure(conf):
    conf.load(['compiler_cxx', 'boost', 'python',
               'default-compiler-flags'])

    conf.check_cfg(package='libndn-cpp-dev', args=['--cflags', '--libs'],
                   uselib_store='NDN_CPP', mandatory=True)

    conf.check_python_version ((2,7))
    conf.check_python_headers ()

    conf.check_boost(lib="python")

def build (bld):
    bld.shlib (features = "pyext",
               target = "openndn",
               source = bld.path.ant_glob(["bindings/**/*.cpp"]),
               use = "NDN_CPP BOOST",
               install_path='${PYTHONARCHDIR}'
               )
