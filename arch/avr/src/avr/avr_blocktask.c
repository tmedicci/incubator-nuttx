/****************************************************************************
 * arch/avr/src/avr/avr_blocktask.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdbool.h>
#include <sched.h>
#include <assert.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/sched.h>

#include "sched/sched.h"
#include "avr_internal.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_block_task
 *
 * Description:
 *   The currently executing task has already removed from ready-to-run list.
 *   Save its context and switch to the next running task at the head of the
 *   ready-to-run list.
 *
 * Input Parameters:
 *   rtcb: Reference to the running task which is different to the
 *     task (next running task) at the head of the list.
 *
 ****************************************************************************/

void up_block_task(struct tcb_s *rtcb)
{
  /* Update scheduler parameters */

  nxsched_suspend_scheduler(rtcb);

  /* Are we in an interrupt handler? */

  if (g_current_regs)
    {
      /* Yes, then we have to do things differently.
       * Just copy the g_current_regs into the OLD rtcb.
       */

      avr_savestate(rtcb->xcp.regs);

      /* Restore the exception context of the rtcb at the (new) head
       * of the ready-to-run task list.
       */

      rtcb = this_task();

      /* Reset scheduler parameters */

      nxsched_resume_scheduler(rtcb);

      /* Then switch contexts */

      avr_restorestate(rtcb->xcp.regs);
    }

  /* No, then we will need to perform the user context switch */

  else
    {
      struct tcb_s *nexttcb = this_task();

      /* Reset scheduler parameters */

      nxsched_resume_scheduler(nexttcb);

      /* Switch context to the context of the task at the head of the
       * ready to run list.
       */

      avr_switchcontext(rtcb->xcp.regs, nexttcb->xcp.regs);

      /* avr_switchcontext forces a context switch to the task at the
       * head of the ready-to-run list.  It does not 'return' in the
       * normal sense.  When it does return, it is because the blocked
       * task is again ready to run and has execution priority.
       */
    }
}
