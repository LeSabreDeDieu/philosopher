# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 16:28:59 by sgabsi            #+#    #+#              #
#    Updated: 2024/10/28 15:44:00 by sgabsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
##  VARIABLES  ##
#################

# Directories
SRC_SUBDIR	=	utils init
SRCDIR		=	./src
INCDIR		=	./include
LIBDIR		=	./lib
OBJDIR		=	obj

# Sources
# INIT
SRC_INIT_DIR	=	$(SRCDIR)/init
SRC_INIT_FILES	=	init_philo.c
SRC_INIT		=	$(addprefix $(SRC_INIT_DIR)/, $(SRC_INIT_FILES))	

# UTILS
SRC_UTILS_DIR	=	$(SRCDIR)/utils
SRC_UTILS_FILES	=	utils.c \
					ft_atoi.c \
					ft_bzero.c \
					ft_calloc.c	\
					gettimeofday_ms.c \
					main_thread_utils.c \
					secured_get_data.c \
					secured_write.c \
					take_forks.c
SRC_UTILS		=	$(addprefix $(SRC_UTILS_DIR)/, $(SRC_UTILS_FILES))				

SRC			=	$(SRC_INIT) \
				$(SRC_UTILS) \
				$(SRCDIR)/check_death.c \
				$(SRCDIR)/launchers.c \
				$(SRCDIR)/philosopher.c \
				$(SRCDIR)/status.c

# Objects
OBJ_SUBDIRS	=	$(SRC_SUBDIR:%=$(OBJDIR)/%)
OBJ			=	$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Output
NAME		=	philo

# Compiler
CC			=	clang
CFLAGS		=	-Wall -Werror -Wextra -MMD -g3 -fsanitize=thread
OPTIONS		=	-I $(INCDIR) -I $(LIBFT_DIR)/includes
LFLAGS		=	-L $(LIBFT_DIR) -lft

# Progress bar
COUNT		=	1
TOTAL_FILES	=	$(shell find $(SRCDIR) -type f -name "*.c" | wc -l)

# Colors
RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
NC			=	\033[0m
KL			=	\033[K

#################
##  TARGETS    ##
#################

all: check

compile: pre_comp $(NAME)

check:
	@if [ -f "$(NAME)" ] && [ -z "$(shell find $(SRCDIR) -type f -name "*.c" -newer $(NAME) 2>/dev/null)" ] && [ -z "$(shell find $(SRCDIR) -type f -name "*.h" -newer $(NAME) 2>/dev/null)" ]; then \
		echo "$(YELLOW)********* Rien à faire - Tout est à jour *********$(NC)"; \
	else \
		make -s compile; \
	fi

pre_comp:
	@echo "$(YELLOW)********* Début de la compilation du programme $(NAME) *********$(NC)"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(OPTIONS) $(LFLAGS) -o $@
	@echo -e "\r$(GREEN)********* Compilation terminée avec succès! *********$(NC)$(KL)"
	@echo "$(GREEN)********* L'executable $(NAME) a été créée. *********$(NC)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(OPTIONS) -c $< -o $@
	@printf "$(NC)\rCompiling files: [%-50s] %3d%% (%d/%d) %s$(KL)" \
		"$(shell printf '=%.0s' $$(seq 1 $$(($(COUNT) * 50 / $(TOTAL_FILES)))))" \
		$$(($(COUNT) * 100 / $(TOTAL_FILES))) \
		$(COUNT) \
		$(TOTAL_FILES) \
		$<
	$(eval COUNT=$(shell echo $$(($(COUNT)+1))))

clean:
	@rm -rf $(OBJDIR)
	@rm -f norm.log
	@echo "$(YELLOW)********* Suppression des fichiers objets *********$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)********* Suppression de l'executable $(NAME) *********$(NC)"

re: fclean compile

norminette:
	@echo "$(YELLOW)********* Exécution de norminette *********$(NC)"
	@norminette src/ include/ > norm.log | grep -B 1 -e "Error" || echo "Tous les fichiers ont passé le check norminette !"

.PHONY: check compile all clean fclean re norminette
