/* read.c - Command to read variables from user.  */
/*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 2006,2007,2008  Free Software Foundation, Inc.
 *
 *  GRUB is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  GRUB is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GRUB.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <grub/dl.h>
#include <grub/misc.h>
#include <grub/mm.h>
#include <grub/env.h>
#include <grub/term.h>
#include <grub/types.h>
#include <grub/extcmd.h>
#include <grub/i18n.h>
#include <grub/safemath.h>

GRUB_MOD_LICENSE ("GPLv3+");

static const struct grub_arg_option options[] =
  {
    {"silent", 's', 0, N_("Do not echo input"), 0, 0},
    {0, 0, 0, 0, 0, 0}
  };

static char *
grub_getline (int silent)
{
  grub_size_t i;
  char *line;
  char *tmp;
  int c;
  grub_size_t alloc_size;

  i = 0;
  line = grub_malloc (1 + sizeof('\0'));
  if (! line)
    return NULL;

  while (1)
    {
      c = grub_getkey ();
      if ((c == '\n') || (c == '\r'))
	break;

      if (!grub_isprint (c))
	continue;

      line[i] = (char) c;
      if (!silent)
	grub_printf ("%c", c);
      if (grub_add (i, 1, &i))
        {
          grub_error (GRUB_ERR_OUT_OF_RANGE, N_("overflow is detected"));
          return NULL;
        }
      if (grub_add (i, 1 + sizeof('\0'), &alloc_size))
        {
          grub_error (GRUB_ERR_OUT_OF_RANGE, N_("overflow is detected"));
          return NULL;
        }
      tmp = grub_realloc (line, alloc_size);
      if (! tmp)
	{
	  grub_free (line);
	  return NULL;
	}
      line = tmp;
    }
  line[i] = '\0';

  return line;
}

static grub_err_t
grub_cmd_read (grub_extcmd_context_t ctxt, int argc, char **args)
{
  struct grub_arg_list *state = ctxt->state;
  char *line = grub_getline (state[0].set);

  if (! line)
    return grub_errno;
  if (argc > 0)
    grub_env_set (args[0], line);

  grub_free (line);
  return 0;
}

static grub_extcmd_t cmd;

GRUB_MOD_INIT(read)
{
  cmd = grub_register_extcmd ("read", grub_cmd_read, 0,
			       N_("[-s] [ENVVAR]"),
			       N_("Set variable with user input."), options);
}

GRUB_MOD_FINI(read)
{
  grub_unregister_extcmd (cmd);
}
