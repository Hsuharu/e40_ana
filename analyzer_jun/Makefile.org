#!/usr/bin/make
##
#  file: Makefile
#  date: 2017.04.10
#

#_______________________________________________________________________________
#
# Colorize
color		= 1
#
# Directories
bin_dir 	= bin
src_dir		= src
include_dir	= include
usr_dir		= usr
lib_dir		= lib
dst_dir		= dst
src_build_dir	= $(src_dir)/build
usr_build_dir	= $(usr_dir)/build
dst_build_dir	= $(dst_dir)/build
#
# ROOT
root_config	= root-config
root_include	= $(shell $(root_config) --cflags)
root_libs	= $(shell $(root_config) --libs) -lMinuit -lEG
#
# HDDAQ Unpacker
unpacker_config		= unpacker-config
unpacker_include	= $(shell $(unpacker_config) --include)
unpacker_libs		= $(shell $(unpacker_config) --libs)
#
CXX	= g++
CFLAGS	= -g -O3 -Wall
CFLAGS	+= -Wno-sign-compare
CFLAGS	+= -std=c++0x
# CFLAGS	+= -Wno-unused-variable -Wno-unused-but-set-variable
#DFLAGS	= -Df2cFortran -Dextname -DDEBUG -fno-inline
DFLAGS	+= -DMemoryLeak
FLAGS	= $(CFLAGS) $(DFLAGS) -I. $(root_include) \
		$(unpacker_include) $(addprefix -I,$(src_dir) $(include_dir))
#
#
lib_objs	= $(lib_dir)/libK18Analyzer.a
k18lib		= -L$(lib_dir)/ -lK18Analyzer
libs		= $(root_libs) $(unpacker_libs) -lrt
#
core_srcs	= $(wildcard $(src_dir)/*.cc)
headers		= $(wildcard $(include_dir)/*.hh)
usr_srcs	= $(wildcard $(usr_dir)/*.cc)
dst_srcs	= $(wildcard $(dst_dir)/*.cc)
#
core_deps	= $(core_srcs:$(src_dir)/%.cc=$(src_build_dir)/%.d)
usr_deps	= $(usr_srcs:$(usr_dir)/%.cc=$(usr_build_dir)/%.d)
dst_deps	= $(dst_srcs:$(dst_dir)/%.cc=$(dst_build_dir)/%.d)
#
core_objs	= $(core_srcs:$(src_dir)/%.cc=$(src_build_dir)/%.o)
usr_objs	= $(usr_srcs:$(usr_dir)/%.cc=$(usr_build_dir)/%.o)
dst_objs	= $(dst_srcs:$(dst_dir)/%.cc=$(dst_build_dir)/%.o)
#
usr_target	= $(usr_srcs:$(usr_dir)/User%.cc=$(bin_dir)/%)
dst_target	= $(dst_srcs:$(dst_dir)/%.cc=$(bin_dir)/%)
#
ar	:= ar r
echo	:= /bin/echo -e
mkdir	:= mkdir -p
mv	:= mv -f
rm	:= rm -rfv
# escape sequence
ifeq ($(color),1)
default_color	= \033[0m
black		= \033[0;30;1m
red		= \033[0;31;1m
green		= \033[0;32;1m
yellow		= \033[0;33;1m
blue		= \033[0;34;1m
magenta		= \033[0;35;1m
cyan		= \033[0;36;1m
white		= \033[0;37;1m
endif

#_______________________________________________________________________________
.PHONY: all dst usr lib clean distclean show help

all: lib usr dst

-include $(core_deps) $(usr_deps) $(dst_deps)

dst: $(dst_target) $(dst_objs)
usr: $(usr_target) $(usr_objs)
lib: $(lib_objs) $(core_objs)

#_______________________________________________________________________________
$(bin_dir)/Dst%: $(dst_build_dir)/Dst%.o $(lib_objs)
	@ $(echo) "$(magenta)=== Linking $@ $(default_color)"
	@ $(mkdir) $(bin_dir)
	$(CXX) $(FLAGS) -o $@ $< $(k18lib) $(libs)

$(bin_dir)/%: $(usr_build_dir)/User%.o $(lib_objs)
	@ $(echo) "$(magenta)=== Linking $@ $(default_color)"
	@ $(mkdir) $(bin_dir)
	$(CXX) $(FLAGS) -o $@ $< $(k18lib) $(libs)

$(lib_objs): $(core_objs)
	@ $(echo) "$(yellow)=== Archiving $@ $(default_color)"
	@ $(mkdir) $(lib_dir)
	$(ar) $(lib_objs) $(core_objs)

$(src_build_dir)/%.o: $(src_dir)/%.cc
	@ $(echo) "$(green)=== Compiling $@ $(default_color)"
	@ $(mkdir) $(src_build_dir)
	$(CXX) $(FLAGS) -o $@ -MMD -c $<

$(usr_build_dir)/%.o: $(usr_dir)/%.cc
	@ $(echo) "$(green)=== Compiling $@ $(default_color)"
	@ $(mkdir) $(usr_build_dir)
	$(CXX) $(FLAGS) -o $@ -MMD -c $<

$(dst_build_dir)/%.o: $(dst_dir)/%.cc
	@ $(echo) "$(green)=== Compiling $@ $(default_color)"
	@ $(mkdir) $(dst_build_dir)
	$(CXX) $(FLAGS) -o $@ -MMD -c $<

#_______________________________________________________________________________
clean:
	@ $(echo) "$(green)=== Cleaning $(default_color)"
	@ $(rm) $(dst_objs) $(usr_objs) $(core_objs) \
	$(lib_objs) $(dst_deps) $(usr_deps) $(core_deps)
	@ find . \( -name "*~" -o -name "\#*\#" \) -exec $(rm) \{\} \;

distclean:
	@ $(echo) "$(green)=== Cleaning $(default_color)"
	@ $(rm) $(bin_dir)/* $(lib_dir)/* \
	$(src_build_dir) $(usr_build_dir) $(dst_build_dir)
	@ find . \( -name "*~" -o -name "\#*\#" \) -exec $(rm) \{\} \;

#_______________________________________________________________________________
sort := tr ' ' '\n' | sort | uniq | sed -e "s:.*./::g" | pr -t -w 80 -3
show:
	@ $(echo) "$(yellow)=== FLAGS $(default_color)"
	@ $(echo) "CFLAGS = $(CFLAGS)"
	@ $(echo) "DFLAGS = $(DFLAGS)"
	@ $(echo) "FLAGS = \n`echo $(FLAGS)|tr ' ' '\n'|sed 's/-/ -/g'`"
	@ $(echo) "$(green)=== core sources $(src_dir)/ $(default_color)"
	@ $(echo) $(core_srcs) | $(sort)
	@ $(echo) "$(cyan)=== headers $(include_dir)/ $(default_color)"
	@ $(echo) $(headers) | $(sort)
	@ $(echo) "$(green)=== usr sources $(usr_dir)/ $(default_color)"
	@ $(echo) $(usr_srcs) | $(sort)
	@ $(echo) "$(green)=== dst sources $(dst_dir)/ $(default_color)"
	@ $(echo) $(dst_srcs) | $(sort)
	@ $(echo) "$(green)=== core objects $(src_build_dir)/ $(default_color)"
	@ $(echo) $(core_objs) | $(sort)
	@ $(echo) "$(green)=== usr objects $(usr_build_dir)/ $(default_color)"
	@ $(echo) $(usr_objs) | $(sort)
	@ $(echo) "$(green)=== dst objects $(dst_build_dir)/ $(default_color)"
	@ $(echo) $(dst_objs) | $(sort)
	@ $(echo) "$(yellow)=== lib objects $(lib_dir)/ $(default_color)"
	@ $(echo) $(lib_objs) | $(sort)
	@ $(echo) "$(magenta)=== usr target $(bin_dir)/ $(default_color)"
	@ $(echo) $(usr_target) | $(sort)
	@ $(echo) "$(magenta)=== dst target $(bin_dir)/ $(default_color)"
	@ $(echo) $(dst_target) | $(sort)

help:
	@ $(echo) "$(green)=== target list$(default_color)"
	@ $(MAKE) --print-data-base --question | \
	awk '/^[^.%][-A-Za-z0-9_]*:/ \
	{ print substr($$1, 1, length($$1)-1) }' | $(sort)
