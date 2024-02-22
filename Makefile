# DunioUtil makefile

THIS_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
TOP_DIR ?= $(THIS_DIR)

$(info TOP_DIR = $(TOP_DIR))

DUINO_MAKEFILE ?= $(THIS_DIR)/../DuinoMakefile

ifeq ("$(wildcard $(DUINO_MAKEFILE)/Makefile)","")
$(error Unable to open $(DUINO_MAKEFILE)/Makefile)
else
include $(DUINO_MAKEFILE)/Makefile
endif
