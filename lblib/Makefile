BASE_NAME		=	liblbmy
ifeq ($(LBMY_COMPILE_MODE),debug)
  BASE_NAME_SUFFIX	=	'_d'
endif
NAME			=	$(BASE_NAME)$(BASE_NAME_SUFFIX).a

CXX		=	g++
RM		=	rm -f
AR		=	ar -cr
RANLIB		=	ranlib

CXXFLAGS	=	-W -Wall -Wextra -ansi -pedantic
ifeq ($(LBMY_COMPILE_MODE),debug)
  CXXFLAGS	+=	-g3
endif
CXXFLAGS	+=	-Iinclude

SRC_DIR		=	src
SOURCES		=	$(SRC_DIR)/AXmlFile.cpp			\

OBJECTS		=	$(SOURCES:.cpp=.o) 
$(NAME)		:	$(OBJECTS)
		$(AR) $(NAME) $(OBJECTS)
		$(RANLIB) $(NAME)

all		:	$(NAME)

clean		:
		$(RM) $(OBJECTS)

fclean		:	clean
		$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re

.SUFFIXES	:	.cpp .o

.cpp.o		:	$(SOURCES)
		$(CXX) -c $< -o $@ $(CXXFLAGS)
