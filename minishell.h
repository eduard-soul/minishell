/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:24:21 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/23 22:16:43 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <limits.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define UNSET 0
# define EXPORT 1

typedef struct s_cmds
{
	char			**argv;
	char			***envp;
	char			**redirections;
	int				fd[2];
	int				std_input;

	struct s_cmds	*next;
	struct s_cmds	*previous;
}t_cmds;

typedef struct s_minishell
{
	char	*str;
	char	*command;
	char	*args;

	int		last_ret;
	int		oldfd_in;
	int		oldfd_out;
	char	*output_cmd;

	char	**envp;
	char	**new_envp;
}t_minishell;

typedef enum e_sigmode
{
	SIGM_INTERACTIVE = 0,
	SIGM_PARENT_EXEC = 1
}t_sigmode;

typedef struct s_sigstate
{
	sig_atomic_t	flag;
	sig_atomic_t	mode;
}t_sigstate;

int		get_signal_flag(void);
void	reset_signal_flag(void);
void	signal_managment(int signum, siginfo_t *siginfo, void *sigclient);
void	setup_interactive_signals(void);
void	setup_child_signals(void);
void	setup_parent_exec_signals(void);
int		nb_x_until_pipe(char *str, int i, int is_arg);
char	*copy_if_arg(char *str, int *i, int *failed_malloc);
char	*copy_if_redirection(char *str, int *i);
t_cmds	*new_parsing_ultra(char **str, t_cmds *cmds, char ***envp,
			int last_ret);
int		ft_strlen(char *str);
char	*ft_atoi(int nb);
char	*ft_strdup(char *to_dup);
char	*ft_strncpy(char *s1, int start, int len);
char	*ft_strjoin(char *s1, char *s2);
int		is_env_name_good(char *str);
int		realloc_new_envp(int which, int position, t_minishell *minishell);
void	print_array_string(char **arr_string);
char	**copy_array_string(char **array);
int		ft_strcmp_char(char *s1, char *s2, char delimiter);
int		is_good_env_char(char c, int is_first);
int		is_env_name_good(char *str);
int		is_unexepected_token(char **str, char **envp);
int		is_unexepexcted_ecected_van_dyhk(char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strchr(char *s1, char c);
char	**ft_split_path(char *str, char delim);
void	restore(t_minishell *minishell);
void	ft_putstr_fd(char *str, int fd);
void	perror_and_exit(char *str, int ret);
void	check_and_close_fds(t_cmds *cmds);
int		end_to_redirections(char **redirections, int which);
int		double_redirect_left_ultra(char *delimiter);
int		ft_echo_ultra(char **argv, int fd);
int		ft_env(char **envp, int fd);
int		ft_unset(char **argv, char ***envp, int i);
void	ft_pwd(t_minishell *minishell);
int		ft_cd(t_minishell *minishell, char **argv);
int		ft_cd_ultra(char ***envp, char **argv);
int		ft_pwd_ultra(int fd);
int		ft_export(char **argv, char ***envp);
int		ft_exit(char **argv, int is_child);
void	free_array(char **arr);
void	set_var_second_part(char *entry, char *key, char *value);
int		set_var_third_part(char **envp, char *entry, char ***env_ref);
int		if_chdir_fail(char *oldpwd, char *path);
void	sig_handler(int signum, siginfo_t *siginfo, void *sigclient);
void	set_mode(sig_atomic_t mode);
void	set_flag(sig_atomic_t value);
void	*free_and_null(void *ptr);
char	*replace_with_ret(char **str, int *i, int last_ret);
char	*search_in_envp_and_replace(char **str, int *i, char **envp, int j);
int		search_and_replace_var(char **str, char **envp, int last_ret, int i);
t_cmds	*add_elem_to_cmds(t_cmds **cmds, int size_argv,
			int size_redir, char ***envp);
int		store_args(char *str, int i, char **argv);
int		store_redirections(char *str, int *i, char **redirections);
void	perror_and_exit(char *str, int ret);
int		ft_fill_word(char *dest, char *src, int i, char delim);
int		skip_prefix(char *str, int i);
int		count_words(char *str, char delim);
char	**free_split(char **result, int j);
char	*ft_malloc_len_word(char *str, int i, char delim);
void	heredoc_sigint(int signum);
int		open_redir(char *t, int which, int *fd);
int		find_key(char **envp, char *key);
int		arg_count(char **argv);
int		set_var(char ***env_ref, char *key, char *value);
int		is_name_delim(char c);
int		len_word(char *s, int p);
int		len_quoted(char *s, int p);
void	skip_quoted_block(char *s, int *i);
void	skip_to_word_end(char *s, int *i);
int		process_redir_if_any(char *s, int *i);
void	skip_ws(char *s, int *i);
int		handle_eof(char *line);
int		handle_sig_and_empty(char *line, int *last_ret);
char	*skip_ws_ptr(char *s);
int		reject_bad_start(char *str, int *last_ret, char *line);
int		process_and_run(char *str, char ***envp_copy, int last_ret);
int		is_built_in(char *str);
void	exec_absolute_path(t_cmds *cmds);
int		ft_search_char_in_str(char *str, char c);
void	search_path_and_exec(t_cmds *cmds);
int		add_fd_of_heredocs(t_cmds *cmds);
t_cmds	*first_executable_cmd(t_cmds *cmds);
int		count_executable_cmds(t_cmds *cmds);
int		exec_commands(t_cmds *cmds, int is_alone_builtin,
			int ret, int is_child);
int		prepare_pipes(t_cmds *cmds);
int		fork_and_exec_commands(t_cmds *cmds);
void	free_all_commands(t_cmds *cmds);
char	*ft_strjoin_w_char(char *s1, char c, char *s2);
int		is_there_a_path(char **envp);
void	put_err_n_viable(char *argv, char *error_msg, int exit_code);
int		is_directory(char *path);
void	fe_skip_node(t_cmds **c);
void	fe_close_prev(t_cmds *c);
int		fe_init(t_cmds *cmds, t_cmds **first, int *nb, int *pret);
int		setup_and_reset_signal(int ret);
int		wait_for_pids(int nb_cmds, int *pids, int i, int exit_code);
int		name_len_until_equal_or_plus(char *s);
int		find_key_index(char **envp, char *key);
char	*build_assignment(char *key, char *value);
char	**append_to_envp(char **envp, char *to_add);
int		exec_builtin(char **argv, int fd, char ***envp, int is_child);
int		free_and_ret(char *str, int ret);
int		handle_no_equal(char ***p_envp, char *name);
int		put_err_and_free_name(char *str, char *name);
int		has_equal_ret(int ret, char ***p_envp, char *name);
int		handle_plus_equal(char ***p_envp, char *name,
			char *value, char *existing);
int		replace_or_append(char ***p_envp, char *name, char *value, int idx);
void		rl_replace_line(const char *text, int clear_undo);

#endif
