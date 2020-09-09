# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/16 11:55:20 by awoimbee          #+#    #+#              #
#    Updated: 2020/09/09 15:33:25 by awoimbee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

CC	=	gcc

CFLAGS =	-Wall -Wextra -Werror -Wpedantic -fno-builtin -fvisibility=hidden \
			-Ofast -ftree-vectorize -fstrict-aliasing

SRC_PATH = src
OBJ_PATH = obj

SRCS_NAME =	malloc.c	\
			free.c		\
			realloc.c	\
			misc.c		\
			uint128.c	\
			init.c		\
			calloc.c	\
			print_allocs.c
OBJ_NAME = $(SRCS_NAME:.c=.o)
###################################  CONST  ####################################
SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CFLAGS += -fPIC -MMD -L./libft -lft -I./src -I./libft

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CFLAGS += -Wno-unused-result
	NUMPROC := $(shell grep -c ^processor /proc/cpuinfo)
else ifeq ($(UNAME_S),Darwin)
	NUMPROC := $(shell sysctl hw.ncpu | awk '{print $$2}')
endif
#####################################  RULES  ##################################

all:	$(NAME)

fast :
	@$(MAKE) -s -j$(NUMPROC)

$(OBJ_PATH)	:
	@mkdir -p $(OBJ_PATH) 2> /dev/null
	@printf "$(GRN)Compiling with \"$(CFLAGS)\" :$(EOC)\n"

$(NAME)	: libft/libft.a $(OBJS)
	@printf "$(GRN)%-50s$(EOC)\n" "Compilation done"
	$(CC) $(OBJS) $(CFLAGS) -shared -o $(NAME)
	strip --strip-all --discard-all $(NAME)
	ln -s $(NAME) $(LINK) | true
	@printf "$(GRN)%-50s$(EOC)\n" "$(NAME) done"

-include $(OBJS:.o=.d)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	@printf "%-50s\r" "$(CC) $@"
	@$(CC) $(CFLAGS) -o $@ -c $<

libft/libft.a:
	@$(MAKE) -C libft fast

tests: fast
	@$(MAKE) --no-print-directory -C ./tests all run

clean	:
	@rm -rf $(OBJ_PATH)
	@printf "$(RED)./$(OBJ_PATH) cleaned$(EOC)\n"
	@printf "Running fclean on tests...\n"
	@$(MAKE) --no-print-directory -C tests fclean
	@$(MAKE) --no-print-directory -C libft fclean

fclean	:	clean
	@rm -f $(NAME) $(LINK)
	@printf "$(RED)$(NAME) & $(LINK) removed$(EOC)\n"

re	:	fclean
	@$(MAKE) --no-print-directory

flowchart:
	@printf "%s\n"	\
	"drive.google.com/file/d/1WmQpjdGgEPmhxpchUW6tD26C3euBPtcL/view?usp=sharing"

.PHONY: all fast so clean fclean re flowchart tests what

GRN =	\033[0;32m
RED =	\033[0;31m
EOC =	\033[0m
