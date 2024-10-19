#ifndef FUNCTIONS_H
# define FUNCTIONS_H

// initilizers
t_mini	ft_init_main(int argc, char **env);
t_token		*init_token(char *cmd);
t_expander	init_ex(t_mini *ms, char *cmd, char **env, t_expander ex);
t_executor	init_exec(t_mini *ms);

// utils
void		ft_end(t_mini *ms, const char *msg, const int code);
char		*ft_array_copy(char **array);
char		**ft_arraydup(char **array);
char		**token_to_array(t_token *token);
void		ft_sa_handler(int sig, siginfo_t *sa, void *info);

// quotes
int			quote_handler(char c, int quotes);
char		*quote_expander(char *cmd);

// cleaner
char		*free_ptr(char *ptr);
char		**free_array(char **array);
void		ft_cleaner(t_mini *ms);
void	    close_fds(int **fd);
t_token		*free_token(t_token *token);

// lexer
char		**ft_lexer(char *input);

// parser
int			ft_parser(t_token **head, char *str);

// path
char		*find_path(char	*cmd, char **env);

// parser_utils
void		check_pipe(char *cmd, t_token **head);
char		**split_args(char *input);
int			builtin(char *token);

// syntax_checker
int			ft_syntchecker(t_mini *ms);

// expander
char		*get_exitstatus(t_mini *ms, char *var, char *cmd);
char		*get_env(t_mini *ms, char *cmd, char **env);
char		*ft_expander(t_mini *ms, char *cmd, char **env);
void		ft_expand(t_mini *ms, t_token **top, char **env);
// exp utils
char		*ft_strjoinn(char *pre, char *affix);
char		*ft_itoaa(int n);
int			equalsign(char *str);

// executer
void		ft_executor(t_mini *ms);

// child
void		child(t_mini *ms, char **cmd, int **fd, int i);

// redirect
char		**redirect(t_mini *ms, char **cmd, int *out, int *in);

// redirect_utils
void		set_redirect(t_mini *ms, char **cmd, int *fd, char **ret);

// print sorted env
void		print_sorted_env(char **env);

// builtins
int			check_bltn(t_mini *ms, char **cmd, char ***env);
void		bltin_echo(t_mini *ms, char **cmd);
void		bltin_cd(t_mini *ms, char **cmd, char ***env);
void		bltin_pwd(t_mini *ms, char **cmd, char **env);
void		bltin_export(t_mini *ms, char **cmd, char ***env);
void		bltin_unset(t_mini *ms, char **cmd, char ***env);
void		bltin_env(t_mini *ms, char **cmd, char ***env);
void		bltin_exit(t_mini *ms, char **cmd);

#endif