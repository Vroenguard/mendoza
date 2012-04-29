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
CP		=	cp
RM		=	rm -f

COMMON_TARGET	=	common/libmendoza_common.a
SMTP_TARGET	=	smtp/smtp_server

all		:	common smtp

common		:
		$(MAKE) common/
		$(CP) $(COMMON_TARGET) ./

smtp		:
		$(MAKE) smtp/
		$(CP) $(SMTP_TARGET) ./

clean		:
		$(MAKE) common/ clean
		$(MAKE) smtp/ clean

fclean		:
		$(MAKE) common/ fclean
		$(MAKE) smtp/ fclean
		$(RM) $(COMMON_TARGET) $(SMTP_TARGET)

re		:
		$(MAKE) common/ re
		$(MAKE) smtp/ re

.PHONY		:	common smtp all
