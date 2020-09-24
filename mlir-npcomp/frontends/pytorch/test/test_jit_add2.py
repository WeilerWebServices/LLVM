# -*- Python -*-
# This file is licensed under a pytorch-style license
# See frontends/pytorch/LICENSE for license information.

import torch
import npcomp.frontends.pytorch as torch_mlir
import npcomp.frontends.pytorch.test as test

# RUN: python %s | FileCheck %s

dev = torch_mlir.mlir_device()
t0 = torch.randn((4,4), device=dev)
t1 = torch.randn((4,4), device=dev)

t2 = t0 + t1

#
# Check the result tensor against the CPU
#
t0_cpu = t0.to('cpu')
t1_cpu = t1.to('cpu')
t2_cpu = t2.to('cpu')

print (t0_cpu, " +\n", t1_cpu, " =\n", t2_cpu)

# CHECK: PASS! add2 check
test.compare(t2, t0_cpu + t1_cpu, "add2")
