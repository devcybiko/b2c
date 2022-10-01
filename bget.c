/**
  * The B2C project is a set of programs and libraries
  * that comprise a languate translator.  B2C compiles
  * a BASIC program into C which is compiled by the Cybiko
  * SDK 2.10 into an application.
  *
  *  Copyright 2004 by Gregory Smith
  *  (greg@alcorgrp.com)
  *
  *  This program is free software; you can redistribute it and/or
  *  modify it under the terms of the GNU General Public License
  *  as published by the Free Software Foundation; either version 2
  *  of the License, or (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with this program; if not, write to the Free Software
  *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
  *
  * @author Gregory Smith (http://www.greg-smith.com, Greg@AlcorGrp.com)
  * @version 1.0
  */
#include "b2c.h"
#include "bget.h"
#include "bterm.h"

void bget_b2c();

Bget *bget_new() {
  Bget *this = CALLOC(1, Bget);
  DBG0(">bget_new\n");

  bget_init(this);

  DBG0("<bget_new\n");
  return this;
}

void bget_init(this)
     Bget *this;
{
  DBG0(">bget_init\n");
  node_init(this);

  this->type = TYPE_GET;
  this->b2c = bget_b2c;

  DBG0("<bget_init\n");
}

void bget_b2c(this)
     Bget *this;
{
  Node *n;
  Bterm *bterm;

  DBG0(">bget_b2c\n");
  fprintf(outfile, "_get(");
  n = this->child;
  n->b2c(this->child); /** filenumber **/

  fprintf(outfile, ",");

  n=n->next;
  if (n->type == TYPE_EXPR && n->child == NULL)
    fprintf(outfile, "-1");
  else
    n->b2c(n); /** file position */

  fprintf(outfile, ",");

  n=n->next;
  if (n->type == TYPE_EXPR && n->child == NULL)
  {
	fprintf(outfile, "(void *)-1,-1");
  }
  else
  {    
      fprintf(outfile, "&");
      n->b2c(n); /** variable to print **/

      fprintf(outfile, ",");
      
      bterm = (Bterm *) n;
      
      if (bterm->dim->child && bterm->child == NULL)
	  {
		bterm->dim->child->b2c(bterm->dim->child);
		fprintf(outfile, "*");
	  }
      
	  switch(bterm->datatype) 
	  {
		case DATATYPE_CHAR : fprintf(outfile, "sizeof(char)"); break;
		case DATATYPE_INT : fprintf(outfile, "sizeof(short)"); break;
		case DATATYPE_LONG : fprintf(outfile, "sizeof(long)"); break;
		case DATATYPE_DOUBLE : fprintf(outfile, "sizeof(fixed)"); break;
		default: doerr2("%s(%d) ERROR - Cannot get '%s' - invalid data type\n", g_infname, 0, bterm->name); break;
	  }
  }

  fprintf(outfile, ")");
  DBG0("<bget_b2c\n");
}
