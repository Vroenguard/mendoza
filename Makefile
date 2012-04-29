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
CREATOR_TARGET	=	mailbox_creator/mailbox_create

all		:	common smtp tools

common		:
		$(MAKE) common/
		$(CP) $(COMMON_TARGET) ./

smtp		:
		$(MAKE) smtp/
		$(CP) $(SMTP_TARGET) ./

tools		:
		$(MAKE) mailbox_creator/
		$(CP) $(CREATOR_TARGET) ./

clean		:
		$(MAKE) common/ clean
		$(MAKE) smtp/ clean
		$(MAKE) mailbox_creator/ clean

fclean		:
		$(MAKE) common/ fclean
		$(MAKE) smtp/ fclean
		$(MAKE) mailbox_creator/ fclean

re		:
		$(MAKE) common/ re
		$(MAKE) smtp/ re

.PHONY		:	common smtp all
