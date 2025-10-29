NAME=minishell

CFLAGS:= -Wall -Wextra -Werror
FLAGS_LEAK= -g -fsanitize=address
FLAG_FILES= -lreadline
CC= cc

SRC= ultra.c ./ft_cd.c ./utils.c ./ft_env.c ./signal.c ./ft_pwd.c ./ft_exit.c \
	 ./ft_split.c ./ft_putstr_fd.c ./until_pipe.c ./ft_strlen.c ./ft_strncpy.c \
	 ./ft_strchr.c ./ft_unset.c ./ft_strcmp.c ./ft_strcmp_char.c ./ft_echo.c ./ft_export.c \
	./redirection.c ./ft_strdup.c ./parsing.c ./ft_strjoin.c ./ft_atoi.c ./setup_and_utils_signal.c \
	./store_args_and_redirs.c ./utils_var_and_cmds.c ./ft_split_utils.c ./double_redirection_left.c \
	./end_to_redirections.c ./ft_cd_utils.c ./arg_copy.c ./redir_copy.c ./words_utils.c ./scan_helpers.c \
	./ft_export_utils1.c ./free.c ./loop_utils.c ./spawn_fork_and_reject.c ./pipes_exec.c \
	./fork_init.c ./exec_fd_utils.c ./exec_builtins.c ./wait_and_heredoc.c \
	./execs_builtins_utils.c ./path_exec.c ./ft_export_utils2.c ./ft_exit_utils.c \
	./safe_utils.c ./save_and_close_dup.c ./save_close_dup_helpers.c ./utils_var_cmds_helpers.c ./double_redir_left_helpers.c ./ft_cd_helpers.c ./process_and_run.c ./new_parsing_ultra.c

INCLUDES=./minishell.h\

OBJ=$(SRC:.c=.o)
#OBJ_LEAK=$(SRC:.c=.o)

GREEN=\033[32m
RED=\033[31m
YELLOW=\033[33m
RESET=\033[0m
CYAN=\033[36m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -I $(INCLUDES) -o $(NAME) $(FLAG_FILES)
	@echo "$(GREEN)- Minishell created ✓ ✓ ✓-$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

leak: CFLAGS += $(FLAGS_LEAK)
leak: $(NAME)
	@echo "$(GREEN)- Minishell created with leak detection ✓ ✓ ✓-$(RESET)"

print:
	@echo "$(YELLOW)✧ Compilling Minishell.. ✧$(RESET)"
	@echo ""

clean:
	@echo "$(RED)🗑️------clean done-------🗑️$(RESET)"
	@echo ""
	@rm -rf $(OBJ)

fclean: clean
	@echo "$(RED)🗑️------fclean done------🗑️$(RESET)"
	@echo ""
	@rm -rf $(NAME)

re: fclean all


.PHONY: all clean fclean re print leak
