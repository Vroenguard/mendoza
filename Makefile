##
## Makefile for blabla in /home/lucian_b/Documents/development/mendoza
## 
## Made by antoine luciani
## Login   <lucian_b@epitech.net>
## 
## Started on  Sat Apr 28 20:51:18 2012 antoine luciani
## Last update Sat Apr 28 20:51:18 2012 antoine luciani
##

MAKE		=	make -C

COMMON_TARGET	=	common/libmendoza_common.a

common		: $(COMMON_TARGET)

$(COMMON_TARGET)	:
		$(MAKE) common/

clean		:
		$(MAKE) common/ clean

fclean		:
		$(MAKE) common/ fclean

re		:
		$(MAKE) common/ re

all		:	common

.PHONY		:	common all
