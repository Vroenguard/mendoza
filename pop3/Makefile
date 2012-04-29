##
## Makefile for blabla in /home/lucian_b/Documents/development/mendoza/common
## 
## Made by antoine luciani
## Login   <lucian_b@epitech.net>
## 
## Started on  Sat Apr 28 13:30:56 2012 antoine luciani
## Last update Sat Apr 28 13:30:56 2012 antoine luciani
##

TARGET		=	pop3_server

CXXFLAGS	+=	-Wall -Wextra -ansi -pedantic -Iinclude/	\
			-I../lblib/include/ -I../common/include/
ifeq ($(DEBUG),true)
  CXXFLAGS	+=	-g3 -DDEBUG
endif

LDFLAGS		+=	-L../common/ -lmendoza_common -lpthread

CXX		=	g++
RM		=	rm -f

SOURCE_DIR	=	src
SOURCES		=	$(SOURCE_DIR)/main.cpp				\
			$(SOURCE_DIR)/Pop3Worker.cpp			\
			$(SOURCE_DIR)/Pop3Server.cpp

OBJECTS		=	$(SOURCES:.cpp=.o)

$(TARGET)	:	$(OBJECTS)
		$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

all		:	$(TARGET)

clean		:
		$(RM) $(OBJECTS)

fclean		:	clean
		$(RM) $(TARGET)

re		:	fclean all

.PHONY		:	all clean fclean re

%.o		:	%.cpp
		$(CXX) -o $@ $(CXXFLAGS) -c $<
