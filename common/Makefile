##
## Makefile for blabla in /home/lucian_b/Documents/development/mendoza/common
## 
## Made by antoine luciani
## Login   <lucian_b@epitech.net>
## 
## Started on  Sat Apr 28 13:30:56 2012 antoine luciani
## Last update Sat Apr 28 13:30:56 2012 antoine luciani
##

TARGET		=	libmendoza_common.a

CXXFLAGS	+=	-Wall -Wextra -ansi -pedantic -Iinclude/
ifeq ($(DEBUG),true)
  CXXFLAGS	+=	g3
endif

CXX		=	g++
RM		=	rm -f
AR		=	ar -cr
RANLIB		=	ranlib

SOURCE_DIR	=	src
SOURCES		=	$(SOURCE_DIR)/FileLock.cpp			\
			$(SOURCE_DIR)/MailBox.cpp

OBJECTS		=	$(SOURCES:.cpp=.o)

$(TARGET)	:	$(OBJECTS)
		$(AR) $(TARGET) $(OBJECTS)
		$(RANLIB) $(TARGET)

all		:	$(TARGET)

clean		:
		$(RM) $(OBJECTS)

fclean		:	clean
		$(RM) $(TARGET)

re		:	fclean all

.PHONY		:	all clean fclean re

%.o		:	%.cpp
		$(CXX) -o $@ $(CXXFLAGS) -c $<
