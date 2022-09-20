# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/15 08:46:38 by eabdelha          #+#    #+#              #
#    Updated: 2022/09/15 10:02:41 by eabdelha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re 

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 

FT_NAME = ftcontainers
STD_NAME = stdcontainers

SRC_PATH = ./src/
FT_TESTS_PATH = ./tests/ft_tests/
STD_TESTS_PATH = ./tests/std_tests/
OBJ_PATH = ./obj/

SRC_INCLUDES =	$(SRC_PATH)vector.hpp				\
				$(SRC_PATH)vector_iterator.hpp		\
				$(SRC_PATH)iterator_traits.hpp	

FT_TESTS	=	ft_main.cpp

STD_TESTS	=	std_main.cpp
	
FT_OBJECTS = $(addprefix $(OBJ_PATH), $(FT_TESTS:.cpp=.o))
STD_OBJECTS = $(addprefix $(OBJ_PATH), $(STD_TESTS:.cpp=.o))

all: $(OBJ_PATH) $(FT_NAME) $(STD_NAME)

$(FT_NAME): $(FT_OBJECTS) 
	@$(CC) $(CFLAGS) $(FT_OBJECTS) -o $(FT_NAME)

$(STD_NAME): $(STD_OBJECTS) 
	@$(CC) $(CFLAGS) $(STD_OBJECTS) -o $(STD_NAME)

$(OBJ_PATH)%.o: $(FT_TESTS_PATH)%.cpp $(SRC_INCLUDES) 
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH)%.o: $(STD_TESTS_PATH)%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH) : 
	@mkdir $@

clean:
	@rm -rf  $(OBJ_PATH)

fclean: clean 
	@rm -f $(FT_NAME) $(STD_NAME) 

re: fclean all
