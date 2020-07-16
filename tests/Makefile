# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/18 23:44:50 by awoimbee          #+#    #+#              #
#    Updated: 2020/07/16 16:44:54 by awoimbee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = malloc_tests

TO_TEST = ../libft_malloc.so

CC = gcc

CFLAGS = -g3 -Wall -Wextra -fno-builtin# -Ofast -march=native

SRC = $(shell find ./src -type f -name "*.c" | sed  's/\.\/src\///g')
OBJ = $(addprefix obj/, $(SRC:.c=.o))
OBJ_FOLDERS = obj $(addprefix obj/, $(shell find ./src -type d -not \( -path './obj' -o -path './obj/*' \) | sed  's/\.\/src\///g'))

CFLAGS += -MMD -I./src -I../src
LDFLAGS = -L../
LDLIBS = -lpthread

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	NUMPROC := $(shell grep -c ^processor /proc/cpuinfo)
else ifeq ($(UNAME_S),Darwin)
	NUMPROC := $(shell sysctl hw.ncpu | awk '{print $$2}')
endif
#####################################  RULES  ##################################

all	: $(NAME)

run :
	LD_PRELOAD="$$LD_PRELOAD:${CURDIR}/../libft_malloc.so" ./$(NAME)

$(NAME)	: $(TO_TEST) $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)
	@printf "$(GRN)Done !$(EOC)\n"

#add rules written by -MMD, the '-' makes it continue even if file doesnt exist
-include $(OBJ:.o=.d)

obj/%.o: src/%.c | $(OBJ_FOLDERS)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_FOLDERS):
	mkdir -p $(OBJ_FOLDERS)

../$(TO_TEST):
	@printf "Missing $(TO_TEST), compiling...\n"
	@$(MAKE) --no-print-directory -C ../ fast

clean	:
	@rm -rf ./obj
	@printf "$(RED)objs cleaned$(EOC)\n"

fclean	:	clean
	@rm -f $(NAME)
	@printf "$(RED)$(NAME) removed$(EOC)\n"

re	:	fclean
	@$(MAKE) --no-print-directory -j$(NUMPROC)

.PHONY: all fast so clean fclean re run

GRN =	\033[0;32m
RED =	\033[0;31m
EOC =	\033[0m
