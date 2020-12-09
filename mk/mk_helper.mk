#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#-----------< Helpers >------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

define add_define
	CFLAGS	+= -D$(1)=$($(1))
endef

define add_include
	INCLUDE	+= $(1)
endef

define add_cflag
	CFLAGS	+= $(1)
endef

define add_ldflag
	LD_FLAGS	+= $(1)
endef
