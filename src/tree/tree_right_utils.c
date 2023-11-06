/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_right_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 01:14:20 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/06 12:41:35 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// t_tree	*build_right_tree(t_data *data, t_token *address)
// {
//     t_tree	*tree = NULL;
//     t_tree	*root = NULL;
//     t_token	*head = data->token_list;
//     int	delim = 0;

//     data->token_list = address;
//     while (address)
//     {
//         if (is_special_type(address))
//         {
//             if (tree == NULL)
//             {
//                 tree = build_right_branch(&data->token_list, address, tree);
//                 root = tree;
//             }
//             else
//             {
//                 tree->right = build_right_branch(&data->token_list, address, tree);
//                 tree = tree->right;
//             }
//             address = data->token_list;
//             delim++;
//         }
//         else
//             address = address->next;
//     }
//     if (delim == 0)
//     {
//         address = data->token_list;
//         tree = build_tree_leaf_right(&data->token_list, tree);
//         root = tree;
//     }
//     else
//     {
//         tree->right = build_tree_leaf_right(&data->token_list, tree);
//         tree = tree->right;
//     }
//     data->token_list = head;
//     return (root);
// }

// t_tree	*build_right_branch(t_token **token, t_token *address, t_tree *tree)
// {
//     int arg_nums;
//     int i;

//     tree = (t_tree *)malloc(sizeof(t_tree));
//     if (!tree)
//         return (NULL);
//     tree->type = address->type;
//     tree->value = address->word;
//     tree->args_array = NULL;
//     i = 0;
//     arg_nums =	arg_count_right(*token, address);
//     tree->left = (t_tree *)malloc(sizeof(t_tree));
//     if (!tree->left)
//     {
//         free(tree);
//         return (NULL);
//     }
//     tree->left->args_array = (char **)malloc(sizeof(char *) * (arg_nums + 1));
//     if (!tree->left->args_array)
//     {
//         free(tree->left);
//         free(tree);
//         return (NULL);
//     }
//     while (*token != address)
//     {
//         tree->left->args_array[i] = ft_strdup((*token)->word);
//         *token = (*token)->next;
//         i++;
//     }
//     tree->left->args_array[i] = NULL;
//     *token = (*token)->next;
//     tree->right = NULL;
//     return (tree);
// }

// t_tree	*build_tree_leaf_right(t_token **token, t_tree *tree)
// {
//     int arg_nums;
//     int i;

//     tree = (t_tree *)malloc(sizeof(t_tree));
//     if (!tree)
//         return (NULL);
//     tree->type = (*token)->type;
//     tree->value = (*token)->word;
//     i = 0;
//     arg_nums =	arg_count_right(*token, NULL);
//     if (arg_nums != 0)
//     {
//         tree->args_array = (char **)malloc(sizeof(char *) * (arg_nums + 1));
//         if (!tree->args_array)
//         {
//             free(tree);
//             return (NULL);
//         }
//     }
//     while (*token != NULL)
//     {
//         tree->args_array[i] = ft_strdup((*token)->word);
//         *token = (*token)->next;
//         i++;
//     }
//     tree->args_array[i] = NULL;
//     tree->left = NULL;
//     tree->right = NULL;
//     return (tree);
// }

// int		arg_count_right(t_token *token, t_token *address)
// {
// 	int count;

// 	count = 0;
// 	while (token != address)
// 	{
// 		count++;
// 		token = token->next;
// 	}
// 	return (count);
// }