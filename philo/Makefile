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
NAME := philo
CC := cc
CFLAGS	:= -Wextra -Wall -Werror -pthread

# Directories
SRC_DIR := ./srcs
SRC_BONUS_DIR := ./srcs_bonus
OBJ_DIR := ./objs
OBJ_BONUS_DIR := ./objs_bonus

# Mandatory sources
SRCS := $(SRC_DIR)/main.c \
		$(SRC_DIR)/utils.c

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Bonus sources
SRCS_BONUS := $(SRC_BONUS_DIR)/main_bonus.c \

OBJS_BONUS := $(SRCS_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

MANDATORY_MARK := .mandatory
BONUS_MARK := .bonus

# Default target
all: $(NAME)

# Mandatory part
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)Created objects directory$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "$(CYAN)Compiled: $(notdir $<)$(RESET)"

$(NAME): $(MANDATORY_MARK)

$(MANDATORY_MARK): $(OBJS)
	@rm -f $(BONUS_MARK)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@touch $(MANDATORY_MARK)
	@echo "$(GREEN)$(NAME) built successfully!$(RESET)"

# Bonus part
$(OBJ_BONUS_DIR):
	@mkdir -p $(OBJ_BONUS_DIR)
	@echo "$(BLUE)Created bonus objects directory$(RESET)"

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJ_BONUS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "$(MAGENTA)Compiled bonus: $(notdir $<)$(RESET)"

bonus: $(BONUS_MARK)

$(BONUS_MARK): $(OBJS_BONUS)
	@rm -f $(MANDATORY_MARK)
	@echo "$(YELLOW)Linking $(NAME) (bonus)...$(RESET)"
	@$(CC) $(OBJS_BONUS) $(LIBS) $(HEADERS) -o $(NAME)
	@touch $(BONUS_MARK)
	@echo "$(GREEN)$(NAME) (bonus) built successfully!$(RESET)"

# Clean rules
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_BONUS_DIR)
	@rm -f $(MANDATORY_MARK)
	@rm -f $(BONUS_MARK)
	@echo "$(RED)Clean completed!$(RESET)"

fclean: clean
	@echo "$(RED)Full clean...$(RESET)"
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)
	@echo "$(RED)Full clean completed!$(RESET)"

re: fclean all

# valgrind and leaks

LEAKS := valgrind --leak-check=full \
		 --show-leak-kinds=all \
		 --track-origins=yes \
		 --log-file=val-leaks.txt \
		 --track-fds=yes

HELGRIND := valgrind --tool=helgrind \
			--log-file=helgrind.txt \
			--track-fds=yes

DRD := valgrind --tool=drd \
	   --log-file=val-drd.txt \
	   --track-fds=yes

val_leaks: re
	@echo "running valgrind (leaks). input used: './bin/philo 198 401 200 200 10'"
	@echo "find trace at ./val-leaks.txt"
	@$(LEAKS) ./$(NAME) 2>&1

val_helg: re
	@echo "running valgrind (helgrind). input used: './bin/philo 5 800 200 200 7'"
	@echo "find trace at ./val-helgrind.txt"
	@$(HELGRIND) ./$(NAME) 2>&1

val_drd: re
	@echo "running valgrind (drd). input used: './bin/philo 1 800 200 200'"
	@echo "find trace at ./val-drd.txt"
	@$(DRD) ./$(NAME) 2>&1

.PHONY: all clean fclean re bonus
