/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: sysclk.c
 * Description		: This file contains sources for sysclk sources
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <syslog.h>
#include <assert.h>
#include <lock/lock.h>
#include <driver/sysclk.h>

static sysclk_config_clk_callback_t *root;
static lock_t sysclk_cb_key;

status_t sysclk_register_config_clk_callback(sysclk_config_clk_callback_t *node)
{
	status_t ret;
	sysclk_config_clk_callback_t *temp;

	lock_acquire(&sysclk_cb_key);

	if(!(node->pre_config && node->post_config))
		ret = error_func_inval_arg;
	else
	{
		ret = success;
		if(root == NULL)
		{
			sysdbg3("sysclk: Adding root node %p\n", node);
			root = node;
		}
		else
		{
			temp = root;
			while(temp->next)
			{
				temp = temp->next;
				if(temp == node)
				{
					sysdbg3("sysclk: Found duplicate node %p, failed to register!\n", temp);
					ret = error_list_node_exists;
					goto exit;
				}
			}
			sysdbg3("sysclk: Adding node to list %p\n", node);
			temp->next = node;
		}
	}

exit:
	lock_release(&sysclk_cb_key);
	return ret;
}

status_t sysclk_deregister_config_clk_callback(sysclk_config_clk_callback_t *node)
{
	status_t ret;
	sysclk_config_clk_callback_t *temp, *prev;

	lock_acquire(&sysclk_cb_key);

	if(root == NULL)
		ret = error_func_inval_arg;
	else
	{
		ret = success;
		temp = root;
		if(root == node)
		{
			sysdbg3("sysclk: Removing root node %p\n", node);
			root = temp->next;
			goto exit;
		}

		while(temp != node)
		{
			prev = temp;
			temp = temp->next;
			if(!temp)
			{
				sysdbg3("sysclk: Node %p not found!. Failed to deregister!", node);
				ret = error_list_node_not_found;
				goto exit;
			}
		}
		sysdbg3("sysclk: Removing node from list %p\n", node);
		prev->next = temp->next;
	}
exit:
	lock_release(&sysclk_cb_key);
	return ret;
}

status_t sysclk_execute_pre_config_clk_callback(void)
{
	status_t ret = success;
	sysclk_config_clk_callback_t *temp;
	temp = root;

	lock_acquire(&sysclk_cb_key);

	do
	{
		if(temp->pre_config)
			ret |= temp->pre_config();
		else
		{
			syslog(fail, "Preconfig CB for node %p is not available!\n", temp);
			ret |= error_func_inval;
		}
		temp = temp->next;
	} while(temp);

	lock_release(&sysclk_cb_key);
	return ret;
}

status_t sysclk_execute_post_config_clk_callback(void)
{
	status_t ret = success;
	sysclk_config_clk_callback_t *temp;
	temp = root;

	lock_acquire(&sysclk_cb_key);

	do
	{
		ret |= temp->post_config();
		if(temp->post_config)
			ret |= temp->post_config();
		else
		{
			syslog(fail, "Postconfig CB for node %p is not available!\n", temp);
			ret |= error_func_inval;
		}
		temp = temp->next;
	} while(temp);

	lock_release(&sysclk_cb_key);
	return ret;
}
