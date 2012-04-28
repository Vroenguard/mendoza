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
SMTP_TARGET	=	smtp/smtp_server

all		:	common smtp

common		: $(COMMON_TARGET)

$(COMMON_TARGET)	:
		$(MAKE) common/

smtp		:	$(SMTP_TARGET)

$(SMTP_TARGET)	:
		$(MAKE) smtp/

clean		:
		$(MAKE) common/ clean
		$(MAKE) smtp/ clean

fclean		:
		$(MAKE) common/ fclean
		$(MAKE) smtp/ fclean

re		:
		$(MAKE) common/ re
		$(MAKE) smtp/ re

.PHONY		:	common all
