#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#-----------< Helpers >------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

define add_define
	CFLAGS	+= -D$(1)=$($(1))
endef

define add_include
	INCLUDE	+= $(1)
endef
