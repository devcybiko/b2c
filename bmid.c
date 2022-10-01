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
#include "node.h"
#include "bmid.h"

void bmid_b2c();

Bmid *bmid_new() {
  Bmid *this = CALLOC(1, Bmid);
  DBG0(">bmid_new\n");

  bmid_init(this);

  DBG0("<bmid_new\n");
  return this;
}

void bmid_init(this)
     Bmid *this;
{
  DBG0(">bmid_init\n");
  bexpr_init(this);

  this->type = TYPE_MID;
  this->b2c = bmid_b2c;

  DBG0("<bmid_init\n");
}

void bmid_b2c(this)
     Bmid *this;
{
  Node *dest;
  Node *src;
  Node *start;
  Node *len;

  DBG0(">bmid_b2c\n");

  fprintf(outfile, "_mid(");
  dest = this->child;
  src = dest->next;
  start = src->next;
  len = start->next;


  dest->b2c(dest);
  fprintf(outfile, ",");
  src->b2c(src);
  fprintf(outfile, ",");
  start->b2c(start);
  fprintf(outfile, ",");
  if (len) len->b2c(len);
  else fprintf(outfile, "-1");
  fprintf(outfile, ")");
  DBG0("<bmid_b2c\n");
}
