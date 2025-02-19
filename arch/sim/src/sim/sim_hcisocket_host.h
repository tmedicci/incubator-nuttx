/****************************************************************************
 * arch/sim/src/sim/sim_hcisocket_host.h
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

#ifndef __ARCH_SIM_SRC_SIM_HCISOCKET_HOST_H
#define __ARCH_SIM_SRC_SIM_HCISOCKET_HOST_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <errno.h>
#include <stdint.h>

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

int sim_bthcisock_hostopen(int dev_idx);
int sim_bthcisock_hostsend(int fd, const void *data, size_t len);
int sim_bthcisock_hostread(int fd, void *data, size_t len);
int sim_bthcisock_hostavail(int fd);
int sim_bthcisock_hostclose(int fd);

#endif /* __ARCH_SIM_SRC_SIM_HCISOCKET_HOST_H */
