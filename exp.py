#!/usr/bin/env python3

import re
import sys
import argparse
from logging import Logger, basicConfig, getLogger
from os import getenv, environ, pathsep
from pathlib import Path
from typing import List, Set, Optional


logger = getLogger(__name__)  # type: Logger


class Expander:
    atcoder_include = re.compile(
        r'#include\s*["<](atcoder/[a-z_]*(|.hpp))[">"]\s*')
    
    # 只匹配 template.h 文件
    template_include = re.compile(
        r'#include\s*"template\.h"\s*')

    include_guard = re.compile(r'#.*ATCODER_[A-Z_]*_HPP')
    template_include_guard = re.compile(r'#.*TEMPLATE_H')

    def is_ignored_line(self, line) -> bool:
        if self.include_guard.match(line):
            return True
        if self.template_include_guard.match(line):
            return True
        if line.strip() == "#pragma once":
            return True
        if line.strip().startswith('//'):
            return True
        return False

    def __init__(self, lib_paths: List[Path]):
        self.lib_paths = lib_paths

    included = set()  # type: Set[Path]

    def find_acl(self, acl_name: str) -> Path:
        for lib_path in self.lib_paths:
            path = lib_path / acl_name
            if path.exists():
                return path
        logger.error('cannot find: {}'.format(acl_name))
        raise FileNotFoundError()
    
    def find_template(self, source_dir: Path) -> Path:
        # 首先在源文件同目录查找
        path = source_dir / 'template.h'
        if path.exists():
            return path
        
        # 然后在lib_paths中查找
        for lib_path in self.lib_paths:
            path = lib_path / 'template.h'
            if path.exists():
                return path
        
        # 最后检查默认的template路径
        default_template_path = Path('D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\competitive-programming\\external\\template\\template.h')
        if default_template_path.exists():
            return default_template_path
        
        logger.error('cannot find template.h')
        raise FileNotFoundError()

    def expand_acl(self, acl_file_path: Path) -> List[str]:
        if acl_file_path in self.included:
            logger.info('already included: {}'.format(acl_file_path.name))
            return []
        self.included.add(acl_file_path)
        logger.info('include: {}'.format(acl_file_path.name))

        acl_source = open(str(acl_file_path), encoding='utf-8').read()

        result = []  # type: List[str]
        for line in acl_source.splitlines():
            if self.is_ignored_line(line):
                continue

            m = self.atcoder_include.match(line)
            if m:
                name = m.group(1)
                result.extend(self.expand_acl(self.find_acl(name)))
                continue
            
            # 处理template.h包含
            m = self.template_include.match(line)
            if m:
                template_path = self.find_template(acl_file_path.parent)
                result.extend(self.expand_template(template_path))
                continue

            result.append(line)
        return result
    
    def expand_template(self, template_path: Path) -> List[str]:
        if template_path in self.included:
            logger.info('already included: {}'.format(template_path.name))
            return []
        self.included.add(template_path)
        logger.info('include template: {}'.format(template_path.name))

        template_source = open(str(template_path), encoding='utf-8').read()

        result = []  # type: List[str]
        for line in template_source.splitlines():
            if self.is_ignored_line(line):
                continue

            # 处理atcoder库包含
            m = self.atcoder_include.match(line)
            if m:
                name = m.group(1)
                result.extend(self.expand_acl(self.find_acl(name)))
                continue

            result.append(line)
        return result

    def expand(self, source: str, source_path: Path, origname) -> str:
        self.included = set()
        result = []  # type: List[str]
        linenum = 0
        for line in source.splitlines():
            linenum += 1
            
            # 处理atcoder库包含
            m = self.atcoder_include.match(line)
            if m:
                acl_path = self.find_acl(m.group(1))
                result.extend(self.expand_acl(acl_path))
                if origname:
                    result.append('#line ' + str(linenum + 1) + ' "' + origname + '"')
                continue
            
            # 处理template.h包含
            m = self.template_include.match(line)
            if m:
                template_path = self.find_template(source_path.parent)
                result.extend(self.expand_template(template_path))
                if origname:
                    result.append('#line ' + str(linenum + 1) + ' "' + origname + '"')
                continue

            result.append(line)
        return '\n'.join(result)


if __name__ == "__main__":
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv('LOG_LEVEL', 'INFO'),
    )
    parser = argparse.ArgumentParser(description='Expander')
    parser.add_argument('source', help='Source File')
    parser.add_argument('-c', '--console',
                        action='store_true', help='Print to Console')
    parser.add_argument('--lib', help='Path to Atcoder Library')
    parser.add_argument('--origname', help='report line numbers from the original ' +
                                           'source file in GCC/Clang error messages')
    opts = parser.parse_args()

    lib_paths = []
    if opts.lib:
        lib_paths.append(Path(opts.lib))
    if 'CPLUS_INCLUDE_PATH' in environ:
        lib_paths.extend(
            map(Path, filter(None, environ['CPLUS_INCLUDE_PATH'].split(pathsep))))
    lib_paths.append(Path('D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\competitive-programming\\external\\ac-library'))
    lib_paths.append(Path.cwd())
    
    expander = Expander(lib_paths)
    source_path = Path(opts.source)
    source = open(opts.source, encoding='utf-8').read()
    output = expander.expand(source, source_path, opts.origname)

    if opts.console:
        print(output)
    else:
        with open('Out.cpp', 'w', encoding='utf-8') as f:
            f.write(output)
