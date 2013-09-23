#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------
#
#
#------------------------------------------------------------
# For compiling production firmware:
#TARGET       = KADE-XBOX-CUSTOM
#CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/ 
#------------------------------------------------------------
# For test firmware (which can be tested on PC):
TARGET       = KADE-XBOX-CUSTOM-T
CC_FLAGS     = -DTESTMODE -DUSE_LUFA_CONFIG_HEADER -IConfig/ 
#------------------------------------------------------------

MCU          = at90usb162
ARCH         = AVR8
BOARD        = MINIMUS
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
SRC          = ../shared/trackball/pstwo.c ../shared/trackball/trackBall.c main.c Descriptors.c XBOXPad.c $(LUFA_SRC_USB)
LUFA_PATH    = ./LUFA
LD_FLAGS     =

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk
