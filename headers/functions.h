#ifndef FUNCTIONS_H
# define FUNCTIONS_H

// utils
void		ft_end(t_mini *ms, const char *msg, const int code);
int			check_quotes(char c, int quotes);
char		*ft_array_copy(char **array);
char		**ft_arraydup(char **array);

// free
char		*free_ptr(char *ptr);
char		**free_array(char **array);
t_token		*free_token(t_token *token);

// lexer
char		**ft_lexer(char *input);

// parser
int			ft_parser(t_token **head, char *str);

// path
char		*find_path(char	*cmd, char **env);

// parser_utils
void		check_pipe(char *cmd, t_token **head);

// syntax_checker
int			ft_syntchecker(t_mini *ms);

// expander
char		*ft_expand(t_mini *ms, char *cmd, char **env);
void		ft_expander(t_mini *ms, t_token **head, char **env);

// expander_utils
char		*get_envp(t_mini *ms, char *cmd, char **env);

// executer
void		ft_executor(t_mini *ms);

// executer_utils
char		**token_to_array(t_token *token);
void		close_fds(int **fd);

// child
void		child(t_mini *ms, char **cmd, int **fd, int i);

// redirect
char		**redirect(t_mini *ms, char **cmd, int *out, int *in);

// redirect_utils
void		set_redirect(t_mini *ms, char **cmd, int *fd, char **ret);

// print sorted env
void    print_sorted_env(char **env);

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
