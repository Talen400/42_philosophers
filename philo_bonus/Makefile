# Colors for output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

# Configuration
NAME := philo_bonus
CC := cc
CFLAGS	:= -g -Wextra -Wall -Werror -pthread

# Directories
SRC_BONUS_DIR := ./srcs
OBJ_BONUS_DIR := ./objs

# Bonus sources
SRCS_BONUS := $(SRC_BONUS_DIR)/main_bonus.c \
			  $(SRC_BONUS_DIR)/parse_bonus.c \
			  $(SRC_BONUS_DIR)/utils_bonus.c \
			  $(SRC_BONUS_DIR)/ft_handle_bonus.c 

OBJS_BONUS := $(SRCS_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

BONUS_MARK := .bonus

# Default target
all: $(NAME)

# Bonus part
$(OBJ_BONUS_DIR):
	@mkdir -p $(OBJ_BONUS_DIR)
	@echo "$(BLUE)Created bonus objects directory$(RESET)"

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJ_BONUS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(MAGENTA)Compiled bonus: $(notdir $<)$(RESET)"

$(NAME): $(BONUS_MARK)

$(BONUS_MARK): $(OBJS_BONUS)
	@echo "$(YELLOW)Linking $(NAME) (bonus)...$(RESET)"
	@$(CC) $(OBJS_BONUS) -o $(NAME)
	@touch $(BONUS_MARK)
	@echo "$(GREEN)$(NAME) (bonus) built successfully!$(RESET)"

# Clean rules
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_BONUS_DIR)
	@rm -f $(BONUS_MARK)
	@echo "$(RED)Clean completed!$(RESET)"

fclean: clean
	@echo "$(RED)Full clean...$(RESET)"
	@rm -rf $(NAME)
	@echo "$(RED)Full clean completed!$(RESET)"

re: fclean all

# valgrind and leaks

LEAKS := valgrind --leak-check=full \
		 --show-leak-kinds=all \
		 --track-origins=yes \
		 #--log-file=val-leaks.txt \
		 --track-fds=yes

HELGRIND := valgrind --tool=helgrind \
		#	--log-file=helgrind.txt \
			--track-fds=yes

DRD := valgrind --tool=drd \
	   #--log-file=val-drd.txt \
	   --track-fds=yes

val_leaks: re
	@echo "running valgrind (leaks). input used: './bin/philo 198 401 200 200 10'"
	@echo "find trace at ./val-leaks.txt"
	@$(LEAKS) ./$(NAME) 198 401 200 200 10 2>&1

val_helg: re
	@echo "running valgrind (helgrind). input used: './bin/philo 5 800 200 200 7'"
	@echo "find trace at ./val-helgrind.txt"
	@$(HELGRIND) ./$(NAME) 5 800 200 200 7 2>&1

val_drd: re
	@echo "running valgrind (drd). input used: './bin/philo 1 800 200 200'"
	@echo "find trace at ./val-drd.txt"
	@$(DRD) ./$(NAME) 1 800 200 200 2>&1

.PHONY: all clean fclean re bonus
